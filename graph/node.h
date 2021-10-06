#ifndef NODE_H
#define NODE_H

#include "edge.h"

#include <QList>

class edge;
class node
{
    static int node_count;
    int id;
    QList<edge*> edges;

public:
    node();
    void add_edge(edge* ed);
    edge* get_edge(int index);

    int get_id();
    int get_position(int id);

    bool operator== (node *& vertex);

    static void reset();
};

#endif // NODE_H
