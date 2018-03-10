//
// Created by Rishabh 2 on 2/20/18.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "SpaceX.h"

void Monopoly::GamestateClass::LeavingGame(BoardClass &board, unsigned long chosenPlayer) {
    unsigned long NONE = 101;

    // Make all his properties purchaseable
    for (unsigned long i = 0; i < board.getInTotalSpaces(); i++) {
        if (board.boardSpaces.at(i)->getTakenByPlayer() == chosenPlayer) {
            board.boardSpaces.at(i)->setTakenByPlayer(NONE); //abstract value 101  = none mean it's not taken
            board.boardSpaces.at(i)->setTaken(false);
            board.boardSpaces.at(i)->sethouseUpgrades(0);
            board.boardSpaces.at(i)->sethotelUpgrades(0);
        }
    }

    // Updating player properties
    board.player.at(chosenPlayer).setMoney(0);
    board.player.at(chosenPlayer).setPosition(NONE);
    board.player.at(chosenPlayer).setNumberName(NONE);
    board.player.at(chosenPlayer).setIsInGame(false);

    unsigned long numPlayersInGame = board.getnumPlayersStillInGame();
    numPlayersInGame -= 1;
    board.setnumPlayersStillInGame(numPlayersInGame);
    if (board.getCurrTurnNumber() != board.rules.getTurnLimit2endGame()
        && board.getnumPlayersStillInGame() != 1) {
        board.displayBoard(board);
    }
}

bool Monopoly::GamestateClass::GameOver(BoardClass *board) {

    // If the game has reached its max turns, gameOver.
    if((*board).rules.getTurnLimit2endGame() == (*board).getCurrTurnNumber()) {
        return true;
    } else if ((*board).rules.getNumOfPlayers2endGame() == (*board).getnumPlayersStillInGame()) {  // If game reaches minimum players to win, gameOver
        return true;
    } else if (board->getNumPlayers() == 1){
        return true;
    } else {
        return false;
    }
}

void Monopoly::GamestateClass::WinnerDeclaration (BoardClass &board, unsigned long totalnumPlayersStillInGame) {
    unsigned long temp = 0;
    unsigned long PlayerWithHighestNetworth = 0;
    unsigned long playerNumNetWorth = 0;

    // # NET-WORTH MECHANICS
    // houses * house cost + hotel cost + property cost + money

    for (unsigned long playerNum = 0; playerNum < board.getNumPlayers(); playerNum++) {
        playerNumNetWorth += board.player.at((playerNum)).getMoney();

        for (unsigned long propertyNum = 0; propertyNum < board.getInTotalSpaces(); propertyNum++) {
            // If player owns property
            if (board.boardSpaces.at(propertyNum)->getTakenByPlayer() ==
                board.player.at((playerNum)).getNumberName()) {
                // property costs
                playerNumNetWorth += board.boardSpaces.at(propertyNum)->getCost();
                // If hotel exists
                if (board.boardSpaces.at(propertyNum)->gethotelUpgrades() > 0) {
                    // networth = hotel + houses
                    playerNumNetWorth += board.boardSpaces.at(propertyNum)->getHotelCost();
                    playerNumNetWorth += board.boardSpaces.at(propertyNum)->gethouseUpgrades() *
                                         board.boardSpaces.at(propertyNum)->getHouseCost();
                }
                    // if houses exist but NO hotel
                else if (board.boardSpaces.at(propertyNum)->gethouseUpgrades() > 0) {
                    // net worth = housing upgrades
                    playerNumNetWorth += board.boardSpaces.at(propertyNum)->gethouseUpgrades() *
                                         board.boardSpaces.at(propertyNum)->getHouseCost();
                }
            }
        }
        board.player.at((playerNum)).setNetWorth(playerNumNetWorth);
        playerNumNetWorth = 0;
    }

    // If total number of players = 1 declare player as winner
    if (board.getNumPlayers() == 1) {
        std::cout << "The winners are" << std::endl << board.player.at(0).getRealName() << std::endl;
        return;
    } else if (board.getnumPlayersStillInGame() == 1 ||
               board.getnumPlayersStillInGame() == board.rules.getNumOfPlayers2endGame()) {
        std::cout << "The winners are" << std::endl;
        for (unsigned long k = 0; k < board.getNumPlayers(); k++) {
            if (board.player.at(k).getIsInGame()) {
                std::cout << board.player.at(k).getRealName() << std::endl;
            }
        }
        return;
    } else {
        bool allPlayersHaveSameNetworth = false;
        for (unsigned long j = 1; j < board.getNumPlayers(); j++) {
            if (board.player.at(j).getNetWorth() == board.player.at(temp).getNetWorth()) {
                allPlayersHaveSameNetworth = true;
            } else {
                allPlayersHaveSameNetworth = false;
                break;
            }

        }
        temp = 0;
        if (allPlayersHaveSameNetworth) {
            std::cout << "The winners are" << std::endl;
            for (unsigned long j = 0; j < board.getNumPlayers(); j++) {
                std::cout << board.player.at(j).getRealName() << std::endl;
            }
            return;
        } else {
            std::cout << "The winners are" << std::endl;
            for (unsigned long j = 1; j < board.getNumPlayers(); j++) {
                if (board.player.at(j).getNetWorth() >= board.player.at(temp).getNetWorth()) {
                    if (board.player.at(j).getNetWorth() >= board.player.at(temp).getNetWorth()) {
                        PlayerWithHighestNetworth = j;
                    } else {
                        PlayerWithHighestNetworth = temp;
                    }
                    temp++;
                }
                std::cout << board.player.at(PlayerWithHighestNetworth).getRealName() << std::endl;
            }
            return;
        }
    }
    // If max turn number has reached,
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame()) {
        // Find person with highest networth and assign to PlayerWithHighestNetworth
        std::cout << "The winners are" << std::endl;
        for (unsigned long k = 0; k < board.getNumPlayers(); k++) {
            if (board.player.at(k).getIsInGame()) {
                std::cout << board.player.at(k).getRealName() << std::endl;
            }
        }
        return;
    } else {
        // If totalnumplayers reaches a minimum,
        if (totalnumPlayersStillInGame == board.rules.getNumOfPlayers2endGame()) {
            std::cout << "The winners are" << std::endl;
            // Declare players still in game as winners
            for (unsigned long k = 0; k < board.getNumPlayers(); k++) {
                if (board.player.at(k).getIsInGame()) {
                    std::cout << board.player.at(k).getRealName() << std::endl;
                }
            }
        }
        return;
    }
}