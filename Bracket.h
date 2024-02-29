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
    Bracket() {
        // I manually update these each season. Eventually I will make a better way of doing this... Maybe next year...
        west.push_back(Team("Kansas", 1, "Big 12"));
        west.push_back(Team("Howard", 16, "MEAC"));
        west.push_back(Team("Arkansas", 8, "SEC"));
        west.push_back(Team("Illinois", 9, "Big Ten"));
        west.push_back(Team("Saint Mary's", 5, "West Coast"));
        west.push_back(Team("VCU", 12, "Atlantic 10"));
        west.push_back(Team("UConn", 4, "Big East"));
        west.push_back(Team("Iona", 13, "MAAC"));
        west.push_back(Team("TCU", 6, "Big 12"));
        west.push_back(Team("ASU", 11, "PAC 12"));
        west.push_back(Team("Gonzaga", 3, "West Coast"));
        west.push_back(Team("Grand Canyon", 14, "WAC"));
        west.push_back(Team("Northwestern", 7, "Big Ten"));
        west.push_back(Team("Boise St", 10, "Mountain West"));
        west.push_back(Team("UCLA", 2, "PAC 12"));
        west.push_back(Team("UNC Asheville", 15, "Big South"));

        south.push_back(Team("Alabama", 1, "SEC"));
        south.push_back(Team("AMCC", 16, "Southland"));
        south.push_back(Team("Maryland", 8, "Big Ten"));
        south.push_back(Team("West Virgina", 9, "Big 12"));
        south.push_back(Team("San Diego St", 5, "Mountain West"));
        south.push_back(Team("Charleston", 12, "Colonial"));
        south.push_back(Team("Virginia", 4, "ACC"));
        south.push_back(Team("Furman", 13, "Southern"));
        south.push_back(Team("Creighton", 6, "Big East"));
        south.push_back(Team("NC State", 11, "ACC"));
        south.push_back(Team("Baylor", 3, "Big 12"));
        south.push_back(Team("USCB", 14, "Big West"));
        south.push_back(Team("Missouri", 7, "SEC"));
        south.push_back(Team("Utah State", 10, "Mountain West"));
        south.push_back(Team("Arizona", 2, "PAC 12"));
        south.push_back(Team("Princeton", 15, "Ivy"));

        east.push_back(Team("Purdue", 1, "Big Ten"));
        east.push_back(Team("FDU", 16, "Northeast"));
        east.push_back(Team("Memphis", 8, "American"));
        east.push_back(Team("FAU", 9, "C-USA"));
        east.push_back(Team("Duke", 5, "ACC"));
        east.push_back(Team("Oral Roberts", 12, "Summit"));
        east.push_back(Team("Tennessee", 4, "SEC"));
        east.push_back(Team("Louisiana", 13, "Sun Belt"));
        east.push_back(Team("Kentucky", 6, "SEC"));
        east.push_back(Team("Providence", 11, "Big East"));
        east.push_back(Team("Kansas St", 3, "Big 12"));
        east.push_back(Team("Montana St", 14, "Big Sky"));
        east.push_back(Team("Michigan St", 7, "Big Ten"));
        east.push_back(Team("USC", 10, "PAC 12"));
        east.push_back(Team("Marquette", 2, "Big East"));
        east.push_back(Team("Vermont", 15, "America East"));

        midwest.push_back(Team("Houston",1, "American"));
        midwest.push_back(Team("N Kentucky",16, "Horizon"));
        midwest.push_back(Team("Iowa",8, "Big Ten"));
        midwest.push_back(Team("Auburn",9, "SEC"));
        midwest.push_back(Team("Miami",5, "ACC"));
        midwest.push_back(Team("Drake",12, "Missouri Valley"));
        midwest.push_back(Team("Indiana",4, "Big Ten"));
        midwest.push_back(Team("Kent State",13, "MAC"));
        midwest.push_back(Team("Iowa State",6, "Big 12"));
        midwest.push_back(Team("PITT",11, "ACC"));
        midwest.push_back(Team("Xavier",3, "Big East"));
        midwest.push_back(Team("Kennesaw St",14, "ASUN"));
        midwest.push_back(Team("Texas A&M",7, "SEC"));
        midwest.push_back(Team("Penn State",10, "Big Ten"));
        midwest.push_back(Team("Texas",2, "Big 12"));
        midwest.push_back(Team("Colgate",15, "Patriot"));
    }

    vector<Team> getWest() const {
        return west;
    }

    vector<Team> getEast() const {
        return east;
    }

    vector<Team> getMidwest() const {
        return midwest;
    }

    vector<Team> getSouth() const {
        return south;
    }

    vector<int> get_final_4_seeds() const {
        vector<int> seeds;
        for (auto i : south_eastTwo) {
            seeds.push_back(i.getSeed());
        }
        for (auto i : west_midwestTwo) {
            seeds.push_back(i.getSeed());
        }
        return seeds;
    }

    Team get_champion() const {
        return champion;
    }

    // all of the following simulation functions simulate rounds of the tournament. There are two calls for every round sim. One that updates a string to keep track
    // of bracket data, and one that does not. The ones that do not are used for checking bias over many simulations where it would not make sense to keep track of individual
    // brackets.
    void sim_round_64(unordered_map<string, float> oddsMap) {
        for (int i = 0; i < 16; i += 2) {
            southEight.push_back(simulateGame(getSouth()[i], getSouth()[i + 1], oddsMap));
        }
        for (int i = 0; i < 16; i += 2) {
            midwestEight.push_back(simulateGame(getMidwest()[i], getMidwest()[i + 1], oddsMap));
        }
        for (int i = 0; i < 16; i += 2) {
            eastEight.push_back(simulateGame(getEast()[i], getEast()[i + 1], oddsMap));
        }
        for (int i = 0; i < 16; i += 2) {
            westEight.push_back(simulateGame(getWest()[i], getWest()[i + 1], oddsMap));
        }
    }

    void sim_round_32(unordered_map<string, float> oddsMap) {
        for (int i = 0; i < 8; i += 2) {
            southFour.push_back(simulateGame(southEight[i], southEight[i + 1], oddsMap));
        }
        for (int i = 0; i < 8; i += 2) {
            midwestFour.push_back(simulateGame(midwestEight[i], midwestEight[i + 1], oddsMap));
        }
        for (int i = 0; i < 8; i += 2) {
            eastFour.push_back(simulateGame(eastEight[i], eastEight[i + 1], oddsMap));
        }
        for (int i = 0; i < 8; i += 2) {
            westFour.push_back(simulateGame(westEight[i], westEight[i + 1], oddsMap));
        }
    }

    void sim_sweet_16(unordered_map<string, float> oddsMap) {
        for (int i = 0; i < 4; i += 2) {
            southTwo.push_back(simulateGame(southFour[i], southFour[i + 1], oddsMap));
        }
        for (int i = 0; i < 4; i += 2) {
            midwestTwo.push_back(simulateGame(midwestFour[i], midwestFour[i + 1], oddsMap));
        }
        for (int i = 0; i < 4; i += 2) {
            eastTwo.push_back(simulateGame(eastFour[i], eastFour[i + 1], oddsMap));
        }
        for (int i = 0; i < 4; i += 2) {
            westTwo.push_back(simulateGame(westFour[i], westFour[i + 1], oddsMap));
        }
    }

    void sim_elite_8(unordered_map<string, float> oddsMap) {
        south_eastTwo.push_back(simulateGame(southTwo[0], southTwo[1], oddsMap));
        west_midwestTwo.push_back(simulateGame(midwestTwo[0], midwestTwo[1], oddsMap));
        south_eastTwo.push_back(simulateGame(eastTwo[0], eastTwo[1], oddsMap));
        west_midwestTwo.push_back(simulateGame(westTwo[0], westTwo[1], oddsMap));
    }

    void sim_final_4(unordered_map<string, float> oddsMap) {
        championshipTwo.push_back(simulateGame(south_eastTwo[0], south_eastTwo[1], oddsMap));
        championshipTwo.push_back(simulateGame(west_midwestTwo[0], west_midwestTwo[1], oddsMap));
    }

    void sim_championship(unordered_map<string, float> oddsMap) {
        champion = simulateGame(championshipTwo[0], championshipTwo[1], oddsMap);
    }

    //
    // these are the overloaded functions that update the bracket string
    //
    void sim_round_64(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "--------------------Round of 64--------------------\n";
        tourneyString += "SOUTH:\n";
        for (int i = 0; i < 16; i += 2) {
            southEight.push_back(simulateGame(getSouth()[i], getSouth()[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "MIDWEST:\n";
        for (int i = 0; i < 16; i += 2) {
            midwestEight.push_back(simulateGame(getMidwest()[i], getMidwest()[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "EAST:\n";
        for (int i = 0; i < 16; i += 2) {
            eastEight.push_back(simulateGame(getEast()[i], getEast()[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "WEST:\n";
        for (int i = 0; i < 16; i += 2) {
            westEight.push_back(simulateGame(getWest()[i], getWest()[i + 1], oddsMap, tourneyString));
        }
    }

    void sim_round_32(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "--------------------Round of 32--------------------\n";
        tourneyString += "SOUTH:\n";
        for (int i = 0; i < 8; i += 2) {
            southFour.push_back(simulateGame(southEight[i], southEight[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "MIDWEST:\n";
        for (int i = 0; i < 8; i += 2) {
            midwestFour.push_back(simulateGame(midwestEight[i], midwestEight[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "EAST:\n";
        for (int i = 0; i < 8; i += 2) {
            eastFour.push_back(simulateGame(eastEight[i], eastEight[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "WEST:\n";
        for (int i = 0; i < 8; i += 2) {
            westFour.push_back(simulateGame(westEight[i], westEight[i + 1], oddsMap, tourneyString));
        }
    }

    void sim_sweet_16(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "----------------------Sweet 16----------------------\n";
        tourneyString += "SOUTH:\n";
        for (int i = 0; i < 4; i += 2) {
            southTwo.push_back(simulateGame(southFour[i], southFour[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "MIDWEST:\n";
        for (int i = 0; i < 4; i += 2) {
            midwestTwo.push_back(simulateGame(midwestFour[i], midwestFour[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "EAST:\n";
        for (int i = 0; i < 4; i += 2) {
            eastTwo.push_back(simulateGame(eastFour[i], eastFour[i + 1], oddsMap, tourneyString));
        }
        tourneyString += "WEST:\n";
        for (int i = 0; i < 4; i += 2) {
            westTwo.push_back(simulateGame(westFour[i], westFour[i + 1], oddsMap, tourneyString));
        }
    }

    void sim_elite_8(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "----------------------Elite 8----------------------\n";
        south_eastTwo.push_back(simulateGame(southTwo[0], southTwo[1], oddsMap, tourneyString));
        west_midwestTwo.push_back(simulateGame(midwestTwo[0], midwestTwo[1], oddsMap, tourneyString));
        south_eastTwo.push_back(simulateGame(eastTwo[0], eastTwo[1], oddsMap, tourneyString));
        west_midwestTwo.push_back(simulateGame(westTwo[0], westTwo[1], oddsMap, tourneyString));
    }

    void sim_final_4(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "----------------------Final 4----------------------\n";
        championshipTwo.push_back(simulateGame(south_eastTwo[0], south_eastTwo[1], oddsMap, tourneyString));
        championshipTwo.push_back(simulateGame(west_midwestTwo[0], west_midwestTwo[1], oddsMap, tourneyString));
    }

    void sim_championship(string& tourneyString, unordered_map<string, float> oddsMap) {
        tourneyString += "--------------------Championship--------------------\n";
        champion = simulateGame(championshipTwo[0], championshipTwo[1], oddsMap, tourneyString);
    }

    void clear_bracket() {
        westEight.clear();
        southEight.clear();
        eastEight.clear();
        midwestEight.clear();
        westFour.clear();
        southFour.clear();
        eastFour.clear();
        midwestFour.clear();
        westTwo.clear();
        southTwo.clear();
        eastTwo.clear();
        midwestTwo.clear();
        south_eastTwo.clear();
        west_midwestTwo.clear();
        championshipTwo.clear();
    }
};

#endif //MM_BRACKET_MAKER_BRACKET_H
