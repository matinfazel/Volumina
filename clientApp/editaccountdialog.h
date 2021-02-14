#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include "memberviewdialog.h"
#include "serverconnection.h"
#include "logindialog.h"

namespace Ui {
class EditAccountDialog;
}

class EditAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccountDialog(ServerConnection *, QWidget *parent = nullptr);
    ~EditAccountDialog();
    bool check_first_name();
    bool check_password_name();
    bool check_email_name();
    bool check_address_name();
    bool check_password_confirm();
    bool check_phone_number();



private slots:
    void on_close_button_clicked();

    void on_parent_closed();

    void on_submit_button_clicked();

private:
    Ui::EditAccountDialog *ui;
    ServerConnection * server;
};

#endif // EDITACCOUNTDIALOG_H
