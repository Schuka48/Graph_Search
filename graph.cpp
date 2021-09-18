#include "graph.h"

int Graph::count_graph = 0;

Graph::Graph()
{
    this->id = ++count_graph;
    sum = 0;
}

void Graph::LoadFromFile(QFile* file)
{
    if(!file->isOpen())
    {
        return;
    }
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

    swap(0, 2);

    swap(0, 1);
    QString str("");

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
        int first_id = edge->get_node(1)->get_id();
        int second_id = edge->get_node(2)->get_id();
        int new_weight = abs(get_node_position(first_id) - get_node_position(second_id)); // сделать проверку на -1 позиции вершины
        edge->set_weight(new_weight);
    }
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
