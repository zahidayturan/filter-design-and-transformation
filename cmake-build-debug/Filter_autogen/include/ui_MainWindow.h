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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *main_widget;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *main_vertical;
    QHBoxLayout *app_bar;
    QLabel *title;
    QPushButton *reload;
    QHBoxLayout *app_menu;
    QVBoxLayout *input_menu;
    QVBoxLayout *input_lpf;
    QLabel *label_lpf;
    QLineEdit *edit_lpf;
    QVBoxLayout *input_hpf;
    QLabel *label_hpf;
    QLineEdit *edit_hpf;
    QVBoxLayout *input_bpf;
    QLabel *label_bpf;
    QLineEdit *edit_bpf;
    QVBoxLayout *input_bw;
    QLabel *label_bw;
    QLineEdit *edit_bw;
    QVBoxLayout *input_c;
    QLabel *label_c;
    QLineEdit *edit_c;
    QVBoxLayout *input_i;
    QLabel *label_i;
    QLineEdit *line_i;
    QVBoxLayout *input_d;
    QLabel *label_d;
    QLineEdit *edit_d;
    QVBoxLayout *output_menu;
    QVBoxLayout *b_output;
    QLabel *b_title;
    QHBoxLayout *b_actives;
    QRadioButton *bl_active;
    QRadioButton *bh_active;
    QRadioButton *bb_active;
    QHBoxLayout *b_buttons;
    QPushButton *b_create;
    QVBoxLayout *c_output;
    QLabel *c_title;
    QHBoxLayout *c_actives;
    QRadioButton *cl_active;
    QRadioButton *ch_active;
    QRadioButton *cb_active;
    QHBoxLayout *c_buttons;
    QPushButton *c_create;
    QVBoxLayout *i_output;
    QLabel *i_title;
    QHBoxLayout *i_actives;
    QRadioButton *il_active;
    QRadioButton *ih_active;
    QRadioButton *ib_active;
    QHBoxLayout *i_buttons;
    QPushButton *i_create;
    QComboBox *comboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(984, 695);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(47, 79, 91);\n"
"font: 10pt \"Montserrat\";\n"
"color: rgb(252, 252, 252);"));
        main_widget = new QWidget(MainWindow);
        main_widget->setObjectName("main_widget");
        main_widget->setAutoFillBackground(false);
        vboxLayout = new QVBoxLayout(main_widget);
        vboxLayout->setSpacing(100);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        vboxLayout->setContentsMargins(50, 50, 50, 50);
        main_vertical = new QVBoxLayout();
        main_vertical->setSpacing(50);
        main_vertical->setObjectName("main_vertical");
        main_vertical->setContentsMargins(-1, 0, -1, -1);
        app_bar = new QHBoxLayout();
        app_bar->setSpacing(10);
        app_bar->setObjectName("app_bar");
        app_bar->setContentsMargins(-1, -1, -1, 0);
        title = new QLabel(main_widget);
        title->setObjectName("title");
        title->setStyleSheet(QString::fromUtf8("font: 900 16pt \"Montserrat Black\";\n"
"color: rgb(220, 238, 241);"));

        app_bar->addWidget(title);

        reload = new QPushButton(main_widget);
        reload->setObjectName("reload");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(reload->sizePolicy().hasHeightForWidth());
        reload->setSizePolicy(sizePolicy);
        reload->setStyleSheet(QString::fromUtf8("background-color: rgb(62, 139, 156);\n"
"border-radius: 4px;\n"
"padding: 4px;"));
        reload->setAutoDefault(false);
        reload->setFlat(false);

        app_bar->addWidget(reload);


        main_vertical->addLayout(app_bar);

        app_menu = new QHBoxLayout();
        app_menu->setSpacing(50);
        app_menu->setObjectName("app_menu");
        app_menu->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        input_menu = new QVBoxLayout();
        input_menu->setSpacing(20);
        input_menu->setObjectName("input_menu");
        input_menu->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        input_menu->setContentsMargins(-1, -1, -1, 0);
        input_lpf = new QVBoxLayout();
        input_lpf->setSpacing(4);
        input_lpf->setObjectName("input_lpf");
        input_lpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_lpf = new QLabel(main_widget);
        label_lpf->setObjectName("label_lpf");

        input_lpf->addWidget(label_lpf);

        edit_lpf = new QLineEdit(main_widget);
        edit_lpf->setObjectName("edit_lpf");
        edit_lpf->setAutoFillBackground(false);
        edit_lpf->setStyleSheet(QString::fromUtf8("border-color: rgb(24, 43, 52);"));
        edit_lpf->setFrame(true);

        input_lpf->addWidget(edit_lpf);


        input_menu->addLayout(input_lpf);

        input_hpf = new QVBoxLayout();
        input_hpf->setSpacing(4);
        input_hpf->setObjectName("input_hpf");
        input_hpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_hpf = new QLabel(main_widget);
        label_hpf->setObjectName("label_hpf");

        input_hpf->addWidget(label_hpf);

        edit_hpf = new QLineEdit(main_widget);
        edit_hpf->setObjectName("edit_hpf");

        input_hpf->addWidget(edit_hpf);


        input_menu->addLayout(input_hpf);

        input_bpf = new QVBoxLayout();
        input_bpf->setSpacing(4);
        input_bpf->setObjectName("input_bpf");
        input_bpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_bpf = new QLabel(main_widget);
        label_bpf->setObjectName("label_bpf");

        input_bpf->addWidget(label_bpf);

        edit_bpf = new QLineEdit(main_widget);
        edit_bpf->setObjectName("edit_bpf");

        input_bpf->addWidget(edit_bpf);


        input_menu->addLayout(input_bpf);

        input_bw = new QVBoxLayout();
        input_bw->setSpacing(4);
        input_bw->setObjectName("input_bw");
        input_bw->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_bw = new QLabel(main_widget);
        label_bw->setObjectName("label_bw");

        input_bw->addWidget(label_bw);

        edit_bw = new QLineEdit(main_widget);
        edit_bw->setObjectName("edit_bw");

        input_bw->addWidget(edit_bw);


        input_menu->addLayout(input_bw);

        input_c = new QVBoxLayout();
        input_c->setSpacing(4);
        input_c->setObjectName("input_c");
        input_c->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_c = new QLabel(main_widget);
        label_c->setObjectName("label_c");

        input_c->addWidget(label_c);

        edit_c = new QLineEdit(main_widget);
        edit_c->setObjectName("edit_c");

        input_c->addWidget(edit_c);


        input_menu->addLayout(input_c);

        input_i = new QVBoxLayout();
        input_i->setSpacing(4);
        input_i->setObjectName("input_i");
        input_i->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_i = new QLabel(main_widget);
        label_i->setObjectName("label_i");

        input_i->addWidget(label_i);

        line_i = new QLineEdit(main_widget);
        line_i->setObjectName("line_i");

        input_i->addWidget(line_i);


        input_menu->addLayout(input_i);

        input_d = new QVBoxLayout();
        input_d->setObjectName("input_d");
        input_d->setContentsMargins(-1, -1, -1, 0);
        label_d = new QLabel(main_widget);
        label_d->setObjectName("label_d");

        input_d->addWidget(label_d);

        edit_d = new QLineEdit(main_widget);
        edit_d->setObjectName("edit_d");

        input_d->addWidget(edit_d);


        input_menu->addLayout(input_d);


        app_menu->addLayout(input_menu);

        output_menu = new QVBoxLayout();
        output_menu->setSpacing(20);
        output_menu->setObjectName("output_menu");
        b_output = new QVBoxLayout();
        b_output->setSpacing(4);
        b_output->setObjectName("b_output");
        b_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        b_title = new QLabel(main_widget);
        b_title->setObjectName("b_title");
        b_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        b_output->addWidget(b_title);

        b_actives = new QHBoxLayout();
        b_actives->setSpacing(10);
        b_actives->setObjectName("b_actives");
        b_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        bl_active = new QRadioButton(main_widget);
        bl_active->setObjectName("bl_active");
        bl_active->setAcceptDrops(false);
        bl_active->setChecked(true);
        bl_active->setAutoExclusive(false);

        b_actives->addWidget(bl_active);

        bh_active = new QRadioButton(main_widget);
        bh_active->setObjectName("bh_active");
        bh_active->setChecked(true);
        bh_active->setAutoRepeat(false);
        bh_active->setAutoExclusive(false);

        b_actives->addWidget(bh_active);

        bb_active = new QRadioButton(main_widget);
        bb_active->setObjectName("bb_active");
        bb_active->setStyleSheet(QString::fromUtf8("font: 10pt \"Montserrat\";"));
        bb_active->setCheckable(true);
        bb_active->setChecked(true);
        bb_active->setAutoRepeat(false);
        bb_active->setAutoExclusive(false);

        b_actives->addWidget(bb_active);


        b_output->addLayout(b_actives);

        b_buttons = new QHBoxLayout();
        b_buttons->setSpacing(10);
        b_buttons->setObjectName("b_buttons");
        b_buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        b_create = new QPushButton(main_widget);
        b_create->setObjectName("b_create");
        b_create->setStyleSheet(QString::fromUtf8("background-color: rgb(24, 43, 52);\n"
"border-radius: 4px;\n"
"padding: 8px;"));

        b_buttons->addWidget(b_create);


        b_output->addLayout(b_buttons);


        output_menu->addLayout(b_output);

        c_output = new QVBoxLayout();
        c_output->setSpacing(4);
        c_output->setObjectName("c_output");
        c_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        c_title = new QLabel(main_widget);
        c_title->setObjectName("c_title");
        c_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        c_output->addWidget(c_title);

        c_actives = new QHBoxLayout();
        c_actives->setSpacing(10);
        c_actives->setObjectName("c_actives");
        c_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        cl_active = new QRadioButton(main_widget);
        cl_active->setObjectName("cl_active");
        cl_active->setChecked(true);
        cl_active->setAutoExclusive(false);

        c_actives->addWidget(cl_active);

        ch_active = new QRadioButton(main_widget);
        ch_active->setObjectName("ch_active");
        ch_active->setChecked(true);
        ch_active->setAutoExclusive(false);

        c_actives->addWidget(ch_active);

        cb_active = new QRadioButton(main_widget);
        cb_active->setObjectName("cb_active");
        cb_active->setChecked(true);
        cb_active->setAutoExclusive(false);

        c_actives->addWidget(cb_active);


        c_output->addLayout(c_actives);

        c_buttons = new QHBoxLayout();
        c_buttons->setSpacing(10);
        c_buttons->setObjectName("c_buttons");
        c_buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        c_create = new QPushButton(main_widget);
        c_create->setObjectName("c_create");
        c_create->setStyleSheet(QString::fromUtf8("background-color: rgb(24, 43, 52);\n"
"border-radius: 4px;\n"
"padding: 8px;"));

        c_buttons->addWidget(c_create);


        c_output->addLayout(c_buttons);


        output_menu->addLayout(c_output);

        i_output = new QVBoxLayout();
        i_output->setSpacing(4);
        i_output->setObjectName("i_output");
        i_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        i_title = new QLabel(main_widget);
        i_title->setObjectName("i_title");
        i_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        i_output->addWidget(i_title);

        i_actives = new QHBoxLayout();
        i_actives->setSpacing(10);
        i_actives->setObjectName("i_actives");
        i_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        il_active = new QRadioButton(main_widget);
        il_active->setObjectName("il_active");
        il_active->setChecked(true);
        il_active->setAutoExclusive(false);

        i_actives->addWidget(il_active);

        ih_active = new QRadioButton(main_widget);
        ih_active->setObjectName("ih_active");
        ih_active->setChecked(true);
        ih_active->setAutoExclusive(false);

        i_actives->addWidget(ih_active);

        ib_active = new QRadioButton(main_widget);
        ib_active->setObjectName("ib_active");
        ib_active->setChecked(true);
        ib_active->setAutoExclusive(false);

        i_actives->addWidget(ib_active);


        i_output->addLayout(i_actives);

        i_buttons = new QHBoxLayout();
        i_buttons->setSpacing(10);
        i_buttons->setObjectName("i_buttons");
        i_buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        i_create = new QPushButton(main_widget);
        i_create->setObjectName("i_create");
        i_create->setStyleSheet(QString::fromUtf8("background-color: rgb(24, 43, 52);\n"
"border-radius: 4px;\n"
"padding: 8px;"));

        i_buttons->addWidget(i_create);


        i_output->addLayout(i_buttons);


        output_menu->addLayout(i_output);

        comboBox = new QComboBox(main_widget);
        comboBox->setObjectName("comboBox");
        comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(241, 249, 250);\n"
"font: 10pt \"Montserrat\";\n"
"border-radius: 4px;\n"
"padding: 8px;\n"
"color: rgb(24, 43, 52);"));

        output_menu->addWidget(comboBox);


        app_menu->addLayout(output_menu);


        main_vertical->addLayout(app_menu);


        vboxLayout->addLayout(main_vertical);

        MainWindow->setCentralWidget(main_widget);

        retranslateUi(MainWindow);

        reload->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "F\304\260LTRE D\303\226N\303\234\305\236\303\234M", nullptr));
        reload->setText(QCoreApplication::translate("MainWindow", "Program\304\261 S\304\261f\304\261rla", nullptr));
        label_lpf->setText(QCoreApplication::translate("MainWindow", "LPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        edit_lpf->setText(QCoreApplication::translate("MainWindow", "340", nullptr));
        edit_lpf->setPlaceholderText(QCoreApplication::translate("MainWindow", "LPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        label_hpf->setText(QCoreApplication::translate("MainWindow", "HPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        edit_hpf->setText(QCoreApplication::translate("MainWindow", "130", nullptr));
        label_bpf->setText(QCoreApplication::translate("MainWindow", "BPF Merkez Frekans\304\261 (\317\211C)  rad/s", nullptr));
        edit_bpf->setText(QCoreApplication::translate("MainWindow", "310", nullptr));
        label_bw->setText(QCoreApplication::translate("MainWindow", "Band Aral\304\261klar\304\261 (BW) rad/s", nullptr));
        edit_bw->setText(QCoreApplication::translate("MainWindow", "95", nullptr));
        label_c->setText(QCoreApplication::translate("MainWindow", "Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        edit_c->setText(QCoreApplication::translate("MainWindow", "0.12", nullptr));
        label_i->setText(QCoreApplication::translate("MainWindow", "Ters Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        line_i->setText(QCoreApplication::translate("MainWindow", "0.19", nullptr));
        label_d->setText(QCoreApplication::translate("MainWindow", "Filtre Derecesi", nullptr));
        edit_d->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        b_title->setText(QCoreApplication::translate("MainWindow", "Butterworth", nullptr));
        bl_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Filtre", nullptr));
        bh_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Filtre", nullptr));
        bb_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        b_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
        c_title->setText(QCoreApplication::translate("MainWindow", "Chebyshev", nullptr));
        cl_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Filtre", nullptr));
        ch_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Filtre", nullptr));
        cb_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        c_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
        i_title->setText(QCoreApplication::translate("MainWindow", "Ters Chebyshev", nullptr));
        il_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Filtre", nullptr));
        ih_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Filtre", nullptr));
        ib_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        i_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Olu\305\237turulan Grafiklerden G\303\266r\303\274nt\303\274le", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
