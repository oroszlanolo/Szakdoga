#ifndef AVLB_H
#define AVLB_H

#include "node_b.h"

typedef struct NodeB * TreeB;

/**
 *AVL TreeB - storing the heights in every node 
 */
class AvlTreeB{
public:
    bool insert(TreeB &, int);
    bool del(TreeB &, int);
    bool getMin(TreeB &, TreeB &);
    void print(TreeB);
    TreeB getNode(TreeB, int);

private:
    bool rootDel(TreeB &);
    bool leftTreeGrow(TreeB &);
    bool rightTreeGrow(TreeB &);
    bool leftTreeShrink(TreeB &);
    bool rightTreeShrink(TreeB &);
    bool rightTreeMinToRoot(TreeB &);
    
    //  M   -   minus
    //  P   -   plus
    bool balancePP(TreeB &);
    bool balanceMM(TreeB &);
    void balanceMMm(TreeB &, TreeB);
    void balanceMMp(TreeB &, TreeB);
    void balancePPm(TreeB &, TreeB);
    void balancePPp(TreeB &, TreeB);
    void balancePP0(TreeB &, TreeB);
    void balanceMM0(TreeB &, TreeB);
};

#endif