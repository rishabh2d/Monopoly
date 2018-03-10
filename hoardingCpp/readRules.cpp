//
// Created by Rishabh 2 on 2/4/18.
//
#include <iostream>
#include <vector>
#include "readRules.h"

// Setters
void Monopoly::RulesClass::setStartingCash(unsigned long startingCashSetter) {
    startingCash = startingCashSetter;
}
unsigned long Monopoly::RulesClass::getStartingCash() const {  // Getter
    return startingCash;
}
void Monopoly::RulesClass::setTurnLimit2endGame (unsigned long turnLimit2endGameSetter) {  // Setter
    turnLimit2endGame = turnLimit2endGameSetter;
}
unsigned long Monopoly::RulesClass::getTurnLimit2endGame() const {  // Getter
    return turnLimit2endGame;
}

void Monopoly::RulesClass::setNumOfPlayers2endGame (unsigned long numOfPlayers2endGameSetter) {  // Setter
    numOfPlayers2endGame = numOfPlayers2endGameSetter;
}
unsigned long Monopoly::RulesClass::getNumOfPlayers2endGame() const {  // Getter
    return numOfPlayers2endGame;
}

void Monopoly::RulesClass::setPropertySetMultiplier (unsigned long propertySetMultiplierSetter) {  // Setter
    propertySetMultiplier = propertySetMultiplierSetter;
}

// Getters
unsigned long Monopoly::RulesClass::getpropertySetMultiplier() const {  // Getter
    return propertySetMultiplier;
}
void Monopoly::RulesClass::setNumberOfHouses_BeforeHotels (unsigned long NumberOfHouses_BeforeHotelsSetter) {  // Setter
    NumberOfHouses_BeforeHotels = NumberOfHouses_BeforeHotelsSetter;
}
unsigned long Monopoly::RulesClass::getNumberOfHouses_BeforeHotels() const {
    return NumberOfHouses_BeforeHotels;
}
void Monopoly::RulesClass::setGOSalaryMultiplier (unsigned long GOSalaryMultiplierSetter) {  // Setter
    GOSalaryMultiplier = GOSalaryMultiplierSetter;
}
unsigned long Monopoly::RulesClass::getGOSalaryMultiplier() const {  // Getter
    return GOSalaryMultiplier;
}
void Monopoly::RulesClass::setTotalNumOfProperties (unsigned long totalNumOfPropertiesSetter) {
    totalNumOfProperties = totalNumOfPropertiesSetter;
}
unsigned long Monopoly::RulesClass::getTotalNumOfProperties () const {
    return totalNumOfProperties;
}

void Monopoly::RulesClass::setTotalRerollsAllowed (unsigned long RerollSetter) {
    totalRerolls = RerollSetter;
}

unsigned long Monopoly::RulesClass::getRerollsAllowed () const {
    return totalRerolls;
}

void Monopoly::RulesClass::setBHE (std::string BHEanswer) {  // Setter
    if (BHEanswer == "Yes") {
        BuildHousesEvenly = true;
    } else {
        BuildHousesEvenly = false;
    }
}

bool Monopoly::RulesClass::getBHE() const {
    return BuildHousesEvenly;
};

void Monopoly::RulesClass::setAuction (std::string auctionAnswer) {  // Setter
    if (auctionAnswer == "Yes") {
        AuctionProperty = true;
    } else{
        AuctionProperty = false;
    }
}

bool Monopoly::RulesClass::getAuction() const{
    return AuctionProperty;
}

void Monopoly::RulesClass::setFreeParkingOption (std::string setter){
    if (setter == "Yes") {
        FreeParkingOption = true;
    }
    else{
        AuctionProperty = false;
    }
}
bool Monopoly::RulesClass::getFreeParkingOption() const {
    return FreeParkingOption;
}
