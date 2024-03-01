//
// Created by adoug on 3/15/2022.
//

#ifndef MM_BRACKET_MAKER_TEAM_H
#define MM_BRACKET_MAKER_TEAM_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <random>
#include "time.h"
#include <iomanip>

using namespace std;

class Team {
private:
    string name;
    string conference;
    int seed;

public:
    Team();
    Team(string name, int seed);
    Team(string name, int seed, std::string conference);

    string getName() const;
    string getConference() const;
    int getSeed() const;
};

// simulateGame() takes in two Team objects, a map from seeding matchups to odds, and a string by reference that tracks simulated games across the bracket
// it calculates a winner based on the seeding matchup and the associated odds, updates the bracketOutput string, and returns the winning Team
Team simulateGame(Team team1, Team team2, unordered_map<string, float> oddsMap);

// overloaded function performs the same task but it updates a string with the result of the simulation so that users can see the competed bracket
Team simulateGame(Team team1, Team team2, unordered_map<string, float> oddsMap, string& bracketOutput);

#endif //MM_BRACKET_MAKER_TEAM_H