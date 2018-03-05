#include <iostream>
#include "node.h"
#include "avltreeh.h"

int main(){
    NodeH* tmp = NULL;
    AvlTreeH treeMaker;
    // treeMaker.insert(tmp,-15);
    // treeMaker.insert(tmp,0);
    // treeMaker.insert(tmp,15);
    // treeMaker.insert(tmp,20);
    // treeMaker.insert(tmp,120);
    // treeMaker.insert(tmp,1325);
    treeMaker.insert(tmp,20);
    treeMaker.insert(tmp,15);
    treeMaker.insert(tmp,0);
    treeMaker.insert(tmp,1325);
    treeMaker.insert(tmp,-15);
    treeMaker.insert(tmp,120);
    treeMaker.print(tmp);
    return 0;
}