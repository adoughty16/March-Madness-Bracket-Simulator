//
// Created by adoug on 3/15/2022.
//

#ifndef MM_BRACKET_MAKER_MATCHUP_H
#define MM_BRACKET_MAKER_MATCHUP_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::ifstream;
using std::string;
using std::vector;
using std::unordered_map;
using std::pair;

class Matchup {
private:
    int winningSeed;
    int losingSeed;

public:

    Matchup();
    Matchup(int winner, int loser);

    void setWinner(int winner);
    void setLoser(int loser);

    int getWinner() const;
    int getLoser() const;
};

// loads data in into vector of matchups from a .csv with winner and loser data
void getDataFromFileTwo(string fileName, vector<Matchup>& matchups);

// loads data in into vector of matchups from a more complicated .csv
void getDataFromFile(string fileName, vector<Matchup>& matchups);

#endif //MM_BRACKET_MAKER_MATCHUP_H
