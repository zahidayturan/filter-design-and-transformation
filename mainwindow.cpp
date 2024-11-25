#include "mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <fstream>
#include <iostream>
#include "ui_MainWindow.h"
#include <cmath>
#include <complex>
#include <vector>
#include <stdexcept>
#include <QString>

using namespace std;
const double omegaMax = 1000.0;
const double omegaMin = 3.0;
const int points = 200;
const int n = 6;
const double e_ripple = 0.12;
const double ice_ripple = 0.19;
const double lpf_wp = 340.0;
const double hpf_wp = 130.0;
const double bpf_wc = 310.0;
const double bpf_bw = 95.0;

void generateButterworth(const QString& filename);
void generateChebyshev(const QString& filename);
void generateInverseChebyshev(const QString& filename);


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->b_create, &QPushButton::clicked, this, &MainWindow::generateButterworthCSV);
    connect(ui->c_create, &QPushButton::clicked, this, &MainWindow::generateChebyshevCSV);
    connect(ui->i_create, &QPushButton::clicked, this, &MainWindow::generateInverseChebyshevCSV);
    connect(ui->reload, &QPushButton::clicked, this, &MainWindow::clearAllFiles);
    populateComboBox();
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onComboBoxSelectionChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void generateButterworth(const QString& filename) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "Butterworth normalize dosyası oluşturulamadı!");
        return;
    }

    for (int l = 0; l < points; ++l) {
        double omega = (omegaMin / points) * l;
        double Hw = 1.0 / std::sqrt(1.0 + std::pow(omega / 1.0, 2 * n));
        //normalize edildiği için / 1.0
        csvFile << omega << "," << Hw << "\n";
    }

    csvFile.close();
}

void generateChebyshev(const QString& filename) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "Chebyshev normalize dosyası oluşturulamadı!");
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
}

void generateInverseChebyshev(const QString& filename) {
    std::ofstream csvFile(filename.toStdString());
    if (!csvFile.is_open()) {
        QMessageBox::critical(nullptr, "Hata", "Inverse Chebyshev normalize dosyası oluşturulamadı!");
        return;
    }

    // Köklerin hesaplanması (kutuplar ve sıfırlar)
    std::vector<std::complex<double>> poles(n);
    std::vector<std::complex<double>> zeros(n);
    double sinhFactor = std::asinh(1.0 / ice_ripple) / n;

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
}

void MainWindow::generateButterworthCSV()
{
    generateButterworth( "butterworth_normalize.csv");

    std::ofstream lpfFile("butterworth_low.csv");
    std::ofstream hpfFile("butterworth_high.csv");
    std::ofstream bpfFile("butterworth_band.csv");

    if (!lpfFile.is_open() || !hpfFile.is_open() || !bpfFile.is_open()) {
        QMessageBox::critical(this, "Hata", "CSV dosyaları oluşturulamadı!");
        return;
    }

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

    populateComboBox();

    // Notify success
    QMessageBox::information(this, "Başarılı", "Butterworth grafikleri oluşturuldu!");
}

void MainWindow::generateChebyshevCSV() {
    generateChebyshev("chebyshev_normalize.csv");

    std::ofstream lpfFile("chebyshev_low.csv");
    std::ofstream hpfFile("chebyshev_high.csv");
    std::ofstream bpfFile("chebyshev_band.csv");

    if (!lpfFile.is_open() || !hpfFile.is_open() || !bpfFile.is_open()) {
        QMessageBox::critical(this, "Hata", "CSV dosyaları oluşturulamadı!");
        return;
    }

    auto computeChebyshevResponse=[](double omega, const QString& type, double wp, double wc = 0.0, double bw = 0.0) {
        double epsilon = std::sqrt(std::pow(10, 0.1 * e_ripple) - 1);
        double Tn = 0.0;  // Varsayılan değer
        double omegaTransformed;

        if (type == "LPF") {
            omegaTransformed = omega / wp;
        } else if (type == "HPF") {
            omegaTransformed = wp / omega;
        } else if (type == "BPF") {
            if (std::abs(omega * bw) < 1e-6) {
                return 0.0; // Bölme hatasını önlemek için sıfır döndür
            }
            omegaTransformed = (omega * omega - wc * wc) / (omega * bw);
        } else {
            throw std::invalid_argument("Invalid filter type");
        }

        // Geçersiz omega değerlerini kontrol et
        if (omegaTransformed < 1) {
            Tn = std::cosh(n * std::acosh(omegaTransformed));
        } else {
            Tn = 0; // Geçersiz durumlarda sabit değer
        }

        double Hw = 1.0 / std::sqrt(1 + std::pow(epsilon * Tn, 2));
        return std::isnan(Hw) ? 0.0 : Hw;  // NaN kontrolü
    };

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;

        // LPF Response
        double lpfResponse = computeChebyshevResponse(omega, "LPF", lpf_wp);
        lpfFile << omega << "," << lpfResponse << "\n";

        // HPF Response
        double hpfResponse = computeChebyshevResponse(omega, "HPF", hpf_wp);
        hpfFile << omega << "," << hpfResponse << "\n";

        // BPF Response
        double bpfResponse = computeChebyshevResponse(omega, "BPF", bpf_wc, bpf_wc, bpf_bw);
        bpfFile << omega << "," << bpfResponse << "\n";
    }

    lpfFile.close();
    hpfFile.close();
    bpfFile.close();

    populateComboBox();

    QMessageBox::information(this, "Başarılı", "Chebyshev grafikleri oluşturuldu!");
}

void MainWindow::generateInverseChebyshevCSV() {

    generateInverseChebyshev("inverse_c_normalize.csv");

    std::ofstream lpfFile("inverse_chebyshev_low.csv");
    std::ofstream hpfFile("inverse_chebyshev_high.csv");
    std::ofstream bpfFile("inverse_chebyshev_band.csv");

    if (!lpfFile.is_open() || !hpfFile.is_open() || !bpfFile.is_open()) {
        QMessageBox::critical(this, "Hata", "CSV dosyaları oluşturulamadı!");
        return;
    }

    auto computeInverseChebyshevResponse = [](double omega, const QString& type, double wp, double wc = 0.0, double bw = 0.0) {
        double epsilon = 1.0 / std::sqrt(std::pow(10, 0.1 * e_ripple) - 1);
        double Tn = 0.0;  // Varsayılan değer
        double omegaTransformed;

        if (type == "LPF") {
            omegaTransformed = wp / omega;
        } else if (type == "HPF") {
            omegaTransformed = omega / wp;
        } else if (type == "BPF") {
            if (std::abs(omega * bw) < 1e-6) {
                return 0.0; // Bölme hatasını önlemek için sıfır döndür
            }
            omegaTransformed = (omega * bw) / (omega * omega - wc * wc);
        } else {
            throw std::invalid_argument("Invalid filter type");
        }

        // Geçersiz omega değerlerini kontrol et
        if (omegaTransformed >= -1 && omegaTransformed <= 1) {
            Tn = std::cos(n * std::acos(omegaTransformed));
        } else {
            Tn = 0; // Geçersiz durumlarda sabit değer
        }

        double Hw = epsilon / std::sqrt(1 + std::pow(Tn, 2));
        return std::isnan(Hw) ? 0.0 : Hw;  // NaN kontrolü
    };

    for (int i = 0; i < points; ++i) {
        double omega = (omegaMax / points) * i;

        // LPF Response
        double lpfResponse = computeInverseChebyshevResponse(omega, "LPF", lpf_wp);
        lpfFile << omega << "," << lpfResponse << "\n";

        // HPF Response
        double hpfResponse = computeInverseChebyshevResponse(omega, "HPF", hpf_wp);
        hpfFile << omega << "," << hpfResponse << "\n";

        // BPF Response
        double bpfResponse = computeInverseChebyshevResponse(omega, "BPF", bpf_wc, bpf_wc, bpf_bw);
        bpfFile << omega << "," << bpfResponse << "\n";
    }

    lpfFile.close();
    hpfFile.close();
    bpfFile.close();

    populateComboBox();

    QMessageBox::information(this, "Başarılı", "Inverse Chebyshev grafikleri oluşturuldu!");
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

void MainWindow::clearAllFiles() {
    QDir dir(QDir::currentPath());
    QStringList filters;
    filters << "*.csv";

    QStringList csvFiles = dir.entryList(filters, QDir::Files);

    // Iterate over each CSV file and attempt to remove it
    bool errorOccurred = false;
    for (const QString &file : csvFiles) {
        if (!QFile::remove(dir.filePath(file))) {
            errorOccurred = true;
        }
    }

    // Notify user about the result
    if (errorOccurred) {
        QMessageBox::warning(nullptr, "Uyarı", "Bazı CSV dosyaları silinemedi!");
    } else {
        QMessageBox::information(nullptr, "Başarılı", "Tüm CSV dosyaları başarıyla silindi!");
    }
    populateComboBox();
}