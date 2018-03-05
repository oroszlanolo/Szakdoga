#ifndef AVLH_H
#define AVLH_H

#include "node.h"

typedef struct NodeH * Tree;

/**
 *AVL Tree storing the heights in every node 
 */
class AvlTreeH{
public:
    void insert(Tree &, int);
    void print(Tree &);
    int height(Tree);
    void rightBalance(Tree &);
    void leftBalance(Tree &);
};

#endif