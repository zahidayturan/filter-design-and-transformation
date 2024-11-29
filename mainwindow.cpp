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
const int DEFAULT_N = 6;
const double DEFAULT_E_RIPPLE = 0.12;
const double DEFAULT_ICE_RIPPLE = 0.19;
const double DEFAULT_P_LPF = 340.0;
const double DEFAULT_P_HPF = 130.0;
const double DEFAULT_C_BPF = 310.0;
const double DEFAULT_BW_BPF = 95.0;

int n = DEFAULT_N; //QLineEdit *edit_d;
double e_ripple = DEFAULT_E_RIPPLE; //QLineEdit *edit_c;
double ice_ripple = DEFAULT_ICE_RIPPLE; //QLineEdit *line_i;
double omega_p_lpf = DEFAULT_P_LPF; //QLineEdit *edit_lpf;
double omega_p_hpf = DEFAULT_P_HPF; //QLineEdit *edit_hpf;
double omega_c_bpf = DEFAULT_C_BPF; //QLineEdit *edit_bpf;
double bw_bpf = DEFAULT_BW_BPF; //QLineEdit *edit_bw;
const int num_points = 200;


void save_to_csv(const std::string& filename, const std::vector<double>& freq, const std::vector<double>& response);


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->b_create, &QPushButton::clicked, this, &MainWindow::generateButterworthCSV);
    connect(ui->c_create, &QPushButton::clicked, this, &MainWindow::generateChebyshevCSV);
    connect(ui->i_create, &QPushButton::clicked, this, &MainWindow::generateInverseChebyshevCSV);
    connect(ui->reload, &QPushButton::clicked, this, &MainWindow::clearAllFiles);
    populateComboBox();
    checkAllCSV();
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onComboBoxSelectionChanged);
    connect(ui->b_open, &QPushButton::clicked, this, [this]() {
        showGraphWithPath("b_all");
    });
    connect(ui->c_open, &QPushButton::clicked, this, [this]() {
        showGraphWithPath("c_all");
    });
    connect(ui->i_open, &QPushButton::clicked, this, [this]() {
        showGraphWithPath("i_all");
    });

    connect(ui->edit_d, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_d, 1, 10, DEFAULT_N);
        updateValues();
    });

    connect(ui->edit_c, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_c, 0.0, 1.0, DEFAULT_E_RIPPLE);
        updateValues();
    });

    connect(ui->line_i, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->line_i, 0.0, 1.0, DEFAULT_ICE_RIPPLE);
        updateValues();
    });

    connect(ui->edit_lpf, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_lpf, 0.0, 1000.0, DEFAULT_P_LPF);
        updateValues();
    });

    connect(ui->edit_hpf, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_hpf, 0, 1000.0, DEFAULT_P_HPF);
        updateValues();
    });

    connect(ui->edit_bpf, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_bpf, 0, 1000.0, DEFAULT_C_BPF);
        updateValues();
    });

    connect(ui->edit_bw, &QLineEdit::editingFinished, this, [this]() {
        validateInput(ui->edit_bw, 0, 200.0, DEFAULT_BW_BPF);
        updateValues();
    });

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generateButterworthCSV()
{
    std::vector<std::complex<double>> poles;

    // Butterworth filtresi için kutupları hesaplama
    for (int k = 0; k < n; ++k) {
        double real = -sin((2 * k + 1) * M_PI / (2 * n));
        std::complex<double> imag(0, cos((2 * k + 1) * M_PI / (2 * n)));
        poles.push_back(real + imag);
    }

    // İkinci derece (biquad) payda polinomlarını hesaplama
    std::vector<std::vector<double>> Hbt;
    for (int k = 0; k < (n + 1) / 2; ++k) {
        if (k == n - k - 1) {  // Tek kök varsa
            Hbt.push_back({0, 1, -poles[k].real()});
        } else {
            std::vector<double> poly = {
                    1,
                    -(poles[k] + poles[n - k - 1]).real(),
                    (poles[k] * poles[n - k - 1]).real()
            };
            Hbt.push_back(poly);
        }
    }

    // Normalize frekans cevabı
    std::vector<double> w_normalized(num_points), Hw_normalized(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_normalized[i] = 0.01 + i * (3.0 - 0.01) / (num_points - 1);  // 0.01'den 3'e kadar
        std::complex<double> Nw = 1, Dw = 1;
        for (const auto& poly : Hbt) {
            Nw *= std::abs(poly[2]);
            Dw *= std::abs(poly[0] * std::pow(std::complex<double>(0, w_normalized[i]), 2) +
                           poly[1] * std::complex<double>(0, w_normalized[i]) + poly[2]);
        }
        Hw_normalized[i] = std::abs(Nw / Dw);
    }

    // Gerçek frekans cevabı
    std::vector<double> w_real(num_points), Hw_lpf(num_points), Hw_hpf(num_points), Hw_bpf(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_real[i] = 1e-3 + i * (600.0 - 1e-3) / (num_points - 1);  // 0.001'den 600'e kadar
        std::complex<double> Nw_lpf = 1, Dw_lpf = 1, Nw_hpf = 1, Dw_hpf = 1, Nw_bpf = 1, Dw_bpf = 1;

        for (const auto& poly : Hbt) {
            // LPF
            Nw_lpf *= poly[2];
            Dw_lpf *= std::abs(poly[0] * std::pow(std::complex<double>(0, w_real[i] / omega_p_lpf), 2) +
                               poly[1] * std::complex<double>(0, w_real[i] / omega_p_lpf) + poly[2]);
            // HPF
            Nw_hpf *= poly[2];
            Dw_hpf *= std::abs(poly[0] * std::pow(std::complex<double>(0, omega_p_hpf / w_real[i]), 2) +
                               poly[1] * std::complex<double>(0, omega_p_hpf / w_real[i]) + poly[2]);
            // BPF
            std::complex<double> bpf_term(0, (w_real[i] * w_real[i] - omega_c_bpf * omega_c_bpf) / (w_real[i] * bw_bpf));
            Nw_bpf *= poly[2];
            Dw_bpf *= std::abs(poly[0] * std::pow(bpf_term, 2) + poly[1] * bpf_term + poly[2]);
        }
        Hw_lpf[i] = std::abs(Nw_lpf / Dw_lpf);
        Hw_hpf[i] = std::abs(Nw_hpf / Dw_hpf);
        Hw_bpf[i] = std::abs(Nw_bpf / Dw_bpf);
    }

    save_to_csv("normalized_butterworth.csv", w_normalized, Hw_normalized);
    save_to_csv("lpf_butterworth.csv", w_real, Hw_lpf);
    save_to_csv("hpf_butterworth.csv", w_real, Hw_hpf);
    save_to_csv("bpf_butterworth.csv", w_real, Hw_bpf);

    populateComboBox();
    checkAllCSV();
    QMessageBox::information(this, "Başarılı", "Butterworth grafikleri oluşturuldu!");
}

void MainWindow::generateChebyshevCSV() {

    std::vector<std::complex<double>> s;
    std::vector<std::vector<double>> Hch;

    // Payda köklerini bulma
    for (int k = 1; k <= n; ++k) {
        double D_Re = -sin((2 * k - 1) * M_PI / (2 * n)) * sinh(asinh(1 / e_ripple) / n);
        double D_Im = cos((2 * k - 1) * M_PI / (2 * n)) * cosh(asinh(1 / e_ripple) / n);
        s.emplace_back(D_Re, D_Im);
    }

    // Biquad payda polinomlarını bulma
    for (int k = 0; k < (n + 1) / 2; ++k) {
        if (k == (n - k - 1)) { // Eğer tek kök varsa
            Hch.push_back({0, 1, -s[k].real()});
        } else {
            std::vector<double> poly(3);
            poly[0] = 1;
            poly[1] = -(s[k] + s[n - k - 1]).real();
            poly[2] = (s[k] * s[n - k - 1]).real();
            Hch.push_back(poly);
        }
    }

    // Normalize frekans ekseni ve cevap
    std::vector<double> w_normalized(num_points), Hw_normalized(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_normalized[i] = 0.02 + i * (2.0 - 0.02) / (num_points - 1); // 0.02'den 2 rad/s'ye kadar
        double freq = w_normalized[i];

        double Nw = 1.0, Dw = 1.0;
        for (const auto& poly : Hch) {
            Nw *= std::abs(poly[2]);
            Dw *= std::abs(poly[0] * std::pow(std::complex<double>(0, freq), 2) +
                           poly[1] * std::complex<double>(0, freq) + poly[2]);
        }
        Hw_normalized[i] = Nw / Dw;
    }

    // Gerçek frekans ekseni ve cevaplar
    std::vector<double> w_real(num_points), Hw_lpf(num_points), Hw_hpf(num_points), Hw_bpf(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_real[i] = i * 600.0 / num_points; // 0'dan 600 rad/s'ye kadar
        double freq = w_real[i];

        double Dw_lpf = 1.0, Dw_hpf = 1.0, Dw_bpf = 1.0;
        for (const auto& poly : Hch) {
            // LPF
            Dw_lpf *= std::abs(poly[0] * std::pow(std::complex<double>(0, freq / omega_p_lpf), 2) +
                               poly[1] * std::complex<double>(0, freq / omega_p_lpf) + poly[2]);
            // HPF
            Dw_hpf *= std::abs(poly[0] * std::pow(std::complex<double>(0, omega_p_hpf / freq), 2) +
                               poly[1] * std::complex<double>(0, omega_p_hpf / freq) + poly[2]);
            // BPF
            Dw_bpf *= std::abs(poly[0] * std::pow(std::complex<double>(0, (freq * freq - omega_c_bpf * omega_c_bpf) / (freq * bw_bpf)), 2) +
                               poly[1] * std::complex<double>(0, (freq * freq - omega_c_bpf * omega_c_bpf) / (freq * bw_bpf)) + poly[2]);
        }

        Hw_lpf[i] = 1.0 / Dw_lpf;
        Hw_hpf[i] = 1.0 / Dw_hpf;
        Hw_bpf[i] = 1.0 / Dw_bpf;
    }

    save_to_csv("normalized_chebyshev.csv", w_normalized, Hw_normalized);
    save_to_csv("lpf_chebyshev.csv", w_real, Hw_lpf);
    save_to_csv("hpf_chebyshev.csv", w_real, Hw_hpf);
    save_to_csv("bpf_chebyshev.csv", w_real, Hw_bpf);

    populateComboBox();
    checkAllCSV();
    QMessageBox::information(this, "Başarılı", "Chebyshev grafikleri oluşturuldu!");
}

void MainWindow::generateInverseChebyshevCSV() {

    std::vector<std::complex<double>> D, Z;
    std::vector<std::vector<double>> HcN, HcD;

    // Payda kökleri (kutuplar) ve sıfırları hesaplama
    for (int k = 1; k <= n; ++k) {
        double D_Re = -sin((2 * k - 1) * M_PI / (2 * n)) * sinh(asinh(1 / ice_ripple) / n);
        double D_Im = cos((2 * k - 1) * M_PI / (2 * n)) * cosh(asinh(1 / ice_ripple) / n);
        D.emplace_back(1.0 / std::complex<double>(D_Re, D_Im)); // Payda kökleri (kutuplar)
        Z.emplace_back(1.0 / std::complex<double>(0, -cos(M_PI * (2 * k - 1) / (2 * n)))); // Pay sıfırları
    }

    // Pay ve payda polinom katsayılarını hesaplama
    for (int k = 0; k < (n + 1) / 2; ++k) {
        if (k == (n - k - 1)) { // Tek kök varsa
            HcN.push_back({0, 0, 1});
            HcD.push_back({0, 1, -D[k].real()});
        } else {
            std::vector<double> polyN = {1, -(Z[k] + Z[n - k - 1]).real(), (Z[k] * Z[n - k - 1]).real()};
            std::vector<double> polyD = {1, -(D[k] + D[n - k - 1]).real(), (D[k] * D[n - k - 1]).real()};
            HcN.push_back(polyN);
            HcD.push_back(polyD);
        }
    }

    // Kazanç çarpanı hesaplama
    double Gain = 1.0;
    for (const auto& polyD : HcD) {
        Gain *= polyD[2];
    }
    for (const auto& polyN : HcN) {
        Gain /= polyN[2];
    }
    Gain = std::pow(Gain, 1.0 / ((n + 1) / 2));
    for (auto& polyN : HcN) {
        for (auto& coeff : polyN) {
            coeff *= Gain;
        }
    }

    // Normalize frekans cevabı
    std::vector<double> w_normalized(num_points), Hw_normalized(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_normalized[i] = 0.02 + i * (8.0 - 0.02) / (num_points - 1); // 0.02'den 8'e kadar
        std::complex<double> Nw = 1, Dw = 1;
        for (size_t k = 0; k < HcN.size(); ++k) {
            Nw *= HcN[k][0] * std::pow(std::complex<double>(0, w_normalized[i]), 2) +
                  HcN[k][1] * std::complex<double>(0, w_normalized[i]) + HcN[k][2];
            Dw *= HcD[k][0] * std::pow(std::complex<double>(0, w_normalized[i]), 2) +
                  HcD[k][1] * std::complex<double>(0, w_normalized[i]) + HcD[k][2];
        }
        Hw_normalized[i] = std::abs(Nw / Dw);
    }

    // Gerçek frekans cevabı
    std::vector<double> w_real(num_points), Hw_lpf(num_points), Hw_hpf(num_points), Hw_bpf(num_points);
    for (int i = 0; i < num_points; ++i) {
        w_real[i] = 1e-3 + i * (600.0 - 1e-3) / (num_points - 1); // 1e-3'ten 600'e kadar
        std::complex<double> Nw_lpf = 1, Dw_lpf = 1, Nw_hpf = 1, Dw_hpf = 1, Nw_bpf = 1, Dw_bpf = 1;
        for (size_t k = 0; k < HcN.size(); ++k) {
            // LPF
            Nw_lpf *= HcN[k][0] * std::pow(std::complex<double>(0, w_real[i] / omega_p_lpf), 2) +
                      HcN[k][1] * std::complex<double>(0, w_real[i] / omega_p_lpf) + HcN[k][2];
            Dw_lpf *= HcD[k][0] * std::pow(std::complex<double>(0, w_real[i] / omega_p_lpf), 2) +
                      HcD[k][1] * std::complex<double>(0, w_real[i] / omega_p_lpf) + HcD[k][2];
            // HPF
            Nw_hpf *= HcN[k][0] * std::pow(std::complex<double>(0, omega_p_hpf / w_real[i]), 2) +
                      HcN[k][1] * std::complex<double>(0, omega_p_hpf / w_real[i]) + HcN[k][2];
            Dw_hpf *= HcD[k][0] * std::pow(std::complex<double>(0, omega_p_hpf / w_real[i]), 2) +
                      HcD[k][1] * std::complex<double>(0, omega_p_hpf / w_real[i]) + HcD[k][2];
            // BPF
            std::complex<double> BPF_term = std::complex<double>(0, (w_real[i] * w_real[i] - omega_c_bpf * omega_c_bpf) / (w_real[i] * bw_bpf));
            Nw_bpf *= HcN[k][0] * std::pow(BPF_term, 2) + HcN[k][1] * BPF_term + HcN[k][2];
            Dw_bpf *= HcD[k][0] * std::pow(BPF_term, 2) + HcD[k][1] * BPF_term + HcD[k][2];
        }
        Hw_lpf[i] = std::abs(Nw_lpf / Dw_lpf);
        Hw_hpf[i] = std::abs(Nw_hpf / Dw_hpf);
        Hw_bpf[i] = std::abs(Nw_bpf / Dw_bpf);
    }

    save_to_csv("normalized_inverse_chebyshev.csv", w_normalized, Hw_normalized);
    save_to_csv("lpf_inverse_chebyshev.csv", w_real, Hw_lpf);
    save_to_csv("hpf_inverse_chebyshev.csv", w_real, Hw_hpf);
    save_to_csv("bpf_inverse_chebyshev.csv", w_real, Hw_bpf);

    populateComboBox();
    checkAllCSV();
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

void updateCSVStatus(const QStringList& csvFiles, QLabel* infoLabel, QPushButton* openButton) {
    int existingFileCount = 0;

    for (const QString& fileName : csvFiles) {
        if (QFile::exists(fileName)) {
            ++existingFileCount;
        }
    }

    if (existingFileCount == csvFiles.size()) {
        infoLabel->setText("grafikler oluşturulmuş");
        infoLabel->setStyleSheet("font: italic 9pt \"Montserrat\";\ncolor: green;");
        openButton->setVisible(true);
    } else if (existingFileCount > 0) {
        infoLabel->setText("grafiklerin bazıları oluşturulmuş");
        infoLabel->setStyleSheet("font: italic 9pt \"Montserrat\";\ncolor: white;");
        openButton->setVisible(true);
    } else {
        infoLabel->setText("grafikler oluşturulmamış");
        infoLabel->setStyleSheet("font: italic 9pt \"Montserrat\";\ncolor: red;");
        openButton->setVisible(false);

    }
}

void MainWindow::checkAllCSV() {
    QStringList bCsvFiles = {
            "normalized_butterworth.csv",
            "lpf_butterworth.csv",
            "hpf_butterworth.csv",
            "bpf_butterworth.csv"
    };
    updateCSVStatus(bCsvFiles, ui->b_info, ui->b_open);

    QStringList cCsvFiles = {
            "normalized_chebyshev.csv",
            "lpf_chebyshev.csv",
            "hpf_chebyshev.csv",
            "bpf_chebyshev.csv"
    };
    updateCSVStatus(cCsvFiles, ui->c_info,ui->c_open);

    QStringList iCsvFiles = {
            "normalized_inverse_chebyshev.csv",
            "lpf_inverse_chebyshev.csv",
            "hpf_inverse_chebyshev.csv",
            "bpf_inverse_chebyshev.csv"
    };
    updateCSVStatus(iCsvFiles, ui->i_info,ui->i_open);
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

    bool errorOccurred = false;
    for (const QString &file : csvFiles) {
        if (!QFile::remove(dir.filePath(file))) {
            errorOccurred = true;
        }
    }

    if (errorOccurred) {
        QMessageBox::warning(nullptr, "Uyarı", "Bazı dosyalar silinemedi!");
    } else {
        QMessageBox::information(nullptr, "Başarılı", "Tüm dosyalar başarıyla silindi! Veriler sıfırlandı");
    }
    resetToDefaultValues();
    populateComboBox();
    checkAllCSV();
}

void save_to_csv(const std::string& filename, const std::vector<double>& freq, const std::vector<double>& response) {
    std::ofstream file(filename);
    if (!file) {
        QString errorMessage = "Dosya açılamadı: " + QString::fromStdString(filename);
        QMessageBox::critical(nullptr, "Hata", errorMessage);
        return;
    }

    for (size_t i = 0; i < freq.size(); ++i) {
        file << freq[i] << "," << response[i] << "\n";
    }
    file.close();
}

void MainWindow::updateValues() {
    bool ok;

    int nValue = ui->edit_d->text().toInt(&ok);
    if (ok) n = nValue;

    double eRippleValue = ui->edit_c->text().toDouble(&ok);
    if (ok) e_ripple = eRippleValue;

    double iceRippleValue = ui->line_i->text().toDouble(&ok);
    if (ok) ice_ripple = iceRippleValue;

    double lpfValue = ui->edit_lpf->text().toDouble(&ok);
    if (ok) omega_p_lpf = lpfValue;

    double hpfValue = ui->edit_hpf->text().toDouble(&ok);
    if (ok) omega_p_hpf = hpfValue;

    double bpfValue = ui->edit_bpf->text().toDouble(&ok);
    if (ok) omega_c_bpf = bpfValue;

    double bwValue = ui->edit_bw->text().toDouble(&ok);
    if (ok) bw_bpf = bwValue;
}

void MainWindow::resetToDefaultValues() {
    n = DEFAULT_N;
    e_ripple = DEFAULT_E_RIPPLE;
    ice_ripple = DEFAULT_ICE_RIPPLE;
    omega_p_lpf = DEFAULT_P_LPF;
    omega_p_hpf = DEFAULT_P_HPF;
    omega_c_bpf = DEFAULT_C_BPF;
    bw_bpf = DEFAULT_BW_BPF;

    ui->edit_d->setText(QString::number(n));
    ui->edit_c->setText(QString::number(e_ripple));
    ui->line_i->setText(QString::number(ice_ripple));
    ui->edit_lpf->setText(QString::number(omega_p_lpf));
    ui->edit_hpf->setText(QString::number(omega_p_hpf));
    ui->edit_bpf->setText(QString::number(omega_c_bpf));
    ui->edit_bw->setText(QString::number(bw_bpf));
}

void MainWindow::validateInput(QLineEdit *lineEdit, double min, double max, double defaultValue) {
    bool ok;
    double value = lineEdit->text().toDouble(&ok);

    if (!ok || value < min || value > max) {
        QMessageBox::warning(this, "Geçersiz Giriş",
                             QString("Lütfen %1 ile %2 arasında bir değer girin.").arg(min).arg(max));

        lineEdit->setText(QString::number(defaultValue));

        lineEdit->setStyleSheet("border: 2px solid red;\nborder-radius: 4px;\npadding: 2px;");
    } else {
        lineEdit->setStyleSheet("border: 2px solid  rgb(241, 249, 250);\nborder-radius: 4px;\npadding: 2px;");
    }
}
