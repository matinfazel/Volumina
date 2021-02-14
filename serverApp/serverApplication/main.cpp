#include <QCoreApplication>
#include "repository.h"
#include "httpserver.h"
#include "QJsonArray"
#include "member.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Library.db");
    db.open();
    HTTPServer server;
    server.startServer();

Member x;
Repository xx;
QJsonArray jsonArray,jsonArray1;

    QJsonObject jsonObject,jsonObject1;


        jsonObject.insert("account_id",QJsonValue::fromVariant("2277"));
        jsonObject.insert("penalty",QJsonValue::fromVariant("445"));

jsonArray.append(jsonObject);
QJsonDocument returnDoc(jsonObject);
qDebug()<<x.readpenalty(returnDoc);
        return a.exec();
}
