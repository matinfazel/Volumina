#include "serverconnection.h"
#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QRegExpValidator>
ConnectDialog::ConnectDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    this->server = srv;
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    this->ui->IPEdit->setValidator(ipValidator);
}
ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_Acceptutton_clicked()
{
    QString server_ip = this->ui->IPEdit->text();

    this->ui->label_message->setText("Connecting...");

    int result = server->connectToServer(server_ip);
    if (result < 0) {
        this->ui->label_message->setText("Connection failed.");
    }
    else
    {
        this->ui->label_message->setText("Connected to server.");
        MainWindow * w = new MainWindow(server);
        w->show();
        server = nullptr;
        this->close();
    }
}

void ConnectDialog::on_ExitButton_clicked()
{
    close();
}
