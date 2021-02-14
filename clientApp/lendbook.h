#ifndef LENDBOOK_H
#define LENDBOOK_H

#include <QDialog>
#include "serverconnection.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class LendBook;
}

class LendBook : public QDialog
{
    Q_OBJECT

public:
    explicit LendBook(ServerConnection *, int book_item_id, QWidget *parent = nullptr);
    ~LendBook();

private slots:
    void on_cancel_button_clicked();

    void on_parent_closed();

    void on_lend_button_clicked();

private:
    Ui::LendBook *ui;
    ServerConnection * server;
    int book_item_id;
};

#endif // LENDBOOK_H
