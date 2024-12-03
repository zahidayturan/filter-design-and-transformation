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
    QVBoxLayout *input_d;
    QLabel *label_d;
    QLineEdit *edit_d;
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
    QVBoxLayout *output_menu;
    QVBoxLayout *b_output;
    QHBoxLayout *b_labels;
    QLabel *b_title;
    QLabel *b_info;
    QHBoxLayout *b_actives;
    QRadioButton *bl_active;
    QRadioButton *bh_active;
    QRadioButton *bb_active;
    QHBoxLayout *b_buttons;
    QPushButton *b_create;
    QPushButton *b_open;
    QVBoxLayout *c_output;
    QHBoxLayout *c_labels;
    QLabel *c_title;
    QLabel *c_info;
    QHBoxLayout *c_actives;
    QRadioButton *cl_active;
    QRadioButton *ch_active;
    QRadioButton *cb_active;
    QHBoxLayout *c_buttons;
    QPushButton *c_create;
    QPushButton *c_open;
    QVBoxLayout *i_output;
    QHBoxLayout *i_labels;
    QLabel *i_title;
    QLabel *i_info;
    QHBoxLayout *i_actives;
    QRadioButton *il_active;
    QRadioButton *ih_active;
    QRadioButton *ib_active;
    QHBoxLayout *i_buttons;
    QPushButton *i_create;
    QPushButton *i_open;
    QComboBox *comboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1160, 639);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 42, 41);\n"
"font: 10pt \"Montserrat\";\n"
"color: rgb(246, 246, 246);"));
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
"color: rgb(246, 246, 246);"));

        app_bar->addWidget(title);

        reload = new QPushButton(main_widget);
        reload->setObjectName("reload");
        sizePolicy.setHeightForWidth(reload->sizePolicy().hasHeightForWidth());
        reload->setSizePolicy(sizePolicy);
        reload->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 22, 22);\n"
"border-radius: 4px;\n"
"padding: 4px 8px;"));
        reload->setAutoDefault(false);
        reload->setFlat(false);

        app_bar->addWidget(reload);


        main_vertical->addLayout(app_bar);

        app_menu = new QHBoxLayout();
        app_menu->setSpacing(72);
        app_menu->setObjectName("app_menu");
        app_menu->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        input_menu = new QVBoxLayout();
        input_menu->setSpacing(12);
        input_menu->setObjectName("input_menu");
        input_menu->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        input_menu->setContentsMargins(-1, 0, -1, 0);
        input_d = new QVBoxLayout();
        input_d->setSpacing(4);
        input_d->setObjectName("input_d");
        input_d->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        input_d->setContentsMargins(-1, -1, -1, 0);
        label_d = new QLabel(main_widget);
        label_d->setObjectName("label_d");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_d->sizePolicy().hasHeightForWidth());
        label_d->setSizePolicy(sizePolicy1);
        label_d->setMaximumSize(QSize(380, 16777215));

        input_d->addWidget(label_d);

        edit_d = new QLineEdit(main_widget);
        edit_d->setObjectName("edit_d");
        edit_d->setMaximumSize(QSize(380, 16777215));
        edit_d->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_d->setClearButtonEnabled(true);

        input_d->addWidget(edit_d);


        input_menu->addLayout(input_d);

        input_lpf = new QVBoxLayout();
        input_lpf->setSpacing(4);
        input_lpf->setObjectName("input_lpf");
        input_lpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_lpf = new QLabel(main_widget);
        label_lpf->setObjectName("label_lpf");
        label_lpf->setMaximumSize(QSize(380, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Montserrat")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        label_lpf->setFont(font);

        input_lpf->addWidget(label_lpf);

        edit_lpf = new QLineEdit(main_widget);
        edit_lpf->setObjectName("edit_lpf");
        edit_lpf->setMaximumSize(QSize(380, 16777215));
        edit_lpf->setAutoFillBackground(false);
        edit_lpf->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_lpf->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        edit_lpf->setFrame(true);
        edit_lpf->setClearButtonEnabled(true);

        input_lpf->addWidget(edit_lpf);


        input_menu->addLayout(input_lpf);

        input_hpf = new QVBoxLayout();
        input_hpf->setSpacing(4);
        input_hpf->setObjectName("input_hpf");
        input_hpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_hpf = new QLabel(main_widget);
        label_hpf->setObjectName("label_hpf");
        label_hpf->setMaximumSize(QSize(380, 16777215));

        input_hpf->addWidget(label_hpf);

        edit_hpf = new QLineEdit(main_widget);
        edit_hpf->setObjectName("edit_hpf");
        edit_hpf->setMinimumSize(QSize(0, 0));
        edit_hpf->setMaximumSize(QSize(380, 16777215));
        edit_hpf->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_hpf->setClearButtonEnabled(true);

        input_hpf->addWidget(edit_hpf);


        input_menu->addLayout(input_hpf);

        input_bpf = new QVBoxLayout();
        input_bpf->setSpacing(4);
        input_bpf->setObjectName("input_bpf");
        input_bpf->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_bpf = new QLabel(main_widget);
        label_bpf->setObjectName("label_bpf");
        label_bpf->setMaximumSize(QSize(380, 16777215));

        input_bpf->addWidget(label_bpf);

        edit_bpf = new QLineEdit(main_widget);
        edit_bpf->setObjectName("edit_bpf");
        edit_bpf->setMaximumSize(QSize(380, 16777215));
        edit_bpf->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_bpf->setClearButtonEnabled(true);

        input_bpf->addWidget(edit_bpf);


        input_menu->addLayout(input_bpf);

        input_bw = new QVBoxLayout();
        input_bw->setSpacing(4);
        input_bw->setObjectName("input_bw");
        input_bw->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_bw = new QLabel(main_widget);
        label_bw->setObjectName("label_bw");
        label_bw->setMaximumSize(QSize(380, 16777215));

        input_bw->addWidget(label_bw);

        edit_bw = new QLineEdit(main_widget);
        edit_bw->setObjectName("edit_bw");
        edit_bw->setMaximumSize(QSize(380, 16777215));
        edit_bw->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_bw->setClearButtonEnabled(true);

        input_bw->addWidget(edit_bw);


        input_menu->addLayout(input_bw);

        input_c = new QVBoxLayout();
        input_c->setSpacing(4);
        input_c->setObjectName("input_c");
        input_c->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_c = new QLabel(main_widget);
        label_c->setObjectName("label_c");
        label_c->setMaximumSize(QSize(380, 16777215));

        input_c->addWidget(label_c);

        edit_c = new QLineEdit(main_widget);
        edit_c->setObjectName("edit_c");
        edit_c->setMaximumSize(QSize(380, 16777215));
        edit_c->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        edit_c->setClearButtonEnabled(true);

        input_c->addWidget(edit_c);


        input_menu->addLayout(input_c);

        input_i = new QVBoxLayout();
        input_i->setSpacing(4);
        input_i->setObjectName("input_i");
        input_i->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_i = new QLabel(main_widget);
        label_i->setObjectName("label_i");
        label_i->setMaximumSize(QSize(380, 16777215));

        input_i->addWidget(label_i);

        line_i = new QLineEdit(main_widget);
        line_i->setObjectName("line_i");
        line_i->setMaximumSize(QSize(380, 16777215));
        line_i->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid  rgb(241, 249, 250);\n"
"padding: 2px;\n"
"border-radius: 0px;"));
        line_i->setClearButtonEnabled(true);

        input_i->addWidget(line_i);


        input_menu->addLayout(input_i);


        app_menu->addLayout(input_menu);

        output_menu = new QVBoxLayout();
        output_menu->setSpacing(34);
        output_menu->setObjectName("output_menu");
        output_menu->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        b_output = new QVBoxLayout();
        b_output->setSpacing(4);
        b_output->setObjectName("b_output");
        b_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        b_labels = new QHBoxLayout();
        b_labels->setObjectName("b_labels");
        b_title = new QLabel(main_widget);
        b_title->setObjectName("b_title");
        sizePolicy1.setHeightForWidth(b_title->sizePolicy().hasHeightForWidth());
        b_title->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat Black")});
        font1.setPointSize(11);
        font1.setWeight(QFont::Black);
        font1.setItalic(false);
        b_title->setFont(font1);
        b_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        b_labels->addWidget(b_title);

        b_info = new QLabel(main_widget);
        b_info->setObjectName("b_info");
        sizePolicy.setHeightForWidth(b_info->sizePolicy().hasHeightForWidth());
        b_info->setSizePolicy(sizePolicy);
        b_info->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        b_info->setStyleSheet(QString::fromUtf8("font: italic 9pt \"Montserrat\";\n"
"color: red;"));

        b_labels->addWidget(b_info);


        b_output->addLayout(b_labels);

        b_actives = new QHBoxLayout();
        b_actives->setSpacing(14);
        b_actives->setObjectName("b_actives");
        b_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        bl_active = new QRadioButton(main_widget);
        bl_active->setObjectName("bl_active");
        bl_active->setEnabled(false);
        bl_active->setAcceptDrops(false);
        bl_active->setAutoFillBackground(false);
        bl_active->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 170, 0);"));
        bl_active->setCheckable(false);
        bl_active->setChecked(false);
        bl_active->setAutoRepeat(false);
        bl_active->setAutoExclusive(false);

        b_actives->addWidget(bl_active);

        bh_active = new QRadioButton(main_widget);
        bh_active->setObjectName("bh_active");
        bh_active->setEnabled(false);
        bh_active->setCheckable(false);
        bh_active->setChecked(false);
        bh_active->setAutoRepeat(false);
        bh_active->setAutoExclusive(false);

        b_actives->addWidget(bh_active);

        bb_active = new QRadioButton(main_widget);
        bb_active->setObjectName("bb_active");
        bb_active->setEnabled(false);
        bb_active->setStyleSheet(QString::fromUtf8("font: 10pt \"Montserrat\";"));
        bb_active->setCheckable(false);
        bb_active->setChecked(false);
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
        b_create->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 119, 115);\n"
"border-radius: 8px;\n"
"padding: 8px;"));

        b_buttons->addWidget(b_create);

        b_open = new QPushButton(main_widget);
        b_open->setObjectName("b_open");
        b_open->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(b_open->sizePolicy().hasHeightForWidth());
        b_open->setSizePolicy(sizePolicy2);
        b_open->setStyleSheet(QString::fromUtf8("background-color: rgb(50, 178, 31);\n"
"border-radius: 8px;\n"
"padding: 8px;"));
        b_open->setCheckable(false);

        b_buttons->addWidget(b_open);


        b_output->addLayout(b_buttons);


        output_menu->addLayout(b_output);

        c_output = new QVBoxLayout();
        c_output->setSpacing(4);
        c_output->setObjectName("c_output");
        c_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        c_labels = new QHBoxLayout();
        c_labels->setObjectName("c_labels");
        c_title = new QLabel(main_widget);
        c_title->setObjectName("c_title");
        sizePolicy1.setHeightForWidth(c_title->sizePolicy().hasHeightForWidth());
        c_title->setSizePolicy(sizePolicy1);
        c_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        c_labels->addWidget(c_title);

        c_info = new QLabel(main_widget);
        c_info->setObjectName("c_info");
        sizePolicy.setHeightForWidth(c_info->sizePolicy().hasHeightForWidth());
        c_info->setSizePolicy(sizePolicy);
        c_info->setStyleSheet(QString::fromUtf8("font: italic 9pt \"Montserrat\";\n"
"color: red;"));

        c_labels->addWidget(c_info);


        c_output->addLayout(c_labels);

        c_actives = new QHBoxLayout();
        c_actives->setSpacing(14);
        c_actives->setObjectName("c_actives");
        c_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        cl_active = new QRadioButton(main_widget);
        cl_active->setObjectName("cl_active");
        cl_active->setEnabled(false);
        cl_active->setCheckable(false);
        cl_active->setChecked(false);
        cl_active->setAutoExclusive(false);

        c_actives->addWidget(cl_active);

        ch_active = new QRadioButton(main_widget);
        ch_active->setObjectName("ch_active");
        ch_active->setEnabled(false);
        ch_active->setCheckable(false);
        ch_active->setChecked(false);
        ch_active->setAutoExclusive(false);

        c_actives->addWidget(ch_active);

        cb_active = new QRadioButton(main_widget);
        cb_active->setObjectName("cb_active");
        cb_active->setEnabled(false);
        cb_active->setCheckable(false);
        cb_active->setChecked(false);
        cb_active->setAutoExclusive(false);

        c_actives->addWidget(cb_active);


        c_output->addLayout(c_actives);

        c_buttons = new QHBoxLayout();
        c_buttons->setSpacing(10);
        c_buttons->setObjectName("c_buttons");
        c_buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        c_create = new QPushButton(main_widget);
        c_create->setObjectName("c_create");
        c_create->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 119, 115);\n"
"border-radius: 8px;\n"
"padding: 8px;"));

        c_buttons->addWidget(c_create);

        c_open = new QPushButton(main_widget);
        c_open->setObjectName("c_open");
        c_open->setStyleSheet(QString::fromUtf8("background-color: rgb(50, 178, 31);\n"
"border-radius: 8px;\n"
"padding: 8px;"));

        c_buttons->addWidget(c_open);


        c_output->addLayout(c_buttons);


        output_menu->addLayout(c_output);

        i_output = new QVBoxLayout();
        i_output->setSpacing(4);
        i_output->setObjectName("i_output");
        i_output->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        i_labels = new QHBoxLayout();
        i_labels->setObjectName("i_labels");
        i_title = new QLabel(main_widget);
        i_title->setObjectName("i_title");
        sizePolicy1.setHeightForWidth(i_title->sizePolicy().hasHeightForWidth());
        i_title->setSizePolicy(sizePolicy1);
        i_title->setStyleSheet(QString::fromUtf8("font: 900 11pt \"Montserrat Black\";"));

        i_labels->addWidget(i_title);

        i_info = new QLabel(main_widget);
        i_info->setObjectName("i_info");
        sizePolicy.setHeightForWidth(i_info->sizePolicy().hasHeightForWidth());
        i_info->setSizePolicy(sizePolicy);
        i_info->setStyleSheet(QString::fromUtf8("font: italic 9pt \"Montserrat\";\n"
"color: red;"));

        i_labels->addWidget(i_info);


        i_output->addLayout(i_labels);

        i_actives = new QHBoxLayout();
        i_actives->setSpacing(14);
        i_actives->setObjectName("i_actives");
        i_actives->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        il_active = new QRadioButton(main_widget);
        il_active->setObjectName("il_active");
        il_active->setEnabled(false);
        il_active->setCheckable(false);
        il_active->setChecked(false);
        il_active->setAutoExclusive(false);

        i_actives->addWidget(il_active);

        ih_active = new QRadioButton(main_widget);
        ih_active->setObjectName("ih_active");
        ih_active->setEnabled(false);
        ih_active->setCheckable(false);
        ih_active->setChecked(false);
        ih_active->setAutoExclusive(false);

        i_actives->addWidget(ih_active);

        ib_active = new QRadioButton(main_widget);
        ib_active->setObjectName("ib_active");
        ib_active->setEnabled(false);
        ib_active->setCheckable(false);
        ib_active->setChecked(false);
        ib_active->setAutoExclusive(false);

        i_actives->addWidget(ib_active);


        i_output->addLayout(i_actives);

        i_buttons = new QHBoxLayout();
        i_buttons->setSpacing(10);
        i_buttons->setObjectName("i_buttons");
        i_buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        i_create = new QPushButton(main_widget);
        i_create->setObjectName("i_create");
        i_create->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 119, 115);\n"
"border-radius: 8px;\n"
"padding: 8px;"));

        i_buttons->addWidget(i_create);

        i_open = new QPushButton(main_widget);
        i_open->setObjectName("i_open");
        i_open->setStyleSheet(QString::fromUtf8("background-color: rgb(50, 178, 31);\n"
"border-radius: 8px;\n"
"padding: 8px;"));

        i_buttons->addWidget(i_open);


        i_output->addLayout(i_buttons);


        output_menu->addLayout(i_output);

        comboBox = new QComboBox(main_widget);
        comboBox->setObjectName("comboBox");
        comboBox->setStyleSheet(QString::fromUtf8("font: 10pt \"Montserrat\";\n"
"border-radius: 8px;\n"
"padding: 8px;\n"
"background-color: rgb(0, 22, 22);\n"
""));
        comboBox->setDuplicatesEnabled(false);

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
        label_d->setText(QCoreApplication::translate("MainWindow", "Filtre Derecesi", nullptr));
        edit_d->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        edit_d->setPlaceholderText(QCoreApplication::translate("MainWindow", "Filtre Derecesi", nullptr));
        label_lpf->setText(QCoreApplication::translate("MainWindow", "LPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        edit_lpf->setText(QCoreApplication::translate("MainWindow", "340", nullptr));
        edit_lpf->setPlaceholderText(QCoreApplication::translate("MainWindow", "LPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        label_hpf->setText(QCoreApplication::translate("MainWindow", "HPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        edit_hpf->setText(QCoreApplication::translate("MainWindow", "130", nullptr));
        edit_hpf->setPlaceholderText(QCoreApplication::translate("MainWindow", "HPF K\303\266\305\237e Frekans\304\261 (\317\211p) rad/s", nullptr));
        label_bpf->setText(QCoreApplication::translate("MainWindow", "BPF Merkez Frekans\304\261 (\317\211C)  rad/s", nullptr));
        edit_bpf->setText(QCoreApplication::translate("MainWindow", "310", nullptr));
        edit_bpf->setPlaceholderText(QCoreApplication::translate("MainWindow", "BPF Merkez Frekans\304\261 (\317\211C)  rad/s", nullptr));
        label_bw->setText(QCoreApplication::translate("MainWindow", "Band Aral\304\261klar\304\261 (BW) rad/s", nullptr));
        edit_bw->setText(QCoreApplication::translate("MainWindow", "95", nullptr));
        edit_bw->setPlaceholderText(QCoreApplication::translate("MainWindow", "Band Aral\304\261klar\304\261 (BW) rad/s", nullptr));
        label_c->setText(QCoreApplication::translate("MainWindow", "Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        edit_c->setText(QCoreApplication::translate("MainWindow", "0.12", nullptr));
        edit_c->setPlaceholderText(QCoreApplication::translate("MainWindow", "Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        label_i->setText(QCoreApplication::translate("MainWindow", "Ters Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        line_i->setText(QCoreApplication::translate("MainWindow", "0.19", nullptr));
        line_i->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ters Chebyshev Filtre Sal\304\261n\304\261m Aral\304\261\304\237\304\261 (\316\265)", nullptr));
        b_title->setText(QCoreApplication::translate("MainWindow", "Butterworth", nullptr));
        b_info->setText(QCoreApplication::translate("MainWindow", "grafikler olu\305\237turulmam\304\261\305\237", nullptr));
        bl_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Ge\303\247iren Filtre", nullptr));
        bh_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Ge\303\247iren Filtre", nullptr));
        bb_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        b_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
        b_open->setText(QCoreApplication::translate("MainWindow", "Grafikleri G\303\266r\303\274nt\303\274le", nullptr));
        c_title->setText(QCoreApplication::translate("MainWindow", "Chebyshev", nullptr));
        c_info->setText(QCoreApplication::translate("MainWindow", "grafikler olu\305\237turulmam\304\261\305\237", nullptr));
        cl_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Ge\303\247iren Filtre", nullptr));
        ch_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Ge\303\247iren Filtre", nullptr));
        cb_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        c_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
        c_open->setText(QCoreApplication::translate("MainWindow", "Grafikleri G\303\266r\303\274nt\303\274le", nullptr));
        i_title->setText(QCoreApplication::translate("MainWindow", "Ters Chebyshev", nullptr));
        i_info->setText(QCoreApplication::translate("MainWindow", "grafikler olu\305\237turulmam\304\261\305\237", nullptr));
        il_active->setText(QCoreApplication::translate("MainWindow", "Al\303\247ak Ge\303\247iren Filtre", nullptr));
        ih_active->setText(QCoreApplication::translate("MainWindow", "Y\303\274ksek Ge\303\247iren Filtre", nullptr));
        ib_active->setText(QCoreApplication::translate("MainWindow", "Band Ge\303\247iren Filtre", nullptr));
        i_create->setText(QCoreApplication::translate("MainWindow", "Grafikleri Olu\305\237tur", nullptr));
        i_open->setText(QCoreApplication::translate("MainWindow", "Grafikleri G\303\266r\303\274nt\303\274le", nullptr));
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
