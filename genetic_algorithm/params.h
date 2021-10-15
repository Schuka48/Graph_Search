#ifndef PARAMS_H
#define PARAMS_H


class Params
{
    int population_size;
    int iter_count;
    double mutation_potention;
    int num_steps_without_improvment;

public:
    Params();

    void set_population_size(int population_size);
    void set_iter_count(int iter_count);
    void set_mutation_potention(double mutation_potention);
    void set_num_steps_without_improvment(int num);

    int get_population_size();
    int get_iter_count();
    double get_mutation_potention();
    int get_num_steps_without_improvment();
};

#endif // PARAMS_H
