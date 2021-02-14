#include "editaccountdialog.h"
#include "ui_editaccountdialog.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

EditAccountDialog::EditAccountDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAccountDialog)
{
    ui->setupUi(this);
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
    server = srv;
    ui->email_line_dit->setText(LoginDialog::cur_user.value("email").toString());
    ui->home_address_text_dit->setText(LoginDialog::cur_user.value("address").toString());
    ui->phone_number_line_dit->setText(LoginDialog::cur_user.value("phone_number").toString());
    ui->first_name_line_dit->setText(LoginDialog::cur_user.value("name").toString());



    QRegularExpression rx_name("[a-z|A-Z ]{5,30}",
                          QRegularExpression::CaseInsensitiveOption);
    ui->first_name_line_dit->setValidator(new QRegularExpressionValidator(rx_name, this));
    QRegularExpression rx_phone_number("^9[0|1|2|3][0-9]{8}$",
                          QRegularExpression::CaseInsensitiveOption);
    ui->phone_number_line_dit->setValidator(new QRegularExpressionValidator(rx_phone_number, this));


    QRegularExpression rx_email("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                          QRegularExpression::CaseInsensitiveOption);
    ui->email_line_dit->setValidator(new QRegularExpressionValidator(rx_email, this));

    QRegularExpression rx_password("((?=.*[a-z])(?=.*[A-Z])(?=.*[1234567890@#$%_*!&?}{]).{8,20})",
                                         QRegularExpression::CaseInsensitiveOption);

    ui->new_password_line_dit->setValidator(new QRegularExpressionValidator(rx_password, this));

    ui->first_name_line_dit->setPlaceholderText("e.g. ali");
    ui->phone_number_line_dit->setPlaceholderText("e.g. 9033312342");
    ui->email_line_dit->setPlaceholderText("e.g. ali ahmadi");



}

EditAccountDialog::~EditAccountDialog()
{
    delete ui;
}

bool EditAccountDialog::check_first_name()
{
    if(!ui->first_name_line_dit->hasAcceptableInput())
    {
        ui->first_name_line_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Name verification"),
                             tr("First name must include 5-30 character"), QMessageBox::Ok);
        return false;
    }

    else {
        ui->first_name_line_dit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }

}

bool EditAccountDialog::check_password_name()
{
    if(!ui->new_password_line_dit->hasAcceptableInput())
    {
        ui->new_password_line_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Password verification"),
                             tr("Password must include 8-20 characters,numbers or symbols"), QMessageBox::Ok);
        return false;
    }

    else {
        ui->new_password_line_dit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool EditAccountDialog::check_email_name()
{
    if(!ui->email_line_dit->hasAcceptableInput())
    {
        ui->email_line_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Email verification"),
                             tr("Invalid Email address"), QMessageBox::Ok);
        return false;
    }

    else {
        ui->email_line_dit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool EditAccountDialog::check_address_name()
{
    QString text= ui->home_address_text_dit->toPlainText();
    if (text.size()>80||text.size()<10)
    {
        ui->home_address_text_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Address verification"),
                             tr("Address text must include 10-80 digits"), QMessageBox::Ok);
        return false;

    }
    else {
        ui->home_address_text_dit->setStyleSheet("QLineEdit { color: black;}");
    return true;
    }
}

bool EditAccountDialog::check_password_confirm()
{

    if(!(ui->confirm_new_password_line_dit->text()==ui->new_password_line_dit->text()))
    {
        ui->confirm_new_password_line_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Confirm Password verification"),
                             tr("Password and confirm password does not match"), QMessageBox::Ok);
        return false;
    }
    else
    {
        ui->confirm_new_password_line_dit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

bool EditAccountDialog::check_phone_number()
{
    if(!ui->phone_number_line_dit->hasAcceptableInput())
    {
        ui->phone_number_line_dit->setStyleSheet("QLineEdit { color: red;}");
        QMessageBox::critical(this, tr("Phone number verification"),
                             tr("Invalid Phone number"), QMessageBox::Ok);
        return false;
    }

    else {
        ui->phone_number_line_dit->setStyleSheet("QLineEdit { color: black;}");
        return true;
    }
}

void EditAccountDialog::on_close_button_clicked()
{
    this->close();
}

void EditAccountDialog::on_parent_closed()
{
    close();
}

void EditAccountDialog::on_submit_button_clicked()
{
    QJsonObject parameter;

    if (check_first_name()&&check_phone_number()&&check_email_name()
            &&check_address_name())
    {
         if (ui->new_password_line_dit->text() == ""){
            parameter.insert("account_id", LoginDialog::cur_user.value("account_id"));
            parameter.insert("email", ui->email_line_dit->text());
            parameter.insert("address", ui->home_address_text_dit->toPlainText());
            parameter.insert("phone_number", ui->phone_number_line_dit->text());
            parameter.insert("password", LoginDialog::cur_user.value("password").toString());
            parameter.insert("name", ui->first_name_line_dit->text());
        } else if(check_password_name()
                  &&check_password_confirm()) {
            parameter.insert("account_id", LoginDialog::cur_user.value("account_id"));
            parameter.insert("email", ui->email_line_dit->text());
            parameter.insert("address", ui->home_address_text_dit->toPlainText());
            parameter.insert("phone_number", ui->phone_number_line_dit->text());
            parameter.insert("password", ui->new_password_line_dit->text());
            parameter.insert("name", ui->first_name_line_dit->text());
        }
        QJsonObject out;
        QJsonDocument doc;

        out.insert("Class", "Librarian");
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
                   this->ui->msg_label->setText("Data changed.");
                    LoginDialog::cur_user["name"] = ui->first_name_line_dit->text();
                    LoginDialog::cur_user["email"] = ui->email_line_dit->text();
                    LoginDialog::cur_user["address"] = ui->home_address_text_dit->toPlainText();
                    LoginDialog::cur_user["phone_number"] = ui->phone_number_line_dit->text();
                    LoginDialog::cur_user["password"] = std::max(ui->new_password_line_dit->text(),
                                                                  LoginDialog::cur_user.value("password").toString());
                } else {
                    this->ui->msg_label->setText("Failed to update user data.");
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
    return;
}
