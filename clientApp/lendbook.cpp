#include "lendbook.h"
#include "ui_lendbook.h"
#include <QMessageBox>
LendBook::LendBook(ServerConnection * srv, int book_item_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LendBook)
{
    this->book_item_id = book_item_id;
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

LendBook::~LendBook()
{
    delete ui;
}

void LendBook::on_cancel_button_clicked()
{
    close();
}

void LendBook::on_parent_closed()
{
    close();
}

void LendBook::on_lend_button_clicked()
{
    QJsonObject klass;
    klass.insert("Class", "lend");
    klass.insert("Func", "create");
    QJsonObject input;
    input.insert("book_item_id", this->book_item_id);
    input.insert("member_id", this->ui->id_line_edit->text());
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
            int status = jsonDoc.object()["status"].toInt();

            if (status == 201) {
                QMessageBox x;
                x.setText("get the book from librarian!");
                x.show();
                close();
            } else {
                QMessageBox x;
                x.setText("Wrong Member ID!");
                x.show();
            }
        } else {
            QMessageBox x;
            x.setText("Communication Error!");
            x.show();
        }
    } else {
        QMessageBox x;
        x.setText("Connection Error!");
        x.show();
    }
}
