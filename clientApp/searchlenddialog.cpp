#include "searchlenddialog.h"
#include "ui_searchlenddialog.h"
#include "lendbook.h"

SearchLendDialog::SearchLendDialog(ServerConnection * srv, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SearchLendDialog)
{
    ui->setupUi(this);
    this->server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

SearchLendDialog::~SearchLendDialog()
{
    delete ui;
}

void SearchLendDialog::on_search_button_clicked()
{
    QJsonObject klass;
    QMap<QString, QString> mp;
    mp["Title"] = "Title";
    mp["Subject"] = "Subject";
    mp["ISBN"] = "Id";
    klass.insert("Class", "Book");
    klass.insert("Func", "searchBy" + mp[this->ui->options_combo_box->currentText()]);
    QJsonObject input;
    input.insert(mp[this->ui->options_combo_box->currentText()],
            this->ui->search_line_edit->text());
    klass.insert("Input", input);
    QJsonDocument doc;
    doc.setObject(klass);
    QByteArray msg = doc.toJson();
    if (server->isOpen()){
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)){
            QByteArray ret = server->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(ret);
            QJsonArray jsonAr = jsonDoc.array();
            ui->result_table->setRowCount(jsonAr.size());
            if (!jsonAr.isEmpty()){
                this->ui->msg_label->setText(QString::number(jsonAr.size()) + " result/s found.");
                for (int i = 0; i < jsonAr.size(); i++) {
                   QJsonObject jsonObj = jsonAr[i].toObject();
                   this->ui->result_table->setItem(i, 0,
                                                   new QTableWidgetItem(jsonObj["book_id"].toString()));
                   this->ui->result_table->setItem(i, 1,
                                                   new QTableWidgetItem(jsonObj["title"].toString()));
                   this->ui->result_table->setItem(i, 2,
                                                   new QTableWidgetItem(jsonObj["publisher"].toString()));
                   this->ui->result_table->setItem(i, 3,
                                                   new QTableWidgetItem(jsonObj["author"].toString()));
                   this->ui->result_table->setItem(i, 4,
                                                   new QTableWidgetItem(jsonObj["translator"].toString()));
                   this->ui->result_table->setItem(i, 5,
                                                   new QTableWidgetItem(jsonObj["edition"].toString()));
                   this->ui->result_table->setItem(i, 6,
                                                   new QTableWidgetItem(jsonObj["subject"].toString()));
                   this->ui->result_table->setItem(i, 7,
                                                   new QTableWidgetItem(jsonObj["language"].toString()));
                }
            } else {
                this->ui->msg_label->setText("No Result");
            }
        }
        else
        {
            this->ui->msg_label->setText("Communication error");
        }
    }
    else
    {
        this->ui->msg_label->setText("Lost connection");
    }
}

void SearchLendDialog::on_parent_closed()
{
    close();
}



int SearchLendDialog::isAvailable(QString book_id) {
    int avaiable = 0;
    QJsonObject klass;
    klass.insert("Class", "BookItem");
    klass.insert("Func", "readAllBooks");
    QJsonObject input;
    input.insert("book_id", book_id);
    klass.insert("Input", input);
    QJsonDocument doc;
    doc.setObject(klass);
    QByteArray msg = doc.toJson();
    if (server->isOpen()){
        server->write(msg);
        server->flush();
        if (server->waitForReadyRead(3000)) {
            QByteArray ret = server->readAll();
            QJsonDocument jsondoc = QJsonDocument::fromJson(ret);
            QJsonArray jsonArray = jsondoc.array();
            for (int i = 0; i < jsonArray.size(); i++) {
                if (jsonArray[i].toObject()["status"].toString() == "1") {
                    avaiable = jsonArray[i].toObject()["book_item_id"].toInt();
                }
            }
        }
    }
    return avaiable;
}


void SearchLendDialog::on_result_table_cellActivated(int row, int column)
{
    this->ui->book_data_text->clear();
    this->ui->book_data_text->append("ISBN : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 0)->text() + "\n");
    this->ui->book_data_text->append("Title : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 1)->text() + "\n");
    this->ui->book_data_text->append("Publication : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 2)->text() + "\n");
    this->ui->book_data_text->append("Author : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 3)->text() + "\n");
    this->ui->book_data_text->append("Translator : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 4)->text() + "\n");
    this->ui->book_data_text->append("Edition : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 5)->text() + "\n");
    this->ui->book_data_text->append("Subject : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 6)->text() + "\n");
    this->ui->book_data_text->append("Language : ");
    this->ui->book_data_text->append(this->ui->result_table->item(row, 7)->text() + "\n");
    this->ui->book_data_text->append("Availability : ");
    available_id = isAvailable(this->ui->result_table->item(row, 0)->text());
    if (available_id) {
        this->ui->book_data_text->append("Available \n");
        ui->lend_button->setEnabled(true);
    } else {
        this->ui->book_data_text->append("Unavailable \n");
        ui->lend_button->setEnabled(false);
    }
}


void SearchLendDialog::on_options_combo_box_activated(int index)
{
}

void SearchLendDialog::on_lend_button_clicked()
{
    QJsonObject out;
    QJsonDocument doc;
    QJsonObject parameter;
    parameter.insert("book_item_id", QString::number(available_id));
    parameter.insert("member_id", MemberViewDialog::member.value("member_id"));
    out.insert("Class", "Lend");
    out.insert("Func", "create");
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
            if (status.toInt() == 201){
               this->ui->msg_label->setText("Book lended.");
                emit refresh_that();
                ui->lend_button->setEnabled(false);
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
