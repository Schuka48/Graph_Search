#ifndef POPULATION_H
#define POPULATION_H

#include <QList>
#include "graph/graph.h"
#include "genetic_algorithm/params.h"

class Population
{
    QList<Graph*> individs;
    Params population_params;

public:
    Population();
    Population(Graph* graph, Params population_params);

    void start();
};

#endif // POPULATION_H
