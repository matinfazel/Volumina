#include "librarianwindow.h"
#include "ui_librarianwindow.h"

LibrarianWindow::LibrarianWindow(ServerConnection * srv,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibrarianWindow)
{
    ui->setupUi(this);
    ui->label->setText("Welcome, " + LoginDialog::cur_user["name"].toString());
    server = srv;
    QRegularExpression rx_name("[a-z|A-Z]{2,15}",
                          QRegularExpression::CaseInsensitiveOption);
    ui->first_name_line_edit_me->setValidator(new QRegularExpressionValidator(rx_name, this));
    ui->last_name_line_edit_me->setValidator(new QRegularExpressionValidator(rx_name, this));

    ui->first_name_line_edit_li->setValidator(new QRegularExpressionValidator(rx_name, this));
    ui->last_name_line_edit_li->setValidator(new QRegularExpressionValidator(rx_name, this));


    QRegularExpression rx_phone_number("^9[0|1|2|3][0-9]{8}$",
                          QRegularExpression::CaseInsensitiveOption);
    ui->phone_line_edit_me->setValidator(new QRegularExpressionValidator(rx_phone_number, this));
    ui->phone_line_edit_li->setValidator(new QRegularExpressionValidator(rx_phone_number, this));

    QRegularExpression rx_card_number("\\d{4}-\\d{4}-\\d{4}-\\d{4}",
                          QRegularExpression::CaseInsensitiveOption);
    ui->card_number_edit_me->setValidator(new QRegularExpressionValidator(rx_card_number, this));


    QRegularExpression rx_national_number("\\d{10}",
                          QRegularExpression::CaseInsensitiveOption);
    ui->account_id_edit_me->setValidator(new QRegularExpressionValidator(rx_national_number, this));
    ui->member_search_line_edit->setValidator(new QRegularExpressionValidator(rx_national_number, this));
    ui->account_id_line_edit_li->setValidator(new QRegularExpressionValidator(rx_national_number, this));

    QRegularExpression rx_member_id("\\d{1,5}",
                          QRegularExpression::CaseInsensitiveOption);
    ui->member_id_edit_me->setValidator(new QRegularExpressionValidator(rx_member_id, this));
    ui->librarian_id_line_edit_li->setValidator(new QRegularExpressionValidator(rx_member_id, this));
    QRegularExpression rx_email("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                          QRegularExpression::CaseInsensitiveOption);
    ui->email_line_edit_me->setValidator(new QRegularExpressionValidator(rx_email, this));
    ui->email_line_edit_li->setValidator(new QRegularExpressionValidator(rx_email, this));

    //^(?=[a-zA-Z0-9._]{8,20}$)(?!.*[_.]{2})[^_.].*[^_.]$
    QRegularExpression rx_username("^(?=[a-zA-Z0-9._]{8,20}$)(?!.*[_.]{2})[^_.].*[^_.]$",
                                  QRegularExpression::CaseInsensitiveOption);
            ui->username_line_edit_li->setValidator(new QRegularExpressionValidator(rx_username, this));


     QRegularExpression rx_password("((?=.*[a-z])(?=.*[A-Z])(?=.*[1234567890@#$%_*!&?}{]).{8,20})",
                                          QRegularExpression::CaseInsensitiveOption);
                    ui->password_line_edit_li->setValidator(new QRegularExpressionValidator(rx_password, this));

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
               ui->subject_line_edit->setValidator(new QRegularExpressionValidator(rx_publish, this));

QRegularExpression rx_edition("^[0-9]{1,3}",
                 QRegularExpression::CaseInsensitiveOption);
                              ui->edition_line_edit->setValidator(new QRegularExpressionValidator(rx_edition, this));


}

LibrarianWindow::~LibrarianWindow()
{
    delete ui;
}

bool LibrarianWindow::check_phone_number()
{
    if(!ui->phone_line_edit_me->hasAcceptableInput())
    {
    ui->phone_line_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Phone number verification"),
                         tr("Phone number must be 11 digits."), QMessageBox::Ok);
    return false;
    }
    else{
         ui->phone_line_edit_me->setStyleSheet("QLineEdit { color: black;}");
         return true;
    }

}

bool LibrarianWindow::check_email()
{

    if(!ui->email_line_edit_me->hasAcceptableInput())
    {
    ui->email_line_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Email verification"),
                         tr("Email format is incorrect"), QMessageBox::Ok);
    return false;
    }
    else{
        ui->email_line_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_card_number()
{
    if(!ui->card_number_edit_me->hasAcceptableInput())
    {
    ui->card_number_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Card number verification"),
                         tr("Card number must be 16 digits"), QMessageBox::Ok);
    return false;
    }
    else{
        ui->card_number_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_national_id()
{
    if(!ui->account_id_edit_me->hasAcceptableInput())
    {
    ui->account_id_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("National id verification"),
                         tr("National id must be 10 digits"), QMessageBox::Ok);
    return false;

    }

    else {
        ui->account_id_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_first_name()
{

    if(!ui->first_name_line_edit_me->hasAcceptableInput())
    {
    ui->first_name_line_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("first name verification"),
                         tr("first name must include 2-15 characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->first_name_line_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_last_name()
{
    if(!ui->last_name_line_edit_me->hasAcceptableInput())
    {
    ui->last_name_line_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Last name verification"),
                         tr("Last name must include 2-15 characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->last_name_line_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }


}

bool LibrarianWindow::check_member_id()
{
    if(!ui->member_id_edit_me->hasAcceptableInput())
    {
    ui->member_id_edit_me->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Member id verification"),
                         tr("member must include 1-5 digits"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->member_id_edit_me->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_address()
{
   QString text= ui->address_text_edit_me->toPlainText();
   if (text.size()>80||text.size()<10)
   {
       ui->address_text_edit_me->setStyleSheet("QLineEdit { color: red;}");
       QMessageBox::critical(this, tr("Address verification"),
                            tr("Adrress text must include 10-80 digits"), QMessageBox::Ok);
       return false;

   }
   else {
       ui->address_text_edit_me->setStyleSheet("QLineEdit { color: black;}");
   return true;
   }
}

bool LibrarianWindow::check_phone_number_li()
{
    if(!ui->phone_line_edit_li->hasAcceptableInput())
    {
    ui->phone_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Phone number id verification"),
                         tr("Phone number must include 11 digits"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->phone_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }


}

bool LibrarianWindow::check_email_li()
{
    if(!ui->email_line_edit_li->hasAcceptableInput())
    {
    ui->email_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Email verification"),
                         tr("Email format is incorrect"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->email_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }


}

bool LibrarianWindow::check_national_id_li()
{
    if(!ui->account_id_line_edit_li->hasAcceptableInput())
    {
    ui->account_id_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("National number verification"),
                         tr("National number must include 10 digits"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->account_id_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_first_name_li()
{
    if(!ui->first_name_line_edit_li->hasAcceptableInput())
    {
    ui->first_name_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("First name verification"),
                         tr("First name must include 2-15 characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->first_name_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_last_name_li()
{
    if(!ui->last_name_line_edit_li->hasAcceptableInput())
    {
    ui->last_name_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Last name verification"),
                         tr("Last name must include 2-15 characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->last_name_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_librarian_id_li()
{
    if(!ui->librarian_id_line_edit_li->hasAcceptableInput())
    {
    ui->librarian_id_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Librarian verification"),
                         tr("Librarian must include 1-5 digits"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->librarian_id_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }




}

bool LibrarianWindow::check_address_li()
{
    QString text= ui->address_text_edit_li->toPlainText();
    if (text.size()>80||text.size()<10)
    {
        ui->address_text_edit_me->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Address verification"),
                             tr("Adrress text must include 10-80 digits"), QMessageBox::Ok);
        return false;

    }
    else {
        ui->address_text_edit_li->setStyleSheet("QLineEdit { color: black;}");
    return true;
    }

}

bool LibrarianWindow::check_username()
{
    if(!ui->username_line_edit_li->hasAcceptableInput())
    {
    ui->username_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Username verification"),
                         tr("Username must include 8-20 characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->username_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_password()
{
    if(!ui->password_line_edit_li->hasAcceptableInput())
    {
    ui->password_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Password verification"),
                         tr("The size of password must be 8-20 characters and must include lowercase and upercase and digits or special symbols"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->password_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_confirm_password()
{
    if(!(ui->confirm_password_line_edit_li->text()==ui->password_line_edit_li->text()))
    {
    ui->confirm_password_line_edit_li->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Confirm Password verification"),
                         tr("Password and confirm password does not match"), QMessageBox::Ok);
    return false;
    }
    else
    {
        ui->confirm_password_line_edit_li->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_isbn()
{
    if(!ui->isbn_line_edit->hasAcceptableInput())
    {
    ui->isbn_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Isbn verification"),
                         tr("Isbn must include 13 digits"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->isbn_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_tilte()
{
    if(!ui->title_line_edit->hasAcceptableInput())
    {
    ui->title_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Title verification"),
                         tr("Title must include 3-30 "), QMessageBox::Ok);
    return false;
    }

    else {
        ui->title_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_edition()
{
    if(!ui->edition_line_edit->hasAcceptableInput())
    {
    ui->edition_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Edition verification"),
                         tr("Edition must include digits "), QMessageBox::Ok);
    return false;
    }

    else {
        ui->edition_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }


}

bool LibrarianWindow::check_author()
{
    if(!ui->author_line_edit->hasAcceptableInput())
    {
    ui->author_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Edition verification"),
                         tr("Author name must include characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->author_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool LibrarianWindow::check_publisher()
{
    if(!ui->publisher_line_edit->hasAcceptableInput())
    {
    ui->publisher_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Publisher name verification"),
                         tr("Publisher name must include characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->publisher_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_language()
{
    if(!ui->language_line_edit->hasAcceptableInput())
    {
    ui->language_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Language name verification"),
                         tr("Language name must include characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->language_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool LibrarianWindow::check_subject()
{
    if(!ui->subject_line_edit->hasAcceptableInput())
    {
    ui->subject_line_edit->setStyleSheet("QLineEdit { color: red;}");
    QMessageBox::critical(this, tr("Subject name verification"),
                         tr("Subject name must include characters"), QMessageBox::Ok);
    return false;
    }

    else {
        ui->subject_line_edit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}







void LibrarianWindow::on_clear_button_me_clicked()
{
    ui->first_name_line_edit_me->clear();
    ui->account_id_edit_me->clear();
    ui->member_id_edit_me->clear();
    ui->card_number_edit_me->clear();
    ui->last_name_line_edit_me->clear();
    ui->email_line_edit_me->clear();
    ui->phone_line_edit_me->clear();
    ui->birth_date_me->clear();
    ui->address_text_edit_me->clear();
    ui->msg_label_me->setText("Please Enter the new member's info");
}

void LibrarianWindow::on_clear_button_li_clicked()
{
    ui->account_id_line_edit_li->clear();
    ui->librarian_id_line_edit_li->clear();
    //ui->
    ui->first_name_line_edit_li->clear();
    ui->last_name_line_edit_li->clear();
    ui->email_line_edit_li->clear();
    ui->phone_line_edit_li->clear();
    ui->birth_date_li->clear();
    ui->address_text_edit_li->clear();
    ui->password_line_edit_li->clear();
    ui->confirm_password_line_edit_li->clear();
    ui->username_line_edit_li->clear();
    ui->msg_label_li->setText("Please Enter the new librarian's info");
}

void LibrarianWindow::on_search_book_button_clicked()
{
    LibSearchView * w = new LibSearchView(server, this);
    w->show();
}

void LibrarianWindow::on_logout_button_clicked()
{
    emit closed();
    MainWindow * w = new MainWindow(server);
    w->show();
    close();
}

void LibrarianWindow::on_help_button_clicked()
{
    HelpLibDialog * w = new HelpLibDialog(this);
    w->show();
}

void LibrarianWindow::on_clear_button_book_clicked()
{
    ui->author_line_edit->clear();
    ui->isbn_line_edit->clear();
    ui->title_line_edit->clear();
    ui->edition_line_edit->clear();
    ui->translator_line_edit->clear();
    ui->publisher_line_edit->clear();
    ui->translator_line_edit->clear();
    ui->language_line_edit->clear();
    ui->subject_line_edit->clear();

    ui->book_msg_label->setText("Please enter the new book's data");
}

void LibrarianWindow::on_submit_button_book_clicked()
{
      if (check_isbn()&&check_tilte()&&check_edition()
              &&check_author()&&check_publisher()
              &&check_language()&&check_subject())
      {

          QJsonObject klass;
          klass.insert("Class", "Book");
          klass.insert("Func", "create");
          QJsonObject input;
          input.insert("book_id",ui->isbn_line_edit->text());
          input.insert("title", ui->title_line_edit->text());
          input.insert("subject", ui->subject_line_edit->text());
          input.insert("publisher", ui->publisher_line_edit->text());
          input.insert("language", ui->language_line_edit->text());
          input.insert("author", ui->author_line_edit->text());
          input.insert("translator",ui->translator_line_edit->text());
          input.insert("edition", ui->edition_line_edit->text());

          klass.insert("Input", input);
          QJsonDocument doc;
          doc.setObject(klass);
          QByteArray msg = doc.toJson();

          if (doc.isObject())
          {

          }
          if (server->isOpen())
          {
              server->write(msg);
              server->flush();
              QByteArray ret = server->readAll();
              ui->new_book_added_label->setText("Book added.");
              QString read(ret);

          }


      }

}

void LibrarianWindow::on_LibrarianWindow_destroyed()
{
    emit closed();
}


void LibrarianWindow::on_edit_account_button_clicked()
{
    EditAccountDialog * w = new EditAccountDialog(server, this);
    w->show();
    ui->label->setText(LoginDialog::cur_user["name"].toString());
}

void LibrarianWindow::on_submit_button_me_clicked()
{

    if (check_first_name()&&check_last_name()&&
            check_phone_number()&&check_email()&&
            check_card_number()&&check_national_id()
            &&check_member_id()&&check_address()
        )

    {


    QJsonObject klass;
    klass.insert("Class", "Member");
    klass.insert("Func", "create");
    QJsonObject input;
    input.insert("name",ui->first_name_line_edit_me->text()+" "+
                 ui->last_name_line_edit_me->text());
    input.insert("phone_number", ui->phone_line_edit_me->text());
    input.insert("email", ui->email_line_edit_me->text());
    input.insert("account_id", ui->account_id_edit_me->text());
    input.insert("birthday", ui->birth_date_me->text());
    input.insert("card_number", ui->card_number_edit_me->text());
    input.insert("member_id",ui->member_id_edit_me->text());
    input.insert("address", ui->address_text_edit_me->toPlainText());

    klass.insert("Input", input);
    QJsonDocument doc;
    doc.setObject(klass);
    QByteArray msg = doc.toJson();

    if (doc.isObject())
    {

    }
    if (server->isOpen())
    {
        server->write(msg);
        server->flush();
        QByteArray ret = server->readAll();
        QString read(ret);
        ui->new_member_added_label->setText("Member added.");
    }

}
}

void LibrarianWindow::on_submit_button_li_clicked()
{
    if (check_first_name_li()&&check_last_name_li()&&check_email_li()&&check_username()
            &&check_password()&&check_confirm_password()&&check_librarian_id_li()&&
            check_national_id_li()&&check_phone_number_li()&&check_address_li())
    {

    }
    QJsonObject klass;
    klass.insert("Class", "Librarian");
    klass.insert("Func", "create");
    QJsonObject input;
    input.insert("name",ui->first_name_line_edit_li->text()+" "+
                 ui->last_name_line_edit_li->text());
    input.insert("phone_number", ui->phone_line_edit_li->text());
    input.insert("email", ui->email_line_edit_li->text());
    input.insert("account_id", ui->account_id_line_edit_li->text());
    input.insert("birthday", ui->birth_date_li->text());
    input.insert("password", ui->password_line_edit_li->text());
    input.insert("librarian_id",ui->librarian_id_line_edit_li->text());
    input.insert("address", ui->address_text_edit_li->toPlainText());
    input.insert("username", ui->username_line_edit_li->text());
    input.insert("account_id", ui->account_id_line_edit_li->text());

    klass.insert("Input", input);
    QJsonDocument doc;
    doc.setObject(klass);
    QByteArray msg = doc.toJson();

    if (doc.isObject())
    {

    }
    if (server->isOpen())
    {
        server->write(msg);
        server->flush();
        QByteArray ret = server->readAll();
        ui->new_librarian_added_label->setText("librarian added.");
        QString read(ret);
    }




}

void LibrarianWindow::on_members_search_options_combo_box_currentIndexChanged(int index)
{
    ui->member_search_line_edit->clear();
    if (index == 0) {
        QRegularExpression rx_national_number("\\d{10}",
                              QRegularExpression::CaseInsensitiveOption);
        ui->member_search_line_edit->setValidator(new QRegularExpressionValidator(rx_national_number, this));
        ui->member_search_line_edit->setPlaceholderText("e.g. 1273459864");
    } else if (index == 1) {
        QRegularExpression rx_name("[a-z|A-Z ]{2,30}",
                              QRegularExpression::CaseInsensitiveOption);
        ui->member_search_line_edit->setValidator(new QRegularExpressionValidator(rx_name, this));
        ui->member_search_line_edit->setPlaceholderText("e.g. ali ahmadi");
    } else if (index == 2) {
        QRegularExpression rx_member_id("\\d{1,5}",
                              QRegularExpression::CaseInsensitiveOption);
        ui->member_search_line_edit->setValidator(new QRegularExpressionValidator(rx_member_id, this));
        ui->member_search_line_edit->setPlaceholderText("e.g. 10234");
    }
}

void LibrarianWindow::on_search_button_clicked()
{
    QJsonObject klass;
    QMap<int, QString> mp;
    mp[0] = "AccountId";
    mp[2] = "MemberId";
    mp[1] = "Name";
    klass.insert("Class", "Member");
    klass.insert("Func", "searchBy" +
                 mp[this->ui->members_search_options_combo_box->currentIndex()]);
    QJsonObject input;
    input.insert(mp[this->ui->members_search_options_combo_box->currentIndex()],
            this->ui->member_search_line_edit->text());
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
            jsonAr = jsonDoc.array();
            ui->result_table->setRowCount(jsonAr.size());
            if (!jsonAr.isEmpty()){
                this->ui->member_result_label->setText(QString::number(jsonAr.size()) + " result/s found.");
                for (int i = 0; i < jsonAr.size(); i++) {
                   QJsonObject jsonObj = jsonAr[i].toObject();
                   this->ui->result_table->setItem(i, 0,
                                                   new QTableWidgetItem(jsonObj["account_id"].toString()));
                   this->ui->result_table->setItem(i, 1,
                                                   new QTableWidgetItem(jsonObj["name"].toString()));
                   this->ui->result_table->setItem(i, 2,
                                                   new QTableWidgetItem(jsonObj["member_id"].toString()));
                   this->ui->result_table->setItem(i, 3,
                                                   new QTableWidgetItem(jsonObj["phone_number"].toString()));
                   }
            } else {
                this->ui->member_result_label->setText("No Result :(");
            }
        }
        else
        {
            this->ui->member_result_label->setText("Communication Sucks!!!");
        }
    }
    else
    {
        this->ui->member_result_label->setText("Lost Connection!!!");
    }
}

void LibrarianWindow::on_result_table_cellActivated(int row, int column)
{
    MemberViewDialog::member = jsonAr[row].toObject();
    MemberViewDialog *w = new MemberViewDialog(server, this);
    w->show();
}
