#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Graph
{
    static int count_graph;
    int id;
    int size;
    int sum;
    QList<node*> nodes;
    QList<edge*> edges;

public:
    Graph();
    Graph(const Graph&);

    Graph& operator= (const Graph& graph);

    void LoadFromFile(QFile* file);

    node* get_node(int index);
    int get_sum();
    int get_node_count();


private:
    int count_sum();
    void set_sum(int sum = INT_MAX);
    void swap(const int first, const int second);
    void edge_recalc();
    void reset();


    int get_node_position(int node_id);
    int get_node_position(QList<node*>& nodes, int node_id);
};

#endif // GRAPH_H
