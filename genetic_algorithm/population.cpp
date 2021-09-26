#include "population.h"

Population::Population()
{
    best_individ = new Graph();
}

Population::Population(Graph* graph, Params population_params)
{

    this->population_params = population_params;
    int pop_size = this->population_params.get_population_size();

    QRandomGenerator* rg = QRandomGenerator::global();
    for(int i = 0; i < pop_size; i++) {
        Graph* individual = new Graph(*graph);
        if(i != 0){
            int try_count = 1;
            try_count = rg->bounded(1, pop_size - 1);
            for(int i(0); i < try_count; i++)
                individual->node_swap(true);
        }
        this->individs.push_back(individual);
    }

    delete rg;

    this->best_individ = get_best_individ();
}

void Population::start()
{
    // функция запуска Генетического алгоритма
}

void Population::mutation(int individ_position)
{
    this->individs[individ_position]->node_swap(true);
}

void Population::idivid_inverison()
{

}

Graph *&Population::get_best_individ()
{
    int best_sum = this->individs[0]->get_sum();
    int best_index = 0;

    for(auto &individ: this->individs) {
        if(individ->get_sum() < best_sum) {
            best_sum = individ->get_sum();
            best_index = this->get_individ_position(individ->get_id());
        }
    }
    return this->individs[best_index];
}

int Population::get_best_individ_position()
{
    int best_sum = this->individs[0]->get_sum();
    int best_index = 0;

    for(auto &individ: this->individs) {
        if(individ->get_sum() < best_sum) {
            best_sum = individ->get_sum();
            best_index = this->get_individ_position(individ->get_id());
        }
    }
    return best_index;
}

int Population::get_individ_position(int individ_id)
{
    int position = 0;

    for(const auto& individ: this->individs) {
        if(individ->get_id() == individ_id)
            return position;
        position++;
    }
    return -1;
}

