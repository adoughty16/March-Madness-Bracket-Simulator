#include "Matchup.h"

Matchup::Matchup() {
    setWinner(-1);
    setLoser(-1);
}

Matchup::Matchup(int winner, int loser) {
    setWinner(winner);
    setLoser(loser);
}

void Matchup::setWinner(int winner) {
    this->winningSeed = winner;
}

void Matchup::setLoser(int loser) {
    this->losingSeed = loser;
}

int Matchup::getWinner() const {
    return winningSeed;
}

int Matchup::getLoser() const {
    return losingSeed;
}

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
        getline(fileIn, junk, ',');
        getline(fileIn, junk, ',');
        getline(fileIn, junk, ',');

        //next line winning seed
        fileIn >> winner >> comma;

        //junk two lines
        if (fileIn.peek() == '"') {
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
        }
        else {
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
        }

        //losing seed
        fileIn >> loser >> comma;

        //junk end of line

        if (fileIn.peek() == '"') {
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');

        }
        else {
            getline(fileIn, junk, ',');
            getline(fileIn, junk, ',');
        }

        if (fileIn.peek() == 1 || fileIn.peek() == 2) {
            fileIn >> junk >> comma;
        }

        matchups.push_back(Matchup(winner, loser));
    }

    fileIn.close();
}