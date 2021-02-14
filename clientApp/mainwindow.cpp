#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchview.h"
#include "logindialog.h"
#include "helpdialog.h"

MainWindow::MainWindow(ServerConnection * srv, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->server = srv;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_search_view_button_clicked()
{
    SearchView * w = new SearchView(server, this);
    w->show();
}

void MainWindow::on_login_button_clicked()
{
    LoginDialog * w = new LoginDialog(server, this);
    connect(w, SIGNAL(login()), this, SLOT(librarian_login()));
    w->show();
}

void MainWindow::on_help_button_clicked()
{
    HelpDialog * w = new HelpDialog(this);
    w->show();
}

void MainWindow::librarian_login()
{
    emit closed();
    this->close();
}


void MainWindow::on_MainWindow_destroyed()
{
    emit closed();
}
