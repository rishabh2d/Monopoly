//
// Created by Rishabh 2 on 2/4/18.
//
#include <iostream>
#include <vector>
#include <string>

#ifndef HOARDINGCPP_PLAYER_H
#define HOARDINGCPP_PLAYER_H

namespace Monopoly {
    class PlayerClass {
    public:

        // Setters
        void setRealName (std::string RealNameSetter);
        void setNumberName (unsigned long numberNameSetter);
        //        void setTotalPropertiesOwned (unsigned long totalPropertiesOwnedSetter);
        void setMoney (unsigned long moneySetter);
        void setPosition (unsigned long positionSetter);
        void setIsInGame(bool boolean);
        void setBid (int bidSetter);
        void setNetWorth (unsigned long netWorthSetter);
        void setNumTurnsInJail (unsigned long turnsSetter);
        void setIsInJail (bool jailSetter);
        void setReleasedFromJail (unsigned long i);
        void setreleasedAfterServing (bool i);

        // Getters
        unsigned long getPositionOnBoard() const;
        std::string getRealName () const;
        unsigned long getNumberName() const;
        unsigned long getMoney() const;
        unsigned long getNetWorth() const;
        bool getIsInGame() const;
        int getBid () const;
        unsigned long getNumTurnsInJail () const;
        bool getIsInJail () const;
        unsigned long getReleasedFromJail () const;
        bool getreleasedAfterServing () const;



    private:
        unsigned long numberName;
        unsigned long money;
        unsigned long netWorth;
        unsigned long positionOnBoard;
        std::string realName;
        bool inGame;
        int bid;
        unsigned long numTurnsInJail;
        bool inJail;
        unsigned long releasedFromJail;
        bool releasedAfterServing;


    };
}



#endif //HOARDINGCPP_PLAYER_H
