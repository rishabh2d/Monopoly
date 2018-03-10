//
// Created by Rishabh 2 on 2/4/18.
//
#include <iostream>
#include <vector>
#include "Player.h"

// Setters
void Monopoly::PlayerClass::setRealName (std::string RealNameSetter) {
    realName = RealNameSetter;
}
void Monopoly::PlayerClass::setNumberName (unsigned long numberNameSetter) {
    numberName = numberNameSetter;
}
void Monopoly::PlayerClass::setMoney (unsigned long moneySetter) {
    money = moneySetter;
}
void Monopoly::PlayerClass::setPosition (unsigned long positionSetter) {
    positionOnBoard = positionSetter;
}

void Monopoly::PlayerClass::setIsInGame(bool boolean) {
    inGame = boolean;
}

void Monopoly::PlayerClass::setNetWorth(unsigned long netWorthSetter) {
    netWorth = netWorthSetter;
}

void Monopoly::PlayerClass::setNumTurnsInJail( unsigned long turnSetter){
    numTurnsInJail = turnSetter;
}

void Monopoly::PlayerClass::setIsInJail(bool jailSetter) {
    inJail = jailSetter;
}

void Monopoly::PlayerClass::setReleasedFromJail(unsigned long i) {
    releasedFromJail = i;
}

unsigned long Monopoly::PlayerClass::getReleasedFromJail() const {
    return releasedFromJail;
}
void Monopoly::PlayerClass::setreleasedAfterServing(bool i) {
    releasedAfterServing = i;
}

bool Monopoly::PlayerClass::getreleasedAfterServing() const {
    return releasedAfterServing;
}

// Getters
std::string Monopoly::PlayerClass::getRealName () const {
    return realName;
}
unsigned long Monopoly::PlayerClass::getNumberName() const {
    return numberName;
}
unsigned long Monopoly::PlayerClass::getMoney() const {
    return money;
}
unsigned long Monopoly::PlayerClass::getPositionOnBoard() const {
    return positionOnBoard;
}
void Monopoly::PlayerClass::setBid (int bidSetter){
    bid = bidSetter;
}

unsigned long Monopoly::PlayerClass::getNetWorth() const{
    return netWorth;
}
bool Monopoly::PlayerClass::getIsInGame() const {
    return inGame;
}
int Monopoly::PlayerClass::getBid () const {
    return bid;
}

unsigned long Monopoly::PlayerClass::getNumTurnsInJail() const {
    return numTurnsInJail;
}

bool Monopoly::PlayerClass::getIsInJail () const{
    return inJail;
}