#include "vertex.h"

int Vertex::vert_id(1);

Vertex::Vertex(Graph* gr)
{
    this->id = vert_id++;
    is_New = true;
    this->gr = gr;
}

int Vertex::get_id()
{
    return this->id;
}

QList<Edge*> &Vertex::get_edges()
{
    return connect_edge;
}

