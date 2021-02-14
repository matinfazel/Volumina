#ifndef RENEWMEMBERDIALOG_H
#define RENEWMEMBERDIALOG_H

#include <QDialog>
#include "serverconnection.h"

namespace Ui {
class RenewMemberDialog;
}

class RenewMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenewMemberDialog(ServerConnection *, QWidget *parent = nullptr);
    ~RenewMemberDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_parent_closed();

private:
    Ui::RenewMemberDialog *ui;
    ServerConnection * server;
};

#endif // RENEWMEMBERDIALOG_H
