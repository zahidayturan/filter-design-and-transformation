#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    csvButton = new QPushButton("CSV Dosyası Oluştur", this);
    graphButton = new QPushButton("Grafiği Göster", this);

    layout = new QVBoxLayout;
    layout->addWidget(csvButton);
    layout->addWidget(graphButton);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(csvButton, &QPushButton::clicked, this, &MainWindow::generateCSV);
    connect(graphButton, &QPushButton::clicked, this, &MainWindow::showGraph);
}

void MainWindow::generateCSV() {
    double omegaMax = 10.0;
    int points = 1000;

    std::ofstream file("butterworth_response.csv");
    if (!file.is_open()) {
        QMessageBox::critical(this, "Hata", "CSV dosyası oluşturulamadı!");
        return;
    }

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;
        file << omega << "," << 1.0 / (1.0 + omega * omega) << "\n";
    }

    file.close();
    QMessageBox::information(this, "Başarılı", "CSV dosyası oluşturuldu!");
}


void MainWindow::showGraph() {
    auto *process = new QProcess(this);
    QDir::setCurrent(QDir::currentPath());
    QDir currentDir(QDir::currentPath());
    currentDir.cdUp();

    QString scriptPath = currentDir.filePath("main.py");
    QString program = currentDir.filePath("venv/Scripts/python.exe") ;
    QStringList arguments;
    arguments << scriptPath;
    qDebug() << "Current venv directory: " << program;
    qDebug() << "Current working directory: " << scriptPath;
    process->start(program, arguments);

    connect(process, &QProcess::started, this, []() {
        qDebug() << "Python script started successfully!";
    });

    connect(process, &QProcess::errorOccurred, this, [](QProcess::ProcessError error) {
        qDebug() << "Error occurred while running the Python script!";
        switch (error) {
            case QProcess::FailedToStart:
                QMessageBox::critical(nullptr, "Error", "Python executable not found or failed to start.");
                break;
            case QProcess::Crashed:
                QMessageBox::critical(nullptr, "Error", "Python script crashed.");
                break;
            case QProcess::WriteError:
                QMessageBox::critical(nullptr, "Error", "An error occurred while writing to the process.");
                break;
            case QProcess::ReadError:
                QMessageBox::critical(nullptr, "Error", "An error occurred while reading from the process.");
                break;
            default:
                QMessageBox::critical(nullptr, "Error", "Unknown error occurred.");
                break;
        }
    });

    connect(process, &QProcess::finished, this, [](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            qDebug() << "Python script executed successfully!";
        } else {
            qDebug() << "Python script finished with errors!";
        }
    });

    connect(process, &QProcess::readyReadStandardOutput, [process]() {
        QByteArray output = process->readAllStandardOutput();
        qDebug() << "Python output:" << output;
    });

    connect(process, &QProcess::readyReadStandardError, [process]() {
        QByteArray errorOutput = process->readAllStandardError();
        qDebug() << "Python error output:" << errorOutput;
    });
}





