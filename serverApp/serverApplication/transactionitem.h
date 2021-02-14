#ifndef TRANSACTION_ITEM_H
#define TRANSACTION_ITEM_H
#include "basecontroller.h"
#include "convertorservice.h"
#include "repository.h"
#include <QJsonArray>

class TransactionItem :public BaseController
{
public:

    TransactionItem();
    QJsonDocument response(QJsonDocument);
    QJsonDocument create(QJsonDocument);
    QJsonDocument searchByMember(QJsonDocument);
    QJsonDocument read(QJsonDocument);
};

#endif // TRANSACTION_ITEM_H
