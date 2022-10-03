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
    stats["age"] = age;
    ss >> position;
    ss >> games_played;
    stats["games_played"] = games_played;
    ss >> games_started;
    stats["games_started"] = games_started;
    ss >> record;
    ss >> completions;
    stats["completions"] = completions;
    ss >> attempts;
    stats["attempts"] = attempts;
    ss >> completion_percentage;
    stats["completion_percentage"] = completion_percentage;
    ss >> yards;
    stats["yards"] = yards;
    ss >> touchdowns;
    stats["touchdowns"] = touchdowns;
    ss >> touchdown_percentage;
    stats["touchdown_percentage"] = touchdown_percentage;
    ss >> interceptions;
    stats["interceptions"] = interceptions;
    ss >> interception_percentage;
    stats["interception_percentage"] = interception_percentage;
    ss >> first_downs;
    stats["first_downs"] = first_downs;
    ss >> longest_pass;
    stats["longest_pass"] = longest_pass;
    ss >> yards_per_attempt;
    stats["yards_per_attempt"] = yards_per_attempt;
    ss >> adjusted_yards_per_attempt;
    stats["adjusted_yards_per_attempt"] = adjusted_yards_per_attempt;
    ss >> yards_per_completion;
    stats["yards_per_completion"] = yards_per_completion;
    ss >> yards_per_game;
    stats["yards_per_game"] = yards_per_game;
    ss >> rating;
    stats["rating"] = rating;
    ss >> qbr;
    stats["qbr"] = qbr;
    ss >> sacked;
    stats["sacked"] = sacked;
    ss >> sack_yards;
    stats["sack_yards"] = sack_yards;
    ss >> sack_percentage;
    stats["sack_percentage"] = sack_percentage;
    ss >> net_yards_per_attempt;
    stats["net_yards_per_attempt"] = net_yards_per_attempt;
    ss >> adjusted_net_yards_per_attempt;
    stats["adjusted_net_yards_per_attempt"] = adjusted_net_yards_per_attempt;
    ss >> comebacks;
    stats["comebacks"] = comebacks;
    ss >> game_winning_drives;
    stats["game_winning_drives"] = game_winning_drives;
    ss >> tmp;
}