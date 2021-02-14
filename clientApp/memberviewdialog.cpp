#include "memberviewdialog.h"
#include "ui_memberviewdialog.h"

MemberViewDialog::MemberViewDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberViewDialog)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));

    ui->renew_book_button->setEnabled(false);
    ui->return_button->setEnabled(false);

    ui->first_name_line_edit->setText(MemberViewDialog::member.value("name").toString());
    ui->last_name_line_edit->setText(MemberViewDialog::member.value("account_id").toString());
    ui->phone_line_edit->setText(MemberViewDialog::member.value("phone_number").toString());
    ui->email_line_edit->setText(MemberViewDialog::member.value("email").toString());
    ui->address_line_edit->setText(MemberViewDialog::member.value("address").toString());
    ui->penalty_line_edit->setText(MemberViewDialog::member.value("penalty").toString());


    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;

    parameter.insert("member_id", MemberViewDialog::member.value("member_id").toString());
    out.insert("Class", "Lend");
    out.insert("Func", "searchByMember");
    out.insert("Input", parameter);
    doc.setObject(out);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QJsonArray lendlist = jsonDoc.array();
            for (int i = 0; i < lendlist.size(); i++){
                QJsonObject lenditem = lendlist[i].toObject();
                if (lenditem.value("return_date").toString() == "lended"){

                    QJsonObject ex_out;
                    QJsonObject ex_parameter;
                    QJsonDocument ex_doc;

                    ex_parameter.insert("book_item_id", lenditem.value("book_item_id").toString());

                    ex_out.insert("Class", "BookItem");
                    ex_out.insert("Func", "readById");
                    ex_out.insert("Input", ex_parameter);

                    ex_doc.setObject(ex_out);
                    msg = ex_doc.toJson();

                    server->write(msg);
                    server->flush();
                    server->waitForBytesWritten();
                    server->waitForReadyRead();
                    QByteArray ex_ret = server->readAll();
                    QJsonDocument ex_jsonDoc = QJsonDocument::fromJson(ex_ret);
                    QString ex_book_id = ex_jsonDoc.array()[0].toObject().value("book_id").toString();




                    QJsonObject fgt_out;
                    QJsonObject fgt_parameter;
                    QJsonDocument fgt_doc;

                    fgt_parameter.insert("Id", ex_book_id);

                    fgt_out.insert("Class", "Book");
                    fgt_out.insert("Func", "searchById");
                    fgt_out.insert("Input", fgt_parameter);

                    fgt_doc.setObject(fgt_out);
                    msg = fgt_doc.toJson();

                    server->write(msg);
                    server->flush();
                    server->waitForBytesWritten();
                    server->waitForReadyRead();
                    QByteArray fgt_ret = server->readAll();
                    QJsonDocument fgt_jsonDoc = QJsonDocument::fromJson(fgt_ret);
                    QJsonObject bookres = fgt_jsonDoc.array()[0].toObject();
                    QString book_name = bookres.value("title").toString();


                    lenditem.insert("title", book_name);
                    result_lendlist.append(lenditem);
                }
            }




            ui->borrow_table->setRowCount(result_lendlist.size());



            for (int i = 0; i < result_lendlist.size(); i++){
                ui->borrow_table->setItem(i, 0, new QTableWidgetItem(QString::number(result_lendlist[i].toObject().value("lend_id").toInt())));
                ui->borrow_table->setItem(i, 1, new QTableWidgetItem(result_lendlist[i].toObject().value("title").toString()));
                ui->borrow_table->setItem(i, 2, new QTableWidgetItem(result_lendlist[i].toObject().value("loan_date").toString()));
                ui->borrow_table->setItem(i, 3, new QTableWidgetItem(result_lendlist[i].toObject().value("renew_times").toString()));
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

MemberViewDialog::~MemberViewDialog()
{
    delete ui;
}

void MemberViewDialog::on_close_button_clicked()
{
    close();
}

void MemberViewDialog::on_lend_button_clicked()
{
    SearchLendDialog * w = new SearchLendDialog(server, this);
    connect(w, SIGNAL(refresh_that()), this, SLOT(refresh_lend()));
    w->show();
}

void MemberViewDialog::on_renew_member_button_clicked()
{
    QJsonObject out;
    QJsonDocument doc;

    out.insert("Class", "Member");
    out.insert("Func", "renew");
    out.insert("Input", MemberViewDialog::member);
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
               this->ui->msg_label->setText("Member renewed.");


            } else {
                this->ui->msg_label->setText("Membership renewal failed.");
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

void MemberViewDialog::on_add_transaction_button_clicked()
{
    AddTransaction * w = new AddTransaction(server, this);
    connect(w, SIGNAL(penaltyupdate()), this, SLOT(update_penalty()));
    w->show();
}

void MemberViewDialog::on_MemberViewDialog_destroyed()
{
    emit closed();
}

void MemberViewDialog::on_add_penalty_button_clicked()
{
    AddPenaltyDialog * w = new AddPenaltyDialog(server, this);
    connect(w, SIGNAL(penaltyupdate()), this, SLOT(update_penalty()));
    w->show();
}

void MemberViewDialog::on_renew_book_button_clicked()
{
    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;
    parameter.insert("lend_id", MemberViewDialog::lend.value("lend_id"));
    QString newnum = QString::number(ui->borrow_table->item(MemberViewDialog::lend.value("index").toInt(), 3)->text().toInt() + 1);
    parameter.insert("renew_times", ui->borrow_table->item(MemberViewDialog::lend.value("index").toInt(), 3)->text());

    out.insert("Class", "Lend");
    out.insert("Func", "renew");
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
               this->ui->msg_label->setText("Book renewed.");

                ui->borrow_table->setItem(MemberViewDialog::lend.value("index").toInt(), 3, new QTableWidgetItem(newnum));

                ui->renew_book_button->setEnabled(false);
                ui->return_button->setEnabled(false);

            } else {
                this->ui->msg_label->setText("This book was renewed too many times.");
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

void MemberViewDialog::on_return_button_clicked()
{
    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;
    parameter.insert("lend_id", MemberViewDialog::lend.value("lend_id"));
    parameter.insert("renew_times", MemberViewDialog::lend.value("renew_times"));
    parameter.insert("book_item_id", MemberViewDialog::lend.value("book_item_id"));
    out.insert("Class", "Lend");
    out.insert("Func", "return");
    out.insert("Input", parameter);
    doc.setObject(out);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(5000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QJsonValue status = jsonDoc.object()["status"];
            qDebug() << status.toInt() << endl;
            if (status.toInt() == 201){
               this->ui->msg_label->setText("The book is returned.");
               this->ui->borrow_table->removeRow(MemberViewDialog::lend.value("index").toInt());

                ui->renew_book_button->setEnabled(false);
                ui->return_button->setEnabled(false);

            } else {
                this->ui->msg_label->setText("This lend is no longer valid.");
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

void MemberViewDialog::on_update_button_clicked()
{
//    repo.updateMember(json["account_id"].toString(), json["email"].toString(),
//            json["address"].toString(), json["phone_number"].toString(),
//            json["card_number"].toString());

    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;
    parameter.insert("account_id", MemberViewDialog::member.value("account_id"));
    parameter.insert("name", ui->first_name_line_edit->text());
    parameter.insert("email", ui->email_line_edit->text());
    parameter.insert("address", ui->address_line_edit->text());
    parameter.insert("phone_number", ui->phone_line_edit->text());
    parameter.insert("card_number", MemberViewDialog::member.value("card_number"));
    parameter.insert("penalty", ui->penalty_line_edit->text());
    out.insert("Class", "Member");
    out.insert("Func", "update");
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
               this->ui->msg_label->setText("Member info were updated.");
            } else {
                this->ui->msg_label->setText("Could not update member data.");
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

void MemberViewDialog::on_borrow_table_cellClicked(int row, int column)
{
    ui->renew_book_button->setEnabled(true);
    ui->return_button->setEnabled(true);
    QJsonObject lend_select;
    lend_select.insert("lend_id", ui->borrow_table->item(row, 0)->text());
    lend_select.insert("title", ui->borrow_table->item(row, 1)->text());
    lend_select.insert("loan_date", ui->borrow_table->item(row, 2)->text());
    lend_select.insert("renew_times", ui->borrow_table->item(row, 3)->text());

    MemberViewDialog::lend = lend_select;
    MemberViewDialog::lend.insert("book_item_id", result_lendlist[row].toObject()["book_item_id"].toString());
    MemberViewDialog::lend.insert("index", row);
}

void MemberViewDialog::refresh_lend()
{
    QJsonObject out;
    QJsonObject parameter;
    QJsonDocument doc;

    result_lendlist = QJsonArray();

    parameter.insert("member_id", MemberViewDialog::member.value("member_id").toString());
    out.insert("Class", "Lend");
    out.insert("Func", "searchByMember");
    out.insert("Input", parameter);
    doc.setObject(out);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QJsonArray lendlist = jsonDoc.array();
            for (int i = 0; i < lendlist.size(); i++){
                QJsonObject lenditem = lendlist[i].toObject();
                if (lenditem.value("return_date").toString() == "lended"){

                    QJsonObject ex_out;
                    QJsonObject ex_parameter;
                    QJsonDocument ex_doc;

                    ex_parameter.insert("book_item_id", lenditem.value("book_item_id").toString());

                    ex_out.insert("Class", "BookItem");
                    ex_out.insert("Func", "readById");
                    ex_out.insert("Input", ex_parameter);

                    ex_doc.setObject(ex_out);
                    msg = ex_doc.toJson();

                    server->write(msg);
                    server->flush();
                    server->waitForBytesWritten();
                    server->waitForReadyRead();
                    QByteArray ex_ret = server->readAll();
                    QJsonDocument ex_jsonDoc = QJsonDocument::fromJson(ex_ret);
                    QString ex_book_id = ex_jsonDoc.array()[0].toObject().value("book_id").toString();




                    QJsonObject fgt_out;
                    QJsonObject fgt_parameter;
                    QJsonDocument fgt_doc;

                    fgt_parameter.insert("Id", ex_book_id);

                    fgt_out.insert("Class", "Book");
                    fgt_out.insert("Func", "searchById");
                    fgt_out.insert("Input", fgt_parameter);

                    fgt_doc.setObject(fgt_out);
                    msg = fgt_doc.toJson();

                    server->write(msg);
                    server->flush();
                    server->waitForBytesWritten();
                    server->waitForReadyRead();
                    QByteArray fgt_ret = server->readAll();
                    QJsonDocument fgt_jsonDoc = QJsonDocument::fromJson(fgt_ret);
                    QJsonObject bookres = fgt_jsonDoc.array()[0].toObject();
                    QString book_name = bookres.value("title").toString();


                    lenditem.insert("title", book_name);
                    result_lendlist.append(lenditem);
                }
            }




            ui->borrow_table->setRowCount(result_lendlist.size());
            ui->borrow_table->clearContents();


            for (int i = 0; i < result_lendlist.size(); i++){
                ui->borrow_table->setItem(i, 0, new QTableWidgetItem(QString::number(result_lendlist[i].toObject().value("lend_id").toInt())));
                ui->borrow_table->setItem(i, 1, new QTableWidgetItem(result_lendlist[i].toObject().value("title").toString()));
                ui->borrow_table->setItem(i, 2, new QTableWidgetItem(result_lendlist[i].toObject().value("loan_date").toString()));
                ui->borrow_table->setItem(i, 3, new QTableWidgetItem(result_lendlist[i].toObject().value("renew_times").toString()));
            }


        }
        else
        {
            this->ui->msg_label->setText("Communication Error.");
            return;
        }
    }
    else
    {
        this->ui->msg_label->setText("Server is disconnected.");
        return;

    }
}

void MemberViewDialog::update_penalty()
{
    QJsonObject out;
    QJsonDocument doc;

    out.insert("Class", "Member");
    out.insert("Func", "readPenalty");
    out.insert("Input", MemberViewDialog::member);
    doc.setObject(out);
    QByteArray msg = doc.toJson();
    if (server->isOpen()) {
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QString penalty = jsonDoc.object()["penalty"].toString();
            MemberViewDialog::member["penalty"] = penalty;
            ui->penalty_line_edit->setText(penalty);
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

void MemberViewDialog::on_parent_closed()
{
    close();
}
