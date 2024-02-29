//
// Created by adoug on 3/15/2022.
//

#ifndef MM_BRACKET_MAKER_TOURNAMENT_H
#define MM_BRACKET_MAKER_TOURNAMENT_H

#include "Bracket.h"

// I might eventually incorporate this but I haven't yet.

class Tournament {

private:
    Bracket bracket;

public:
    Tournament() {

        bracket = Bracket();

    }
};

#endif //MM_BRACKET_MAKER_TOURNAMENT_H
