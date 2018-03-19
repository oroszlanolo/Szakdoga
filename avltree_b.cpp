#include <iostream>
#include <cstddef>
#include "avltree_b.h"
#include "node_b.h"

bool AvlTreeB::insert(Tree &t, int k){
    if(t == NULL){
        t = new NodeB(k);
        return true;
    }
    if(k < t->key){
        // d = insert(t->left, k)
        if(insert(t->left, k)){
            // d = leftTreeGrow(t)
            return leftTreeGrow(t);
        }else{
            // d = false
            return false;
        }
    }else if(k > t->key){
        // d = insert(t->right, k)
        if(insert(t->right, k)){
            // d = rightTreeGrow(t)
            return rightTreeGrow(t);
        }else{
            // d = false
            return false;
        }
    }else{
        //d = false;
        return false;
    }
}

bool AvlTreeB::del(Tree &t, int k){
    return false;
}

void AvlTreeB::rootDel(Tree &t){

}


void AvlTreeB::getMin(Tree &t, Tree &minP){

}

bool AvlTreeB::leftTreeGrow(Tree &t){
    if(t->balance == -1){
        Tree l = t->left;
        if(l->balance == -1){
            balanceMMm(t,l);
        }else{
            balanceMMp(t,l);
        }
        // d = false
        return false;
    }else{
        --t->balance;
        // d = (t->balance < 0)
        return t->balance < 0;
    }
}
bool AvlTreeB::rightTreeGrow(Tree &t){
    if(t->balance == 1){
        Tree r = t->right;
        if(r->balance == 1){
            balancePPp(t,r);
        }else{
            balancePPm(t,r);
        }
        return false;
    }else{
        ++t->balance;
        return t->balance > 0;
    }
}

void AvlTreeB::balanceMMm(Tree &t, Tree l){
    t->left = l->right;
    l->right = t;
    l->balance = t->balance = 0;
    t = l;
}
void AvlTreeB::balanceMMp(Tree &t, Tree l){
    Tree r = l->right;
    l->right = r->left;
    t->left = r->right;
    r->left = l;
    r->right = t;
    l->balance = - ((r->balance + 1) / 2);
    t->balance = (1 - r->balance) / 2;
    r->balance = 0;
    t = r;
}
void AvlTreeB::balancePPm(Tree &t, Tree r){
    Tree l = r->left;
    t->right = l->left;
    r->left = l->right;
    l->left = t;
    l->right = r;
    t->balance = - ((l->balance + 1) / 2);
    r->balance = (1 - l->balance) / 2;
    l->balance = 0;
    t = l;
}
void AvlTreeB::balancePPp(Tree &t, Tree r){
    t->right = r->left;
    r->left = t;
    r->balance = t->balance = 0;
    t = r;
}



void AvlTreeB::print(Tree &t){
    if(t == NULL){
        std::cout << "Empty tree" << std::endl;
        return;
    }
    if(t->left != NULL){
        print(t->left);
    }
    std::cout << t->balance << ":" <<  t->key << ", ";
    if(t->right != NULL){
        print(t->right);
    }
}