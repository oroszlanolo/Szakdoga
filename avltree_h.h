#ifndef AVLH_H
#define AVLH_H

#include "node_h.h"

typedef struct NodeH * Tree;

/**
 *AVL Tree - storing the heights in every node 
 */
class AvlTreeH
{
public:
    void insert(Tree &, int);
    bool del(Tree &, int);
    void getMin(Tree &, Tree &);
    void print(Tree);
    Tree getNode(Tree, int);
private:
    int height(Tree);
    void rootDel(Tree &);
    void rightBalance(Tree &);
    void leftBalance(Tree &);
};

#endif