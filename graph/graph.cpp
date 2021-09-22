#include "graph.h"

int Graph::count_graph = 0;

Graph::Graph()
{
    this->id = ++count_graph;
    sum = 0;
    reset();
}

Graph::Graph(const Graph & graph)
{
    this->id = ++count_graph;
    reset(); // обнуление id вершин и ребер
    size = graph.size;

    QList<node*> tmp; // временный лист вершин
    for(int i = 0; i < size; i++) {

        node* vertex = new node();
        tmp.push_back(vertex);
    }

    for(const auto& node: graph.nodes) { // расстановка узлов в порядке копируемого графа
        int node_id = node->get_id(); // id первого узла в копируемом графе
        int node_position = get_node_position(tmp, node_id); // позиция в tmp узла с node_id
        this->nodes.push_back(tmp[node_position]); // добавление в this->nodes узла с node_position
    }

    for(int i = 0; i < graph.edges.size(); i++) { // копирование ребер
        edge* ed = new edge();

        int first_node_id = graph.edges[i]->get_first_node_id();
        int second_node_id = graph.edges[i]->get_second_node_id();

        int first_node_position = this->get_node_position(first_node_id);
        int second_node_position = this->get_node_position(second_node_id);

        ed->set_first(this->nodes[first_node_position]);
        ed->set_second(this->nodes[second_node_position]);
        ed->set_weight(graph.edges[i]->get_weight());

        this->edges.push_back(ed);
        this->nodes[first_node_position]->add_edge(ed);
        this->nodes[second_node_position]->add_edge(ed);
    }
    this->sum = graph.sum;
}

Graph &Graph::operator=(const Graph &graph)
{
    if(this == &graph)
        return *this;

    reset();
    this->id = graph.id;
    if(this->nodes.isEmpty() || this->edges.isEmpty())
    {
        this->nodes.clear();
        this->edges.clear();
    }

    size = graph.size;
    sum = graph.sum;

    QList<node*> tmp; // временный лист вершин
    for(int i = 0; i < size; i++) {

        node* vertex = new node();
        tmp.push_back(vertex);
    }

    for(const auto& node: graph.nodes) { // расстановка узлов в порядке копируемого графа
        int node_id = node->get_id(); // id первого узла в копируемом графе
        int node_position = get_node_position(tmp, node_id); // позиция в tmp узла с node_id
        this->nodes.push_back(tmp[node_position]); // добавление в this->nodes узла с node_position
    }
    for(int i = 0; i < size; i++) { // копирование ребер
        edge* ed = new edge();

        int first_node_id = graph.edges[i]->get_first_node_id();
        int second_node_id = graph.edges[i]->get_second_node_id();

        int first_node_position = this->get_node_position(first_node_id);
        int second_node_position = this->get_node_position(second_node_id);

        ed->set_first(this->nodes[first_node_position]);
        ed->set_second(this->nodes[second_node_position]);
        ed->set_weight(graph.edges[i]->get_weight());

        this->edges.push_back(ed);
        this->nodes[first_node_position]->add_edge(ed);
        this->nodes[second_node_position]->add_edge(ed);
    }

    return *this;
}

void Graph::LoadFromFile(QFile* file)
{
    if(!file->isOpen()) return;

    QTextStream txt(file);
    QString size = "";
    txt >> size;

    try {
        this->size = size.toInt();
        qDebug() << size;
    } catch (...) {
        qDebug() << "Wrong!";
        return;
    }

    for(int i(0); i < this->size; i++) {
        node* vertex = new node();
        this->nodes.push_back(vertex);
    }

    for(int i(0); i < this->size; i++) {
        QString str;
        for(int j(0); j < this->size; j++) {
            txt >> str;

            if(str == "INF" || i >= j)
                continue;
                // создание и инициализация ребер + добавление их в список у вершины
            edge* ed = new edge();
            ed->set_first(this->nodes[i]);
            ed->set_second(this->nodes[j]);
            ed->set_weight(abs(i-j));
            this->edges.push_back(ed);

            this->nodes[i]->add_edge(ed);
            this->nodes[j]->add_edge(ed);
        }
    }
    int graph_sum =this->count_sum();
    this->set_sum(graph_sum);

//    swap(0, 2); // тест
//    swap(0, 1);
}

int Graph::get_sum()
{
    return this->sum;
}

int Graph::count_sum() // расчет суммы
{
    int graph_sum = 0;
    for(auto edge: edges) {
        graph_sum += edge->get_weight();
    }
    if(!graph_sum)
        return INT_MAX;
    else return graph_sum;
}

void Graph::set_sum(int sum)
{
    this->sum = sum;
}

void Graph::swap(const int first, const int second) // меняет местами вершины, расположенные по линейке
{
    QList<node*> new_nodes;
    int c(0);
    for(int i(0); i < this->size; i++) {
       if(i != first && i != second) {
           new_nodes.push_back(this->nodes[i]);
       }
       else {
           if(!c){
               new_nodes.push_back(this->nodes[second]);
               c++;
           }
           else {
            new_nodes.push_back(this->nodes[first]);
           }
       }
    }

    this->nodes = new_nodes;
    this->edge_recalc(); // пересчет длин ребер
    this->set_sum(this->count_sum()); // назначение новой суммы веса ребер графа
}

void Graph::edge_recalc() // пересчет весов ребер
{
    for(auto& edge: this->edges) {

        int first_edge_position = get_node_position(edge->get_node(1)->get_id());
        int second_edge_position  = get_node_position(edge->get_node(2)->get_id());
        if (first_edge_position > -1 && second_edge_position > -1) {
            int new_weight = abs(first_edge_position - second_edge_position);
            edge->set_weight(new_weight);
        }
        else {
            edge->set_weight(INT_MAX);
        }
    }
}

void Graph::reset() // сброс id для узлов и ребер
{
    node::reset();
    edge::reset();
}

int Graph::get_node_count()
{
    return this->nodes.size();
}

int Graph::get_node_position(int node_id) // возвращает позцицию вершины по ее id
{
    int c = 0;
    for(auto node: this->nodes) {
        if(node->get_id() == node_id)
            return c;
        c++;
    }
    return -1;
}

int Graph::get_node_position(QList<node *> &nodes, int node_id)
{
    int c = 0;
    for(auto node: nodes) {
        if(node->get_id() == node_id)
            return c;
        c++;
    }
    return -1;

}
