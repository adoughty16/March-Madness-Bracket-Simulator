//
// Created by adoug on 3/15/2022.
//

#ifndef MM_BRACKET_MAKER_BRACKET_H
#define MM_BRACKET_MAKER_BRACKET_H

#include "Team.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Bracket {
private:
    Team champion;
    // for round of 64
    vector<Team> west;
    vector<Team> south;
    vector<Team> east;
    vector<Team> midwest;
    // for round of 32
    vector<Team> westEight;
    vector<Team> southEight;
    vector<Team> eastEight;
    vector<Team> midwestEight;
    // for sweet 16
    vector<Team> westFour;
    vector<Team> southFour;
    vector<Team> eastFour;
    vector<Team> midwestFour;
    // for elite 8
    vector<Team> westTwo;
    vector<Team> southTwo;
    vector<Team> eastTwo;
    vector<Team> midwestTwo;
    // for final 4
    vector<Team> south_eastTwo;
    vector<Team> west_midwestTwo;
    // for championship
    vector<Team> championshipTwo;
public:
    Bracket();

    vector<Team> getWest() const;
    vector<Team> getEast() const;
    vector<Team> getMidwest() const;
    vector<Team> getSouth() const;
    vector<int> get_final_4_seeds() const;
    Team get_champion() const;

    // all of the following simulation functions simulate rounds of the tournament. There are two calls for every round sim. One that updates a string to keep track
    // of bracket data, and one that does not. The ones that do not are used for checking bias over many simulations where it would not make sense to keep track of individual
    // brackets.
    void sim_round_64(unordered_map<string, float> oddsMap);
    void sim_round_32(unordered_map<string, float> oddsMap);
    void sim_sweet_16(unordered_map<string, float> oddsMap);
    void sim_elite_8(unordered_map<string, float> oddsMap);
    void sim_final_4(unordered_map<string, float> oddsMap);
    void sim_championship(unordered_map<string, float> oddsMap);

    //
    // these are the overloaded functions that update the bracket string
    //
    void sim_round_64(string& tourneyString, unordered_map<string, float> oddsMap);
    void sim_round_32(string& tourneyString, unordered_map<string, float> oddsMap);
    void sim_sweet_16(string& tourneyString, unordered_map<string, float> oddsMap);
    void sim_elite_8(string& tourneyString, unordered_map<string, float> oddsMap);
    void sim_final_4(string& tourneyString, unordered_map<string, float> oddsMap);
    void sim_championship(string& tourneyString, unordered_map<string, float> oddsMap);

    void clear_bracket();
};

#endif //MM_BRACKET_MAKER_BRACKET_H
