#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include "basecontroller.h"
#include "convertorservice.h"
#include "repository.h"
#include <QJsonArray>
#include <QDate>

class Librarian : public BaseController
{
public:
    Librarian();
    QJsonDocument response(QJsonDocument);// to do
    QJsonDocument create(QJsonDocument);
    int remove(QJsonDocument);// to do
    QJsonDocument update(QJsonDocument);
    QJsonDocument searchByAccountId(QJsonDocument);
};

#endif // LIBRARIAN_H
