#ifndef TASKCONFIRM_H
#define TASKCONFIRM_H

#include <QObject>
#include <QRunnable>

class TaskConfirm : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TaskConfirm();
protected:
     void run() override;

signals:
    void result(QString);
};

#endif // TASKCONFIRM_H
