#include "book.h"
#include "repository.h"
Book::Book()
{

}

QJsonDocument Book::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    qDebug() << func << endl;
    if (func == "create") { // creates a new book
        output = create(jsonInput);
    } else if (func == "searchByTitle") { // returns a json array of all bookItems of a certain book
        output = searchByTitle(jsonInput);
    } else if (func == "searchById") { // change status required input is barcode and current status 1 as availabe 0 as unavailable
        output = searchById(jsonInput);
    } else if (func == "searchBySubject"){
        output = searchBySubject(jsonInput);
    } else if (func == "update") {
        output = update(jsonInput);
    } else {
        qDebug() << func << endl;
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}



QJsonDocument Book::create(QJsonDocument input)
{
    Repository q;
    QJsonObject jsonObject = input.object();
    q.createBook(jsonObject["book_id"].toString(),
            jsonObject["title"].toString(), jsonObject["subject"].toString(),
            jsonObject["publisher"].toString(), jsonObject["language"].toString(),
            jsonObject["author"].toString(), jsonObject["translator"].toString(),
            jsonObject["edition"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}


QJsonDocument Book::update(QJsonDocument input)
{
    Repository q;
    QJsonObject jsonObject = input.object();
    q.updateBook(jsonObject["book_id"].toString(),
            jsonObject["title"].toString(), jsonObject["subject"].toString(),
            jsonObject["publisher"].toString(), jsonObject["language"].toString(),
            jsonObject["author"].toString(), jsonObject["translator"].toString(),
            jsonObject["edition"].toString());
    QJsonObject outjson;
    outjson.insert("status", 200);
    QJsonDocument output(outjson);
    return output;
}


QJsonDocument Book::searchById(QJsonDocument input)
{
    Repository repo;
    return repo.readBooksById(input.object()["Id"].toString());

}


QJsonDocument Book::searchByTitle(QJsonDocument input)
{
    Repository repo;
    qDebug() << input.object()["Title"].toString() << endl;
    return repo.readBooksByTitle(input.object()["Title"].toString());
}

QJsonDocument Book::searchBySubject(QJsonDocument input)
{
    Repository repo;
    return repo.readBooksBySubject(input.object()["Subject"].toString());
}
