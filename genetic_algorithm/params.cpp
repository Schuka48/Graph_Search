#include "params.h"

Params::Params()
{
    this->population_size = 10;
    this->iter_count = 10;
    this->mutation_potention = 0.01;
}

void Params::set_population_size(int population_size)
{
    this->population_size = population_size;
}

void Params::set_iter_count(int iter_count)
{
    this->iter_count = iter_count;
}

void Params::set_mutation_potention(double mutation_potention)
{
    this->mutation_potention = mutation_potention;
}

int Params::get_population_size()
{
    return this->population_size;
}

int Params::get_iter_count()
{
    return this->iter_count;
}

double Params::get_mutation_potention()
{
    return this->mutation_potention;
}