#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>



class Graph
{
    friend struct Comparator;
    static int count_graph;
    int id;
    int size;
    int sum;
    QList<node*> nodes;
    QList<edge*> edges;

public:


    Graph();
    Graph(const Graph&);
    ~Graph();

    Graph& operator= (const Graph& graph);

    bool LoadFromFile(QFile* file, int &error);
    void node_swap(bool random, QPair<int, int> node_numbers = {0,1});
    void node_inversion(int start_node);

    node* get_node(int index);
    int get_sum();
    int get_node_count();
    int get_node_position(int node_id);
    int get_id();
    int get_size();

    bool operator<(const Graph* gr);
    bool operator==(Graph* &gr);

    static QPair<int, int> generate_graph_slice(int graph_size);
    Graph *cross(Graph *&individ, QPair<int, int> border);

private:
    int count_sum();
    void set_sum(int sum = INT_MAX);
    void swap(const int first, const int second);
    void edge_recalc();
    void reset();

    int get_node_position(QList<node*>& nodes, int node_id);
};

struct Comparator {
    bool operator()(const Graph* first, const Graph* second){
        return first->sum < second->sum;
    }
};


#endif // GRAPH_H
