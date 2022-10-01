#include <iostream>
#include <fstream>
#include <vector>
#include "Quarterback.hpp"

int main (int argc, char** argv)
{
    std::ifstream file;
    std::string line;
    std::vector<Quarterback*> qbs;
    Quarterback *tmp;

    /* Exit if not enough args */
    if (argc != 2)
    {
        std::cerr << "usage: ./qb-stat-grapher file.csv --flags" << std::endl;
        return -1; 
    }

    file.open(argv[1]);

    /* Exit if failed to open file */
    if (!file.is_open())
    {
        std::cerr << "Failed to open input file" << std::endl;
        return -1;
    }

    /* Read in all the QBs for this file */
    while (std::getline(file, line))
    {
        tmp = new Quarterback(line);
        qbs.push_back(tmp);
    }

    return 0;
}