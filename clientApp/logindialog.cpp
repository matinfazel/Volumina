#include "logindialog.h"
#include "ui_logindialog.h"
QJsonObject LoginDialog::cur_user;
LoginDialog::LoginDialog(ServerConnection * srv,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_cancel_button_clicked()
{
    server = nullptr;
    close();
}

void LoginDialog::on_submit_button_clicked()
{
    QJsonObject klass;
    klass.insert("Class", "login");
    klass.insert("Func", "login");
    QJsonObject input;
    input.insert("username", ui->username_line_edit->text());
    input.insert("password", ui->password_line_edit->text());
    klass.insert("Input", input);
    QJsonDocument doc;
    doc.setObject(klass);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            qDebug() << jsonDoc.toJson() << endl;;
            QJsonValue status = jsonDoc.object()["status"];
            if (status.toString() == "201"){
                LoginDialog::cur_user = jsonDoc.object();
                LibrarianWindow * w = new LibrarianWindow(server);
                w->setWindowState(Qt::WindowMaximized);
                w->show();
                w = nullptr;
                emit login();
                close();
            } else {
                this->ui->message_label->setText("Wrong username or password." + status.toString());
            }
        }
        else
        {
            this->ui->message_label->setText("Communication Error.");
        }
    }
    else
    {
        this->ui->message_label->setText("Server is disconnected.");
    }

}

void LoginDialog::on_parent_closed()
{
    close();
}
