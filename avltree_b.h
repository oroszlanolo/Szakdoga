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
    bool rootDel(Tree &);
    bool getMin(Tree &, Tree &);
    void print(Tree &);
    bool leftTreeGrow(Tree &);
    bool rightTreeGrow(Tree &);
    bool leftTreeShrink(Tree &);
    bool rightTreeShrink(Tree &);
    bool rightTreeMinToRoot(Tree &);
    
    //  M   -   minus
    //  P   -   plus
    bool balancePP(Tree &);
    bool balanceMM(Tree &);
    void balanceMMm(Tree &, Tree);
    void balanceMMp(Tree &, Tree);
    void balancePPm(Tree &, Tree);
    void balancePPp(Tree &, Tree);
    void balancePP0(Tree &, Tree);
    void balanceMM0(Tree &, Tree);
};

#endif