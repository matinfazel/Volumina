#ifndef CONVERTORSERVICE_H
#define CONVERTORSERVICE_H

#include <QJsonDocument>
#include <QSqlQueryModel>

class ConvertorService
{
public:
    ConvertorService();
    static QJsonDocument toJson(QSqlQueryModel *);
};

#endif // CONVERTORSERVICE_H
