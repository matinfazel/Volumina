#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include "clienttask.h"

class HTTPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HTTPServer(QObject *parent = nullptr);
    void startServer();

protected:
    void incomingConnection(qintptr descriptor);

};

#endif // HTTPSERVER_H
