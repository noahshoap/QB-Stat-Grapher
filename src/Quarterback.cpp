#include "Quarterback.hpp"

Quarterback::Quarterback(std::string& s)
{
    std::stringstream ss;
    std::string tmp;

    std::replace(s.begin(), s.end(), ' ', '_');
    std::replace(s.begin(), s.end(), ',', ' ');

    ss.str(s);

    while (ss >> tmp)
    {
        std::cout << tmp << ' ';
    }
    std::cout << std::endl;

}