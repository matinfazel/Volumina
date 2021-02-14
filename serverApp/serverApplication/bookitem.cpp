#include "bookitem.h"
#include "repository.h"
BookItem::BookItem()
{

}


QJsonDocument BookItem::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    if (func == "create") { // creates a new bookItem
        output = create(jsonInput);
    } else if (func == "readAllBooks") { // returns a json array of all bookItems of a certain book
        output = readAllBooks(jsonInput);
    } else if (func == "readById") { // change status required input is barcode and current status 1 as availabe 0 as unavailable
        output = readById(jsonInput);
    } else if (func == "changeStatus") { // change status required input is barcode and current status 1 as availabe 0 as unavailable
        output = changeStatus(jsonInput);
    } else {
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}


QJsonDocument BookItem::create(QJsonDocument input) {
    Repository q;
    QJsonObject jsonObject = input.object();
    q.createBookItem(jsonObject["book_id"].toString(), "1",
            jsonObject["barcode"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}


QJsonDocument BookItem::readAllBooks(QJsonDocument input) {
    Repository q;
    return q.readAllBookItem(input.object()["book_id"].toString());
}

QJsonDocument BookItem::readById(QJsonDocument input) {
    Repository q;
    return q.readBookItem(input.object()["book_item_id"].toString());
}


QJsonDocument BookItem::changeStatus(QJsonDocument input) {
    Repository q;
    QJsonObject jsonObject = input.object();
    q.updateBookItem(jsonObject["book_item_id"].toString(), jsonObject["status"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}
