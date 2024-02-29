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

    Matchup() {
        setWinner(-1);
        setLoser(-1);
    }

    Matchup(int winner, int loser) {
        setWinner(winner);
        setLoser(loser);
    }

    void setWinner(int winner) {
        this->winningSeed = winner;
    }

    void setLoser(int loser) {
        this->losingSeed = loser;
    }

    int getWinner() const {
        return winningSeed;
    }

    int getLoser() const {
        return losingSeed;
    }
};

// loads data in into vector of matchups from a .csv with winner and loser data
void getDataFromFileTwo(string fileName, vector<Matchup>& matchups) {

    ifstream fileIn;
    fileIn.open(fileName);

    string header;

    if (fileIn) {
        getline(fileIn, header); //consume header line
    }

    int loser, winner;
    char comma;

    while (fileIn && fileIn.peek() != EOF) {

        fileIn >> winner >> comma;
        fileIn >> loser >> comma;

        matchups.push_back(Matchup(winner, loser));

    }

    fileIn.close();

}

// loads data in into vector of matchups from a more complicated .csv
void getDataFromFile(string fileName, vector<Matchup>& matchups) {

    ifstream fileIn;
    fileIn.open(fileName);

    string header;

    if (fileIn) {
        getline(fileIn, header); //consume header line
    }

    string junk;
    int loser, winner;
    char comma;

    while (fileIn && fileIn.peek() != EOF) {

        //junk first 3 values
        getline(fileIn,junk,',');
        getline(fileIn,junk,',');
        getline(fileIn,junk,',');

        //next line winning seed
        fileIn >> winner >> comma;

        //junk two lines
        if (fileIn.peek() == '"') {
            getline(fileIn,junk,',');
            getline(fileIn,junk,',');
            getline(fileIn,junk,',');
        }
        else {
            getline(fileIn,junk,',');
            getline(fileIn,junk,',');
        }

        //losing seed
        fileIn >> loser >> comma;

        //junk end of line

        if (fileIn.peek() == '"') {
            getline(fileIn,junk,',');
            getline(fileIn,junk,',');
            getline(fileIn,junk,',');

        }
        else {
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
        }

        if (fileIn.peek() == 1 || fileIn.peek() == 2) {
            fileIn >> junk >> comma;
        }

        matchups.push_back(Matchup(winner,loser));
    }

    fileIn.close();
}


#endif //MM_BRACKET_MAKER_MATCHUP_H
