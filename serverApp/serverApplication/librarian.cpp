#include "librarian.h"

Librarian::Librarian()
{

}


QJsonDocument Librarian::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    if (func == "create") { // creates a new book
        output = create(jsonInput);
    } else if (func == "searchByAccountId") { // change status required input is barcode and current status 1 as availabe 0 as unavailable
        output = searchByAccountId(jsonInput);
    } else if (func == "update") {
        output = update(jsonInput);
    } else {
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}


//QJsonDocument Librarian::findID(QJsonDocument jsondoc)
//{

//    if (!jsondoc.array().at(0)["name"].toString().isEmpty())
//    {
//        QString name=jsondoc.array().at(0)["name"].toString();

//        QSqlQueryModel *model=new QSqlQueryModel();
//        QSqlQuery q;
//        QSqlQuery member;
//        model=new QSqlQueryModel();
//        QString query;
//        query="select * from account join librarian on account.name like '%";
//        query+=name;
//        query+="%'";
//        int i=0;
//        q.exec(query);
//        query+=" where ";
//        while( q.next())
//        {
//            if (i>0)
//                query+=" or ";
//            QString account_id= q.value("account_id").toString();
//            QString member_id= q.value("account_id").toString();
//            query+="  (librarian.account_id=";
//            query+=member_id;
//            query+=" and account.account_id=";
//            query+=account_id;
//            query+=")";

//            i++;
//       }
//        model->setQuery(query);
//        return ConvertorService::toJson(model);
//        QJsonDocument d;
//        return d;
//    }

//    else if (!jsondoc.array().at(0)["account_id"].toString().isEmpty())
//    {
//        QString account_id=jsondoc.array().at(0)["account_id"].toString();
//        Repository *x=new Repository();
//        return  x->readLibrarian(account_id);
//    }


//QJsonDocument d;
//return d;
//}

QJsonDocument Librarian::create(QJsonDocument input)
{
    Repository repo;
    QJsonObject jsonObject = input.object();
    repo.createLibrarian(jsonObject["account_id"].toString(),
           jsonObject["name"].toString(), jsonObject["email"].toString(),
           jsonObject["birthday"].toString(), jsonObject["address"].toString(),
           jsonObject["phone_number"].toString(), jsonObject["librarian_id"].toString(),
           jsonObject["password"].toString(),jsonObject["username"].toString());
    QJsonObject outjson;
    outjson.insert("status", 200);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Librarian::searchByAccountId(QJsonDocument input)
{
    Repository repo;
    return repo.readLibrarian(input.object()["account_id"].toString());
}

QJsonDocument Librarian::update(QJsonDocument input)
{
    Repository repo;
    QJsonObject jsonObject = input.object();
    qDebug() << jsonObject["account_id"] << endl;
    long acc=jsonObject["account_id"].toInt();

    repo.updateLibrarian(QString::number(acc),jsonObject["name"].toString(),
           jsonObject["email"].toString(), jsonObject["address"].toString(),
           jsonObject["phone_number"].toString(), jsonObject["password"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

int Librarian::remove(QJsonDocument json)
{
    Repository * x=new Repository();
    QString account_id=json.array().at(0)["account_id"].toString();
    x->deleteLibrarian(account_id);
    return 1;
}
