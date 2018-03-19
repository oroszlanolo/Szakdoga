#ifndef AVLB_H
#define AVLB_H

#include "node_b.h"

typedef struct NodeB * Tree;

/**
 *AVL Tree - storing the heights in every node 
 */
class AvlTreeB{
public:
    bool insert(Tree &, int);
    bool del(Tree &, int);
    void rootDel(Tree &);
    void getMin(Tree &, Tree &);
    void print(Tree &);
    bool leftTreeGrow(Tree &);
    bool rightTreeGrow(Tree &);
    
    //  M   -   minus
    //  P   -   plus
    void balanceMMm(Tree &, Tree);
    void balanceMMp(Tree &, Tree);
    void balancePPm(Tree &, Tree);
    void balancePPp(Tree &, Tree);
};

#endif