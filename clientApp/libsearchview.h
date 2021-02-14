#ifndef LIBSEARCHVIEW_H
#define LIBSEARCHVIEW_H

#include <QDialog>
#include "serverconnection.h"
#include "serverconnection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegExp>
#include <QMessageBox>

namespace Ui {
class LibSearchView;
}

class LibSearchView : public QDialog
{
    Q_OBJECT

public:
    explicit LibSearchView(ServerConnection *,QWidget *parent = nullptr);
    ~LibSearchView();

private slots:
    void on_close_button_clicked();

    void on_parent_closed();

    void on_search_button_clicked();

    void on_result_table_cellActivated(int row, int column);

    void on_create_item_button_clicked();

private:
    Ui::LibSearchView *ui;
    ServerConnection * server;

};

#endif // LIBSEARCHVIEW_H
