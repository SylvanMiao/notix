/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *errortip;
    QHBoxLayout *horizontalLayout;
    QLabel *userlabel;
    QLineEdit *userlineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *emaillabel;
    QLineEdit *emaillineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *codelabel;
    QLineEdit *codelineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *confirmlabel;
    QLineEdit *confirmlineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *verifylabel;
    QLineEdit *verifylineEdit;
    QPushButton *verifybtn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *confirmbtn;
    QPushButton *cancelbtn;
    QWidget *page_2;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(300, 500);
        RegisterDialog->setMinimumSize(QSize(300, 500));
        RegisterDialog->setMaximumSize(QSize(300, 500));
        verticalLayout_2 = new QVBoxLayout(RegisterDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        errortip = new QLabel(widget);
        errortip->setObjectName("errortip");
        errortip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(errortip);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        userlabel = new QLabel(page);
        userlabel->setObjectName("userlabel");
        userlabel->setMinimumSize(QSize(0, 25));
        userlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(userlabel);

        userlineEdit = new QLineEdit(page);
        userlineEdit->setObjectName("userlineEdit");
        userlineEdit->setMinimumSize(QSize(0, 25));
        userlineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(userlineEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        emaillabel = new QLabel(page);
        emaillabel->setObjectName("emaillabel");
        emaillabel->setMinimumSize(QSize(0, 25));
        emaillabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(emaillabel);

        emaillineEdit = new QLineEdit(page);
        emaillineEdit->setObjectName("emaillineEdit");
        emaillineEdit->setMinimumSize(QSize(0, 25));
        emaillineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(emaillineEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        codelabel = new QLabel(page);
        codelabel->setObjectName("codelabel");
        codelabel->setMinimumSize(QSize(0, 25));
        codelabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(codelabel);

        codelineEdit = new QLineEdit(page);
        codelineEdit->setObjectName("codelineEdit");
        codelineEdit->setMinimumSize(QSize(0, 25));
        codelineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(codelineEdit);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        confirmlabel = new QLabel(page);
        confirmlabel->setObjectName("confirmlabel");
        confirmlabel->setMinimumSize(QSize(0, 25));
        confirmlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(confirmlabel);

        confirmlineEdit = new QLineEdit(page);
        confirmlineEdit->setObjectName("confirmlineEdit");
        confirmlineEdit->setMinimumSize(QSize(0, 25));
        confirmlineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(confirmlineEdit);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verifylabel = new QLabel(page);
        verifylabel->setObjectName("verifylabel");
        verifylabel->setMinimumSize(QSize(0, 25));
        verifylabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verifylabel);

        verifylineEdit = new QLineEdit(page);
        verifylineEdit->setObjectName("verifylineEdit");
        verifylineEdit->setMinimumSize(QSize(0, 25));
        verifylineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verifylineEdit);

        verifybtn = new QPushButton(page);
        verifybtn->setObjectName("verifybtn");
        verifybtn->setMinimumSize(QSize(0, 25));
        verifybtn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verifybtn);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        confirmbtn = new QPushButton(page);
        confirmbtn->setObjectName("confirmbtn");
        confirmbtn->setMinimumSize(QSize(0, 30));
        confirmbtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(confirmbtn);

        cancelbtn = new QPushButton(page);
        cancelbtn->setObjectName("cancelbtn");
        cancelbtn->setMinimumSize(QSize(0, 30));
        cancelbtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(cancelbtn);


        verticalLayout_3->addLayout(horizontalLayout_6);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        errortip->setText(QCoreApplication::translate("RegisterDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        userlabel->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        emaillabel->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        codelabel->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        confirmlabel->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        verifylabel->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        verifybtn->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        confirmbtn->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancelbtn->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
