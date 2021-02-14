#ifndef LENDDIALOG_H
#define LENDDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include "serverconnection.h"
#include "memberviewdialog.h"

namespace Ui {
class LendDialog;
}

class LendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LendDialog(ServerConnection *, QWidget *parent = nullptr);
    ~LendDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LendDialog * ui;
    ServerConnection * server;
};

#endif // LENDDIALOG_H
