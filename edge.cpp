#include "edge.h"

int Edge::edge_id(1);

Edge::Edge(Graph* gr)
{
    this->index = edge_id++;
    this->first = nullptr;
    this->second = nullptr;
    this->gr = gr;
}

Edge::Edge()
{
    this->index = edge_id++;
    this->first = nullptr;
    this->second = nullptr;
}

void Edge::set_first(Vertex *vertex)
{
    this->first = vertex;
}

void Edge::set_second(Vertex *vertex)
{
    this->second = vertex;
}

bool Edge::calc_weight()
{
    int f = gr->get_vert_position(first);
    int s = gr->get_vert_position(second);
    if(f >= 0 && s >= 0) {
        this->weight = abs(f-s);
        return true;
    }
    return false;
}

void Edge::set_weight(int weight)
{
    this->weight = weight;
}

int Edge::get_weight()
{
    return this->weight;
}

Vertex *Edge::get_second()
{
    return this->second;
}

Vertex *Edge::get_first()
{
    return this->first;
}
