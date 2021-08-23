#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include "graph.h"

class Vertex;
class Graph;

class Edge
{
    int index;
    int weight;
    Vertex* first;
    Vertex* second;
    Graph* gr;

    static int edge_id;

public:
    Edge(Graph* gr);
    Edge();
    bool inline operator== (const Edge& edge){
        return this->index == edge.index;
    }
    bool inline operator > (const Edge& edge) {
        return this->weight > edge.weight;
    }
    bool inline operator < (const Edge& edge) {
        return this->weight < edge.weight;
    }

    void set_first(Vertex* vertex);
    void set_second(Vertex* vertex);

    bool calc_weight();
    void set_weight(int weight);
    int get_weight();
    Vertex* get_second();
    Vertex* get_first();
};

#endif // EDGE_H
