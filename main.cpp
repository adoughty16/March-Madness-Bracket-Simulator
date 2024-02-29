#include <iostream>
#include "Matchup.h"
#include <unordered_map>
#include <iomanip>
#include "Team.h"
#include "Bracket.h"

using namespace std;

// NOTE a higher seed means a lower number. The #1 seed is a higher seed than the #16 seed. This can sometimes be confusing...

int main() {

    srand(time(NULL));
    bool BIAS_CHECKING = false;
    int BIAS_CHECK_ITERS = 10000;

    // load historic games into matchups
    vector<Matchup> matchups;
    getDataFromFile("C:/Users/adoug/CLionProjects/MM_Bracket_Maker/Results.csv", matchups);
    getDataFromFileTwo("C:/Users/adoug/CLionProjects/MM_Bracket_Maker/Results2.csv", matchups);

    //seeding total tracks total matchups bewteen seed pairs
    unordered_map<string, int> seedingTotal;
    //seedingHighSeedWins tracks total matchups between seed pairs in which the higher seed won
    unordered_map<string, int> seedingHighSeedWins;
    //seedingHighSeedPercentage will be used to store the proportion of games between seed pairs won by the higher seed
    unordered_map<string, float> seedingHighSeedPercentage;

    // for every matchup in matchups vector
    for(auto i: matchups) {

        // get the winning and losing seeds of the matchup
        int winner = i.getWinner();
        int loser = i.getLoser();

        string winnerS = to_string(winner);
        string loserS = to_string(loser);
        string seedVseed;

        //format so that the higher seed (lower number) is first.
        // 
        // i.e. 1-6, and 6-1 are two ways to encode a 1 seed vs a 6 seed. We don't want to have two keys in the map associated with the same
        // seeding matchup, so this makes sure we only use the form low-high (1-6, in the case of the example)
        if (winner <= loser) {
            seedVseed = winnerS + "-" + loserS;
        }
        else {
            seedVseed = loserS + "-" + winnerS;
        }
        
        // if this seeding combination is not already in the map, add it
        if (seedingTotal.count(seedVseed) == 0) {
            seedingTotal.insert(pair<string, int>(seedVseed, 1));
        }
        // otherwise increment the value associated with it
        else {
            seedingTotal[seedVseed]++;
        }
        
        // if the seed of the winner is lower than the seed of the loser (numerically)
        if (winner < loser) {
            //then the higher seed (in terms of the tournament) won
            //add it to the highSeedWins map, or increment the value if it is already there
            if (seedingHighSeedWins.count(seedVseed) == 0) {
                seedingHighSeedWins.insert(pair<string, int>(seedVseed, 1));
            }
            else {
                seedingHighSeedWins[seedVseed]++;
            }
        }
    }

    //go through the total matchups
    for(auto i : seedingTotal) {
        //and update the percentage map
        seedingHighSeedPercentage.insert(pair<string, float>(i.first,100 * (seedingHighSeedWins[i.first])  / float(i.second)));
    }


    // if we are checking the model for bias we want to simulate it repeatedly and print the results of BIAS_CHECK_ITERS itterations
    if (BIAS_CHECKING) {
        // Run the simulation 1000 times
        unordered_map<string, int> winnersCount;
        for (int i = 0; i < BIAS_CHECK_ITERS; ++i) {
            Bracket tourney = Bracket();
            string champ;
            string champConference;
            int champSeed = 999; // Default value higher than 4
            bool rejected = true;

            // Simulate brackets until generating a reasonable one
            while (champSeed > 4 || rejected) {
                rejected = false;
                tourney.sim_round_64(seedingHighSeedPercentage);
                tourney.sim_round_32(seedingHighSeedPercentage);
                tourney.sim_sweet_16(seedingHighSeedPercentage);
                tourney.sim_elite_8(seedingHighSeedPercentage);
                tourney.sim_final_4(seedingHighSeedPercentage);
                tourney.sim_championship(seedingHighSeedPercentage);

                for (auto seed : tourney.get_final_4_seeds()) {
                    if (seed > 11) {
                        rejected = true;
                    }
                }

                champ = tourney.get_champion().getName();
                champSeed = tourney.get_champion().getSeed();
                champConference = tourney.get_champion().getConference();

                if (champSeed > 4 || (champConference != "ACC" &&
                    champConference != "Big 12" &&
                    champConference != "Big East" &&
                    champConference != "Big Ten" &&
                    champConference != "PAC 12" &&
                    champConference != "SEC")) {
                    rejected = true;
                    tourney.clear_bracket();
                }
            }

            // Count the winner
            winnersCount[champ]++;
        }

        // Convert the map to a vector of pairs
        vector<pair<string, int>> winners(winnersCount.begin(), winnersCount.end());

        // Sort the vector based on the values (integers)
        sort(winners.begin(), winners.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second; // Sort in descending order of integer values
            });

        // Print the results
        for (const auto& pair : winners) {
            cout << pair.first << " won " << pair.second << " times." << endl;
        }
    }

    //otherwise simulate one bracket and print result
    else {
        //Tourney
        Bracket tourney = Bracket();
        //seed of champion (to control loop)
        int champSeed = 999; //default value higher than 4
        string tourneyString;
        string champ;
        string champConference;
        bool rejected = true;

        // while loop will keep simulating brackets until it has generated one that is deemed reasonable (based on the seed/conference of the champ, seeds of the final four)
        while (champSeed > 4 || rejected) {

            rejected = false;
            //tourneyString will aggregate matchup data throughout the simulation so that we can display the complete bracket at the end
            tourneyString = "";

            //simulate each round
            tourney.sim_round_64(tourneyString, seedingHighSeedPercentage);
            tourney.sim_round_32(tourneyString, seedingHighSeedPercentage);
            tourney.sim_sweet_16(tourneyString, seedingHighSeedPercentage);
            tourney.sim_elite_8(tourneyString, seedingHighSeedPercentage);
            tourney.sim_final_4(tourneyString, seedingHighSeedPercentage);
            tourney.sim_championship(tourneyString, seedingHighSeedPercentage);

            // reject any brackets that have any seed higher than an 11 in the final four
            for (auto i : tourney.get_final_4_seeds()) {
                if (i > 11) {
                    rejected = true;
                }
            }

            champ = tourney.get_champion().getName();
            champSeed = tourney.get_champion().getSeed();
            champConference = tourney.get_champion().getConference();

            //reject any brackets that have a seed higher than 4 winning, or a winner that doesn't belong to one of the 6 most competitive conferences
            if (champSeed > 4 || (champConference != "ACC" &&
                champConference != "Big 12" &&
                champConference != "Big East" &&
                champConference != "Big Ten" &&
                champConference != "PAC 12" &&
                champConference != "SEC")) {
                //set rejection flag
                rejected = true;
                // Clear bracket
                tourney.clear_bracket();
            }
        }

        //print bracket
        std::cout << tourneyString << endl;
        std::cout << "Champ:  #" << champSeed << " " << champ << endl;
    }

    return 0;
}
