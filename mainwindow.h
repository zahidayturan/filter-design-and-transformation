#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void generateButterworthCSV();
    void generateChebyshevCSV();
    void generateInverseChebyshevCSV();
    void showGraphWithPath(const QString &filename);

private:
    Ui::MainWindow *ui;
    void populateComboBox();
    void onComboBoxSelectionChanged(int index);
    void clearAllFiles();
    void checkAllCSV();

    void updateValues();

    void resetToDefaultValues();
};
#endif

