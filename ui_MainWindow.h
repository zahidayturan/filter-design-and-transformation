/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *csvButton;
    QPushButton *butterworthButton;
    QPushButton *graphButton;
    QComboBox *comboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1103, 418);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 57, 57);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(false);
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(50);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        vboxLayout->setContentsMargins(50, 50, 50, 50);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        vboxLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        csvButton = new QPushButton(centralwidget);
        csvButton->setObjectName("csvButton");
        csvButton->setAutoFillBackground(false);
        csvButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(csvButton);

        butterworthButton = new QPushButton(centralwidget);
        butterworthButton->setObjectName("butterworthButton");

        horizontalLayout->addWidget(butterworthButton);

        graphButton = new QPushButton(centralwidget);
        graphButton->setObjectName("graphButton");
        graphButton->setEnabled(true);
        graphButton->setAutoFillBackground(false);
        graphButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        graphButton->setCheckable(false);

        horizontalLayout->addWidget(graphButton);


        vboxLayout->addLayout(horizontalLayout);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");

        vboxLayout->addWidget(comboBox);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        csvButton->setText(QCoreApplication::translate("MainWindow", "B\303\274t\303\274n Dosyalar\304\261 Olu\305\237tur", nullptr));
        butterworthButton->setText(QCoreApplication::translate("MainWindow", "Butterworth CSV", nullptr));
        graphButton->setText(QCoreApplication::translate("MainWindow", "Manuel Grafik G\303\266ster", nullptr));
#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Olu\305\237turulan Grafiklerden Se\303\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
