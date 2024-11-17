#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void generateCSV();
    void showGraph();

private:
    QPushButton *csvButton;
    QPushButton *graphButton;
    QVBoxLayout *layout;
};

#endif

