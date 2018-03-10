//
// Created by Rishabh 2 on 2/7/18.
//
#include <iostream>
#include "SpaceX.h"

int Monopoly::DiceRollClass::getDiceRoll (FILE *RANDOM_FILENAME, Monopoly::BoardClass &board, int *num1, int *num2) {


    fscanf(RANDOM_FILENAME, "%d\n%d\n", &(*num1), &(*num2));

    diceRoll = (*num1 % 6) + (*num2 % 6) + 2;

    *num1 %= 6;
    *num2 %= 6;

    // Restart file if number of dice turns are over
    if (feof(RANDOM_FILENAME)) {
        fseek(RANDOM_FILENAME, 0, SEEK_SET);
    }

    return diceRoll;
}