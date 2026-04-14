#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->registerbtn, &QPushButton::clicked, this, &LoginDialog::SwitchRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
