#ifndef NODEH_H
#define NODEH_H

#include <cstddef>

struct NodeH
{
    int key;
    int height;
    NodeH* left;
    NodeH* right;


    NodeH(int k)
    {
        key = k;
        left = right = NULL;
        height = 0;
    }
    ~NodeH()
    {
        delete left;
        delete right;
    }
};


#endif