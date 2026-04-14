#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "ui_logindialog.h"  // 包含生成的UI头文件
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::Dialog *ui;

signals:
    void SwitchRegister();
};

#endif // LOGINDIALOG_H
