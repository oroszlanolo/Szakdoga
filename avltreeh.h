#ifndef AVLH_H
#define AVLH_H

#include "node.h"

typedef struct Node * Tree;

class AvlTreeH{
public:
    void insert(int,Tree &);
    void print(Tree &);
};

#endif