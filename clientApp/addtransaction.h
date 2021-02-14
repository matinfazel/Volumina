#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include "memberviewdialog.h"
#include "serverconnection.h"

namespace Ui {
class AddTransaction;
}

class AddTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit AddTransaction(ServerConnection *, QWidget *parent = nullptr);
    ~AddTransaction();

private slots:
    void on_pushButton_clicked();

    void on_parent_closed();

    void on_pushButton_2_clicked();

private:
    Ui::AddTransaction *ui;
    ServerConnection * server;
signals:
    void penaltyupdate();
};

#endif // ADDTRANSACTION_H
