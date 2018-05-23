
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <time.h>

#include "node_b.h"
#include "avltree_b.h"
#include "node_h.h"
#include "avltree_h.h"
#include "node_rb.h"
#include "rbtree.h"

bool testInsert(NodeB* &nb, NodeH* &nh, RBTree &rb, int testSize);
bool testDelete(NodeB* &nb, NodeH* &nh, RBTree &rb, int testSize);
bool testTrees(NodeB* nb, NodeH* nh, RBTree &rb);
int isCorrectAVLH(NodeH *t, bool &correct);
int isCorrectAVLB(NodeB *t, bool &correct);
bool sameTree(NodeH *h, NodeB *b);

int main()
{
    NodeB *nodeB = NULL;
    NodeH *nodeH = NULL;
    RBTree rbTree;

    std::cout << "Testing insert." << std::endl;
    if(testInsert(nodeB,nodeH,rbTree,10000))
    {
        std::cout << "Insert is okay." << std::endl;
    }else
    {
        std::cout << "Error at insert." << std::endl;
    }
    std::cout << "Testing delete." << std::endl;
    if(testDelete(nodeB,nodeH,rbTree,5000))
    {
        std::cout << "Delete is okay." << std::endl;
    }else
    {
        std::cout << "Error at Delete." << std::endl;
    }
    

    

    delete nodeB;
    delete nodeH;
    return 0;
}


bool testInsert(NodeB* &nb, NodeH* &nh, RBTree &rb, int testSize)
{
    srand (time(NULL));
    std::vector<int> inputVector;
    for(int i = 0; i < testSize; ++i)
    {
        inputVector.push_back(rand() % 100000);
    }
    AvlTreeH treeMaker_H;
    AvlTreeB treeMaker_B;
    for(std::vector<int>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
    {
        treeMaker_H.insert(nh, *it);
        treeMaker_B.insert(nb, *it);
        rb.insert(*it);
        if(!testTrees(nb,nh,rb))
            return false;
    }
    std::cout << "Checking whether the trees contain every key they should...";
    for(std::vector<int>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
    {
        if(treeMaker_H.getNode(nh,*it) == NULL)
        {
            std::cout << "Error, AVL Tree H does not contain " << *it << std::endl;
            return false;
        }
        if(treeMaker_B.getNode(nb,*it) == NULL)
        {
            std::cout << "Error, AVL Tree B does not contain " << *it << std::endl;
            return false;
        }
        if(!rb.contains(*it))
        {
            std::cout << "Error, Red-Black Tree does not contain " << *it << std::endl;
            return false;
        }
    }
    std::cout << "ok" << std::endl;

    return testTrees(nb,nh,rb);
}

bool testDelete(NodeB* &nb, NodeH* &nh, RBTree &rb, int testSize)
{
    std::vector<int> deleteVector;
    for(int i = 0; i < testSize; ++i)
    {
        deleteVector.push_back(rand() % 100000);
    }
    AvlTreeH treeMaker_H;
    AvlTreeB treeMaker_B;
    for(std::vector<int>::iterator it = deleteVector.begin(); it != deleteVector.end(); ++it)
    {
        treeMaker_H.del(nh, *it);
        treeMaker_B.del(nb, *it);
        rb.del(*it);
        if(!testTrees(nb,nh,rb))
            return false;
    }

    return testTrees(nb,nh,rb);
}


bool testTrees(NodeB* nb, NodeH* nh, RBTree &rb)
{
    bool correct = true;
    // std::cout << "Checking AVLH...";
    isCorrectAVLH(nh,correct);
    if(correct)
    {
        // std::cout << "ok" << std::endl;
    }else
    {
        std::cout << "Error with AVLH" << std::endl;
        return false;
    }
    correct = true;

    // std::cout << "Checking AVLB...";
    isCorrectAVLB(nb,correct);
    if(correct)
    {
        // std::cout << "ok" << std::endl;
    }else
    {
        std::cout << "Error with AVLB" << std::endl;
        return false;
    }

    // std::cout << "Checking if the two trees are identical...";
    if(sameTree(nh,nb))
    {
        // std::cout << "ok" << std::endl;
    }else
    {
        std::cout << "Error, AVLH and AVLB are not identical" << std::endl;
        return false;
    }

    // std::cout << "Checking if the Red-Black Tree is correct...";
    if(rb.isCorrect())
    {
        // std::cout << "ok" << std::endl;
    }else
    {
        std::cout << "Error with Red-Black Tree" << std::endl;
        return false;
    }
    return true;
}

int isCorrectAVLH(NodeH *t, bool &correct)
{
    if(!correct)
        return -1;

    int left = -1, right = -1;
    if(t->left != NULL)
    {
        left = isCorrectAVLH(t->left,correct);
    }
    if(!correct)
        return left;

    if(t->right != NULL)
    {
        right = isCorrectAVLH(t->right,correct);
    }

    int balance = right-left;
    int h = 1 + std::max(left,right);
    if(balance < -1 || balance > 1)
    {
        std::cout << "Incorrect balancing! Balance is " << balance << " at node " << t->key << "." << std::endl;
        correct = false;
    }
    if(t->height != h)
    {
        std::cout << "Incorrect height! Height of " << t->key <<  " is " << h << ", the stored height is: " << t->height << "." << std::endl;
        correct = false;
    }
    return h;
}

int isCorrectAVLB(NodeB *t, bool &correct)
{
    if(!correct)
        return -1;

    int left = -1, right = -1;
    if(t->left != NULL)
    {
        left = isCorrectAVLB(t->left,correct);
    }
    if(!correct)
        return left;

    if(t->right != NULL)
    {
        right = isCorrectAVLB(t->right,correct);
    }

    int balance = right-left;
    if(balance < -1 || balance > 1)
    {
        std::cout << "Incorrect balancing! Balance is " << balance << " at node " << t->key << "." << std::endl;
        correct = false;
    }
    if(t->balance != balance)
    {
        std::cout << "Incorrect balance stored! Balance of" << t->key <<  "is " << balance << ", the stored balance is: " << t->balance << "." << std::endl;
        correct = false;
    }
    return 1 + std::max(left,right);
}

bool sameTree(NodeH *h, NodeB *b)
{
    if(h->key != b->key)
        return false;
    if(h->left == NULL && b->left != NULL)
        return false;
    if(h->right == NULL && b->right != NULL)
        return false;
    
    if(h->left != NULL && !sameTree(h->left, b->left))
        return false;
    if(h->right != NULL && !sameTree(h->right, b->right))
        return false;

    return true;
}