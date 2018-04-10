#include <iostream>
#include <cstddef>
#include "avltree_h.h"
#include "node_h.h"

void AvlTreeH::insert(Tree &t, int k)
{
    //if the tree is empty(the root is null), then create a new root with the value "k" as the key.
    if(t == NULL)
    {
        t = new NodeH(k);
        return;
    }
    if(k < t->key)
    {
        insert(t->left,k);
        t->height = 1 + std::max(height(t->left),height(t->right));
        if(height(t->right) - height(t->left) == -2){
            leftBalance(t);
        }
    }else if(k > t->key)
    {
        insert(t->right,k);
        t->height = 1 + std::max(height(t->left),height(t->right));
        if(height(t->right) - height(t->left) == 2){
            rightBalance(t);
        }
    }else
    {
        return;
    }

}

bool AvlTreeH::del(Tree &t, int k)
{
    if(t == NULL)
    {
        return false;
    }

    if(t->key > k)
    {
        if(del(t->left,k))
        {
            //t->right >= t->left
            if(height(t->right) - height(t->left) == 2){
                rightBalance(t);
            }else{
                t->height = height(t->right) + 1;
            }
            return true;
        }
    }else if(t->key < k)
    {
        if(del(t->right,k))
        {
            //t->left >= t->right
            if(height(t->right) - height(t->left) == -2){
                leftBalance(t);
            }else{
                t->height = height(t->left) + 1;
            }
            return true;
        }
    }else if(t->key == k)
    {
        rootDel(t);

        return true;
    }
    return false;
}

void AvlTreeH::rootDel(Tree &t)
{
    if(t->left == NULL)
    {
        Tree p = t;
        t = p->right;
        delete p;
    }else if(t->right == NULL)
    {
        Tree p = t;
        t = p->left;
        delete p;
    }else
    {
        Tree p;
        getMin(t->right,p);
        p->left = t->left;
        p->right = t->right;
        p->height = t->height;
        t->left = t->right = NULL;
        delete t;
        t = p;
    }
}


void AvlTreeH::getMin(Tree &t, Tree &minP)
{
    if(t->left == NULL)
    {
        minP = t;
        t = minP->right;
        minP->right = NULL;
    }else
    {
        getMin(t->left,minP);
        if(height(t->left) - height(t->right) == 2)
        {
            rightBalance(t);
        }else
        {
            t->height = height(t->right) + 1;
        }
    }
}

void AvlTreeH::rightBalance(Tree &t)
{
    Tree r = t->right;
    int hr = height(r->right);
    int hl = height(r->left);
    if(hr-hl >= 0){
        t->right = r->left;
        r->left = t;
        //the height of t->left and t->right is either equal or t->right is greater by one. so the new height of t is  the height of t->right + 1.
        t->height = height(t->right) + 1;
        //t can't be NULL here, so we can use t->height
        r->height = t->height + 1;
        t = r;
    }else
    {
        Tree l = r->left;
        t->right = l->left;
        r->left = l->right;
        l->left = t;
        l->right = r;

        //after the rotation
        //given, that the height of t->left is h, then r->right is also h.
        //The heights of t->right and r->left are h or h-1.
        //So the height of both t and r are h+1
        t->height = 1 + height(t->left);
        r->height = t->height;  //t is not NULL
        l->height = 1 + t->height;  //t is not NULL

        t = l;
    }
}

void AvlTreeH::leftBalance(Tree &t)
{
    Tree l = t->left;
    int hr = height(l->right);
    int hl = height(l->left);
    if(hr-hl <= 0){
        t->left = l->right;
        l->right = t;
        //the height of t->left and t->right is either equal or t->left is greater by one. 
        //So the new height of t is the height of t->left + 1.
        t->height = height(t->left) + 1;
        //t can't be NULL here, so we can use t->height
        l->height = t->height + 1;
        t = l;
    }else
    {
        Tree r = l->right;
        l->right = r->left;
        t->left = r->right;
        r->left = l;
        r->right = t;

        //after the rotation
        //given, that the height of t->right is h, then l->left is also h.
        //The heights of t->left and l->right are h or h-1.
        //So the height of both t and l are h+1
        t->height = 1 + height(t->right);
        l->height = t->height;  //t is not NULL
        r->height = 1 + t->height;  //t is not NULL

        t = r;
    }
}

void AvlTreeH::print(Tree &t)
{
    if(t == NULL)
    {
        std::cout << "Empty tree" << std::endl;
        return;
    }
    if(t->left != NULL)
    {
        print(t->left);
    }
    std::cout << t->height << ":" << t->key << ", ";
    if(t->right != NULL)
    {
        print(t->right);
    }
}

int AvlTreeH::height(Tree p)
{
    if(p == NULL)
    {
        return -1;
    }else
    {
        return p->height;
    }
}