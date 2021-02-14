#include "addpenaltydialog.h"
#include "ui_addpenaltydialog.h"

AddPenaltyDialog::AddPenaltyDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPenaltyDialog)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

AddPenaltyDialog::~AddPenaltyDialog()
{
    delete ui;
}

void AddPenaltyDialog::on_cancel_button_clicked()
{
    close();
}

void AddPenaltyDialog::on_parent_closed()
{
    close();
}

void AddPenaltyDialog::on_add_button_clicked()
{
    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;
    parameter.insert("penalty", QString::number(ui->fee_spin_box->value()));
    parameter.insert("account_id", MemberViewDialog::member.value("account_id"));
    out.insert("Class", "Member");
    out.insert("Func", "addPenalty");
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
                            + ui->fee_spin_box->value());
                qDebug() << MemberViewDialog::member.value("penalty") << endl;
                this->ui->msg_label->setText("Penalty added.");
                emit penaltyupdate();
                close();
            } else {
                this->ui->msg_label->setText("Could not add penalty.");
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
