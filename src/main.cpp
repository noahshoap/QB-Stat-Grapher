#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <exception>
#include "Quarterback.hpp"

int main (int argc, char** argv)
{
    std::ifstream file;
    std::string line;
    std::string direction;
    std::string stat;
    int number_qbs;
    int i;
    std::vector<Quarterback*> qbs;
    std::multimap<double, Quarterback*> sorted_qbs;
    Quarterback *tmp;

    /* Exit if not enough args */
    if (argc != 6)
    {
        std::cerr << "usage: ./qb-stat-grapher file.csv output.jgr top|bottom stat NUM_QBS" << std::endl;
        return -1; 
    }

    file.open(argv[1]);

    /* Exit if failed to open file */
    if (!file.is_open())
    {
        std::cerr << "Failed to open input file" << std::endl;
        return -1;
    }

    try
    {
        direction = argv[3];
        stat = argv[4];
        number_qbs = std::stod(argv[5]);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Something is wrong with your command line args." << std::endl;
        return -1;
    }

    std::cout << direction << ' ';
    std::cout << stat << ' ';
    std::cout << number_qbs << std::endl;
    /* Ignore first line */
    std::getline(file, line);

    /* Read in all the QBs for this file */
    while (std::getline(file, line))
    {
        tmp = new Quarterback(line);
        if (!(tmp->position == "qb" || tmp->position == "QB"))
        {
            delete(tmp);
            continue;
        }
        qbs.push_back(tmp);

        if (tmp->stats.find(stat) != tmp->stats.end())
        {
            sorted_qbs.insert(std::make_pair(tmp->stats[stat], tmp));
        }
    }

    if (direction == "top")
    {
        i = 0;
        for (auto it = sorted_qbs.rbegin(); it != sorted_qbs.rend() && i != number_qbs; ++it, ++i)
        {
            std::cout << it->second->name << ' ' << it->second->stats[stat] << std::endl;
        }
    }
    else if (direction == "bottom")
    {
        i = 0;
        for (auto it = sorted_qbs.begin(); it != sorted_qbs.end() && i != number_qbs; ++it, ++i)
        {
            std::cout << it->second->name << ' ' << it->second->stats[stat] << std::endl;
        }
    }

    return 0;
}