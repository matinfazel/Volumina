#ifndef CLIENTTASK_H
#define CLIENTTASK_H

#include <QDebug>
#include <QObject>
#include <QThreadPool>
#include <QTcpSocket>
#include "taskconfirm.h"
#include "authservice.h"
//#include "repository.h"

class ClientTask : public QObject
{
    Q_OBJECT
public:
    explicit ClientTask(QObject * parent = nullptr);
    void setDescriptor(qintptr);

protected:


private:
    qintptr descriptor;
    QTcpSocket * socket;
    bool loggedIn = false;

    bool logged_in;
    int librarian_id;

public slots:
    void readyRead();
    void connected();
    void disconnected();
    void TaskResult(QByteArray);
};

#endif // CLIENTTASK_H
