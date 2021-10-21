#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QThread>
#include "population.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(Graph* individ, Params params, int threadCount, QObject *parent = nullptr);

signals:
    void finish();

public slots:
    void start();
    void started();
    void finished();
    void algorithm_finished();
    QList<Population*>& get_result();

private:
    QList<QThread*> threads;
    Graph* start_individ;
    Params population_params;
    QList<Population*> all_populations;
    int finished_algorithms = 0;

    void check_finished();
};

#endif // MANAGER_H
