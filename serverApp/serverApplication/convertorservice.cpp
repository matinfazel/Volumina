#include "convertorservice.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSqlRecord>
ConvertorService::ConvertorService()
{

}

QJsonDocument ConvertorService::toJson(QSqlQueryModel * query)
{
    QJsonArray jsonArray;
    for (int i = 0; i < query->rowCount(); i++) {
        QJsonObject jsonObject;
        for (int j = 0; j < query->record(i).count(); j++) {
            query->record(i);
            jsonObject.insert(query->record(i).fieldName(j),
                              QJsonValue::fromVariant(query->record(i).value(j)));
        }
        jsonArray.append(jsonObject);
    }
    QJsonDocument returnDoc(jsonArray);
    return returnDoc;
}
