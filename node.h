#ifndef NODE_H
#define NODE_H

#include <cstddef>

struct Node{
    int key;
    int height;
    Node* left;
    Node* right;


    Node(int k){
        key = k;
        left = right = NULL;
        height = 0;
    }
};


#endif