#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "You must give an output name as the first argument, and the vector length as the second argument" << std::endl;
        return 1;
    }

    //creating random vector
    int size = atoi (argv[2]);
    std::vector<int> numbers;
    for(int i = 0; i < size; ++i)
    {
        numbers.push_back(i);
    }
    srand(time(NULL));
    std::random_shuffle(numbers.begin(), numbers.end());

    //opening the outfile
    std::ofstream outfile;
    outfile.open(argv[1]);
    if(!outfile.is_open())
    {
        std::cout << "Error while opening outfile: " << argv[1] << std::endl;
        return 1;
    }

    //writing the vector to the outfile
    for(std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        outfile << *it << " ";
    }
    outfile.close();

    std::cout << "Success!" << std::endl;
    return 0;
}