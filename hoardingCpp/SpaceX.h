//
// Created by Rishabh 2 on 2/28/18.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Player.h"
#include "readRules.h"

#ifndef HOARDINGCPP_SPACEX_H
#define HOARDINGCPP_SPACEX_H

namespace Monopoly {

    class BoardClass;
    class DiceRollClass;

    class DiceRollClass {
    public:
        int getDiceRoll (FILE* RANDOM_FILENAME, Monopoly::BoardClass &board, int *num1, int *num2);

    private:
        int diceRoll;
    };

    class GamestateClass {
    public:
        // General
        int PlayerMovement      (GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll, unsigned long chosenPlayer, FILE* RANDOM_FILENAME);
        void MovementMechanics(GamestateClass &Gamestate,Monopoly::BoardClass &board, Monopoly::DiceRollClass *diceRoll,
                               unsigned long chosenPlayer, FILE* RANDOM_FILENAME, int diceRollValue);
        // Game End
        void LeavingGame        (BoardClass &board, unsigned long chosenPlayer);
        bool GameOver           (BoardClass *board);
        void WinnerDeclaration  (BoardClass &board, unsigned long totalnumPlayersInGame);

        // Houses+Hotel Mechanics
        void BuyingUpgradeMechanics   (BoardClass &board, DiceRollClass *diceRoll, unsigned long chosenPlayer, FILE* RANDOM_FILENAME);
        void SellingUpgradeMechanics  (BoardClass &board, DiceRollClass *diceRoll, unsigned long chosenPlayer, FILE* RANDOM_FILENAME);
        bool SellingUpgradesForRent  (Monopoly::BoardClass &board, unsigned long chosenPlayer, unsigned long PositionRent);
        bool SellingUpgradesToPayBank  (Monopoly::BoardClass &board, unsigned long chosenPlayer, unsigned long PositionRent);
        void GoToJail (BoardClass &board, unsigned long chosenPlayer,
                       unsigned long numTurnsInJail, unsigned long playerPositionOnBoard,
                       unsigned long JailSpace);
        // Final
        void FreeParking (BoardClass &board, unsigned long chosenPlayer, unsigned long playerPositionOnBoard);
        void PayToBankMechanics (BoardClass &board, unsigned long chosenPlayer, unsigned long playerMoney, unsigned long playerPositionOnBoard);
        bool JailMechanics(BoardClass &board, unsigned long positionOfJail,
                           unsigned long playerMoney, unsigned long chosenPlayer,
                           Monopoly::DiceRollClass *diceRoll, FILE* RANDOM_FILENAME);
    };

    class SpaceClass {
    public:

        void display(unsigned long index, BoardClass &board);
        void setType (std::string TypeSetter);
        std::string getType() const;
        void setName (std::string SpaceNameSetter);
        std::string getName() const;

        // Property Space
        virtual void setSetID(unsigned long setIDSetter) {}
        virtual void setIntraSetID(unsigned long IntraSetIDSetter) {}
        virtual void setCost(unsigned long costSetter);
        virtual void setHouseCost(unsigned long houseCostSetter) {}
        virtual void setHotelCost(unsigned long hotelCostSetter) {}
        virtual void setRent(unsigned long rentSetter) {}
        virtual void setrentWithHouse(unsigned long rentWithHouseSetter) {}
        virtual void setrentWithHotel(unsigned long rentWithHotelSetter) {}
        virtual void setPropName(std::string nameSetter) {}
        virtual void setTakenByPlayer(unsigned long TakenByPlayerSetter) {}
        virtual void setTaken(bool TakenSetter) {}
        virtual void setNumber(unsigned long numberSetter) {}
        virtual void sethouseUpgrades(unsigned long sethouseUpgradesSetter) {}
        virtual void sethotelUpgrades(unsigned long sethotelUpgradesSetter) {}
        virtual void setNumberOfHousesBeforeHotels(unsigned long NumberOfHousesBeforeHotelsSetter) {}
        virtual unsigned long getSetID() const { return 101; }
        virtual unsigned long getIntraSetID() const{ return 101; }
        virtual unsigned long getCost() const{ return 101; }
        virtual unsigned long getRent() const{ return 101; }
        virtual unsigned long getHouseCost() const{ return 101; }
        virtual unsigned long getHotelCost() const{ return 101; }
        virtual unsigned long getRentWithHotel() const{ return 101; }
        virtual unsigned long getRentWithHouse() const{ return 101; }
        virtual unsigned long getNumber() const{ return 101; }
        virtual unsigned long getTakenByPlayer() const{ return 101; }
        virtual std::string getPropName() const { return "error"; }
        virtual bool getTaken() const{ return false; }
        virtual unsigned long gethotelUpgrades() const{ return 101; }
        virtual unsigned long gethouseUpgrades() const{ return 101; }
        virtual unsigned long getNumberOfHousesBeforeHotels() const{ return 101; }

        // GO space
        virtual void setGOMoney(unsigned long money) {}
        virtual unsigned long getGOMoney() const { return 0;}
        //const std::string &getGoName() const;

        // Jail Space
        virtual void setMoney2EscapeJail(unsigned long money2EscapeSetter) {}
        virtual void setNumTurnsInJail (unsigned long numTurnsInJailSetter) {}
        virtual unsigned long getMoney2EscapeJail() const {return 101;}
        virtual unsigned long getNumTurnsInJail() const {return 101;}

        // Free Parking
        virtual void setParkingMoney(unsigned long moneySetter) {}
        virtual unsigned long getParkingMoney() const {return 0;}

        // Go To Jail
        virtual void setInJail (bool inJailSetter) {}
        virtual bool getInJail () const{return 0;}
        virtual void setJailSpace (unsigned long setter) {}
        virtual unsigned long getJailSpace () const {return 0;}

        // Pay To Bank Space
        virtual void setAmtMoneyToPayBank(unsigned long AmtMoneyToPayBankSetter) {}
        virtual unsigned long getAmtMoneyToPayBank() const {return 101;}

        // Class Activator
        virtual void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                                   unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                                   unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace) {}

    protected:
        std::string nameOfSpace;
    private:
        bool isPurchaseable;
        std::string typeName;
    };


    class PropertySpaceClass: public SpaceClass{
    public:

        // Setters
        void setSetID(unsigned long setIDSetter);
        void setIntraSetID(unsigned long IntraSetIDSetter);
        void setCost(unsigned long costSetter);
        void setHouseCost(unsigned long houseCostSetter);
        void setHotelCost(unsigned long hotelCostSetter);
        void setRent(unsigned long rentSetter);
        void setrentWithHouse(unsigned long rentWithHouseSetter);
        void setrentWithHotel(unsigned long rentWithHotelSetter);
        void setPropName(std::string nameSetter);
        void setTakenByPlayer(unsigned long TakenByPlayerSetter);
        void setTaken(bool TakenSetter);
        void setNumber(unsigned long numberSetter);

        // Upgrades
        void sethouseUpgrades(unsigned long sethouseUpgradesSetter);
        void sethotelUpgrades(unsigned long sethotelUpgradesSetter);
        void setNumberOfHousesBeforeHotels(unsigned long NumberOfHousesBeforeHotelsSetter);
        // Getters
        unsigned long getSetID() const;
        unsigned long getIntraSetID() const;
        unsigned long getCost() const;
        unsigned long getRent() const;
        unsigned long getHouseCost() const;
        unsigned long getHotelCost() const;
        unsigned long getRentWithHotel() const;
        unsigned long getRentWithHouse() const;
        unsigned long getNumber() const;
        unsigned long getTakenByPlayer() const;
        std::string getPropName() const;
        bool getTaken() const;

        // Upgrades
        unsigned long gethotelUpgrades() const;
        unsigned long gethouseUpgrades() const;
        unsigned long getNumberOfHousesBeforeHotels() const;

        // Other
        void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace);

    private:
        unsigned long setID;
        unsigned long IntraSetID;
        unsigned long cost;
        unsigned long houseCost;
        unsigned long hotelCost;
        unsigned long rent;
        unsigned long rentWithHotel;
        unsigned long rentWithHouse;
        unsigned long takenByPlayer;
        unsigned long houseUpgrades;
        unsigned long hotelUpgrades;
        unsigned long NumberOfHousesBeforeHotels;
        unsigned long number;
        bool taken;
        std::string name;
    };

    class GoSpaceClass: public SpaceClass {
    public:

        void setGOMoney(unsigned long moneySetter);
        unsigned long getGOMoney() const;

        void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace);

    private:
        unsigned long moneyForCrossing;
        std::string GOname;
    };

    class GoToJail: public SpaceClass {
    public:

        void setInJail (bool inJailSetter);
        bool getInJail () const;
        void setJailSpace (unsigned long setter);
        unsigned long getJailSpace () const;
        void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace);

    private:
        bool inJail;
        unsigned long JailSpace;
    };

    class FreeParkingSpace: public SpaceClass {
    public:
        void setParkingMoney(unsigned long moneySetter);
        unsigned long getParkingMoney () const;

        void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace);
    private:
        unsigned long parkingMoney;
    };

    class JailClass: public SpaceClass {
    public:

        void setMoney2EscapeJail(unsigned long money2EscapeSetter);
        void setNumTurnsInJail (unsigned long numTurnsInJailSetter);

        unsigned long getMoney2EscapeJail() const;
        unsigned long getNumTurnsInJail() const;

    private:
        unsigned long numTurnsInJail;
        unsigned long money2EscapeJail;
        bool releasedFromJail;
    };

    class PayToBankSpaceClass: public SpaceClass {

    public:

        void setAmtMoneyToPayBank(unsigned long AmtMoneyToPayBankSetter);
        unsigned long getAmtMoneyToPayBank() const;
        void callMechanics(GamestateClass &Gamestate, BoardClass &board, DiceRollClass *diceRoll,
                           unsigned long chosenPlayer, int diceRollValue, FILE *RANDOM_FILENAME,
                           unsigned long playerPositionOnBoard, unsigned long numTurnsInJail, unsigned long JailSpace);

    private:
        unsigned long amtMoneyToPayBank;
    };

    class BoardClass {
    public:

        void readBoard(char* BOARD_FILENAME);
        void readRules(char* RULES_FILENAME);
        void displayBoard(BoardClass &board);
        void PlayerInitialization(BoardClass &board);
        void setnumPlayersStillInGame (unsigned long numPlayersStillInGameSetter);
        unsigned long getnumPlayersStillInGame() const;
        void setNumPlayers(unsigned long numPlayersSetter);
        unsigned long getNumPlayers() const;
        unsigned long getCurrTurnNumber() const;
        void setCurrTurnNumber(unsigned long numberSetter);
        void setInTotalSpaces(unsigned long inTotalSetter);
        unsigned long getInTotalSpaces() const;
        void setJailPosition (unsigned long i);
        unsigned long getJailPosition();
        void setParkingPosition (unsigned long i);
        unsigned long getParkingPosition() const;
        void setPayToBankPosition (unsigned long i);
        unsigned long getPayToBankPosition() const ;

        std::vector<std::unique_ptr<SpaceClass>> boardSpaces;
        std::vector<PlayerClass>player;
        RulesClass rules;

    private:
        unsigned long numPlayersStillInGame;
        unsigned long numPlayers;
        unsigned long turnNumber;
        unsigned long inTotal; // total number of properties
        unsigned long jailPosition;
        unsigned long parkingPosition;
        unsigned long payToBankPosition;

    };

}

#endif //HOARDINGCPP_SPACEX_H
