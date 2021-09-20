#include "edge.h"

int edge::edge_count = 0;

edge::edge(int weight)
{
    this->id = ++edge_count;
    this->weight = weight;
}

bool edge::set_first(node *vertex)
{
    if(vertex != nullptr) {
        this->first = vertex;
        return true;
    }
    return false;
}

bool edge::set_second(node *vertex)
{
    if(vertex != nullptr) {
        this->second = vertex;
        return true;
    }
    return false;
}

void edge::set_weight(int weight)
{
    if(weight > 0) {
        this->weight = weight;
    }
}

int edge::get_weight()
{
    return this->weight;
}

node *edge::get_node(int number)
{
    if(number == 2) {
        return this->second;
    }
    if(number == 1) {
        return this->first;
    }
    return nullptr;
}

int edge::get_first_node_id()
{
    return first->get_id();
}

int edge::get_second_node_id()
{
    return second->get_id();
}

void edge::reset()
{
    edge_count = 0;
}
