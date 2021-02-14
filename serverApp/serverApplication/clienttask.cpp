#include "clienttask.h"
#include "basecontroller.h"
#include "bookitem.h"
#include "book.h"
#include "lend.h"
#include "transactionItem.h"
#include "member.h"
#include "librarian.h"
#include <QJsonDocument>
#include <QJsonObject>

ClientTask::ClientTask(QObject * parent) : QObject(parent)
{
    this->logged_in = false;
    this->librarian_id = -1;
}

void ClientTask::setDescriptor(qintptr descriptor)
{
    this->socket = new QTcpSocket();
    socket->setSocketDescriptor(descriptor);

    connect(this->socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Client " << descriptor << "connected.";

}

void ClientTask::readyRead()
{
    QByteArray msg = this->socket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(msg);
    QString klass = jsonDocument.object().value("Class").toString();
    QString func = jsonDocument.object().value("Func").toString();
    QJsonDocument jsonInput(jsonDocument.object().value("Input").toObject());
    qDebug() << "Client " << this->socket->socketDescriptor() << ": " << msg;
    QMap<QString, BaseController *> mp;
    mp["Member"] = new Member();
    mp["BookItem"] = new BookItem();
    mp["Book"] = new Book();
    mp["Lend"] = new Lend();
    mp["Librarian"] = new Librarian();
    mp["TransactionItem"] = new TransactionItem();
    QJsonDocument output;
    if (klass == "login"){
        AuthService *login = new AuthService();
        output = login->login(jsonDocument);
    } else if (mp[klass] != nullptr){
        output = mp[klass]->response(jsonDocument);
    } else {

    }
    TaskResult(output.toJson());

//    if (true)
//    {
//    TaskConfirm * rsptask = new TaskConfirm();
//        rsptask->setAutoDelete(true);
//        connect(rsptask, SIGNAL(result(QString)), this, SLOT(TaskResult(QString)), Qt::QueuedConnection);
//        QThreadPool::globalInstance()->start(rsptask);
//    }
}

void ClientTask::connected()
{
    //qDebug() << "client connect event";
}

void ClientTask::disconnected()
{
    qDebug() << "Client " << this->socket->socketDescriptor() << " disconnected.";
}


void ClientTask::TaskResult(QByteArray otp)
{
    //This function sends the results of a finished task to the client
    otp += "\r\n";
    this->socket->write(otp);
    this->socket->flush();
    qDebug() << this->socket->socketDescriptor() << " < " << otp << endl;
}
