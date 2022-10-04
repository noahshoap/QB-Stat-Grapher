/* main.cpp
 * Noah Shoap
 * Reads in .csv file, sorts it into map keyed off command-arg stat, creates a jgraph file
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <exception>
#include "Quarterback.hpp"

// round integer to higher 10
int round(int n)
{
    // round down
    int a = (n / 10) * 10;
     
    // add 10
    int b = a + 10;
 
    return b;
}

int main (int argc, char** argv)
{
    std::ifstream file;
    std::ofstream output;
    std::string line;
    std::string direction;
    std::string stat;
    int number_qbs;
    int i;
    int max_y;
    double max_x;
    double football_x, football_y;
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

    /* Try to parse command line args; exit if exception occurs */
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
    /* Ignore first line */
    std::getline(file, line);

    /* Read in all the QBs for this file */
    while (std::getline(file, line))
    {
        tmp = new Quarterback(line);
        
        /* If player is not a QB, ignore that player */
        if (!(tmp->position == "qb" || tmp->position == "QB"))
        {
            delete tmp;
            continue;
        }

        /* If player has not started around half the season, ignore */
        if (tmp->games_started < 8)
        {
            delete tmp;
            continue;
        }

        /* Insert quarterback into QB vector */
        qbs.push_back(tmp);

        /* Verify that the stat we're looking for exists. */
        if (tmp->stats.find(stat) != tmp->stats.end())
        {
            sorted_qbs.insert(std::make_pair(tmp->stats[stat], tmp));
        }
        else
        {
            std::cerr << "The stat '" << stat << "' does not exist.  Please try another one." << std::endl;
            return -1; 
        }
    }

    /* Set dimensions of football grid */
    max_y = round(sorted_qbs.rbegin()->second->stats[stat]);
    max_x = ((2.8 - 0.2) * 0.75 * number_qbs) + 0.2;

    /* Open jgraph file */
    output.open(argv[2]);

    /* Output newgraph, title information */
    output << "newgraph\n" << std::endl;
    output << "title : ";

    if (direction == "top") output << "Top ";
    else output << "Bottom ";

    output << number_qbs << " QBs by " << stat << std::endl;

    output << std::endl;

    /* X-Axis */
    output << "xaxis" << std::endl;
    output << "  min 0.2 ";
    output << "max "; 
    output << max_x;
    output << "\n  no_auto_hash_labels mhash 0 hash 2 shash 1" << std::endl;
    output << "hash_labels fontsize 8 hjl vjt rotate -45" << std::endl;

    output << std::endl;

    /* Y-Axis */
    output << "yaxis" << std::endl;
    output << "  label : " << stat << std::endl;
    output << "  min 0 max ";
    output << max_y << std::endl;

    output << std::endl;

    /* Football field drawing */
    output << "newcurve marktype box marksize ";
    output << max_x << ' ';
    output << max_y;
    output << " cfill 0 .5 0 pts ";
    output << (max_x) / 2 << ' ' << (double) max_y / (double) 2 << std::endl;
    
    output << std::endl;

    /* Draw out 10-yard lines */
    output << "shell : echo \"\" | awk '{\\" << std::endl;
    output << "\t\tfor (i = 1; i < " << max_y <<  "; i += " << max_y / 10 << ") { \\" << std::endl;
    output << "\t\t\tprintf (\"newline gray 1 pts 0 %d ";
    output << max_x;
    output << " %d\\n\", i - 1, i - 1); \\" << std::endl;
    output << "\t\t} }'" << std::endl;
    output << std::endl;

    /* Draw out 1-yard marks */
    output << "shell : echo \"\" | awk '{\\" << std::endl;
    output << "\t\tfor (i = 0; i <= ";
    output << number_qbs * 2;
    output << "; i += 1) { \\" << std::endl;
    output << "\t\t\tfor (j = 0; j < " << max_y << "; j += " << max_y /20 << ".1) { \\" << std::endl;
    output << "\t\t\t\tprintf \"newline gray 1 pts %f %f %f %f\\n\",0.97 + i, j, 1.03 + i, j; \\" << std::endl;
   // output << "\t\t\tprintf \"newline gray 1 pts 1.97 %f 2.03 %f\\n\", i, i; \\" << std::endl;
    output << "\t\t} } }'" << std::endl;
    output << std::endl;

    int index = 1;

    football_x = max_x * 0.0633;
    football_y = max_y * 0.0572;

    /* Print out QB names at hash marks */
    if (direction == "top")
    {
        i = 0;
        for (auto it = sorted_qbs.rbegin(); it != sorted_qbs.rend() && i != number_qbs; ++it, ++i)
        {
            output << "xaxis" << std::endl;
            output << "hash_label at " << index << " : " << it->second->first_name << " ";
            output << it->second->last_name << std::endl;

            /* Start drawing footballs */
            output << "newcurve eps football.eps marksize " << football_x << " " << football_y << " pts" << std::endl;
            output << "\tshell : echo \"\" | awk '{ for (i = 0; i < " << it->second->stats[stat] << "; i++) printf \"" << index << ", %f\\n\", i }'" << std::endl;

            index += 2;
        }
    }
    else if (direction == "bottom")
    {
        i = 0;
        for (auto it = sorted_qbs.begin(); it != sorted_qbs.end() && i != number_qbs; ++it, ++i)
        {
            output << "xaxis" << std::endl;
            output << "hash_label at " << index << " : " << it->second->first_name << " ";
            output << it->second->last_name << std::endl;

            /* Start drawing footballs */
            output << "newcurve eps football.eps marksize " << football_x << " " << football_y << " pts" << std::endl;
            output << "\tshell : echo \"\" | awk '{ for (i = 0; i < " << it->second->stats[stat] << "; i++) printf \"" << index << ", %f\\n\", i }'" << std::endl;

            index += 2;
        }
    }

    /* Close files */
    file.close();
    output.close();

    /* Free QB memory */
    for (size_t j = 0; j < qbs.size(); ++j)
    {
        tmp = qbs[j];
        delete tmp;
    }

    return 0;
}