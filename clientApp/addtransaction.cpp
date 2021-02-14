#include "addtransaction.h"
#include "ui_addtransaction.h"

QJsonObject MemberViewDialog::member;
QJsonObject MemberViewDialog::lend;


AddTransaction::AddTransaction(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransaction)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

AddTransaction::~AddTransaction()
{
    delete ui;
}

void AddTransaction::on_pushButton_clicked()
{
    close();
}

void AddTransaction::on_parent_closed()
{
    close();
}

void AddTransaction::on_pushButton_2_clicked()
{
    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;
    parameter.insert("penalty", QString::number(ui->spinBox->value()));
    parameter.insert("account_id", MemberViewDialog::member.value("account_id"));
    out.insert("Class", "Member");
    out.insert("Func", "addPayment");
    out.insert("Input", parameter);
    doc.setObject(out);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QJsonValue status = jsonDoc.object()["status"];
            qDebug() << status.toInt() << endl;
            if (status.toInt() == 201){
                MemberViewDialog::member.value("penalty") =
                        QString::number(
                            MemberViewDialog::member.value("penalty").toInt()
                            - ui->spinBox->value());
                this->ui->msg_label->setText("Payment added.");
                emit penaltyupdate();
                close();
            } else {
                this->ui->msg_label->setText("Could not add payment.");
            }
        }
        else
        {
            this->ui->msg_label->setText("Communication Error.");
        }
    }
    else
    {
        this->ui->msg_label->setText("Server is disconnected.");
    }
}
