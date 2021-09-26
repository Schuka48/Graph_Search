#ifndef POPULATION_H
#define POPULATION_H

#include <QList>
#include <QRandomGenerator>

#include "graph/graph.h"
#include "genetic_algorithm/params.h"

class Population
{
    QList<Graph*> individs;
    Params population_params;
    Graph* best_individ;

public:
    Population();
    Population(Graph* graph, Params population_params);

    void start();
    void mutation(int individ_position);
    void idivid_inverison();
    void round();


    Graph*& get_best_individ();
    int get_best_individ_position();

    int get_individ_position(int individ_id);
};

#endif // POPULATION_H
