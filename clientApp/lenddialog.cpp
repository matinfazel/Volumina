#include "lenddialog.h"
#include "ui_lenddialog.h"

LendDialog::LendDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LendDialog)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SIGNAL(on_parent_closed()));
}

LendDialog::~LendDialog()
{
    delete ui;
}

void LendDialog::on_pushButton_clicked()
{
    QJsonObject out;
    QJsonDocument doc;
    QJsonObject parameter;
    parameter.insert("book_item_id", ui->isbn_line_edit->text());
    parameter.insert("member_id", MemberViewDialog::member.value("member_id"));
    out.insert("Class", "Lend");
    out.insert("Func", "Create");
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
            qDebug() << status.toString() << endl;
            if (status.toString() == "201"){
               this->ui->msg_label->setText("Book lended.");
                close();
            } else {
                this->ui->msg_label->setText("Could not lend this book.");
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

void LendDialog::on_pushButton_2_clicked()
{
    close();
}
