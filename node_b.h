#ifndef NODEB_H
#define NODEB_H

#include <cstddef>

struct NodeB{
    int key;
    int balance;
    NodeB* left;
    NodeB* right;


    NodeB(int k){
        key = k;
        left = right = NULL;
        balance = 0;
    }
};


#endif