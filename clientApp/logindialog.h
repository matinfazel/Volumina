#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "serverconnection.h"
#include "librarianwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <memberviewdialog.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    static QJsonObject cur_user;
    explicit LoginDialog(ServerConnection *, QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_submit_button_clicked();

    void on_cancel_button_clicked();

    void on_parent_closed();

private:
    Ui::LoginDialog *ui;
    ServerConnection * server;
signals:
    void login();
};



#endif // LOGINDIALOG_H
