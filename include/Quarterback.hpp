#ifndef QUARTERBACK_HPP
#define QUARTERBACK_HPP

#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>

class Quarterback
{
public:
    Quarterback(std::string&);
    std::string name;
    std::string team;
    std::string position;
    unsigned age;
    unsigned games_played;
    unsigned games_started;
    std::string record;
    unsigned completions;
    unsigned attempts;
    double completion_percentage;
    unsigned yards;
    unsigned touchdowns;
    double touchdown_percentage;
    unsigned interceptions;
    double interception_percentage;
    unsigned first_downs;
    unsigned longest_pass;
    double yards_per_attempt;
    double adjusted_yards_per_attempt;
    double yards_per_completion;
    double yards_per_game;
    double rating;
    double qbr;
    unsigned sacked;
    unsigned sack_yards;
    double sack_percentage;
    double net_yards_per_attempt;
    double adjusted_net_yards_per_attempt;
    unsigned comebacks;
    unsigned game_winning_drives;
};

#endif