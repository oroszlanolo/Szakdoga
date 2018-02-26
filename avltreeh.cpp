#include <iostream>
#include <cstddef>
#include "avltreeh.h"
#include "node.h"

void AvlTreeH::insert(int k, Tree &p){
    //if the tree is empty(the root is null), then create a new root with the value "k" as the key.
    if(p == NULL){
        p = new Node(k);
        return;
    }
    if(k < p->key){
        AvlTreeH::insert(k,p->left);
    }else{
        AvlTreeH::insert(k,p->right);
    }

}

void AvlTreeH::print(Tree &p){
    if(p == NULL){
        std::cout << "Empty tree" << std::endl;
        return;
    }
    if(p->left != NULL){
        AvlTreeH::print(p->left);
    }
    std::cout << p->key << ", ";
    if(p->right != NULL){
        AvlTreeH::print(p->right);
    }
}