//
// Created by Rishabh 2 on 2/4/18.
//
#include <iostream>
#include <vector>
#include <string>

#ifndef HOARDINGCPP_READRULES_H
#define HOARDINGCPP_READRULES_H

namespace Monopoly {
    class RulesClass {
    public:

        // Setters
        void setStartingCash(unsigned long startingCashSetter);
        void setTurnLimit2endGame(unsigned long turnLimit2endGameSetter);
        void setNumOfPlayers2endGame(unsigned long numOfPlayers2endGameSetter);
        void setPropertySetMultiplier(unsigned long propertySetMultiplierSetter);
        void setNumberOfHouses_BeforeHotels(unsigned long NumberOfHouses_BeforeHotelsSetter);
        void setBHE(std::string BHESetter);
        void setGOSalaryMultiplier(unsigned long GOSalaryMultiplierSetter);
        void setTotalNumOfProperties(unsigned long totalNumOfPropertiesSetter);
        void setTotalRerollsAllowed (unsigned long RerollSetter);
        void setAuction (std::string auctionAnswer);
        void setFreeParkingOption (std::string setter);

        // Getters
        unsigned long getGOSalaryMultiplier() const;
        unsigned long getTotalNumOfProperties() const;
        unsigned long getStartingCash() const;
        unsigned long getTurnLimit2endGame() const;
        unsigned long getpropertySetMultiplier() const;
        unsigned long getNumOfPlayers2endGame() const;
        unsigned long getNumberOfHouses_BeforeHotels() const;
        unsigned long getRerollsAllowed () const;
        bool getBHE () const;
        bool getAuction() const;
        bool getFreeParkingOption () const;

    private:
        // Variables in use
        unsigned long startingCash;
        unsigned long totalNumOfProperties;
        unsigned long turnLimit2endGame;
        unsigned long numOfPlayers2endGame;
        unsigned long propertySetMultiplier;
        unsigned long NumberOfHouses_BeforeHotels;
        unsigned long GOSalaryMultiplier;
        unsigned long totalRerolls;
        bool BuildHousesEvenly;
        bool AuctionProperty;
        bool FreeParkingOption;

    };
}

#endif //HOARDINGCPP_READRULES_H
