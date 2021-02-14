#include "httpserver.h"
#define PORT 1234

HTTPServer::HTTPServer(QObject *parent) : QTcpServer(parent)
{

}

void HTTPServer::startServer()
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);

    if (this->listen(QHostAddress::Any, PORT))
    {
        qDebug() << "Server initialization successful.";
    }
    else
    {
        qDebug() << "Server initialization failed.";
    }
}

void HTTPServer::incomingConnection(qintptr descriptor)
{
    qDebug() << "Incomming connection from " << descriptor << ".";
    ClientTask * task = new ClientTask();
    task->setDescriptor(descriptor);
}
