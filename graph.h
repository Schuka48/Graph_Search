#ifndef GRAPH_H
#define GRAPH_H

typedef unsigned long ul;

#include "vertex.h"
#include "edge.h"

#include <QList>
#include <QTextStream>

using namespace std;

class Edge;
class Vertex;

class Graph
{
    int id;
    int size;
    QList<Edge> edges;
    QList<Vertex> verts;
    ul gr_sum;

    static int gr_id;


public:
    Graph();
    bool LoadFromFile(QFile* file);
    void set_graph_size(int size);
    Vertex& get_vertex(int index);
    int get_vert_position(Vertex* v);
    ul get_sum();
    void calculate();
    Edge* get_max_edge();
    int get_graph_size();
    void find_best_posting(Edge* edge);
    void recalc(int first, int second);
};

#endif // GRAPH_H
