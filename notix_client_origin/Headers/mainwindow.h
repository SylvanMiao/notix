#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
/***************************************************************
 * Copyright (c) 2026 miaoye
 *
 * 文件名:    mainwindow.h
 * 功能描述:   主窗口
 *
 * 作者:      miaoye
 * 版本号:     1.0.0
 *
 * 修改历史:
 * 版本号  日期       作者    修改内容
 * ------  ---------- ------- --------------------------------
 * 1.0.0   2026-02-24 miaoye  初始版本创建
 *
 **************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchRegister();
private:
    Ui::MainWindow *ui;
    LoginDialog* _login;
    RegisterDialog* _register;
};
#endif // MAINWINDOW_H
