#include "mainwindow.h"
#include "connectdialog.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerConnection * server = new ServerConnection();
    ConnectDialog e(server);
    e.show();
    return a.exec();
}
