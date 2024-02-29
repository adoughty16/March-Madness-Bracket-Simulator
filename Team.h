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
    Team() {
        name = "default";
        seed = -1;
        conference = "default";
    }

    Team(string name, int seed) {
        this->name = name;
        this->seed = seed;
    }


    Team(string name, int seed, string conference) {
        this->name = name;
        this->seed = seed;
        this->conference = conference;
    }

    string getName() const {
        return name;
    }

    string getConference() const {
        return conference;
    }

    int getSeed() const {
        return seed;
    }
};

// simulateGame() takes in two Team objects, a map from seeding matchups to odds, and a string by reference that tracks simulated games across the bracket
// it calculates a winner based on the seeding matchup and the associated odds, updates the bracketOutput string, and returns the winning Team
Team simulateGame(Team team1, Team team2, unordered_map<string, float> oddsMap) {
    string seeding;
    float odds;
    Team highSeed;
    Team lowSeed;
    Team winner;
    int randomNum;
    int bit;

    // if statements find the team with the higher seed in the matchup
    if (team1.getSeed() < team2.getSeed()) {
        lowSeed = team2;
        highSeed = team1;
        // seeding will be used as a key to find the odds of one team winning for a given seeded matchup
        seeding = to_string(team1.getSeed()) + "-" + to_string(team2.getSeed());
    }
    if (team1.getSeed() > team2.getSeed()) {

        lowSeed = team1;
        highSeed = team2;
        seeding = to_string(team2.getSeed()) + "-" + to_string(team1.getSeed());
    }
    if (team1.getSeed() == team2.getSeed()) {
        // if the teams have the same seed, pick one of them as the high seed randomly
        // this will prevent bias towards the teams that end up getting passed into the first argument
        // naturally as part of the way the bracket is constructed
        if (rand() % 2 == 1) {
            lowSeed = team1;
            highSeed = team2;
        }
        else {
            lowSeed = team2;
            highSeed = team1;
        }

        seeding = to_string(team2.getSeed()) + "-" + to_string(team1.getSeed());
    }

    // get the odds of the higher seed winning
    odds = oddsMap[seeding];

    randomNum = 1 + rand() % 100;

    if (randomNum < odds) {
        winner = highSeed;
    }
    if (randomNum >= odds) {
        winner = lowSeed;
    }
    if (odds < 0.001) {
        winner = highSeed;
    }

    return winner;



}

// overloaded function performs the same task but it updates a string with the result of the simulation so that users can see the competed bracket
Team simulateGame(Team team1, Team team2, unordered_map<string, float> oddsMap, string& bracketOutput) {

    ostringstream matchupResult;
    ostringstream highTitle;
    ostringstream lowTitle;
    string seeding;
    float odds;
    Team highSeed;
    Team lowSeed;
    Team winner;
    int randomNum;
    int bit;

    // if statements find the team with the higher seed in the matchup
    if (team1.getSeed() < team2.getSeed()) {
        lowSeed = team2;
        highSeed = team1;
        // seeding will be used as a key to find the odds of one team winning for a given seeded matchup
        seeding = to_string(team1.getSeed()) + "-" + to_string(team2.getSeed());
    }
    if (team1.getSeed() > team2.getSeed()) {

        lowSeed = team1;
        highSeed = team2;
        seeding = to_string(team2.getSeed()) + "-" + to_string(team1.getSeed());
    }
    if (team1.getSeed() == team2.getSeed()) {
        // if the teams have the same seed, pick one of them as the high seed randomly
        // this will prevent bias towards the teams that end up getting passed into the first argument
        // naturally as part of the way the bracket is constructed
        if (rand() % 2 == 1) {
            lowSeed = team1;
            highSeed = team2;
        }
        else {
            lowSeed = team2;
            highSeed = team1;
        }

        seeding = to_string(team2.getSeed()) + "-" + to_string(team1.getSeed());
    }

    // get the odds of the higher seed winning
    odds = oddsMap[seeding];

    randomNum = 1 + rand() % 100;

    if (randomNum < odds) {
        winner = highSeed;
    }
    if (randomNum >= odds) {
        winner = lowSeed;
    }
    if (odds < 0.001) {
        winner = highSeed;
    }
    highTitle << "#" << highSeed.getSeed() << " " << highSeed.getName();
    lowTitle << "#" <<lowSeed.getSeed() << " " << lowSeed.getName();
    matchupResult << setw(20) << left << highTitle.str();
    matchupResult << setw(4) << left << "vs";
    matchupResult << setw(20) << left << lowTitle.str();
    matchupResult << setw(10) << "winner: " << "#" << winner.getSeed() << " " << winner.getName() << endl;

    bracketOutput += matchupResult.str();

    return winner;
}

#endif //MM_BRACKET_MAKER_TEAM_H
