#include <iostream>
#include "SpaceX.h"

int main (int argc, char * argv[]) {
    Monopoly::GamestateClass Gamestate;
    Monopoly::BoardClass board;
    Monopoly::DiceRollClass diceRoll;
    unsigned long currentTurnNumber = 0;

    board.readRules(argv[1]);
    board.readBoard(argv[2]);
    FILE *RANDOM_FILENAME = fopen(argv[3], "r");

    board.PlayerInitialization(board);
    unsigned long numPlayers = board.getNumPlayers();
    unsigned long totalnumPlayersStillInGame = board.getnumPlayersStillInGame();
    board.setCurrTurnNumber(currentTurnNumber);

    // While game is not over
    while (!Gamestate.GameOver (&board)) {
        Gamestate.PlayerMovement(Gamestate, board, &diceRoll, currentTurnNumber % numPlayers, RANDOM_FILENAME);
        currentTurnNumber++;
        board.setCurrTurnNumber(currentTurnNumber);
    }

    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame()) {
        board.displayBoard(board);
    } else if (board.rules.getTurnLimit2endGame() != 0 && board.getnumPlayersStillInGame() == 1) {
        (board).displayBoard(board);
    }
    fclose(RANDOM_FILENAME);
    Gamestate.WinnerDeclaration(board, totalnumPlayersStillInGame);

    return 0;
}