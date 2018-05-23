#ifndef BW_H
#define BW_H

#include "node_rb.h"
#include <cstddef>

typedef struct NodeRB * TreeRB;

/**
 *Red-Black Tree 
 */
class RBTree
{
private:
    NodeRB* NIL;
    NodeRB* root;
    void insertFixup(TreeRB);
    void deleteFixup(TreeRB);
    void rightRotate(TreeRB);
    void leftRotate(TreeRB);
    void transplant(TreeRB, TreeRB);
    void printRek(TreeRB,int);
    int correctRek(TreeRB, bool &);
public:
    RBTree()
    {
        NIL = new NodeRB(0,BLACK,NULL,NULL);
        root = NIL;
    }
    ~RBTree()
    {
        delete root;
        delete NIL;
    }
    void reset();
    void insert(int);
    bool del(int);
    TreeRB getMin(TreeRB);
    void print();
    TreeRB getNode(int);
    bool contains(int);
    bool isCorrect();
};

#endif