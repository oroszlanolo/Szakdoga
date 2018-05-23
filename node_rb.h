#ifndef NODERB_H
#define NODERB_H

#include <cstddef>

enum RBColor{
    RED,BLACK
};

struct NodeRB
{
    int key;
    RBColor color;
    NodeRB *left, *right, *parent;


    NodeRB(int k, RBColor col, NodeRB* nil, NodeRB* p)
    {
        key = k;
        left = right = nil;
        color = col;
        parent = p;
    }
    ~NodeRB()
    {
        delete left;
        delete right;
    }
};


#endif