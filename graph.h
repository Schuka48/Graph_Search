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
    void LoadFromFile(QFile* file);
    node* get_node(int index);
    int get_sum();


private:
    int count_sum();
    void set_sum(int sum = INT_MAX);
    void swap(const int first, const int second);
    void edge_recalc();

    int get_node_position(int node_id);
};

#endif // GRAPH_H
