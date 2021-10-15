#include "population.h"

Population::Population()
{
   qDebug() << "Created population with address: " << this;
   this->number_of_rounds_without_improvement = 0;
}

Population::Population(Graph* graph, Params population_params)
{   
    this->number_of_rounds_without_improvement = 0;
    this->population_params = population_params;
    int pop_size = this->population_params.get_population_size();

    QRandomGenerator* rg = QRandomGenerator::global();
    for(int i = 0; i < pop_size; i++) {
        Graph* individual = new Graph(*graph);
        if(i != 0){                     // рандомно меняем структуру графа
            int try_count = 1;
            try_count = rg->bounded(1, pop_size);
            for(int i(0); i < try_count; i++)
                individual->node_swap(true);
        }
        this->individs.push_back(individual);
    }

    this->best_individ = get_best_individ();
    this->population_sorting();

    delete rg;
}

// Запуск Генетического алгоритма
void Population::start()
{
    // функция работы генетического алгоритма расположения графа на линейке
    algorithm();
}

// Мутация особи
void Population::mutation(int individ_position)
{
    this->individs[individ_position]->node_swap(true);
}

void Population::tournament_selection()
{
    int population_size = this->population_params.get_population_size();
    int count_selected_individuals = (population_size / 2) + population_size % 2; // количество необходимых раундов

    QList<int> selected_individuals; // позиции индивидов, отобранных турнирным методом
    QList<Graph*> tmp;

    for(int i = 0; i < count_selected_individuals; i++) {
        QList<int> tournament_players = get_tournament_players((population_size / 3), population_size); // тройки турнирного отбора
        // отбор внутри тройки индивидов
        selected_individuals.push_back(tournament_round(tournament_players));   
    }
    // из списка selected_individuals сформировать новую популяцию

    // Необходимо, чтобы количество особей, полученных скрещиванием было четным
    // Поэтому, если разница между размером популяции и кол-вом отобранных особей нечетная - добавляем еще одну лучшую из оставшихся
    for(auto position: selected_individuals) {
        if(tmp.indexOf(individs[position]) >= 0) {
            Graph* gr = new Graph(*individs[position]);
            tmp.push_back(gr);
            continue;
        }
        tmp.push_back(individs[position]);
    }
    // если число отобранных особей нечетное - добавляем лучшую особь, которой нет в новой популяции
    if(((population_size - count_selected_individuals) % 2) == 1) {
        for(auto& individ: this->individs) {
            if(tmp.indexOf(individ) < 0) {
                tmp.push_back(individ);
                break;
            }
        }
    }
    // реализация очистки памяти для особей, не прошедших отбор;
    this->population_cleanup(tmp);
    individs.clear();
    individs = tmp;
}

// Функция скрещивания
void Population::crossing_individs()
{
       int new_population_size = individs.size();
       int population_size = this->population_params.get_population_size();

       int crossing_individs = 0; // количество особей, полученных путем скрещивания

       int i = 0;
       while((crossing_individs + new_population_size) != population_size) {
           QPair<int, int> graph_slice = Graph::generate_graph_slice(individs[0]->get_size());
           _crossIndivids(graph_slice, i, i + 1);
           i += 2;
           crossing_individs += 2;
       }
}

void Population::population_mutation()
{
    int size = this->best_individ->get_size();

    for(int i = 0; i < size; i++) {
        double probability = this->population_params.get_mutation_potention() * 100;
        int potention = QRandomGenerator::global()->bounded(0,100);

        if(potention < probability) {
            this->mutation(i);
        }
    }
}

// раунд генетического алгоритма
void Population::round()
{
    this->tournament_selection();
    this->crossing_individs();
    this->population_mutation();

    bool new_individ_is_better = freeze_check(this->get_best_individ()); // проверка отсутствия улучшения в алгоритме

    if(new_individ_is_better) {
        this->best_individ = this->get_best_individ();
    }
}

// выполнение основного алгоритма программы
void Population::algorithm()
{
    int count_of_round = 0;
    while(count_of_round != population_params.get_iter_count() || fixation != true) {
        round();
        count_of_round++;
    }
}

bool Population::freeze_check(Graph* new_best_individ)
{
    int new_best_sum = new_best_individ->get_sum();
    int best_sum = best_individ->get_sum();
    if(new_best_sum == best_sum) {
        this->number_of_rounds_without_improvement++;

        if(this->number_of_rounds_without_improvement > this->population_params.get_num_steps_without_improvment())
        {
            this->fixation = true;
            return false;
        }
    }
    else if(new_best_sum > best_sum){
        this->number_of_rounds_without_improvement++;
        return false;
    }
    else {
        this->number_of_rounds_without_improvement = 0;
        return true;
    }
    return false;
}

// Освобождение памяти для особей, не прошедших отбор
void Population::population_cleanup(const QList<Graph *>& new_population)
{
    for(const auto & individ: this->individs) {
        if(new_population.indexOf(individ) < 0) {
            delete individ;
        }
    }
}

void Population::_crossIndivids(QPair<int, int> border_slice, int first_parent, int second_parent)
{
    Graph* first_child = individs[first_parent]->cross(individs[second_parent], border_slice);
    Graph* second_child = individs[second_parent]->cross(individs[first_parent], border_slice);

    this->individs.push_back(first_child);
    this->individs.push_back(second_child);
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

// возвращает список участников раунда турнирного отбора
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

// Проведение очередного раунда турнирного отбра
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

