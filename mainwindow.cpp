#include "mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include "ui_MainWindow.h"
#include <cmath>
#include <complex>
#include <vector>
#include <stdexcept>
#include <QString>

using namespace std;

void generateButterworth(const QString& filename, int n, double omegaMax, int points);

void generateChebyshev(const QString& filename, double e_ripple, int n, int points);

void generateInverseChebyshev(const QString& filename, double e_ripple, int n, int points);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->csvButton, &QPushButton::clicked, this, &MainWindow::generateCSV);
    connect(ui->butterworthButton, &QPushButton::clicked, this, &MainWindow::generateButterworthCSV);
    connect(ui->graphButton, &QPushButton::clicked, this, &MainWindow::showGraph);
    populateComboBox();
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onComboBoxSelectionChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generateCSV()
{
    const double omegaMax = 1000.0; // Maksimum omega değeri
    const int points = 200; // Verilecek frekans noktası sayısı
    const int n = 6;  // Filter order for 6th degree

    generateButterworth( "bnf_response.csv", n, 3, 200);

    generateChebyshev("cnf_response.csv",0.12,6,200);

    generateInverseChebyshev("icnf_response.csv",0.19,6,200);

    std::ofstream lpfFile("lpf_response.csv");
    if (!lpfFile.is_open())
    {
        QMessageBox::critical(this, "Hata", "LPF CSV dosyası oluşturulamadı!");
        return;
    }

    std::ofstream hpfFile("hpf_response.csv");
    if (!hpfFile.is_open())
    {
        QMessageBox::critical(this, "Hata", "HPF CSV dosyası oluşturulamadı!");
        return;
    }

    std::ofstream bpfFile("bpf_response.csv");
    if (!bpfFile.is_open())
    {
        QMessageBox::critical(this, "Hata", "BPF CSV dosyası oluşturulamadı!");
        return;
    }

    const double lpf_wp = 340.0;  // LPF köşe frekansı (rad/s)
    const double hpf_wp = 130.0;  // HPF köşe frekansı (rad/s)
    const double bpf_wc = 310.0;  // BPF merkez frekansı (rad/s)
    const double bpf_bw = 95.0;   // BPF band genişliği (rad/s)


    // Helper function for calculating Butterworth filter poles
    auto calculatePoles = [](int n) {
        vector<complex<double>> poles(n);
        for (int k = 0; k < n; ++k) {
            double theta = (2 * k + 1) * M_PI / (2 * n);
            double realPart = -sin(theta);
            double imagPart = cos(theta);
            poles[k] = complex<double>(realPart, imagPart);
        }
        return poles;
    };

    // Helper function to compute the frequency response
    auto computeFrequencyResponse = [](int n, const vector<complex<double>>& poles, double wp, double omega, const string& type, double wc = 0.0, double bw = 0.0) {
        complex<double> jw(0.0, omega);
        complex<double> s;

        // Frequency transformation
        if (type == "LPF") {
            s = jw / wp;
        } else if (type == "HPF") {
            s = wp / jw;
        } else if (type == "BPF") {
            s = (pow(jw, 2) + pow(wc, 2)) / (bw * jw);
        } else {
            throw invalid_argument("Invalid filter type");
        }

        complex<double> numerator = 1.0;
        complex<double> denominator = 1.0;
        for (int k = 0; k < n; ++k) {
            denominator *= (s - poles[k]);
        }
        return abs(numerator / denominator);
    };

    // Calculate poles for Butterworth filter
    vector<complex<double>> poles = calculatePoles(n);

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;
        double lpfResponse = computeFrequencyResponse(n, poles, lpf_wp, omega, "LPF");
        lpfFile << omega << "," << lpfResponse << "\n";
    }

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;
        double hpfResponse = computeFrequencyResponse(n, poles, hpf_wp, omega, "HPF");
        hpfFile << omega << "," << hpfResponse << "\n";
    }

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;
        double bpfResponse = computeFrequencyResponse(n, poles, bpf_wc, omega, "BPF", bpf_wc, bpf_bw);
        bpfFile << omega << "," << bpfResponse << "\n";
    }

    // Close the CSV files
    lpfFile.close();
    hpfFile.close();
    bpfFile.close();

    // Notify success
    QMessageBox::information(this, "Başarılı", "CSV dosyaları oluşturuldu!");
}

void MainWindow::showGraph() {

    QString filename = QFileDialog::getOpenFileName(this, "CSV Dosyasını Seç", "", "CSV Dosyaları (*.csv)");

    if (!filename.isEmpty())
    {
        auto *process = new QProcess(this);
        QDir::setCurrent(QDir::currentPath());
        QDir currentDir(QDir::currentPath());
        currentDir.cdUp();

        QString scriptPath = currentDir.filePath("main.py");
        QString program = currentDir.filePath("venv/Scripts/python.exe");
        QStringList arguments;

        arguments << scriptPath << filename;

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
}

void generateButterworth(const QString& filename, int n, double omegaMax, int points) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "CSV dosyası oluşturulamadı!");
        return;
    }

    for (int l = 0; l < points; ++l) {
        double omega = (omegaMax / points) * l;
        double Hw = 1.0 / std::sqrt(1.0 + std::pow(omega / 1.0, 2 * n));
        //normalize edildiği için / 1.0
        csvFile << omega << "," << Hw << "\n";
    }

    csvFile.close();
    QMessageBox::information(nullptr, "Başarılı", "CSV dosyası başarıyla oluşturuldu!");
}

void denormalizeLPF(const std::string& inputFilename, const std::string& outputFilename, double omegaP) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Giriş veya çıkış dosyası açılamadı!");
    }

    // İlk geçiş: normalize edilmiş frekansların maksimumunu bul
    double maxOmegaN = 0.0;
    double omegaN, Hw;
    while (inputFile >> omegaN) {
        char comma;
        inputFile >> comma >> Hw;
        if (omegaN > maxOmegaN) {
            maxOmegaN = omegaN;
        }
    }

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Ölçekleme faktörünü hesapla
    double scalingFactor = 3.0 / (maxOmegaN * omegaP);

    // Denormalize edilmiş frekansları yaz
    while (inputFile >> omegaN) {
        char comma;
        inputFile >> comma >> Hw;
        double omega = omegaN * omegaP * scalingFactor; // Ölçekleme uygulanmış frekans
        outputFile << omega << "," << Hw << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void denormalizeHPF(const std::string& inputFilename, const std::string& outputFilename, double omegaP) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Giriş veya çıkış dosyası açılamadı!");
    }

    double omegaN, Hw;
    while (inputFile >> omegaN) {
        char comma;
        inputFile >> comma >> Hw;
        double omega = omegaP / omegaN;  // Denormalize frekans
        outputFile << omega << "," << Hw << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void denormalizeBPF(const std::string& inputFilename, const std::string& outputFilename, double omegaC, double BW) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Giriş veya çıkış dosyası açılamadı!");
    }

    double omegaN, Hw;
    while (inputFile >> omegaN) {
        char comma;
        inputFile >> comma >> Hw;
        double result = ((omegaN * omegaN) + (omegaC * omegaC)) / (BW * omegaN);  // Denormalize frekans
        outputFile << result << "," << Hw << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void generateChebyshev(const QString& filename, double e_ripple, int n, int points) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "CSV dosyası oluşturulamadı!");
        return;
    }

    std::vector<std::complex<double>> poles(n);
    double sinhFactor = std::asinh(1.0 / e_ripple) / n;

    for (int k = 0; k < n; ++k) {
        double angle = (2.0 * k + 1) * M_PI / (2.0 * n);
        double D_Re = -std::sin(angle) * std::sinh(sinhFactor);
        double D_Im = std::cos(angle) * std::cosh(sinhFactor);
        poles[k] = std::complex<double>(D_Re, D_Im);
    }

    // İkinci dereceden polinomların katsayılarının hesaplanması
    std::vector<std::vector<double>> Hch;
    for (int k = 0; k < (n + 1) / 2; ++k) {
        if (k == n - k - 1) {
            // Reel kök varsa, ayrı ele alınır
            Hch.push_back({0, 1, -poles[k].real()});
        } else {
            // Eşlenik kökler için polinom çarpımı
            std::complex<double> p1 = poles[k];
            std::complex<double> p2 = poles[n - k - 1];
            Hch.push_back({1, -(p1.real() + p2.real()), (p1 * p2).real()});
        }
    }

    // Frekans ve genlik hesaplaması
    for (int l = 1; l <= points; ++l) {
        double w = 2.0 * l / points;
        double Nw = 1.0;
        double Dw = 1.0;

        for (const auto& poly : Hch) {
            // H(s) -> H(jw) dönüşümü ve genlik hesaplaması
            std::complex<double> jw(0, w);
            std::complex<double> denominator = poly[0] * std::pow(jw, 2) + poly[1] * jw + poly[2];
            Nw *= std::abs(poly[2]); // Sadece sabit pay
            Dw *= std::abs(denominator);
        }

        double Hw = Nw / Dw;
        csvFile << w << "," << Hw << "\n";
    }

    csvFile.close();
    QMessageBox::information(nullptr, "Başarılı", "CSV dosyası başarıyla oluşturuldu!");
}

void generateInverseChebyshev(const QString& filename, double e_ripple, int n, int points) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "CSV dosyası oluşturulamadı!");
        return;
    }

    // Köklerin hesaplanması (kutuplar ve sıfırlar)
    std::vector<std::complex<double>> poles(n);
    std::vector<std::complex<double>> zeros(n);
    double sinhFactor = std::asinh(1.0 / e_ripple) / n;

    for (int k = 0; k < n; ++k) {
        double angle = (2.0 * k + 1) * M_PI / (2.0 * n);
        double D_Re = -std::sin(angle) * std::sinh(sinhFactor);
        double D_Im = std::cos(angle) * std::cosh(sinhFactor);

        poles[k] = 1.0 / std::complex<double>(D_Re, D_Im); // Kutuplar
        zeros[k] = 1.0 / (-std::complex<double>(0, std::cos(angle))); // Sıfırlar
    }

    // Pay ve payda polinomlarının katsayılarının hesaplanması
    std::vector<std::vector<double>> HcN; // Pay katsayıları
    std::vector<std::vector<double>> HcD; // Payda katsayıları

    for (int k = 0; k < (n + 1) / 2; ++k) {
        if (k == n - k - 1) {
            // Reel kök varsa
            HcN.push_back({0, 0, 1});
            HcD.push_back({0, 1, -poles[k].real()});
        } else {
            // Eşlenik kökler için polinom çarpımı
            std::complex<double> z1 = zeros[k];
            std::complex<double> z2 = zeros[n - k - 1];
            std::complex<double> p1 = poles[k];
            std::complex<double> p2 = poles[n - k - 1];

            HcN.push_back({1, -(z1.real() + z2.real()), (z1 * z2).real()});
            HcD.push_back({1, -(p1.real() + p2.real()), (p1 * p2).real()});
        }
    }

    // Kazanç hesabı ve normalize etme
    double gain = 1.0;
    for (const auto& d : HcD) {
        gain *= d[2]; // Payda sabiti
    }
    for (const auto& n : HcN) {
        gain /= n[2]; // Pay sabiti
    }
    gain = std::pow(gain, 1.0 / ((n + 1) / 2));
    for (auto& n : HcN) {
        n[2] *= gain;
    }

    // Frekans ve genlik hesaplaması
    for (int l = 1; l <= points; ++l) {
        double w = 4.0 * l / points;
        std::complex<double> Nw(1, 0);
        std::complex<double> Dw(1, 0);

        for (size_t k = 0; k < HcN.size(); ++k) {
            std::complex<double> jw(0, w);

            // HcN(jw) ve HcD(jw) çarpanlarını hesapla
            std::complex<double> num = HcN[k][0] * std::pow(jw, 2) + HcN[k][1] * jw + HcN[k][2];
            std::complex<double> den = HcD[k][0] * std::pow(jw, 2) + HcD[k][1] * jw + HcD[k][2];

            Nw *= num;
            Dw *= den;
        }

        double Hw = std::abs(Nw / Dw);
        csvFile << w << "," << Hw << "\n";
    }

    csvFile.close();
    QMessageBox::information(nullptr, "Başarılı", "CSV dosyası başarıyla oluşturuldu!");
}

void MainWindow::generateButterworthCSV() {
    const QString filename = "butterworth_response.csv";
    const int filterOrder = 6;
    const double omegaMax = 3.0;
    const int points = 200;

    generateButterworth(filename, filterOrder, omegaMax, points);
    std::cout << "Normalize butterworth butterworth_response.csv dosyasına yazıldı." << std::endl;

    try {
        const std::string inputFilename = "butterworth_response.csv";

        double omegaLPF = 340.0;   // LPF köşe frekansı
        double omegaHPF = 130.0;   // HPF köşe frekansı
        double omegaBPF = 310.0;   // BPF merkez frekansı
        double BW = 95.0;          // BPF bant genişliği

        denormalizeLPF(inputFilename, "lpf_response.csv", omegaLPF);
        std::cout << "LPF frekans cevabı lpf_response.csv dosyasına yazıldı." << std::endl;

        denormalizeHPF(inputFilename, "hpf_response.csv", omegaHPF);
        std::cout << "HPF frekans cevabı hpf_response.csv dosyasına yazıldı." << std::endl;

        denormalizeBPF(inputFilename, "bpf_response.csv", omegaBPF, BW);
        std::cout << "BPF frekans cevabı bpf_response.csv dosyasına yazıldı." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }
}

void MainWindow::populateComboBox() {
    QDir dir(QDir::currentPath());
    QStringList filters;
    filters << "*.csv";
    QStringList fileList = dir.entryList(filters, QDir::Files);

    ui->comboBox->clear();
    for (const QString &file : fileList) {
        ui->comboBox->addItem(file);
    }
}

void MainWindow::onComboBoxSelectionChanged(int index) {
    if (index >= 0) {
        QString selectedFile = ui->comboBox->itemText(index);
        showGraphWithPath(selectedFile);
    }
}

void MainWindow::showGraphWithPath(const QString &filename) {
    if (!filename.isEmpty()) {
        auto *process = new QProcess(this);

        QDir currentDir(QDir::currentPath());
        currentDir.cdUp();
        QString scriptPath = currentDir.filePath("main.py");
        QString program = currentDir.filePath("venv/Scripts/python.exe");
        QStringList arguments;
        arguments << scriptPath << filename;

        process->start(program, arguments);

        connect(process, &QProcess::readyReadStandardOutput, [process]() {
            qDebug() << "Python output:" << process->readAllStandardOutput();
        });

        connect(process, &QProcess::readyReadStandardError, [process]() {
            qDebug() << "Python error output:" << process->readAllStandardError();
        });
    }
}

