#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "basecontroller.h"
class AuthService
{

public:
    AuthService();

    QJsonDocument login(QJsonDocument);
private:
    QString username;
    QString password;
};

#endif // AUTHSERVICE_H
