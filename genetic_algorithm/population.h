#ifndef POPULATION_H
#define POPULATION_H

#include <QList>
#include <QRandomGenerator>
#include <memory>

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

private:
    Graph*& get_best_individ();

    int get_best_individ_position();
    int get_individ_position(int individ_id);

    QList<int> get_tournament_players(int tournament_size, int population_size);
    int tournament_round(QList<int>& tournament_players);

    void population_sorting();
    void mutation(int individ_position);
    void tournament_selection();
    void crossing_individs();
    void round();

    void population_cleanup(const QList<Graph*>& new_population);
    void _crossIndivids(QPair<int, int> border_slice, int first_parent, int second_parent);
};

#endif // POPULATION_H
