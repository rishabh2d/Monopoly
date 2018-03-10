//
// Created by Rishabh 2 on 2/5/18.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "SpaceX.h"

int Monopoly::GamestateClass::PlayerMovement(GamestateClass &Gamestate, Monopoly::BoardClass &board, Monopoly::DiceRollClass *diceRoll,
                                             unsigned long chosenPlayer, FILE* RANDOM_FILENAME) {
    unsigned long numTurnsInJail;
    int choice;
    bool turnHasNotEnded = true;
    int num1, num2;
    bool playerIsJailed = board.player.at(chosenPlayer).getIsInJail();
    unsigned long positionOfJail = board.getJailPosition();
    unsigned long playerPositionOnBoard = board.player.at(chosenPlayer).getPositionOnBoard();
    //unsigned long moneyToPayBank = board.boardSpaces[board.getPayToBankPosition()]->getAmtMoneyToPayBank();
    bool freeParkingIsEnabled = board.rules.getFreeParkingOption();
    bool bankruptcyHasBeenDeclared = true;

    //board.displayBoard(board);

    if (positionOfJail > 10000) {
        //do nothing
    } else
        numTurnsInJail = board.boardSpaces[positionOfJail]->getNumTurnsInJail();

    unsigned long playerMoney = board.player.at(chosenPlayer).getMoney();

    // If the player is not in game, then print a newline and end the player turn.
    // FIXME - Do we need to print a new line/endl ?
    if ( !(board.player.at(chosenPlayer).getIsInGame())) {
        return 0;
    }
    if (playerIsJailed) {
        playerIsJailed = Monopoly::GamestateClass::JailMechanics(board, positionOfJail,
                                                                 board.player.at(chosenPlayer).getMoney(), chosenPlayer,
                                                                 diceRoll, RANDOM_FILENAME);
    }
    if (playerIsJailed) {
        return 0;
    } else {

        int diceRollValue; //= (*diceRoll).getDiceRoll(RANDOM_FILENAME, &(*board), &num1, &num2);

        unsigned long counter = 0;

        if (board.player.at(chosenPlayer).getreleasedAfterServing() == true) {

            if (playerMoney >= board.boardSpaces[positionOfJail]->getMoney2EscapeJail()) {
                playerMoney -= board.boardSpaces[positionOfJail]->getMoney2EscapeJail();
                board.player.at(chosenPlayer).setMoney(playerMoney);

                std::cout << board.player.at(chosenPlayer).getRealName()
                          << ", you had to pay $" << board.boardSpaces[positionOfJail]->getMoney2EscapeJail()
                          << " to get out of jail" << std::endl;

                if (freeParkingIsEnabled) {
                    // put this money in free parking instead
                    unsigned long moneyInParking = board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
                    moneyInParking += board.boardSpaces[positionOfJail]->getMoney2EscapeJail();
                    board.boardSpaces[board.getParkingPosition()]->setParkingMoney(moneyInParking);
                }
            } else {  // if player does not have enough money to pay jail escape fee
                bankruptcyHasBeenDeclared = SellingUpgradesForRent(board, chosenPlayer,
                                                                   board.boardSpaces[positionOfJail]->getMoney2EscapeJail());

                if (bankruptcyHasBeenDeclared) {

                    board.player.at(chosenPlayer).setMoney(0);
                    board.player.at(chosenPlayer).setNetWorth(0);
                    board.player.at(chosenPlayer).setIsInGame(false);
                    board.player.at(chosenPlayer).setNumberName(101);
                    board.player.at(chosenPlayer).setPosition(0);
                    unsigned long reducePlayerByOne = board.getnumPlayersStillInGame() - 1;
                    board.setnumPlayersStillInGame(reducePlayerByOne);

                    // Print final lines

                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << " went bankrupt when paying to leave jail "
                              << std::endl;

                    if (freeParkingIsEnabled) {
                        unsigned long moneyInParking = board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
                        moneyInParking += playerMoney;
                        board.boardSpaces[board.getParkingPosition()]->setParkingMoney(moneyInParking);
                        playerMoney = 0;
                    }

                } else {
                    playerMoney -= board.boardSpaces[positionOfJail]->getMoney2EscapeJail();
                    board.player.at(chosenPlayer).setMoney(playerMoney);

                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << ", you had to pay $" << board.boardSpaces[positionOfJail]->getMoney2EscapeJail()
                              << " to get out of jail" << std::endl;

                    if (freeParkingIsEnabled) {  // put this money in free parking instead
                        unsigned long moneyInParking = board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
                        moneyInParking += board.boardSpaces[positionOfJail]->getMoney2EscapeJail();
                        board.boardSpaces[board.getParkingPosition()]->setParkingMoney(moneyInParking);
                    }
                }
            }
        }

        while (turnHasNotEnded && board.player.at(chosenPlayer).getIsInGame()) {
            while (counter != board.rules.getRerollsAllowed() + 1) {
                //FIXME correct displayboardclass
                //board.displayBoard(board);

                std::cout << board.player.at(chosenPlayer).getRealName() << " please enter your move" << std::endl;
                std::cout << "1 to roll dice" << std::endl;
                std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
                std::cout << "3 to sell a house or hotel" << std::endl;
                std::cout << "4 to leave the game" << std::endl;

                std::cout << "Your move: ";
                std::cin >> choice;

                if (choice == 1) {
                    if (counter > 0) {
                        if (num1 != num2) {
                            diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                        }
                        else if (board.rules.getRerollsAllowed() <= 0){
                            diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                        }
                        std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                  << diceRollValue << std::endl;
                        playerPositionOnBoard += static_cast<unsigned long> (diceRollValue);

                        if (playerPositionOnBoard >= board.getInTotalSpaces()) {
                            while (playerPositionOnBoard >= board.getInTotalSpaces()) {
                                // Decrease the player position until he is on board he is on board.
                                playerPositionOnBoard -= board.getInTotalSpaces();
                                if (playerPositionOnBoard == 0) {
                                    playerMoney += board.boardSpaces.at(0)->getGOMoney() * board.rules.getGOSalaryMultiplier();
                                    break;
                                }
                                // Increase the player money every time he crosses GO
                                playerMoney += board.boardSpaces.at(0)->getGOMoney();
                            }
                            // If after placing the player on board, the player lands on GO, Multiply money given
                            // FIXME - add it to the else statement below
                        }

                        // Update the new money and position for chosen player after a possible GORepetition
                        board.player.at(chosenPlayer).setMoney(playerMoney);
                        board.player.at(chosenPlayer).setPosition(playerPositionOnBoard);

                        board.boardSpaces[playerPositionOnBoard]->callMechanics(Gamestate, board, diceRoll, chosenPlayer, diceRollValue,
                                                                                RANDOM_FILENAME, playerPositionOnBoard, numTurnsInJail,
                                                                                positionOfJail);
                    } else {
                        diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                        std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                  << diceRollValue << std::endl;

                        playerPositionOnBoard += static_cast<unsigned long> (diceRollValue);
                        playerMoney = board.player.at(chosenPlayer).getMoney();

                        if (playerPositionOnBoard >= board.getInTotalSpaces()) {
                            while (playerPositionOnBoard >= board.getInTotalSpaces()) {
                                // Decrease the player position until he is on board he is on board.
                                playerPositionOnBoard -= board.getInTotalSpaces();
                                if (playerPositionOnBoard == 0) {
                                    playerMoney += board.boardSpaces.at(0)->getGOMoney() * board.rules.getGOSalaryMultiplier();
                                    break;
                                }
                                // Increase the player money every time he crosses GO
                                playerMoney += board.boardSpaces.at(0)->getGOMoney();
                            }
                            // If after placing the player on board, the player lands on GO, Multiply money given
                            // FIXME - add it to the else statement below
                        }

                        // Update the new money and position for chosen player after a possible GORepetition
                        board.player.at(chosenPlayer).setMoney(playerMoney);
                        board.player.at(chosenPlayer).setPosition(playerPositionOnBoard);
                        if (playerPositionOnBoard == board.getJailPosition()) {
                            board.displayBoard(board);
                        }

                        board.boardSpaces[playerPositionOnBoard]->callMechanics(Gamestate, board, diceRoll, chosenPlayer, diceRollValue,
                                                                                RANDOM_FILENAME, playerPositionOnBoard, numTurnsInJail,
                                                                                positionOfJail);
                    }
                    turnHasNotEnded = false;
                    //board.displayBoard(board);

                } else if (choice == 2) {
                    BuyingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                    board.displayBoard(board);
                    turnHasNotEnded = true;
                } else if (choice == 3) {
                    SellingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                    board.displayBoard(board);
                    turnHasNotEnded = true;
                } else if (choice == 4) {
                    LeavingGame(board, chosenPlayer);
                    turnHasNotEnded = false;
                    // ADDITION - 36 - MADE THIS DISPLAY BOARD SHOW THE BOARD2
                    //board.displayBoard(board);
                    break;
                } else {
                    std::cout << "Incorrect Choice. Choose again." << std::endl;
                    turnHasNotEnded = true;
                    //exit(0);
                }

                if ((num1) == (num2)) {
                    if (counter != board.rules.getRerollsAllowed()  && board.rules.getRerollsAllowed() > 0) {
                        fscanf(RANDOM_FILENAME, "%d\n%d\n", &num1, &num2);
                        diceRollValue = (num1 % 6) + (num2 % 6) + 2;
                        counter++;
                    }
                    else{
                        counter++;
                    }
                }
                else {
                    break;
                }
            }
            if (counter == board.rules.getRerollsAllowed() + 1
                && turnHasNotEnded) {
                counter++;
            }
        }
    }
    unsigned long x = board.player.at(chosenPlayer).getReleasedFromJail();
    x++;
    board.player.at(chosenPlayer).setReleasedFromJail(x);

    if (board.player.at(chosenPlayer).getreleasedAfterServing() == true) {
        board.player.at(chosenPlayer).setreleasedAfterServing(false);
    }

    return 0;
}

void Monopoly::GamestateClass::MovementMechanics(GamestateClass &Gamestate,Monopoly::BoardClass &board, Monopoly::DiceRollClass *diceRoll,
                                                 unsigned long chosenPlayer, FILE* RANDOM_FILENAME, int diceRollValue) {

    //unsigned long numTurnsInJail = board.boardSpaces[positionOfJail]->getNumTurnsInJail();
    unsigned long playerPositionOnBoard = board.player.at(chosenPlayer).getPositionOnBoard();
    unsigned long playerMoney = board.player.at(chosenPlayer).getMoney();

    // # RENT MECHANICS

    // Using the following variables for managing rent
    unsigned long owner = board.boardSpaces.at(static_cast<unsigned long> (playerPositionOnBoard))->getTakenByPlayer();
    char choice = 'x';
    unsigned long SetIDofPlayerPosition = board.boardSpaces.at(playerPositionOnBoard)->getSetID();
    bool multiplerActivated = false;
    unsigned long PositionRent;

    // If the property position is not a GO Position
    if (playerPositionOnBoard != 0) {
        if (board.boardSpaces.at((playerPositionOnBoard))->getTaken()) {
            // If the position is owned by another player playing
            if (board.boardSpaces.at((playerPositionOnBoard))->getTakenByPlayer() !=
                chosenPlayer) {
                // Checking if property set multiplier applies
                for (unsigned long j = 1; j < board.getInTotalSpaces(); j++) {
                    if (board.boardSpaces.at(j)->getSetID() == SetIDofPlayerPosition) {
                        if (board.boardSpaces.at(j)->getTakenByPlayer() == owner) {
                            multiplerActivated = true;
                        } else {
                            multiplerActivated = false;
                            break;
                        }
                    }
                }
            }

            unsigned long numHouses = board.boardSpaces.at(playerPositionOnBoard)->gethouseUpgrades();

            // Choosing the type of rent
            if (board.boardSpaces.at(playerPositionOnBoard)->gethotelUpgrades() > 0) {
                // If hotels, exist, then rent with hotel
                PositionRent = board.boardSpaces.at(playerPositionOnBoard)->getRentWithHotel();
            } else if (board.boardSpaces.at(playerPositionOnBoard)->gethouseUpgrades() > 0) {
                // If houses exist, then rent with the number of houses
                PositionRent = static_cast<unsigned long>
                (board.boardSpaces.at(playerPositionOnBoard)->getRentWithHouse() * pow(2, (numHouses - 1)));
            } else if (multiplerActivated) {
                // If no hotels or houses, but property set multiplier is activated
                PositionRent =
                        board.boardSpaces.at(playerPositionOnBoard)->getRent() * board.rules.getpropertySetMultiplier();
            } else {
                // If no upgrades and Property Set Multiplier (PSM) is not activated
                PositionRent = board.boardSpaces.at(playerPositionOnBoard)->getRent();
            }

            bool bankruptcyHasBeenDeclared;
            if (playerMoney < PositionRent && chosenPlayer != owner) {

                bankruptcyHasBeenDeclared = SellingUpgradesForRent(board, chosenPlayer, PositionRent);

                if (bankruptcyHasBeenDeclared) {
                    unsigned long ownerMoney = board.player.at((owner)).getMoney();
                    // Assign chosenPlayer's money to owner
                    ownerMoney += playerMoney;
                    board.player.at((owner)).setMoney(ownerMoney);

                    // Assign chosenPlayer's properties to owner
                    for (unsigned long j = 0; j < board.getInTotalSpaces(); j++) {
                        if (board.boardSpaces.at(j)->getTakenByPlayer() ==
                            board.player.at(chosenPlayer).getNumberName()) {
                            board.boardSpaces.at(j)->setTakenByPlayer(owner);
                        }
                    }

                    playerMoney = 0;
                    // Update player properties
                    board.player.at(chosenPlayer).setMoney(0);
                    board.player.at(chosenPlayer).setNetWorth(0);
                    board.player.at(chosenPlayer).setIsInGame(false);
                    board.player.at(chosenPlayer).setNumberName(101);
                    board.player.at(chosenPlayer).setPosition(0);
                    unsigned long reducePlayerByOne = board.getnumPlayersStillInGame() - 1;
                    board.setnumPlayersStillInGame(reducePlayerByOne);

                    // Print final lines
                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << " went bankrupt to " << board.player.at((owner)).getRealName()
                              << " for landing on " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                              << std::endl;
                }
            } else {  // If the player DOES have enough money to pay rent,
                unsigned long ownerMoney = board.player.at((owner)).getMoney();
                if (owner != chosenPlayer) {
                    // Decrease money from chosenPlayer
                    playerMoney -= PositionRent;
                    board.player.at(chosenPlayer).setMoney(playerMoney);

                    // Pay the owner
                    ownerMoney += PositionRent;
                    board.player.at(static_cast<unsigned long> (owner)).setMoney(ownerMoney);

                    // Print final lines
                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << " paid " << board.player.at(static_cast<unsigned long> (owner)).getRealName()
                              << " $" << PositionRent
                              << " for landing on "
                              << board.boardSpaces.at(static_cast<unsigned long> (playerPositionOnBoard))->getName()
                              << std::endl;
                } else {
                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << ", you landed on "
                              << board.boardSpaces.at(playerPositionOnBoard)->getName()
                              << " which you already own" << std::endl;

                }
            }

        } else {  // If the position is not taken by a player (getTaken bool = false)
            // If the player money is lesser than price of property
            if (playerMoney < board.boardSpaces.at(
                    playerPositionOnBoard)->getCost()) {  // If the player wants to buy but cannot afford the property,

                std::cout << board.player.at(chosenPlayer).getRealName()
                          << ", you don't have enough money to afford "
                          << board.boardSpaces.at(playerPositionOnBoard)->getName() << ". ";
                std::cout << board.boardSpaces.at(playerPositionOnBoard)->getName()
                          << " costs $" << board.boardSpaces.at(playerPositionOnBoard)->getCost()
                          << " but you only have $" << board.player.at(chosenPlayer).getMoney() << std::endl;
            } else {  // If the player can afford property
                std::cout << "Would you like to buy " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                          << " for $" << board.boardSpaces.at(playerPositionOnBoard)->getCost() << "?" << std::endl;
                std::cout << "Rent on " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                          << " is $" << board.boardSpaces.at(playerPositionOnBoard)->getRent() << std::endl;

                std::cout << "Enter y for yes or n for no: " << std::endl;
                std::cin >> choice;
            }
            if (choice == 'Y' || choice == 'y') {
                // If player wants to buy and can afford the property,
                if (playerMoney >= board.boardSpaces.at(playerPositionOnBoard)->getCost()) {
                    // Reduce the property cost from chosenPlayer's money
                    playerMoney -= board.boardSpaces.at(playerPositionOnBoard)->getCost();
                    // Assign the player the property
                    board.boardSpaces.at(playerPositionOnBoard)->setTakenByPlayer(
                            chosenPlayer);
                    board.boardSpaces.at(playerPositionOnBoard)->setTaken(true);

                    // Print final lines
                    std::cout << board.player.at(chosenPlayer).getRealName()
                              << " bought " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                              << " for $" << board.boardSpaces.at(playerPositionOnBoard)->getCost() << std::endl;

                    board.player.at(chosenPlayer).setMoney(playerMoney);
                    //board.displayBoard(board);
                }
            } else if (choice == 'N' || choice == 'n') {
                //# AUCTION MECHANICS
                if (board.rules.getAuction()) {
                    //declaring class of vectors for players to iterate through
                    std::vector<PlayerClass> playerVector;
                    unsigned long highestBid = 0;
                    int playerBid;
                    unsigned long i = 0;
                    unsigned long playerHighestBid;
                    unsigned long zeroCounter = 0;

                    //initializing playerVector with players

                    for (unsigned long x = 0; x < board.getNumPlayers(); x++) {
                        if (board.player.at(x).getIsInGame())
                            playerVector.push_back(board.player.at(x));
                    }

                    std::cout << "Starting the auction for "
                              << board.boardSpaces.at(playerPositionOnBoard)->getName()
                              << std::endl;

                    while (i < playerVector.size()) {
                        if (!playerVector.empty()) {
                            //if first player
                            if (highestBid == 0) {
                                std::cout << "No one has bid on " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                                          << "[$" << board.boardSpaces.at(playerPositionOnBoard)->getCost() << "] " << "yet" << std::endl;
                                std::cout << playerVector.at(i).getRealName()
                                          << ", enter a bid of at least $" << highestBid + 1 << " to "
                                          << std::endl
                                          << "bid on the property or a value less than that to leave the auction"
                                          << std::endl << "Your bid: ";
                                std::cin >> playerBid;
                                playerVector.at(i).setBid(playerBid);

                                if (playerBid == 0)
                                    zeroCounter++;

                                if (playerVector.at(i).getBid() > static_cast<int> (highestBid)) {
                                    highestBid = playerVector.at(i).getBid();
                                    playerHighestBid = playerVector.at(i).getNumberName();
                                }
                                if (playerBid == 0 || playerBid < static_cast<int>(highestBid)) {
                                    playerVector.erase(playerVector.begin() + (i));
                                    if (playerVector.empty()) {
                                        std::cout << "No one decided to purchase "
                                                  << board.boardSpaces.at(playerPositionOnBoard)->getName()
                                                  << std::endl;
                                        break;
                                    } else {
                                        //playerVector.at(i).setInAuction(false);
                                        i--;
                                    }
                                }
                                i++;
                            } else {
                                std::cout << "The current bid for " << board.boardSpaces.at(playerPositionOnBoard)->getName()
                                          << " [$ " << board.boardSpaces.at(playerPositionOnBoard)->getCost() << "] "
                                          << "is $" << highestBid
                                          << " by " << board.player.at(playerHighestBid).getRealName() << std::endl;
                                std::cout << playerVector.at(i).getRealName()
                                          << ", enter a bid of at least $" << highestBid + 1 << " to " << std::endl
                                          << "bid on the property or a value less than that to leave the auction" << std::endl;

                                std::cout << "Your bid: ";
                                std::cin >> playerBid;
                                playerVector.at(i).setBid(playerBid);

                                //if (playerBid == 0)
                                //zeroCounter++;

                                if (playerVector.at(i).getBid() > static_cast<int> (highestBid)) {
                                    highestBid = playerVector.at(i).getBid();
                                    playerHighestBid = playerVector.at(i).getNumberName();
                                }
                                if (playerBid == 0 || playerBid < static_cast<int>(highestBid)) {
                                    playerVector.erase(playerVector.begin() + (i));
                                    //playerVector.at(i).setInAuction(false);
                                    i--;
                                }
                                i++;
                                if (i == playerVector.size()) {
                                    i = 0;
                                }

                            }

                            if (playerVector.size() == 1) {
                                //giving player with highest bid that property
                                //giving player ownership

                                //zeroCounter
                                //FIXME
                                if (zeroCounter >= playerVector.size()) {
                                    //do nothing
                                } else {
                                    board.boardSpaces.at(playerPositionOnBoard)->setTakenByPlayer(
                                            static_cast<unsigned long> (playerHighestBid));
                                    board.boardSpaces.at(playerPositionOnBoard)->setTaken(
                                            true);
                                    //paying for property
                                    board.player.at(playerHighestBid).setMoney(
                                            board.player.at(playerHighestBid).getMoney() - highestBid);

                                    std::cout << board.player.at(playerHighestBid).getRealName() << " won "
                                              << board.boardSpaces.at(playerPositionOnBoard)->getName()
                                              << " for $" << highestBid << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame()) {
                    board.displayBoard(board);
                }
            }
        }  // else if playerPosition == 0, multiply money by GOSalary Multipler (has been done in the GO-Repetition Mechanics)
    }
}

void Monopoly::GamestateClass::GoToJail (BoardClass &board, unsigned long chosenPlayer,
                                         unsigned long numTurnsInJail, unsigned long playerPositionOnBoard,
                                         unsigned long JailSpace) {

    board.player.at(chosenPlayer).setNumTurnsInJail(numTurnsInJail);
    board.player.at(chosenPlayer).setIsInJail(true);
    board.player.at(chosenPlayer).setPosition(JailSpace);
    playerPositionOnBoard = board.player.at(chosenPlayer).getPositionOnBoard();

    board.player.at(chosenPlayer).setPosition(JailSpace);
    std::cout << board.player.at(chosenPlayer).getRealName() << ", you were sent to "
              << board.boardSpaces[playerPositionOnBoard]->getName() << " for "
              << board.player.at(chosenPlayer).getNumTurnsInJail() << " turns" << std::endl;
}

void Monopoly::GamestateClass::FreeParking (BoardClass &board,
                                            unsigned long chosenPlayer,
                                            unsigned long playerPositionOnBoard) {

    unsigned long playerMoney = board.player.at(chosenPlayer).getMoney();

    board.player.at(chosenPlayer).setMoney(
            board.player.at(chosenPlayer).getMoney()
            + board.boardSpaces.at(playerPositionOnBoard)->getParkingMoney());

    if (board.boardSpaces.at(board.getParkingPosition())->getParkingMoney() > 0) {

        playerMoney += board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
        board.player.at(chosenPlayer).setMoney(playerMoney);

        std::cout << board.player.at(chosenPlayer).getRealName()
                  << " got $" << board.boardSpaces.at(board.getParkingPosition())->getParkingMoney()
                  << " for landing on " << board.boardSpaces.at(playerPositionOnBoard)->getName() << std::endl;

        board.boardSpaces.at(board.getParkingPosition())->setParkingMoney(0);
    }
}

void Monopoly::GamestateClass::PayToBankMechanics (BoardClass &board,
                                                   unsigned long chosenPlayer,
                                                   unsigned long playerMoney, unsigned long playerPositionOnBoard) {

    // Bank format from file to read - // ○ Type, Name, Amount to be Paid to Bank // Type - Pay

    unsigned long moneyToPayBank = board.boardSpaces[playerPositionOnBoard]->getAmtMoneyToPayBank();
    bool freeParkingIsEnabled = board.rules.getFreeParkingOption();
    bool bankrupctyHasBeenDeclared;

    if (playerMoney >= moneyToPayBank) {
        if (freeParkingIsEnabled) {
            // put this money in free parking instead
            playerMoney -= moneyToPayBank;
            board.player.at(chosenPlayer).setMoney(playerMoney);

            unsigned long moneyToPutInParking = board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
            moneyToPutInParking += moneyToPayBank;
            board.boardSpaces[board.getParkingPosition()]->setParkingMoney(moneyToPayBank);

            std::cout << board.player.at(chosenPlayer).getRealName()
                      << " paid the bank $" << moneyToPayBank
                      << " for landing on " << board.boardSpaces[playerPositionOnBoard]->getName() << std::endl;


        } else {  // if free parking is not on
            playerMoney -= moneyToPayBank;
            board.player.at(chosenPlayer).setMoney(playerMoney);

            std::cout << board.player.at(chosenPlayer).getRealName()
                      << " paid the bank $" << moneyToPayBank
                      << " for landing on " << board.boardSpaces[playerPositionOnBoard]->getName() << std::endl;
        }
    } else {  // Bankruptcy

        bankrupctyHasBeenDeclared = SellingUpgradesToPayBank(board, chosenPlayer, moneyToPayBank);

        if (bankrupctyHasBeenDeclared) {
            // Assign chosenPlayer's properties to BANK (101)
            for (unsigned long j = 0; j < board.getInTotalSpaces(); j++) {
                if (board.boardSpaces.at(j)->getTakenByPlayer() ==
                    board.player.at(chosenPlayer).getNumberName()) {
                    board.boardSpaces.at(j)->setTakenByPlayer(101);
                }
            }

            // Update player properties
            board.player.at(chosenPlayer).setMoney(0);
            board.player.at(chosenPlayer).setNetWorth(0);
            board.player.at(chosenPlayer).setIsInGame(false);
            board.player.at(chosenPlayer).setNumberName(101);
            board.player.at(chosenPlayer).setPosition(0);
            unsigned long reducePlayerByOne = board.getnumPlayersStillInGame() - 1;
            board.setnumPlayersStillInGame(reducePlayerByOne);

            // Print final lines

            std::cout << board.player.at(chosenPlayer).getRealName()
                      << " went bankrupt by landing on " << board.boardSpaces[playerPositionOnBoard]->getName() << std::endl;
        }
    }
}

bool Monopoly::GamestateClass:: JailMechanics(BoardClass &board,
                                              unsigned long JailPosition,
                                              unsigned long playerMoney, unsigned long chosenPlayer,
                                              Monopoly::DiceRollClass *diceRoll, FILE* RANDOM_FILENAME) {

    if (board.player.at(chosenPlayer).getNumTurnsInJail() == 0) {
        return false;
    }

    char choice;
    int numChoice;
    bool turnHasNotEnded = true;
    int num1, num2;
    unsigned long numTurnsPlayerInJail = board.player.at(chosenPlayer).getNumTurnsInJail();
    bool freeParkingIsEnabled = board.rules.getFreeParkingOption();

    std::cout << board.player.at(chosenPlayer).getRealName() << " you are in jail for "
              << board.player.at(chosenPlayer).getNumTurnsInJail() << " turns." << std::endl;

    if (playerMoney >= board.boardSpaces[JailPosition]->getMoney2EscapeJail()) {
        std::cout << "Would you like to pay $" << board.boardSpaces[JailPosition]->getMoney2EscapeJail()
                  << " to leave jail early?" << std::endl;

        std::cout << "y for yes and n for no: ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            board.player.at(chosenPlayer).setIsInJail(false);
            board.player.at(chosenPlayer).setNumTurnsInJail(0);
            playerMoney -= board.boardSpaces[JailPosition]->getMoney2EscapeJail();
            board.player.at(chosenPlayer).setMoney(playerMoney);
            board.player.at(chosenPlayer).setReleasedFromJail(0);

            if (freeParkingIsEnabled) {
                // put this money in free parking instead
                unsigned long moneyInParking = board.boardSpaces.at(board.getParkingPosition())->getParkingMoney();
                moneyInParking += board.boardSpaces[board.getJailPosition()]->getMoney2EscapeJail();
                board.boardSpaces[board.getParkingPosition()]->setParkingMoney(moneyInParking);
            }

            return false;
        } else if (choice == 'n' || choice == 'N') {

            int diceRollValue;
            unsigned long counter = 0;

            while (turnHasNotEnded) {
                while (counter != board.rules.getRerollsAllowed() + 1) {

                    std::cout << board.player.at(chosenPlayer).getRealName() << " please enter your move" << std::endl;
                    std::cout << "1 to roll dice" << std::endl;
                    std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
                    std::cout << "3 to sell a house or hotel" << std::endl;
                    std::cout << "4 to leave the game" << std::endl;

                    std::cout << "Your move: ";
                    std::cin >> numChoice;

                    if (numChoice == 1) {
                        if (counter > 0) {
                            if (num1 != num2) {
                                diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                            }
                            std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                      << diceRollValue << std::endl;
                        } else {
                            diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                            std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                      << diceRollValue << std::endl;
                        }
                        std::cout << "You are still stuck in jail" << std::endl;
                        numTurnsPlayerInJail--;
                        if (numTurnsPlayerInJail == 0) {
                            board.player.at(chosenPlayer).setreleasedAfterServing(true);
                        }

                        board.player.at(chosenPlayer).setNumTurnsInJail(numTurnsPlayerInJail);
                        board.displayBoard(board);

                        return true;
                    } else if (numChoice == 2) {
                        BuyingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                        turnHasNotEnded = true;
                    } else if (numChoice == 3) {
                        SellingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                        turnHasNotEnded = true;
                    } else if (numChoice == 4) {
                        LeavingGame(board, chosenPlayer);
                        return true;
                    } else {
                        std::cout << "Incorrect Choice. Ending Program." << std::endl;
                        turnHasNotEnded = true;
                        exit(0);
                    }
                }
                if ((num1) == (num2)) {
                    if (counter != board.rules.getRerollsAllowed()) {
                        fscanf(RANDOM_FILENAME, "%d\n%d\n", &num1, &num2);
                        diceRollValue = (num1 % 6) + (num2 % 6) + 2;
                        counter++;
                    } else {
                        counter++;
                    }
                } else {
                    break;
                }

                if (counter == board.rules.getRerollsAllowed() + 1
                    && turnHasNotEnded) {
                    counter++;
                }
            }
        } else {
            std::cout << "Invalid choice to leave jail. Ending Program." << std::endl;
            exit(0);
        }
    } else {  // if player  does not have enough moni to escape jail
        int diceRollValue; //= (*diceRoll).getDiceRoll(RANDOM_FILENAME, &(*board), &num1, &num2);
        unsigned long counter = 0;

        while (turnHasNotEnded) {
            while (counter != board.rules.getRerollsAllowed() + 1) {

                std::cout << board.player.at(chosenPlayer).getRealName() << " please enter your move" << std::endl;
                std::cout << "1 to roll dice" << std::endl;
                std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
                std::cout << "3 to sell a house or hotel" << std::endl;
                std::cout << "4 to leave the game" << std::endl;

                std::cout << "Your move: ";
                std::cin >> numChoice;

                if (numChoice == 1) {
                    if (counter > 0) {
                        if (num1 != num2) {
                            diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                        }
                        std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                  << diceRollValue << std::endl;
                    } else {
                        diceRollValue = (*diceRoll).getDiceRoll(RANDOM_FILENAME, board, &num1, &num2);
                        std::cout << board.player.at(chosenPlayer).getRealName() << ", you rolled a "
                                  << diceRollValue << std::endl;
                    }
                    std::cout << "You are still stuck in jail" << std::endl;
                    numTurnsPlayerInJail--;
                    if (numTurnsPlayerInJail == 0) {
                        board.player.at(chosenPlayer).setreleasedAfterServing(true);
                    }
                    board.displayBoard(board);
                    board.player.at(chosenPlayer).setNumTurnsInJail(numTurnsPlayerInJail);

                    return true;
                } else if (numChoice == 2) {
                    BuyingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                    turnHasNotEnded = true;
                } else if (numChoice == 3) {
                    SellingUpgradeMechanics(board, &(*diceRoll), chosenPlayer, RANDOM_FILENAME);
                    turnHasNotEnded = true;
                } else if (numChoice == 4) {
                    LeavingGame(board, chosenPlayer);
                    //turnHasNotEnded = false;
                    return true;
                } else {
                    std::cout << "Incorrect Choice. Ending Program." << std::endl;
                    exit(0);
                }
            }
            if ((num1) == (num2)) {
                if (counter != board.rules.getRerollsAllowed()) {
                    fscanf(RANDOM_FILENAME, "%d\n%d\n", &num1, &num2);
                    diceRollValue = (num1 % 6) + (num2 % 6) + 2;
                    counter++;
                } else {
                    counter++;
                }
            } else {
                break;
            }

            if (counter == board.rules.getRerollsAllowed() + 1
                && turnHasNotEnded) {
                counter++;
            }
        }

        return true;
    }
    return true;
}

void Monopoly::PropertySpaceClass::callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                                 unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                                 unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace) {

    Gamestate.MovementMechanics(Gamestate, board, diceRoll, chosenPlayer, RANDOM_FILENAME, diceRollValue);
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame() - 1
        || board.getnumPlayersStillInGame() == 1) {
        return;
    }
    board.displayBoard(board);
}

void Monopoly::GoSpaceClass::callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace) {

    Gamestate.MovementMechanics(Gamestate, board, diceRoll, chosenPlayer, RANDOM_FILENAME, diceRollValue);
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame() - 1) {
        return;
    }
    board.displayBoard(board);

}

void Monopoly::GoToJail::callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                       unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                       unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace) {

    Gamestate.GoToJail(board, chosenPlayer, numTurnsInJail, playerPositionOnBoard, JailSpace);
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame() - 1) {
        return;
    }
    board.displayBoard(board);

}

void Monopoly::FreeParkingSpace::callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                               unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                               unsigned long playerPositionOnBoard, unsigned long numTurnsInJail,
                                               unsigned long JailSpace) {

    Gamestate.FreeParking(board, chosenPlayer, playerPositionOnBoard);
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame() - 1) {
        return;
    }
    board.displayBoard(board);

}

void Monopoly::PayToBankSpaceClass::callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                                  unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                                  unsigned long playerPositionOnBoard, unsigned long numTurnsInJail,
                                                  unsigned long JailSpace) {

    unsigned long playerMoney = board.player.at(chosenPlayer).getMoney();
    Gamestate.PayToBankMechanics(board, chosenPlayer, playerMoney, playerPositionOnBoard);
    if (board.getCurrTurnNumber() == board.rules.getTurnLimit2endGame() - 1) {
        return;
    }
    board.displayBoard(board);
}