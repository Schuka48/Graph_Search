#include "graph.h"

int Graph::gr_id = 0;

Graph::Graph()
{
    this->gr_sum = 0;
    this->size = 0;
    this->id = gr_id++;
}

bool Graph::LoadFromFile(QFile *file)
{
    int size;
    QTextStream txt(file);
    txt >> size;
    if(size)
        this->size = size;
    for(int i(0); i < size; i++)
    {
        Vertex v(this);
        verts.push_back(v);
    }
    for(int i(0); i < size; i++)
    {
        QString str;
        for (int j(0); j < size ; j++) {
              txt >> str;
              if(j <= i)
                  continue;
              if(str != "INF") {
                  Edge* ed = new Edge(this);
                  ed->set_first(&get_vertex(i));
                  ed->set_second(&get_vertex(j));
                  if(!ed->calc_weight())
                  {
                      // причина, по которой нельзя посчитать длину ребра
                  }
                  edges.push_back(*ed);
                  verts[i].get_edges().push_back(&edges.last());
                  verts[j].get_edges().push_back(&edges.last());
              }
        }
    }
    this->gr_sum = get_sum();
    return true;
}

void Graph::set_graph_size(int size)
{
    this->size = size;
}

Vertex &Graph::get_vertex(int index)
{
    return  this->verts[index];
}

int Graph::get_vert_position(Vertex *v)
{
    return verts.indexOf(*v);
}

ul Graph::get_sum()
{
    ul sum(0);
    for(auto& ed: edges)
    {
        sum += ul(ed.get_weight());
    }
    return sum;
}

void Graph::calculate()
{

    Edge* max_edge = this->get_max_edge();
    find_best_posting(max_edge);
}

Edge *Graph::get_max_edge()
{
    Edge* max_edge = &edges.first();
    for(auto& ed: edges) {
        if(ed.get_weight() > max_edge->get_weight())
            max_edge = &ed;
    }
    return max_edge;
}

int Graph::get_graph_size()
{
    return this->size;
}

void Graph::find_best_posting(Edge* edge)
{
    int fixed_position = this->get_vert_position(edge->get_first());
    int dynamic_position = this->get_vert_position(edge->get_second());
    for(int i(0); i < this->size; i++) {
        if (i == fixed_position || i == dynamic_position)
            continue;
        swap(verts[dynamic_position], verts[i]); // не понятное поведение программы
        edge->set_weight(abs(fixed_position - i));
        // пересчет ребер поменяных вершин
        recalc(dynamic_position, i);

    }
}

void Graph::recalc(int first, int second)
{
    for(auto& ed: verts[first].get_edges()) {
        if(get_vertex(first) == *ed->get_first() && get_vertex(second) == *ed->get_second())
            continue;
        ed->set_weight(abs(get_vert_position(ed->get_first()) - get_vert_position(ed->get_second())));
    }
    for(auto& ed: verts[second].get_edges()) {
        if(get_vertex(first) == *ed->get_first() && get_vertex(second) == *ed->get_second())
            continue;
        ed->set_weight(abs(get_vert_position(ed->get_first()) - get_vert_position(ed->get_second())));
    }
}
