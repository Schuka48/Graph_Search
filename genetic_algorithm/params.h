#ifndef PARAMS_H
#define PARAMS_H


class Params
{
    int population_size;
    int iter_count;
    double mutation_potention;
    int num_steps_without_improvment;
    int tournament_size;
    int thread_count;

public:
    Params();

    void set_population_size(int population_size);
    void set_iter_count(int iter_count);
    void set_mutation_potention(double mutation_potention);
    void set_num_steps_without_improvment(int num);

    int get_population_size() const;
    int get_iter_count() const;
    double get_mutation_potention() const;
    int get_num_steps_without_improvment() const;
    int get_tournament_size() const;
    void set_tournament_size(int value);
    int get_thread_count() const;
    void set_thread_count(int value);
};

#endif // PARAMS_H
