#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <exception>
#include "Quarterback.hpp"

int main (int argc, char** argv)
{
    std::ifstream file;
    std::ofstream output;
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

    output.open(argv[2]);
    output << "newgraph\n" << std::endl;

    /* X-Axis */
    output << "xaxis" << std::endl;
    output << "  min 0.2 ";
    output << "max "; 
    output << ((2.8 - 0.2) / 2 * number_qbs) + 0.2;
    output << " size ";
    output << 5 * number_qbs / 2;
    output << "\n  no_auto_hash_labels mhash 0 hash 1 shash 1" << std::endl;

    output << std::endl;

    /* Y-Axis */
    output << "yaxis" << std::endl;
    output << "  min 0 max 10";
    output << " size 6" << std::endl;
    output << "  nodraw" << std::endl;

    output << std::endl;

    /* Football field drawing */
    output << "newcurve marktype box marksize ";
    output << ( (2.8 - 0.2) / 2 * number_qbs) << ' ';
    output << 10;
    output << " cfill 0 .5 0 pts 1.5 5" << std::endl;
    
    output << std::endl;

    /* Draw out numbers */
    output << "newstring hjc vjc font Times-Italic lgray 1 fontsize 14 x 0.75" << std::endl;
    output << std::endl;

    output << "shell : echo \"\" | awk '{\\" << std::endl;
    output << "\t\tfor (i = 1; i < 10; i += 1) { \\" << std::endl;
    output << "\t\t\tprintf \"copystring y %d : %d0\\n\",i, i \\" << std::endl;
    output << "\t\t} }'" << std::endl;
    output << std::endl;

    /* Draw out 10-yard lines */
    output << "shell : echo \"\" | awk '{\\" << std::endl;
    output << "\t\tfor (i = 1; i < 10; i += 1) { \\" << std::endl;
    output << "\t\t\tprintf (\"newline gray 1 pts 1 %d ";
    output << ((2.8 - 0.2) / 2 * number_qbs) + 0.2;
    output << " %d\\n\", i, i); \\" << std::endl;
    output << "\t\t} }'" << std::endl;
    output << std::endl;

    /* Draw out 1-yard marks */
    output << "shell : echo \"\" | awk '{\\" << std::endl;
    output << "\t\tfor (i = 0.97; i < ";
    output << number_qbs;
    output << "; i += 1) { \\" << std::endl;
    output << "\t\t\tfor (j = 1; j < 10; j += .1) { \\" << std::endl;
    output << "\t\t\t\tprintf \"newline gray 1 pts %f %f 1.03 %f\\n\",i, j, j; \\" << std::endl;
   // output << "\t\t\tprintf \"newline gray 1 pts 1.97 %f 2.03 %f\\n\", i, i; \\" << std::endl;
    output << "\t\t} } }'" << std::endl;
    output << std::endl;

    file.close();
    output.close();
    return 0;
}