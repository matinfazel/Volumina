#ifndef MEMBER_H
#define MEMBER_H

#include "basecontroller.h"
#include "convertorservice.h"
#include "repository.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDate>
class Member : public BaseController
{
public:
    Member();
    QJsonDocument response(QJsonDocument);
    QJsonDocument searchByName(QJsonDocument);
    QJsonDocument searchByAccountId(QJsonDocument);
    QJsonDocument searchByMemberId(QJsonDocument);
    QJsonDocument findID(QJsonDocument) ;
    QJsonDocument create(QJsonDocument);
    QJsonDocument renew(QJsonDocument);
    QJsonDocument read(QJsonDocument);
    QJsonDocument update(QJsonDocument);
    QJsonDocument remove(QJsonDocument);
    QJsonDocument addPenalty(QJsonDocument);
    QJsonDocument addPayment(QJsonDocument);
    QJsonDocument readpenalty(QJsonDocument);
    ~Member();
};



#endif // MEMBER_H
