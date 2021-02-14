#include "libsearchview.h"
#include "ui_libsearchview.h"

LibSearchView::LibSearchView(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibSearchView)
{
    ui->setupUi(this);

    QRegularExpression rx_isbn("\\d{13}",
                               QRegularExpression::CaseInsensitiveOption);
    ui->isbn_line_edit->setValidator(new QRegularExpressionValidator(rx_isbn, this));


    QRegularExpression rx_title("([A-Z|a-z|0-9]).{2,30}",
                                QRegularExpression::CaseInsensitiveOption);
    ui->title_line_edit->setValidator(new QRegularExpressionValidator(rx_title, this));


    QRegularExpression rx_publish("([A-Z|a-z]).{2,30}",
                                  QRegularExpression::CaseInsensitiveOption);
    ui->author_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));
    ui->translator_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));
    ui->language_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));
    ui->subject_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));
    ui->publisher_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));

    QRegularExpression rx_edition("^[0-9]{1,3}",
                   QRegularExpression::CaseInsensitiveOption);
    ui->edition_line_edit->setValidator(new QRegularExpressionValidator(rx_edition, this));

    server = srv;
    connect(parent, SIGNAL(closed()), this, SIGNAL(on_parent_closed()));
    this->ui->create_item_button->setEnabled(false);
}

LibSearchView::~LibSearchView()
{
    delete ui;
}

void LibSearchView::on_close_button_clicked()
{
    close();
}

void LibSearchView::on_parent_closed()
{
    close();
}

void LibSearchView::on_search_button_clicked()
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
                this->ui->label->setText("No Result");
            }
        }
        else
        {
            this->ui->label->setText("Communication error");
        }
    }
    else
    {
        this->ui->label->setText("Server error");
    }
}

void LibSearchView::on_result_table_cellActivated(int row, int column)
{
    ui->isbn_line_edit->setText(ui->result_table->item(row, 0)->text());
    ui->title_line_edit->setText(ui->result_table->item(row, 1)->text());
    ui->publisher_line_edit->setText(ui->result_table->item(row, 2)->text());
    ui->author_line_edit->setText(ui->result_table->item(row, 3)->text());
    ui->translator_line_edit->setText(ui->result_table->item(row, 4)->text());
    ui->edition_line_edit->setText(ui->result_table->item(row, 5)->text());
    ui->subject_line_edit->setText(ui->result_table->item(row, 6)->text());
    ui->language_line_edit->setText(ui->result_table->item(row, 7)->text());

    this->ui->create_item_button->setEnabled(true);

    QJsonObject klass;
    klass.insert("Class", "BookItem");
    klass.insert("Func", "readAllBooks");
    QJsonObject input;
    input.insert("book_id",
            ui->result_table->item(row, 0)->text());
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
            if (!jsonAr.isEmpty()){
                this->ui->label->setText(QString::number(jsonAr.size()) + " result/s found.");
                for (int i = 0; i < jsonAr.size(); i++) {
                    QJsonObject jsonObj = jsonAr[i].toObject();
                    QJsonObject klassIn;
                    klass.insert("Class", "Lend");
                    klass.insert("Func", "searchByBook");
                    QJsonObject inputIn;
                    input.insert("book_item_id",
                           jsonObj["book_item_id"].toString());
                    klass.insert("Input", input);
                    QJsonDocument doc;
                    doc.setObject(klass);
                    msg = doc.toJson();



                    if (server->isOpen()){
                        server->write(msg);
                        server->flush();
                        if (server->waitForReadyRead(3000)){
                            ret = server->readAll();
                            QJsonDocument jsonDocIn = QJsonDocument::fromJson(ret);
                            QJsonArray jsonArIn = jsonDoc.array();
                            if (!jsonAr.isEmpty()){
                                this->ui->label->setText(QString::number(jsonAr.size()) + " result/s found.");
                                for (int i = 0; i < jsonAr.size(); i++) {
                                    QJsonObject jsonObjIn = jsonAr[i].toObject();

                                }

                            }
                        }
                    }
                }
            }
        } else {
            this->ui->label->setText("Communication Sucks!!!");
        }
    } else {
        this->ui->label->setText("Server Sucks!!!");
    }
}



void LibSearchView::on_create_item_button_clicked()
{
    QJsonObject klass;
    QMap<QString, QString> mp;
    klass.insert("Class", "BookItem");
    klass.insert("Func", "create");
    QJsonObject input;
    input.insert("book_id", ui->isbn_line_edit->text());
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
            if (jsonDoc.object()["status"].toInt() == 201){
                this->ui->label->setText("Book item added.");
                this->ui->create_item_button->setEnabled(false);
            } else {
                this->ui->label->setText("Could not create a new book item.");

            }
        }
        else
        {
            this->ui->label->setText("Communication Sucks!!!");
        }
    } else {
        this->ui->label->setText("Server Sucks!!!");
    }
}
