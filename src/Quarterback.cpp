#include "Quarterback.hpp"

Quarterback::Quarterback(std::string& s)
{
    std::stringstream ss;
    std::string tmp;

    std::replace(s.begin(), s.end(), ' ', '_');
    std::replace(s.begin(), s.end(), ',', ' ');

    ss.str(s);

    /* Read information into class */
    ss >> tmp;
    ss >> name;
    ss >> team;
    ss >> age;
    ss >> position;
    ss >> games_played;
    ss >> games_started;
    ss >> record;
    ss >> completions;
    ss >> attempts;
    ss >> completion_percentage;
    ss >> yards;
    ss >> touchdowns;
    ss >> touchdown_percentage;
    ss >> interceptions;
    ss >> interception_percentage;
    ss >> first_downs;
    ss >> longest_pass;
    ss >> yards_per_attempt;
    ss >> adjusted_yards_per_attempt;
    ss >> yards_per_completion;
    ss >> yards_per_game;
    ss >> rating;
    ss >> qbr;
    ss >> sacked;
    ss >> sack_yards;
    ss >> sack_percentage;
    ss >> net_yards_per_attempt;
    ss >> adjusted_net_yards_per_attempt;
    ss >> comebacks;
    ss >> game_winning_drives;
    ss >> tmp;
}