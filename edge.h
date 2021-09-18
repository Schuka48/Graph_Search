#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class node;
class edge
{
    static int edge_count;
    int id;
    int weight;
    node* first;
    node* second;

public:
    edge(int weight = 0);

    bool set_first(node* vertex);
    bool set_second(node* vertex);
    void set_weight(int weight);

    int get_weight();
    node* get_node(int number);
};

#endif // EDGE_H
