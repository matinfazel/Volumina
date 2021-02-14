#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QObject>
#include <QDialog>
#include "serverconnection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegExp>
namespace Ui {
class SearchView;
}

class SearchView : public QDialog
{
    Q_OBJECT

public:
    explicit SearchView(ServerConnection *, QWidget *parent = nullptr);
    ~SearchView();

private slots:
    void on_search_button_clicked();

    void on_parent_closed();

    void on_pushButton_clicked();

    void on_result_table_cellActivated(int row, int column);

    void on_options_combo_box_activated(int index);

private:
    int isAvailable(QString book_item_id);
    long long int barcode;
    Ui::SearchView *ui;
    ServerConnection * server;
};

#endif // SEARCHVIEW_H
