#include "manager.h"

Manager::Manager(int threadCount, QObject *parent) : QObject(parent)
{
    for(int i = 0; i < threadCount; i++) {
        QThread* thread = new QThread(this);
        thread->setObjectName("Thread N " + QString::number(i));

        connect(thread, &QThread::started, this, &Manager::started);
        connect(thread, &QThread::finished, this, &Manager::finished);
    }
}

void Manager::start()
{

}

void Manager::started()
{
    QThread* thread = qobject_cast<QThread*>(sender());
    if(!thread) return;
}

void Manager::finished()
{

}
