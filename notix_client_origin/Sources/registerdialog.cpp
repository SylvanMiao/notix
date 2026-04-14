#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QRegularExpression>
#include "HttpMgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->codelineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmlineEdit->setEchoMode(QLineEdit::Password);

    ui->errortip->setProperty("state", "normal");
    repolish(ui->errortip);

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_verifybtn_clicked()
{
    // stannnnis@163.com
    auto email = ui ->emaillineEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();

    if (match){

    }else{
        ShowTip(tr("邮箱格式不正确"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCode err)
{
    if (err != ErrorCode::SUCCESS){
        ShowTip(tr("网络请求错误"),false);
        return;
    }
    // 解析JSON字符串， res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()){
        ShowTip(tr("json解析失败"), false);
        return;
    }
    // json 解析错误
    if (!jsonDoc.isObject()){
        ShowTip(tr("json解析格式错误"), false);
        return;
    }

    // 解析成功回调
    _handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::ShowTip(QString str, bool b_ok)
{
    if (b_ok){
        ui->errortip->setProperty("state","normal");
    }else{
        ui->errortip->setProperty("state","err");
    }
    ui->errortip->setText(str);
    repolish(ui->errortip);
}

// 回调函数初始化
void RegisterDialog::initHttpHandlers()
{
    // 注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if (error != ErrorCode::SUCCESS){
            ShowTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        ShowTip(tr("验证码已经发送到邮箱"), true);
        qDebug() << "email is " << email;
    });

}

