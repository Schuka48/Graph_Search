#include "population.h"

Population::Population()
{

}

Population::Population(Graph* graph, Params population_params)
{

    this->population_params = population_params;

    int pop_size = this->population_params.get_population_size();

    for(int i = 0; i < pop_size; i++) {
        Graph* individual = new Graph(*graph);
        this->individs.push_back(individual);
    }
}

void Population::start()
{
    // функция запуска Генетического алгоритма
}
