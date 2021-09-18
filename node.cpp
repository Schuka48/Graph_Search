#include "node.h"

int node::node_count = 0;

node::node()
{
    this->id = ++node_count;
}

void node::add_edge(edge *ed)
{
    this->edges.push_back(ed);
}

edge*node::get_edge(int index)
{
    if(this->edges.count() > index)
    {
        return this->edges[index];
    }
    return this->edges[0];
}

int node::get_id()
{
    return this->id;
}


