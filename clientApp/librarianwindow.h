#ifndef LIBRARIANWINDOW_H
#define LIBRARIANWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileInfo>
#include "serverconnection.h"
#include "libsearchview.h"
#include "mainwindow.h"
#include "helplibdialog.h"
#include "editaccountdialog.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <logindialog.h>
#include "memberviewdialog.h"

namespace Ui {
class LibrarianWindow;
}

class LibrarianWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibrarianWindow(ServerConnection *, QWidget *parent = nullptr);
    ~LibrarianWindow();

    //for member
    bool check_phone_number();
    bool check_email();
    bool check_card_number();
    bool check_national_id();
    bool check_first_name();
    bool check_last_name();
    bool check_member_id();
    bool check_address();

    //for librarian
    bool check_phone_number_li();
    bool check_email_li();
    bool check_national_id_li();
    bool check_first_name_li();
    bool check_last_name_li();
    bool check_librarian_id_li();
    bool check_address_li();
    bool check_username();
    bool check_password();
    bool check_confirm_password();

    //for book

    bool check_isbn();
    bool check_tilte();
    bool check_edition();
    bool check_author();
    bool check_publisher();
    bool check_language();
    bool check_subject();



private slots:
    void on_clear_button_me_clicked();

    void on_clear_button_li_clicked();

    void on_search_book_button_clicked();

    void on_logout_button_clicked();

    void on_help_button_clicked();

    void on_clear_button_book_clicked();

    void on_submit_button_book_clicked();

    void on_LibrarianWindow_destroyed();

    void on_edit_account_button_clicked();

    void on_submit_button_me_clicked();

    void on_submit_button_li_clicked();

    void on_members_search_options_combo_box_currentIndexChanged(int index);

    void on_search_button_clicked();

    void on_result_table_cellActivated(int row, int column);

private:
    QJsonArray jsonAr;
    Ui::LibrarianWindow *ui;
    ServerConnection * server;
signals:
    void closed();
};

#endif // LIBRARIANWINDOW_H
