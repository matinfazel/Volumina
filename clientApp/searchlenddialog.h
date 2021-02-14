#ifndef SEARCHLENDDIALOG_H
#define SEARCHLENDDIALOG_H

#include <QObject>
#include <QDialog>
#include "serverconnection.h"
#include "memberviewdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegExp>
namespace Ui {
class SearchLendDialog;
}

class SearchLendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchLendDialog(ServerConnection *, QWidget *parent = nullptr);
    ~SearchLendDialog();

private slots:
    void on_search_button_clicked();

    void on_parent_closed();


    void on_result_table_cellActivated(int row, int column);

    void on_options_combo_box_activated(int index);

    void on_lend_button_clicked();

private:
    int isAvailable(QString book_item_id);
    long long int barcode;
    Ui::SearchLendDialog *ui;
    ServerConnection * server;
    int available_id = 0;

signals:
    void refresh_that();
};
#endif // SEARCHLENDDIALOG_H
