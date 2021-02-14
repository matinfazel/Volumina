#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serverconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ServerConnection *, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_search_view_button_clicked();

    void on_login_button_clicked();

    void on_help_button_clicked();

    void librarian_login();

    void on_MainWindow_destroyed();

private:
    ServerConnection * server;
    Ui::MainWindow *ui;

signals:
    void closed();
};
#endif // MAINWINDOW_H
