#include "manager.h"

Manager::Manager(Graph *individ, Params params, int threadCount, QObject *parent) : QObject(parent)
{
    this->start_individ = individ;
    this->population_params = params;

    for(int i = 0; i < threadCount; i++) {
        QThread* thread = new QThread(this);
        thread->setObjectName("Thread N " + QString::number(i));

        connect(thread, &QThread::started, this, &Manager::started);
        connect(thread, &QThread::finished, this, &Manager::finished);

        threads.append(thread);
    }
}

void Manager::start()
{
    for(auto thread: threads) {
        Population* population = new Population(start_individ, this->population_params);
        all_populations.push_back(population);
        population->moveToThread(thread);

        connect(thread, &QThread::started, population, &Population::start);
        connect(population, &Population::finished, this, &Manager::algorithm_finished);
        thread->start();

    }

}

void Manager::started()
{
    QThread* thread = qobject_cast<QThread*>(sender());

    if(!thread) return;
}

void Manager::finished()
{
    QThread* thread = qobject_cast<QThread*>(sender());
    thread->deleteLater();
}

void Manager::algorithm_finished()
{
    // тут выполняется код по обработке завершения алгоритма
    this->finished_algorithms++;
    check_finished();
}

QList<Population *> &Manager::get_result()
{
    return all_populations;
}

void Manager::check_finished()
{
    if(this->finished_algorithms == threads.size())
        emit finish();
}
