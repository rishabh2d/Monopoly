//
// Created by Rishabh 2 on 2/20/18.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include "SpaceX.h"

void Monopoly::GamestateClass::BuyingUpgradeMechanics(Monopoly::BoardClass &board, Monopoly::DiceRollClass *diceRoll,
                                                      unsigned long chosenPlayer, FILE* RANDOM_FILENAME) {


    bool upgradeActivated = false;
    bool playerCanUpgrade2Hotels = false;
    unsigned long totalProperties = board.getInTotalSpaces();
    std::vector<unsigned long> UpgradeableProperties;
    unsigned long numberOfHouseUpgradesForTheProperty;
    unsigned long numberOfHotelUpgradesForTheProperty;
    unsigned long chosenPropertyToUpgrade;
    unsigned long propertyCounter = 0;
    unsigned long numProps = 0;

    for (unsigned long indx = 1; indx < totalProperties; indx++) {
        if (board.boardSpaces.at(indx)->getSetID() > numProps) {
            numProps = board.boardSpaces.at(indx)->getSetID();
        }
    }
    numProps++;
    std::vector<unsigned long> numPropertiesInSetID(numProps);

    // Finding number of intrasets in a setID
    propertyCounter = 0;
    for (unsigned long i = 0; i < numProps; i++) {
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                propertyCounter++;
            }
        }
        numPropertiesInSetID.at(i) = propertyCounter;
        propertyCounter = 0;
    }

    // Finding the number of properties in a given SETID
    // that are taken
    std::vector<bool> propertiesInTheSetIDareTaken(numProps);
    unsigned long counter = 0;
    for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {  // While setID remains same
                if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer) {
                    counter++;
                }
                if (counter == numPropertiesInSetID.at(i)) {
                    propertiesInTheSetIDareTaken.at(i) = true;
                }
            }
        }
        counter = 0;
    }

    // Checking if player can upgrade any of his properties
    // to houses
    counter = 0;
    for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {  // While setID remains same
                if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer) {
                    counter++;
                }
                if (counter == numPropertiesInSetID.at(i)) {
                    upgradeActivated = true;
                    break;
                } else {
                    upgradeActivated = false;
                }
            }
        }
        if (upgradeActivated) {
            break;
        }
        counter = 0;
    }

    bool housesMustBeBuiltEvenly = board.rules.getBHE();
    int displayedPropertyNo = 0;

    if (upgradeActivated) {
        if (housesMustBeBuiltEvenly) {
            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (unsigned long j = 1; j < totalProperties; j++) {
                    if (board.boardSpaces.at(j)->getSetID() == i) {

                        // If the property is taken by the chosen player,
                        // and other properties in the ID are taken by chosen player,
                        // store that property into the vector
                        if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                            && propertiesInTheSetIDareTaken.at(i) == true
                            && board.boardSpaces.at(j)->gethotelUpgrades() == 0) {
                            UpgradeableProperties.push_back(j);
                        }
                    }
                }
            }

            if (UpgradeableProperties.empty()) {
                std::cout << "You don't have any properties that you can upgrade" << std::endl;
                return;
            }

            unsigned long lowest = 100;
            std::vector<unsigned long> LowestUpgradedHouses;
            std::vector<unsigned long> lowestInSetID;
            std::vector<unsigned long> lowestProperties2Display;

            unsigned long j = 0;

            // Finding the property with lowest houses
            // in each setID
            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (j = 0; j < UpgradeableProperties.size(); j++) {
                    if (board.boardSpaces.at(UpgradeableProperties.at(j))->getSetID() == i) {
                        if (board.boardSpaces.at(UpgradeableProperties.at(j))->gethouseUpgrades() <= lowest) {
                            lowest = board.boardSpaces.at(UpgradeableProperties.at(j))->gethouseUpgrades();
                        }
                    }
                }
                lowestInSetID.push_back(lowest);
                lowest = 100;
            }

            // then check through the properties
            // to see if there exist other properties with the lowest upgrades
            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (j = 0; j < UpgradeableProperties.size(); j++) {
                    if (board.boardSpaces.at(UpgradeableProperties.at(j))->getSetID() == i) {
                        if (board.boardSpaces.at(UpgradeableProperties.at(j))->gethouseUpgrades() == lowestInSetID.at(i)) {
                            lowestProperties2Display.push_back(board.boardSpaces.at(UpgradeableProperties.at(j))->getNumber());
                        }
                    }
                }
            }

            unsigned long lowestPropertyNumber;

            // show only those properties which can be upgraded
            // i.e (houses with the 'lowest' upgrades in their setID)
            std::cout << "Which property do you want to upgrade?" << std::endl;
            for (unsigned long l = 0; l < lowestProperties2Display.size(); l++) {
                lowestPropertyNumber = lowestProperties2Display.at(l);
                if (lowestPropertyNumber == 0) {
                    lowestPropertyNumber++;
                }
                std::cout << displayedPropertyNo << ". " << board.boardSpaces.at(lowestPropertyNumber)->getName();
                // If the number of houses on the property = number of houses that can be built before they are transformed to hotel,
                if (board.boardSpaces.at(lowestPropertyNumber)->gethouseUpgrades()
                    == board.rules.getNumberOfHouses_BeforeHotels()) {
                    std::cout << " [$" << board.boardSpaces.at(lowestPropertyNumber)->getHotelCost() << "]" << std::endl;
                } else {
                    std::cout << " [$" << board.boardSpaces.at(lowestPropertyNumber)->getHouseCost() << "]" << std::endl;
                }
                displayedPropertyNo++;
            }
            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToUpgrade;
            chosenPropertyToUpgrade = lowestProperties2Display.at(chosenPropertyToUpgrade);

        } else {  // if houses can be built unevenly
            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (unsigned long j = 1; j < totalProperties; j++) {
                    if (board.boardSpaces.at(j)->getSetID() == i) {
                        if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                            && propertiesInTheSetIDareTaken.at(i) == true
                            && board.boardSpaces.at(j)->gethotelUpgrades() == 0) {

                            UpgradeableProperties.push_back(j);
                        }
                    }
                }
            }

            if (UpgradeableProperties.empty()) {
                std::cout << "You don't have any properties that you can upgrade" << std::endl;
                return;
            }

            displayedPropertyNo = 0;
            // if the player owns all properties in a set id
            std::cout << "Which property do you want to upgrade?" << std::endl;
            // Printing the names of the houses which can be upgraded by player
            for (unsigned long i = 0; i < UpgradeableProperties.size(); i++) {
                std::cout << displayedPropertyNo << ". "
                          << board.boardSpaces.at(UpgradeableProperties.at(i))->getName() << " ";
                // if the property has enough houses already, then print hotel cost
                if (board.boardSpaces.at(UpgradeableProperties.at(i))->gethouseUpgrades()
                    == board.rules.getNumberOfHouses_BeforeHotels()) {
                    std::cout << "[$" << board.boardSpaces.at(UpgradeableProperties.at(i))->getHotelCost() << "]" << std::endl;
                } else {
                    // else print house cost
                    std::cout << "[$" << board.boardSpaces.at(UpgradeableProperties.at(i))->getHouseCost() << "]" << std::endl;
                }
                displayedPropertyNo++;
            }

            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToUpgrade;
            chosenPropertyToUpgrade = UpgradeableProperties.at(chosenPropertyToUpgrade);
        }

        // If the house upgrades at the chosen property
        // is equal to number of houses before hotels rule,
        // then upgrade rent to hotelRent
        if (board.boardSpaces.at(chosenPropertyToUpgrade)->gethouseUpgrades() ==
            board.rules.getNumberOfHouses_BeforeHotels()) {
            playerCanUpgrade2Hotels = true;
        }

        if (playerCanUpgrade2Hotels) {
            // If player has enough money to upgrade to hotel
            if (board.player.at(chosenPlayer).getMoney() >=
                (board.boardSpaces.at(chosenPropertyToUpgrade)->getHotelCost())) {
                // Increase hotel upgrades for the property
                numberOfHotelUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToUpgrade)->gethotelUpgrades();
                numberOfHotelUpgradesForTheProperty++;
                board.boardSpaces.at(chosenPropertyToUpgrade)->sethotelUpgrades(numberOfHotelUpgradesForTheProperty);

                // Decrease the money from player's account with the cost of building hotel
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney -= board.boardSpaces.at(chosenPropertyToUpgrade)->getHotelCost();
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            } else {
                std::cout << "Player, you don't have enough money to upgrade to hotel." << std::endl;
            }
        } else {  // If player can NOT upgrade to hotels, upgrade to house
            // if the player has enough money to upgrade that property to a house,
            if (board.player.at(chosenPlayer).getMoney() >=
                board.boardSpaces.at(chosenPropertyToUpgrade)->getHouseCost()) {
                // Increase house upgrades for the property
                numberOfHouseUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToUpgrade)->gethouseUpgrades();
                numberOfHouseUpgradesForTheProperty++;
                board.boardSpaces.at(chosenPropertyToUpgrade)->sethouseUpgrades(numberOfHouseUpgradesForTheProperty);

                // Decrease the money from player's account with the cost of building house
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney -= board.boardSpaces.at(chosenPropertyToUpgrade)->getHouseCost();
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            } else {
                // FIXME - print error message that the player does not have enough money to upgrade to house.
                std::cout << "You cannot afford to upgrade to house." << std::endl;
            }
        }
    } else {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
    }
}

void Monopoly::GamestateClass::SellingUpgradeMechanics(Monopoly::BoardClass &board, Monopoly::DiceRollClass *diceRoll,
                                                       unsigned long chosenPlayer, FILE* RANDOM_FILENAME) {


    bool DowngradeActivated = false;
    bool playerCanDowngradeHotels = false;
    unsigned long totalProperties = board.getInTotalSpaces();
    std::vector<unsigned long> DowngradeableProperties;
    unsigned long chosenPropertyToDowngrade;
    unsigned long numberOfHouseUpgradesForTheProperty;
    unsigned long numberOfHotelUpgradesForTheProperty;
    unsigned long propertyCounter = 0;
    unsigned long numProps = 0;

    for (unsigned long indx = 1; indx < totalProperties; indx++) {
        if (board.boardSpaces.at(indx)->getSetID() > numProps) {
            numProps = board.boardSpaces.at(indx)->getSetID();
        }
    }
    numProps++;
    std::vector<unsigned long> numPropertiesInSetID(numProps);

    // Finding number of intras in a setID
    propertyCounter = 0;
    for (unsigned long i = 0; i < numProps; i++) {
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                propertyCounter++;
            }
        }
        numPropertiesInSetID.at(i) = propertyCounter;
        propertyCounter = 0;
    }

    std::vector<bool> propertiesInTheSetIDareTaken(numProps);
    unsigned long counter = 0;
    for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer) {
                    counter++;
                }
                if (counter == numPropertiesInSetID.at(i)) {
                    propertiesInTheSetIDareTaken.at(i) = true;
                }
            }
        }
        counter = 0;
    }

    counter = 0;
    for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                    && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0 ) ) {
                    counter++;
                }
                if (counter == 1  // IF any of the houses have even 1 upgrade, it can be downgraded
                    && (board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0) ) {
                    DowngradeActivated = true;
                    break;
                }
                if (counter == numPropertiesInSetID.at(i)) {
                    DowngradeActivated = true;
                    break;
                } else {
                    DowngradeActivated = false;
                }
            }
        }
        if (DowngradeActivated) {
            break;
        }
        counter = 0;
    }

    if (DowngradeActivated) {
        for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
            for (unsigned long j = 1; j < totalProperties; j++) {
                if (board.boardSpaces.at(j)->getSetID() == i) {
                    // If the property is taken by the chosen player, and has upgrades on it > 0
                    // and all the properties in it's set ID are taken by chosen player
                    // the property can be downgraded
                    if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                        && propertiesInTheSetIDareTaken.at(i) == true
                        && (board.boardSpaces.at(j)->gethouseUpgrades() > 0 ||
                            board.boardSpaces.at(j)->gethotelUpgrades() > 0)) {

                        DowngradeableProperties.push_back(j);
                    }
                }
            }
        }
    }

    if (DowngradeableProperties.empty()) {
        std::cout << "You don't have any upgrades that you can sell" << std::endl;
        return;
    }

    bool housesMustBeSoldEvenly = board.rules.getBHE();

    if (DowngradeActivated) {
        if (housesMustBeSoldEvenly) {

            // in a set id of upgradeable properties,
            // run through the properties and find the property with lowest upgrades
            // then check through the properties if there exists other properties with the lowest upgrades
            // run through the lowest upgraded property-vector and display properties
            unsigned long highest = 0;
            std::vector<unsigned long> HighestUpgradedHouses;
            std::vector<unsigned long> highestInSetID;
            std::vector<unsigned long> highestProperties2Display;
            unsigned long j = 0;

            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (j = 0; j < DowngradeableProperties.size(); j++) {
                    if (board.boardSpaces.at(DowngradeableProperties.at(j))->getSetID() == i) {

                        if (board.boardSpaces.at(DowngradeableProperties.at(j))->gethouseUpgrades()
                            + board.boardSpaces.at(DowngradeableProperties.at(j))->gethotelUpgrades() >= highest) {

                            highest = board.boardSpaces.at(DowngradeableProperties.at(j))->gethouseUpgrades()
                                      + board.boardSpaces.at(DowngradeableProperties.at(j))->gethotelUpgrades();
                        }
                    }
                }
                highestInSetID.push_back(highest);
                highest = 0;
            }

            // then check through the properties if there exists
            // other properties with the lowest upgrades
            for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                for (j = 0; j < DowngradeableProperties.size(); j++) {
                    if (board.boardSpaces.at(DowngradeableProperties.at(j))->getSetID() == i) {

                        if (board.boardSpaces.at(DowngradeableProperties.at(j))->gethouseUpgrades()
                            + board.boardSpaces.at(DowngradeableProperties.at(j))->gethotelUpgrades() == highestInSetID.at(i)) {

                            highestProperties2Display.push_back(board.boardSpaces.at(DowngradeableProperties.at(j))->getNumber());
                        }
                    }
                }
            }

            int displayPropertyNo = 0;
            unsigned long highestPropertyNumber;

            // show only those properties which can be upgraded (houses with the 'lowest' upgrades in their setID)
            std::cout << "Which property do you want to downgrade?" << std::endl;
            for (unsigned long h = 0; h < highestProperties2Display.size(); h++) {
                highestPropertyNumber = highestProperties2Display.at(h);
                if (highestPropertyNumber == 0) {
                    highestPropertyNumber++;
                }
                std::cout << displayPropertyNo << ". " << board.boardSpaces.at(highestPropertyNumber)->getName();
                // If the number of houses on the property = number of houses that can be built before they are transformed to hotel,
                if (board.boardSpaces.at(highestPropertyNumber)->gethouseUpgrades()
                    == board.rules.getNumberOfHouses_BeforeHotels()) {
                    std::cout << " [$" << ((board.boardSpaces.at(DowngradeableProperties.at(h))->getHotelCost()) / 2) << "]" << std::endl;
                } else {
                    std::cout << " [$" << ((board.boardSpaces.at(DowngradeableProperties.at(h))->getHouseCost()) / 2) << "]" << std::endl;
                }
                displayPropertyNo++;
            }
            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToDowngrade;
            chosenPropertyToDowngrade = highestProperties2Display.at(chosenPropertyToDowngrade);

        } else {  // If houses can be sold unevenly

            int displayedPropertyNo = 0;
            // if the player owns all properties in a set id
            std::cout << "Which property do you want to downgrade?" << std::endl;
            // Printing the names of the houses which can be downgraded by player
            for (unsigned long i = 0; i < DowngradeableProperties.size(); i++) {
                std::cout << displayedPropertyNo << ". "
                          << board.boardSpaces.at(DowngradeableProperties.at(i))->getName()
                          << " ";

                // if the property has enough houses already, then print hotel cost
                if (board.boardSpaces.at(DowngradeableProperties.at(i))->gethouseUpgrades()
                    == board.rules.getNumberOfHouses_BeforeHotels()) {
                    std::cout << "[$" << ((board.boardSpaces.at(DowngradeableProperties.at(i))->getHotelCost()) / 2) << "]"
                              << std::endl;
                } else {
                    // else print house cost
                    std::cout << "[$" << ((board.boardSpaces.at(DowngradeableProperties.at(i))->getHouseCost()) / 2) << "]"
                              << std::endl;
                }
                displayedPropertyNo++;
            }

            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToDowngrade;
            chosenPropertyToDowngrade = DowngradeableProperties.at(chosenPropertyToDowngrade);
        }

        if (board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades() > 0) {
            playerCanDowngradeHotels = true;
        }

        if (playerCanDowngradeHotels) {
            // Decrease the number of hotel upgrades for the property
            numberOfHotelUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades();
            numberOfHotelUpgradesForTheProperty--;
            board.boardSpaces.at(chosenPropertyToDowngrade)->sethotelUpgrades(numberOfHotelUpgradesForTheProperty);

            // Increase the money from player's account with the cost of building hotel divided by 2
            unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
            chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHotelCost()) / 2);
            board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
        } else {  // If player can NOT upgrade to hotels, upgrade to house
            // Decrease house upgrades for the property
            numberOfHouseUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethouseUpgrades();
            numberOfHouseUpgradesForTheProperty--;
            board.boardSpaces.at(chosenPropertyToDowngrade)->sethouseUpgrades(numberOfHouseUpgradesForTheProperty);

            // Increase the money from player's account with the cost of building house divided by 2
            unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
            chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHouseCost()) / 2);
            board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);

        }
    } else {
        std::cout << "You don't have any upgrades that you can sell" << std::endl;
    }
}

bool Monopoly::GamestateClass::SellingUpgradesForRent(Monopoly::BoardClass &board, unsigned long chosenPlayer, unsigned long PositionRent) {

    bool DowngradeActivated = false;
    bool playerCanDowngradeHotels = false;
    unsigned long totalProperties = board.getInTotalSpaces();
    std::vector<unsigned long> DowngradeableProperties;
    unsigned long chosenPropertyToDowngrade;
    unsigned long numberOfHouseUpgradesForTheProperty;
    unsigned long numberOfHotelUpgradesForTheProperty;
    unsigned long propertyCounter = 0;
    unsigned long numProps = 0;

    // Storing the number of properties found in one ID
    // (storing number of intrasetIDs in 1 setID)
    for (unsigned long indx = 1; indx < totalProperties; indx++) {
        if (board.boardSpaces.at(indx)->getSetID() > numProps) {
            numProps = board.boardSpaces.at(indx)->getSetID();
        }
    }
    numProps++;
    std::vector<unsigned long> numPropertiesInSetID(numProps);

    // Finding number of intras in a setID
    propertyCounter = 0;
    for (unsigned long i = 0; i < numProps; i++) {
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                propertyCounter++;
            }
        }
        numPropertiesInSetID.at(i) = propertyCounter;
        propertyCounter = 0;
    }

    // This vector checks if all the properties in a setID are taken or not
    std::vector<bool> propertiesInTheSetIDareTaken(numProps);

    // Keep selling upgrades while the money is lesser than the rent
    // If all upgrades sold, return true for bankruptcy
    int countrix = 0;
    do {
        unsigned long counter = 0;
        for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
            for (unsigned long j = 1; j < totalProperties; j++) {
                if (board.boardSpaces.at(j)->getSetID() == i) {
                    if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer) {

                        counter++;
                    }
                    if (counter == numPropertiesInSetID.at(i)) {
                        propertiesInTheSetIDareTaken.at(i) = true;
                    }
                }
            }
            counter = 0;
        }

        counter = 0;
        for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
            for (unsigned long j = 1; j < totalProperties; j++) {
                if (board.boardSpaces.at(j)->getSetID() == i) {
                    if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                        && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0 ) ) {
                        counter++;
                    }
                    if (counter == 1  // IF any of the houses have even 1 upgrade, it can be downgraded
                        && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0) ) {
                        DowngradeActivated = true;
                        break;
                    }
                    if (counter == numPropertiesInSetID.at(i)) {
                        DowngradeActivated = true;
                        break;
                    } else {
                        DowngradeActivated = false;
                    }
                }
            }
            if (DowngradeActivated) {
                break;
            }
            counter = 0;
        }

        // IF the downgrade has been activated,
        // then store the properties which can be downgraded... in a vector
        if (DowngradeActivated) {
            // Storing the specific properties which the player can downgrade... in a vector
            if (DowngradeActivated) {
                for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                    for (unsigned long j = 1; j < totalProperties; j++) {
                        if (board.boardSpaces.at(j)->getSetID() == i) {
                            // If the property is taken by the chosen player, and has upgrades on it > 0
                            // and all the properties in it's set ID are taken by chosen player
                            // the property can be downgraded
                            if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                                && propertiesInTheSetIDareTaken.at(i) == true
                                && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0) ) {

                                DowngradeableProperties.push_back(j);
                            }
                        }
                    }
                }
            }

            if (DowngradeableProperties.empty()) {
                return true;
            }
            int displayedPropertyNo = 0;

            if (DowngradeActivated) {
                if (countrix == 0) {
                    std::cout << "You have " << board.player.at(chosenPlayer).getMoney()
                              << " but you owe " << PositionRent << std::endl;
                }
                countrix++;

                displayedPropertyNo = 0;
                // if the player owns all properties in a set id
                std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;

                // Printing the names of the houses which can be downgraded by player
                for (unsigned long i = 0; i < DowngradeableProperties.size(); i++) {
                    std::cout << displayedPropertyNo << ". "
                              << board.boardSpaces.at(DowngradeableProperties.at(i))->getName() << " ";
                    // if the property has enough houses already, then print hotel cost
                    if (board.boardSpaces.at(DowngradeableProperties.at(i))->gethouseUpgrades()
                        == board.rules.getNumberOfHouses_BeforeHotels()) {
                        std::cout << "[$" << board.boardSpaces.at(DowngradeableProperties.at(i))->getHotelCost() << "]" << std::endl;
                    } else {
                        // else print house cost
                        std::cout << "[$" << board.boardSpaces.at(DowngradeableProperties.at(i))->getHouseCost() << "]" << std::endl;
                    }
                    displayedPropertyNo++;
                }
            }
            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToDowngrade;

            chosenPropertyToDowngrade = DowngradeableProperties.at(chosenPropertyToDowngrade);

            if (board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades() > 0) {
                playerCanDowngradeHotels = true;
            }

            if (playerCanDowngradeHotels) {
                // Decrease the number of hotel upgrades for the property
                numberOfHotelUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades();
                numberOfHotelUpgradesForTheProperty--;
                board.boardSpaces.at(chosenPropertyToDowngrade)->sethotelUpgrades(numberOfHotelUpgradesForTheProperty);

                // Increase the money from player's account with the cost of building hotel divided by 2
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHotelCost()) / 2);
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            } else {  // If player can NOT upgrade to hotels, upgrade to house
                // Decrease house upgrades for the property
                numberOfHouseUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethouseUpgrades();
                numberOfHouseUpgradesForTheProperty--;
                board.boardSpaces.at(chosenPropertyToDowngrade)->sethouseUpgrades(numberOfHouseUpgradesForTheProperty);

                // Increase the money from player's account with the cost of building house divided by 2
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHouseCost()) / 2);
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            }
        } else {
            // If player has no properties to downgrade (downgrade activated == false), then
            // BANKRUPTCY, so return true.
            return true;
        }
    } while (board.player.at(chosenPlayer).getMoney() < PositionRent
             || !DowngradeableProperties.empty());

    // If the while loop exited because the money was more than rent
    if (board.player.at(chosenPlayer).getMoney() >= PositionRent) {
        // Return false for declared bankruptcy
        return false;
    } else if (DowngradeableProperties.empty()) {
        // If the while loop exited because all his properties are sold
        // and his money is still less than rent
        return true;
    }
    return false;
}

bool Monopoly::GamestateClass::SellingUpgradesToPayBank(Monopoly::BoardClass &board,
                                                        unsigned long chosenPlayer, unsigned long PositionRent) {

    bool DowngradeActivated = false;
    bool playerCanDowngradeHotels = false;
    unsigned long totalProperties = board.getInTotalSpaces();
    std::vector<unsigned long> DowngradeableProperties;
    unsigned long chosenPropertyToDowngrade;
    unsigned long numberOfHouseUpgradesForTheProperty;
    unsigned long numberOfHotelUpgradesForTheProperty;
    unsigned long propertyCounter = 0;
    unsigned long numProps = 0;

    for (unsigned long indx = 1; indx < totalProperties; indx++) {
        if (board.boardSpaces.at(indx)->getSetID() > numProps) {
            numProps = board.boardSpaces.at(indx)->getSetID();
        }
    }
    numProps++;
    std::vector<unsigned long> numPropertiesInSetID(numProps);

    // Finding number of intras in a setID
    propertyCounter = 0;
    for (unsigned long i = 0; i < numProps; i++) {
        for (unsigned long j = 1; j < totalProperties; j++) {
            if (board.boardSpaces.at(j)->getSetID() == i) {
                propertyCounter++;
            }
        }
        numPropertiesInSetID.at(i) = propertyCounter;
        propertyCounter = 0;
    }

    // This vector checks if all the properties in a setID are taken or not
    std::vector<bool> propertiesInTheSetIDareTaken(numProps);


    do {
        unsigned long counter = 0;
        for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
            for (unsigned long j = 1; j < totalProperties; j++) {
                if (board.boardSpaces.at(j)->getSetID() == i) {
                    if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer) {

                        counter++;
                    }
                    if (counter == numPropertiesInSetID.at(i)) {
                        propertiesInTheSetIDareTaken.at(i) = true;
                    }
                }
            }
            counter = 0;
        }

        counter = 0;
        for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
            for (unsigned long j = 1; j < totalProperties; j++) {
                if (board.boardSpaces.at(j)->getSetID() == i) {
                    if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                        && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0 ) ) {
                        counter++;
                    }
                    if (counter == 1  // IF any of the houses have even 1 upgrade, it can be downgraded
                        && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0) ) {
                        DowngradeActivated = true;
                        break;
                    }
                    if (counter == numPropertiesInSetID.at(i)) {
                        DowngradeActivated = true;
                        break;
                    } else {
                        DowngradeActivated = false;
                    }
                }
            }
            if (DowngradeActivated) {
                break;
            }
            counter = 0;
        }

        // IF the downgrade has been activated,
        // then store the properties which can be downgraded... in a vector
        if (DowngradeActivated) {
            // Storing the specific properties which the player can downgrade... in a vector
            if (DowngradeActivated) {
                for (unsigned long i = 0; i < numProps; i++) {  // number of setIDs
                    for (unsigned long j = 1; j < totalProperties; j++) {
                        if (board.boardSpaces.at(j)->getSetID() == i) {
                            // If the property is taken by the chosen player, and has upgrades on it > 0
                            // and all the properties in it's set ID are taken by chosen player
                            // the property can be downgraded
                            if (board.boardSpaces.at(j)->getTakenByPlayer() == chosenPlayer
                                && propertiesInTheSetIDareTaken.at(i) == true
                                && ( board.boardSpaces.at(j)->gethouseUpgrades() > 0 || board.boardSpaces.at(j)->gethotelUpgrades() > 0) ) {

                                DowngradeableProperties.push_back(j);
                            }
                        }
                    }
                }
            }

            if (DowngradeableProperties.empty()) {
                return true;
            }

            int displayedPropertyNo = 0;

            if (DowngradeActivated) {
                displayedPropertyNo = 0;
                // if the player owns all properties in a set id
                std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;

                // Printing the names of the houses which can be downgraded by player
                for (unsigned long i = 0; i < DowngradeableProperties.size(); i++) {
                    std::cout << displayedPropertyNo << ". "
                              << board.boardSpaces.at(DowngradeableProperties.at(i))->getName() << " ";
                    // if the property has enough houses already, then print hotel cost
                    if (board.boardSpaces.at(DowngradeableProperties.at(i))->gethouseUpgrades()
                        == board.rules.getNumberOfHouses_BeforeHotels()) {
                        std::cout << "[$" << board.boardSpaces.at(DowngradeableProperties.at(i))->getHotelCost() << "]" << std::endl;
                    } else {
                        // else print house cost
                        std::cout << "[$" << board.boardSpaces.at(DowngradeableProperties.at(i))->getHouseCost() << "]" << std::endl;
                    }
                    displayedPropertyNo++;
                }
            }
            std::cout << "Your choice: " << std::endl;
            std::cin >> chosenPropertyToDowngrade;

            chosenPropertyToDowngrade = DowngradeableProperties.at(chosenPropertyToDowngrade);

            if (board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades() > 0) {
                playerCanDowngradeHotels = true;
            }

            if (playerCanDowngradeHotels) {
                // Decrease the number of hotel upgrades for the property
                numberOfHotelUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethotelUpgrades();
                numberOfHotelUpgradesForTheProperty--;
                board.boardSpaces.at(chosenPropertyToDowngrade)->sethotelUpgrades(numberOfHotelUpgradesForTheProperty);

                // Increase the money from player's account with the cost of building hotel divided by 2
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHotelCost()) / 2);
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            } else {  // If player can NOT upgrade to hotels, upgrade to house
                // Decrease house upgrades for the property
                numberOfHouseUpgradesForTheProperty = board.boardSpaces.at(chosenPropertyToDowngrade)->gethouseUpgrades();
                numberOfHouseUpgradesForTheProperty--;
                board.boardSpaces.at(chosenPropertyToDowngrade)->sethouseUpgrades(numberOfHouseUpgradesForTheProperty);

                // Increase the money from player's account with the cost of building house divided by 2
                unsigned long chosenPlayerMoney = board.player.at(chosenPlayer).getMoney();
                chosenPlayerMoney += ((board.boardSpaces.at(chosenPropertyToDowngrade)->getHouseCost()) / 2);
                board.player.at(chosenPlayer).setMoney(chosenPlayerMoney);
            }
        } else {
            // If player has no properties to downgrade (downgrade activated == false),
            // then BANKRUPTCY, so return true.
            return true;
        }
    } while (board.player.at(chosenPlayer).getMoney() < PositionRent
             || !DowngradeableProperties.empty());

    // If the while loop exited because the money was more than rent
    if (board.player.at(chosenPlayer).getMoney() >= PositionRent) {
        return false;
    } else if (DowngradeableProperties.empty()) {
        // If the while loop exited because all his properties are sold
        // and his money is still less than rent
        return true;
    }
    return true;
}