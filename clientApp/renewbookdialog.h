#ifndef RENEWBOOKDIALOG_H
#define RENEWBOOKDIALOG_H

#include <QDialog>
#include "serverconnection.h"

namespace Ui {
class RenewBookDialog;
}

class RenewBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenewBookDialog(ServerConnection *, QWidget *parent = nullptr);
    ~RenewBookDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_parent_closed();

private:
    Ui::RenewBookDialog *ui;
    ServerConnection * server;
};

#endif // RENEWBOOKDIALOG_H
