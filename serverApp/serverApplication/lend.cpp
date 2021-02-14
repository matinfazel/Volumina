#include "lend.h"
#include "convertorservice.h"
#include <QJsonArray>
#include <QDate>
#include <QJsonDocument>

Lend::Lend()
{

}

QJsonDocument Lend::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    if (func == "create") { // creates a new lend
        output = create(jsonInput);
    } else if (func == "searchByMember") { // returns a json array of all bookItems of a certain book
        output = searchByMember(jsonInput);
    } else if (func == "searchByBook") { // returns a json array of all bookItems of a certain book
        output = searchByBook(jsonInput);
    } else if (func == "renew") {
        output = renew(jsonInput);
    } else if (func == "return") {
        output = returnBookItem(jsonInput);
    } else {
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}

QJsonDocument Lend::searchByMember(QJsonDocument input)
{
    Repository repo;
    return repo.readLendByMember(input.object()["member_id"].toString());
}

QJsonDocument Lend::searchByBook(QJsonDocument input)
{
    Repository repo;
    return repo.readLendByBook(input.object()["book_item_id"].toString());
}

QJsonDocument Lend::create(QJsonDocument jsondoc)
{
    Repository repo;
    QString book_item_id = jsondoc.object()["book_item_id"].toString();
    QString member_id = jsondoc.object()["member_id"].toString();
    QString renew_times = "0";
    QString loan_date = QDate::currentDate().toString("yyyy-MM-dd");
    QString return_date = "lended";
    repo.createLend(jsondoc.object()["book_item_id"].toString(),
            jsondoc.object()["member_id"].toString(),
            renew_times, loan_date, return_date);
    BookItem * bookItem = new BookItem();
    QJsonObject status;
    status.insert("book_item_id", jsondoc.object()["book_item_id"].toString());
    status.insert("status", "0");
    QJsonDocument change;
    change.setObject(status);
    bookItem->changeStatus(change);
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Lend::renew(QJsonDocument jsondoc)
{
    Repository * x = new Repository();
    QJsonObject outjson;
    outjson.insert("status", 201);
    QString lend_id = jsondoc.object()["lend_id"].toString();
    QString renew_times = jsondoc.object()["renew_times"].toString();
    int ren = renew_times.toInt();
    ren++;
    if (ren >= 3) {
        outjson["status"] = 406 ;
        QJsonDocument output(outjson);
        return output;
    }
    renew_times=QString::number(ren);
    qDebug()<<renew_times;
    x->updateLend(lend_id,renew_times, "lended");
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Lend::returnBookItem(QJsonDocument input)
{
    Repository repo;
    qDebug() << input.object()["lend_id"].toString() << endl;
    repo.updateLend(input.object()["lend_id"].toString(),
            input.object()["renew_times"].toString(), QDate::currentDate().toString("yyyy-MM-dd"));
    QJsonObject outjson;

    BookItem * bookItem = new BookItem();
    QJsonObject status;
    status.insert("book_item_id", input.object()["book_item_id"].toString());
    status.insert("status", "1");
    QJsonDocument change;
    change.setObject(status);
    bookItem->changeStatus(change);

    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}
