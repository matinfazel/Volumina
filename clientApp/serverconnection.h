#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QTcpSocket>

class ServerConnection : public QTcpSocket
{
public:
    ServerConnection();
    int connectToServer(QString);
};
#endif // SERVERCONNECTION_H
