#ifndef POPULATION_H
#define POPULATION_H

#include <QList>
#include <QRandomGenerator>
#include <memory>
#include <QObject>

#include "graph/graph.h"
#include "genetic_algorithm/params.h"



class Population: public QObject
{
    Q_OBJECT

    QList<Graph*> individs;
    Params population_params;
    Graph* best_individ;
    int number_of_rounds_without_improvement;
    bool fixation = false;
    Graph* selected_individual;

public:
    explicit Population(QObject *parent = nullptr);
    explicit Population(Graph* graph, Params population_params, QObject *parent = nullptr);

    Graph*& get_best_individ();
    QList<Graph*>& get_population();

    void start();

private:

    int get_best_individ_position();
    int get_individ_position(int individ_id);

    QList<int> get_tournament_players(int tournament_size, int population_size);
    int tournament_round(QList<int>& tournament_players);

    void population_sorting();
    void mutation(int individ_position);
    void tournament_selection();
    void crossing_individs();
    void population_mutation();
    void round();
    void algorithm();

    bool freeze_check(Graph* new_best_individ);

    void population_cleanup(const QList<Graph*>& new_population);
    void _crossIndivids(QPair<int, int> border_slice, int first_parent, int second_parent); 

signals:
    void finished();
};

#endif // POPULATION_H
