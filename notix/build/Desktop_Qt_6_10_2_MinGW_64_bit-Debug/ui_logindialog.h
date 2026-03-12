/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *userlabel;
    QLineEdit *userEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *passwordlabel;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QLabel *forgetlabel;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *registerbtn;
    QPushButton *loginbtn;
    QLabel *versionlabel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(300, 500);
        Dialog->setMinimumSize(QSize(300, 500));
        Dialog->setMaximumSize(QSize(300, 500));
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(Dialog);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 200));
        widget->setMaximumSize(QSize(16777215, 200));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(200, 200));
        label->setMaximumSize(QSize(200, 200));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Notixhead.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        userlabel = new QLabel(Dialog);
        userlabel->setObjectName("userlabel");
        userlabel->setMinimumSize(QSize(0, 30));
        userlabel->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(userlabel);

        userEdit = new QLineEdit(Dialog);
        userEdit->setObjectName("userEdit");
        userEdit->setMinimumSize(QSize(0, 30));
        userEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(userEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        passwordlabel = new QLabel(Dialog);
        passwordlabel->setObjectName("passwordlabel");
        passwordlabel->setMinimumSize(QSize(0, 30));
        passwordlabel->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(passwordlabel);

        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        forgetlabel = new QLabel(Dialog);
        forgetlabel->setObjectName("forgetlabel");
        forgetlabel->setMinimumSize(QSize(0, 20));
        forgetlabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_6->addWidget(forgetlabel);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        registerbtn = new QPushButton(Dialog);
        registerbtn->setObjectName("registerbtn");
        registerbtn->setMinimumSize(QSize(0, 30));
        registerbtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(registerbtn);

        loginbtn = new QPushButton(Dialog);
        loginbtn->setObjectName("loginbtn");
        loginbtn->setMinimumSize(QSize(0, 30));
        loginbtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(loginbtn);


        verticalLayout->addLayout(horizontalLayout_7);

        versionlabel = new QLabel(Dialog);
        versionlabel->setObjectName("versionlabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Century Gothic")});
        versionlabel->setFont(font);

        verticalLayout->addWidget(versionlabel);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QString());
        userlabel->setText(QCoreApplication::translate("Dialog", "\347\224\250\346\210\267:", nullptr));
        passwordlabel->setText(QCoreApplication::translate("Dialog", "\345\257\206\347\240\201:", nullptr));
        forgetlabel->setText(QCoreApplication::translate("Dialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        registerbtn->setText(QCoreApplication::translate("Dialog", "\346\263\250\345\206\214", nullptr));
        loginbtn->setText(QCoreApplication::translate("Dialog", "\347\231\273\345\275\225", nullptr));
        versionlabel->setText(QCoreApplication::translate("Dialog", "Notix V1.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
