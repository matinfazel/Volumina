#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "serverconnection.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(ServerConnection *, QWidget *parent = nullptr);
    ~ConnectDialog();

private slots:

    void on_ExitButton_clicked();

    void on_Acceptutton_clicked();

private:
    Ui::ConnectDialog *ui;
    ServerConnection * server;
};

#endif // CONNECTDIALOG_H
