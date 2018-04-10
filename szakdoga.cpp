#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <chrono>

#include "node_b.h"
#include "avltree_b.h"
#include "node_h.h"
#include "avltree_h.h"

std::vector<int> loadTest(std::string filename);

int main(int argc, char* argv[]){
    if(argc < 3)
    {
        std::cout << "Incorrect Argument number" << std::endl;
        std::cout << "The first Argument should be \"B\" or \"H\" depending on wich AVL-Tree you want to test" << std::endl;
        std::cout << "The second Argument should be the name of the test input file inside of the \"test_inputs\" folder" << std::endl;
        return 1;
    }

    std::cout << "Loading test input . . . ";
    std::vector<int> testNumbers = loadTest(argv[2]);
    std::cout << "done!" << std::endl;

    if(argv[1][0] == 'B')
    {
        std::cout << "Building AVL-tree type B . . . ";
        NodeB* root_B = NULL;
        AvlTreeB treeMaker_B;

        auto begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_B.insert(root_B, *it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "done!" << std::endl;
        std::cout << "Build time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / 1000000000.0 << "s" << std::endl;
    }else if(argv[1][0] == 'H')
    {
        std::cout << "Building AVL-tree type H. . . ";
        NodeH* root_H = NULL;
        AvlTreeH treeMaker_H;

        auto begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_H.insert(root_H, *it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "done!" << std::endl;

        std::cout << "Build time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / 1000000000.0 << "s" << std::endl;
    }else
    {
        std::cout << "The second argument should be \"B\" or \"H\" depending on the type of the Tree you want to test" << std::endl;
        std::cout << "\"B\"\t-\tAVL-Tree using balance" << std::endl;
        std::cout << "\"H\"\t-\tAVL-Tree using heights" << std::endl;
    }
    return 0;
}



std::vector<int> loadTest(std::string filename)
{
    std::vector<int> ret;

    std::ifstream infile;
    std::string folderName = "test_inputs/";
    infile.open(folderName.append(filename).c_str());
    if(!infile.is_open())
    {
        std::cout << "Error while opening input file: " << folderName << std::endl;
        exit(1);
    }
    int input_tmp;
    while(infile >> input_tmp)
    {
        ret.push_back(input_tmp);
    }
    infile.close();
    return ret;
}