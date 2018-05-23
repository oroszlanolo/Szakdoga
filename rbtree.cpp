#include <iostream>
#include "rbtree.h"
#include "node_rb.h"
#include <cstddef>

#pragma region publicModify

void RBTree::insert(int z)
{
    TreeRB y = NIL;
    TreeRB x = root;
    while(x != NIL){
        y = x;
        if(z < x->key)
        {
            x = x->left;
        }else if(z > x->key)
        {
            x = x->right;
        }else
        {
            return;
        }
    }
    TreeRB zNode = new NodeRB(z,RED,NIL,y);
    if(y == NIL)
    {
        root = zNode;
    }else if(zNode->key < y->key)
    {
        y->left = zNode;
    }else
    {
        y->right = zNode;
    }
    insertFixup(zNode);
}


bool RBTree::del(int zNum)
{
    TreeRB z = getNode(zNum);
    if(z == NIL)
    {
        return false;
    }
    TreeRB y = z;
    TreeRB x;
    RBColor yOriginalColor = y->color;
    if(z->left == NIL)
    {
        x = z->right;
        transplant(z,z->right);
    }else if(z->right == NIL)
    {
        x = z->left;
        transplant(z,z->left);
    }else
    {
        y = getMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }else
        {
            transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(yOriginalColor == BLACK)
    {
        deleteFixup(x);
    }


    return true;
}

void RBTree::reset()
{
    delete root;
    NIL = new NodeRB(0,BLACK,NULL,NULL);
    root = NIL;
}

#pragma endregion


TreeRB RBTree::getNode(int z)
{
    TreeRB ret = root;
    while(ret != NIL && ret->key != z)
    {
        if(z < ret->key)
        {
            ret = ret->left;
        }else
        {
            ret = ret->right;
        }
    }
    return ret;
}

TreeRB RBTree::getMin(TreeRB t)
{
    TreeRB ret = t;
    if(ret == NIL)
    {
        return ret;
    }
    while(ret->left != NIL)
    {
        ret = ret->left;
    }
    return ret;
}

#pragma region fixpups

void RBTree::insertFixup(TreeRB z)
{
    while(z->parent->color == RED)
    {
        if(z->parent == z->parent->parent->left)
        {
            TreeRB y = z->parent->parent->right;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }else
        {
            TreeRB y = z->parent->parent->left;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::deleteFixup(TreeRB x)
{
    while(x != root && x->color == BLACK)
    {
        if(x == x->parent->left)
        {
            TreeRB w = x->parent->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }else
        {
            TreeRB w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }

        }
    }
    x->color = BLACK;
}

void RBTree::rightRotate(TreeRB y)
{
    TreeRB x = y->left;
    y->left = x->right;
    if(x->right != NIL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NIL)
    {
        root = x;
    }else if(y == y->parent->left)
    {
        y->parent->left = x;
    }else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RBTree::leftRotate(TreeRB x)
{
    TreeRB y = x->right;
    x->right = y->left;
    if(y->left != NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NIL)
    {
        root = y;
    }else if(x == x->parent->left)
    {
        x->parent->left = y;
    }else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::transplant(TreeRB u, TreeRB v)
{
    if(u->parent == NIL)
    {
        root = v;
    }else if(u == u->parent->left)
    {
        u->parent->left = v;
    }else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

#pragma endregion


void RBTree::print()
{
    if(root == NIL)
    {
        std::cout << "Empty tree" << std::endl;
        return;
    }
    printRek(root, 0);
    std::cout << std::endl;
}
void RBTree::printRek(TreeRB t, int n)
{
    if(t->left != NIL)
    {
        printRek(t->left, n+1);
    }
    std:: cout << n << ":" << t->color << ":" << t->key << ", ";
    if(t->right != NIL)
    {
        printRek(t->right, n+1);
    }
}

bool RBTree::contains(int z)
{
    TreeRB t = root;
    while(t != NIL && t->key != z)
    {
        if(z < t->key)
        {
            t = t->left;
        }else
        {
            t = t->right;
        }
    }
    return t != NIL;
}

bool RBTree::isCorrect()
{
    if(root->color == RED)
    {
        return false;
    }
    bool correct = true;
    correctRek(root,correct);
    return correct;
}

int RBTree::correctRek(TreeRB t, bool &correct)
{
    if(!correct)
    {
        return 1;
    }

    if(t == NIL)
    {
        correct = t->color == BLACK;
        return 1;
    }else
    {
        if(t->color == RED && (t->left->color == RED || t->right->color == RED)) //red nodes children must be black
        {
            std::cout << "Node " << t->key << " is red, but not both of its children are black." << std::endl;
            correct = false;
            return 1;
        }
        if(t != root && t->parent->left != t && t->parent->right != t) //check if the parent pointer is correct
        {
            std::cout << "Incorrect parent pointer at node " << t->key << std::endl;
            correct = false;
            return 1;
        }
        int left = correctRek(t->left, correct);
        if(!correct)
        {
            return 1;
        }
        int right = correctRek(t->right, correct);

        if(left != right)   //check if the left subtree has the same number of black nodes as the right one
        {
            correct = false;
        }

        return t->color == BLACK ? 1+left : left;
    }
}