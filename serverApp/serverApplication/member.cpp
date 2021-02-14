#include "member.h"

Member::Member()
{

}

QJsonDocument Member::response(QJsonDocument input)
{
    QString func = input.object().value("Func").toString();
    QJsonDocument jsonInput(input.object().value("Input").toObject());
    QJsonDocument output;
    if (func == "create") { // creates a new book
        output = create(jsonInput);
    } else if (func == "searchByMemberId") { // returns a json array of all bookItems of a certain book
        output = searchByMemberId(jsonInput);
    } else if (func == "searchByAccountId") { // change status required input is barcode and current status 1 as availabe 0 as unavailable
        output = searchByAccountId(jsonInput);
    } else if (func == "searchByName"){
        output = searchByName(jsonInput);
    } else if (func == "renew") {
        output = renew(jsonInput);
    } else if (func == "addPenalty") {
        output = addPenalty(jsonInput);
    } else if (func=="addPayment"){
        output = addPayment(jsonInput);
    } else if (func == "update") {
        output = update(jsonInput);
    } else if(func=="readPenalty"){
        output = readpenalty(jsonInput);
    }
    else {
        QJsonObject jsonOut;
        jsonOut.insert("status", 404);
        output.setObject(jsonOut);
    }
    return output;
}

QJsonDocument Member::searchByMemberId(QJsonDocument input) {
    Repository repo;
    return repo.readMembersByMemberId(input.object()["MemberId"].toString());
}

QJsonDocument Member::searchByAccountId(QJsonDocument input) {
    Repository repo;
    return repo.readMembersByAccountId(input.object()["AccountId"].toString());
}

QJsonDocument Member::searchByName(QJsonDocument input) {
    Repository repo;
    return repo.readMembersByName(input.object()["Name"].toString());
}

QJsonDocument Member::create(QJsonDocument input)
{
    qDebug() << "create Member \n";
    Repository repo;
    QJsonObject json = input.object();
    QString card_expire_date=QDate::currentDate().QDate::addYears(1).toString("yyyy-MM-dd");

    repo.createMember(json["member_id"].toString(), json["card_number"].toString(),
            json["account_id"].toString(), card_expire_date, json["name"].toString(),
            json["email"].toString(), json["birthday"].toString(),
            json["address"].toString(), json["phone_number"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::update(QJsonDocument input)
{
    Repository repo;
    QJsonObject json = input.object();
    qDebug() << "Here We Go again" << endl;
    repo.updateMember(json["account_id"].toString(), json["email"].toString(),
            json["address"].toString(), json["phone_number"].toString(),
            json["card_number"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::renew(QJsonDocument input)
{
    Repository repo;
    QJsonObject json = input.object();
    QDate expire = QDate::fromString(json["card_expire_date"].toString(), "yyyy-MM-dd");
    expire = expire.addYears(1);
    qDebug() << expire.toString() << " " << json["account_id"].toString() << endl;
    repo.renewMember(json["account_id"].toString(), expire.toString("yyyy-MM-dd"));
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::remove(QJsonDocument jsondoc)
{
    Repository repo;
    repo.deleteMember(jsondoc.object()["account_id"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::addPenalty(QJsonDocument jsondoc)
{
    Repository repo;
    repo.addPenalty(jsondoc.object()["account_id"].toString(),jsondoc.object()["penalty"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::addPayment(QJsonDocument jsondoc)
{
    Repository repo;
    repo.add_payment(jsondoc.object()["account_id"].toString(),jsondoc.object()["penalty"].toString());
    QJsonObject outjson;
    outjson.insert("status", 201);
    QJsonDocument output(outjson);
    return output;
}

QJsonDocument Member::readpenalty(QJsonDocument jsondoc)
{
    Repository repo;
    return repo.readPenalty(jsondoc.object()["account_id"].toString());
}

Member::~Member() {

}
