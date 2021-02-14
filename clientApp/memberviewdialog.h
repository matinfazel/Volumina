#ifndef MEMBERVIEWDIALOG_H
#define MEMBERVIEWDIALOG_H

#include <QDialog>
#include "serverconnection.h"
#include "lendbook.h"
#include "renewmemberdialog.h"
#include "addtransaction.h"
#include "addpenaltydialog.h"
#include "searchview.h"
#include "searchlenddialog.h"


namespace Ui {
class MemberViewDialog;
}

class MemberViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberViewDialog(ServerConnection *, QWidget *parent = nullptr);
    ~MemberViewDialog();
    static QJsonObject lend;
    static QJsonObject member;

private slots:
    void on_close_button_clicked();

    void on_lend_button_clicked();

    void on_renew_member_button_clicked();

    void on_add_transaction_button_clicked();

    void on_MemberViewDialog_destroyed();

    void on_add_penalty_button_clicked();

    void on_renew_book_button_clicked();

    void on_return_button_clicked();

    void on_update_button_clicked();

    void on_borrow_table_cellClicked(int row, int column);

    void refresh_lend();

    void update_penalty();

    void on_parent_closed();

private:
    Ui::MemberViewDialog *ui;
    ServerConnection * server;
    QJsonArray result_lendlist;
signals:
    void closed();

};

#endif // MEMBERVIEWDIALOG_H
