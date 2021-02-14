#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include "repository.h"

class BaseController
{
public:
    BaseController();
    virtual QJsonDocument response(QJsonDocument) = 0;
};

#endif // BASECONTROLLER_H
