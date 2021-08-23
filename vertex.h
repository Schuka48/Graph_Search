#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"
#include "graph.h"
#include <QList>

class Edge;
class Graph;

class Vertex
{
    int id;
    bool is_New;
    QList<Edge*> connect_edge;
    Graph* gr;

    static int vert_id;
public:
    Vertex(Graph* gr);
    bool inline operator!= (const Vertex& v) {
        return this->id != v.id;
    }
    bool inline operator== (const Vertex& v) {
        return this->id == v.id;
    }
    int get_id();
    QList<Edge*>& get_edges();
};

#endif // VERTEX_H
