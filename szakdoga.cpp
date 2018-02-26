#include <iostream>
#include "node.h"
#include "avltreeh.h"

int main(){
    Node* tmp = NULL;
    AvlTreeH treeMaker;
    treeMaker.insert(20,tmp);
    treeMaker.insert(15,tmp);
    treeMaker.insert(0,tmp);
    treeMaker.insert(1325,tmp);
    treeMaker.insert(-15,tmp);
    treeMaker.insert(120,tmp);
    treeMaker.print(tmp);
    return 0;
}