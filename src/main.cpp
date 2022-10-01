#include <iostream>
#include <fstream>
#include "Quarterback.hpp"

int main (int argc, char** argv)
{
    std::ifstream file;

    if (argc != 2)
    {
        std::cerr << "usage: ./qb-stat-grapher file.csv --flags" << std::endl;
        return -1; 
    }

    file.open(argv[1]);

    if (!file.is_open())
    {
        std::cerr << "Failed to open input file" << std::endl;
        return -1;
    }

    return 0;
}