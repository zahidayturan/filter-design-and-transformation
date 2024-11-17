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
    QPushButton *csvButton;
    QPushButton *graphButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1103, 596);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(false);
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(50);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        vboxLayout->setContentsMargins(50, 50, 50, 50);
        csvButton = new QPushButton(centralwidget);
        csvButton->setObjectName("csvButton");

        vboxLayout->addWidget(csvButton);

        graphButton = new QPushButton(centralwidget);
        graphButton->setObjectName("graphButton");
        graphButton->setEnabled(true);

        vboxLayout->addWidget(graphButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        csvButton->setText(QCoreApplication::translate("MainWindow", "CSV Dosyas\304\261 Olu\305\237tur", nullptr));
        graphButton->setText(QCoreApplication::translate("MainWindow", "Grafi\304\237i G\303\266ster", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
