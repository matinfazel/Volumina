#ifndef ADDPENALTYDIALOG_H
#define ADDPENALTYDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include "memberviewdialog.h"
#include "serverconnection.h"

namespace Ui {
class AddPenaltyDialog;
}

class AddPenaltyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPenaltyDialog(ServerConnection *, QWidget *parent = nullptr);
    ~AddPenaltyDialog();

private slots:
    void on_cancel_button_clicked();
    void on_parent_closed();

    void on_add_button_clicked();

private:
    Ui::AddPenaltyDialog *ui;
    ServerConnection * server;
signals:
    void penaltyupdate();
};

#endif // ADDPENALTYDIALOG_H
