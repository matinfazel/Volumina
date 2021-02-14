#ifndef BOOK_H
#define BOOK_H

#include <basecontroller.h>

class Book : public BaseController
{
public:
    Book();
    QJsonDocument response(QJsonDocument) override;
    QJsonDocument create(QJsonDocument);
    QJsonDocument update(QJsonDocument);
    QJsonDocument searchByTitle(QJsonDocument);
    QJsonDocument searchById(QJsonDocument);
    QJsonDocument searchBySubject(QJsonDocument);
};

#endif // BOOK_H
