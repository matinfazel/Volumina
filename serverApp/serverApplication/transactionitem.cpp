#include "transactionItem.h"
#include <QDate>
TransactionItem::TransactionItem()
{

}

QJsonDocument TransactionItem::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    if (func == "create") { // creates a new transaction item
        output = create(jsonInput);
    } else if (func == "searchByMember") { // returns a json array of all bookItems of a certain book
        output = searchByMember(jsonInput);
    } else {
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}

QJsonDocument TransactionItem::searchByMember(QJsonDocument input)
{
    Repository repo;
    return repo.readTransactionByMember(input.object()["member_id"].toString());
}

QJsonDocument TransactionItem::create(QJsonDocument jsondoc)
{
    Repository repo;
    QString member_id=jsondoc.object()["member_id"].toString();
    QString payment=jsondoc.object()["payment"].toString();
    QString payment_date= QDate::currentDate().toString("yyyy-MM-dd");
    repo.createTransactionItem(member_id,payment,payment_date);
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;

}

QJsonDocument TransactionItem::read(QJsonDocument jsondoc)
{
    Repository * x=new Repository();
    QString transaction_id=jsondoc.array().at(0)["transaction_id"].toString();

    return x->readTransactionId(transaction_id);


}




