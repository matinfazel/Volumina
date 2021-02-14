#ifndef BOOKITEM_H
#define BOOKITEM_H

#include "basecontroller.h"

class BookItem : public BaseController
{
public:
    BookItem();
    QJsonDocument response(QJsonDocument) override;
    QJsonDocument create(QJsonDocument);
    QJsonDocument readById(QJsonDocument);
    QJsonDocument readAllBooks(QJsonDocument);
    QJsonDocument changeStatus(QJsonDocument);
    QJsonDocument remove(QJsonDocument);
};

#endif // BOOKITEM_H
