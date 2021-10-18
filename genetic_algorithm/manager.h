#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QThread>
#include "population.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(int threadCount, QObject *parent = nullptr);

signals:

public slots:
    void start();
    void started();
    void finished();

private:
    QList<QThread*> threads;
};

#endif // MANAGER_H
