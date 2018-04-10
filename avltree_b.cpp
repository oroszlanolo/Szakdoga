#include <iostream>
#include <cstddef>
#include "avltree_b.h"
#include "node_b.h"

bool AvlTreeB::insert(TreeB &t, int k){
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

bool AvlTreeB::del(TreeB &t, int k){
    if(t == NULL){
        return false;
    }
    if(k < t->key){
        if(del(t->left,k)){
            return leftTreeShrink(t);
        }else{
            return false;
        }

    }else if(k > t->key){
        if(del(t->right,k)){
            return rightTreeShrink(t);
        }else{
            return false;
        }
    }else{
        return rootDel(t);
    }
}

bool AvlTreeB::rootDel(TreeB &t){
    if(t->left == NULL){
        TreeB p = t;
        t = p->right;
        delete p;
        return true;
    }else if(t->right == NULL){
        TreeB p = t;
        t = p->left;
        delete p;
        return true;
    }else{
        if(rightTreeMinToRoot(t)){
            return rightTreeShrink(t);
        }else{
            return false;
        }
    }
}


bool AvlTreeB::getMin(TreeB &t, TreeB &minP){
    if(t->left == NULL){
        minP = t;
        t = minP->right;
        minP->right = NULL;
        return true;
    }else{
        if(getMin(t->left,minP)){
            leftTreeShrink(t);
            return true;
        }else{
            return false;
        }
    }
}

bool AvlTreeB::rightTreeMinToRoot(TreeB &t){
    TreeB p = NULL;
    bool d = getMin(t->right,p);

    p->left = t->left;
    p->right = t->right;
    p->balance = t->balance;

    t->left = t->right = NULL;
    delete t;
    t = p;

    return d;
}

bool AvlTreeB::leftTreeGrow(TreeB &t){
    if(t->balance == -1){
        TreeB l = t->left;
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
bool AvlTreeB::rightTreeGrow(TreeB &t){
    if(t->balance == 1){
        TreeB r = t->right;
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

bool AvlTreeB::leftTreeShrink(TreeB &t){
    if(t->balance == 1){
        return balancePP(t);
    }else{
        ++t->balance;
        return t->balance == 0;
    }
}

bool AvlTreeB::rightTreeShrink(TreeB &t){
    if(t->balance == -1){
        return balanceMM(t);
    }else{
        ++t->balance;
        return t->balance == 0;
    }
}


//  BALANCE functiions


bool AvlTreeB::balancePP(TreeB &t){
    TreeB r = t->right;
    bool d = true;
    switch(r->balance){
        case -1:
            balancePPm(t,r);
            break;
        case 0:
            balancePP0(t,r);
            d = false;
            break;
        case 1:
            balancePPp(t,r);
            break;
    }
    return d;
}
bool AvlTreeB::balanceMM(TreeB &t){
    TreeB l = t->left;
    bool d = true;
    switch(l->balance){
        case -1:
            balanceMMm(t,l);
            break;
        case 0:
            balanceMM0(t,l);
            d = false;
            break;
        case 1:
            balanceMMp(t,l);
            break;
    }
    return d;
}
void AvlTreeB::balanceMMm(TreeB &t, TreeB l){
    t->left = l->right;
    l->right = t;
    l->balance = t->balance = 0;
    t = l;
}
void AvlTreeB::balanceMMp(TreeB &t, TreeB l){
    TreeB r = l->right;
    l->right = r->left;
    t->left = r->right;
    r->left = l;
    r->right = t;
    l->balance = - ((r->balance + 1) / 2);
    t->balance = (1 - r->balance) / 2;
    r->balance = 0;
    t = r;
}
void AvlTreeB::balancePPm(TreeB &t, TreeB r){
    TreeB l = r->left;
    t->right = l->left;
    r->left = l->right;
    l->left = t;
    l->right = r;
    t->balance = - ((l->balance + 1) / 2);
    r->balance = (1 - l->balance) / 2;
    l->balance = 0;
    t = l;
}
void AvlTreeB::balancePPp(TreeB &t, TreeB r){
    t->right = r->left;
    r->left = t;
    r->balance = t->balance = 0;
    t = r;
}
void AvlTreeB::balancePP0(TreeB &t, TreeB r){
    t->right = r->left;
    r->left = t;

    t->balance = 1;
    r->balance = -1;
    t = r;
}
void AvlTreeB::balanceMM0(TreeB &t, TreeB l){
    t->left = l->right;
    l->right = t;

    t->balance = -1;
    l->balance = 1;
    t = l;
}



void AvlTreeB::print(TreeB &t){
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