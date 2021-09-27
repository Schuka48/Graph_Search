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

    this->best_individ = get_best_individ();
    this->population_sorting();
    this->tournament_selection();

    delete rg;
}

void Population::start()
{
    // функция запуска Генетического алгоритма
}

void Population::mutation(int individ_position)
{
    this->individs[individ_position]->node_swap(true);
}

void Population::tournament_selection()
{
    int population_size = this->population_params.get_population_size();
    int count_selected_individuals = (population_size / 2) + population_size % 2;


    QList<int> selected_individuals;

    for(int i = 0; i < count_selected_individuals; i++) { // тройки турнирного отбора
        QList<int> tournament_players = get_tournament_players((population_size / 3), population_size);
        // отбор внутри тройки индивидов
        selected_individuals.push_back(tournament_round(tournament_players));
        // из списка selected_individuals сформировать новую популяцию
    }

    QString str("");

//    QList<Graph*> tmp;
//    for(int i = 0; i < count_selected_individuals; i++) {
//        tmp.push_back(individs[i]);
//    }
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

QList<int> Population::get_tournament_players(int tournament_size, int population_size)
{
    QRandomGenerator* rg = QRandomGenerator::global();

    QList<int> individuals_position;
    individuals_position.push_back(rg->bounded(population_size));

    while(individuals_position.size() != tournament_size) {
        int position = static_cast<int>(rg->bounded(population_size));
        if(individuals_position.contains(position))
            continue;

        individuals_position.push_back(position);
    }

    delete rg;
    return individuals_position;
}

int Population::tournament_round(QList<int> &tournament_players)
{
    int best_player = tournament_players[0];
    int best_sum = this->individs[tournament_players[0]]->get_sum();
    for(auto position: tournament_players)
    {
        if(this->individs[position]->get_sum() < best_sum)
        {
            best_player = position;
            best_sum = this->individs[position]->get_sum();
        }
    }
    return best_player; // возвращает индекс лучшего из турнирного раунда
}

void Population::population_sorting()
{
    std::sort(individs.begin(), individs.end(), Comparator());
}

