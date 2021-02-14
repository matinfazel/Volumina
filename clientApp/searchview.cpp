#include "searchview.h"
#include "ui_searchview.h"
#include "lendbook.h"

SearchView::SearchView(ServerConnection * srv, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SearchView)
{
    ui->setupUi(this);
    this->server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

SearchView::~SearchView()
{
    delete ui;
}

void SearchView::on_search_button_clicked()
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
                this->ui->label->setText(QString::number(jsonAr.size()) + " result/s found.");
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
                this->ui->label->setText("No Result :(");
            }
        }
        else
        {
            this->ui->label->setText("Communication Sucks!!!");
        }
    }
    else
    {
        this->ui->label->setText("Server Sucks!!!");
    }
}

void SearchView::on_parent_closed()
{
    close();
}

void SearchView::on_pushButton_clicked()
{
    LendBook * book = new LendBook(server, 123);//cahnge 123 to book_item_id
    book->show();

}

int SearchView::isAvailable(QString book_id) {
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


void SearchView::on_result_table_cellActivated(int row, int column)
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
    if (isAvailable(this->ui->result_table->item(row, 0)->text())) {
        this->ui->book_data_text->append("Available \n");
    } else {
        this->ui->book_data_text->append("Unavailable \n");
    }
}


void SearchView::on_options_combo_box_activated(int index)
{
}
