//
// Created by Rishabh 2 on 2/28/18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <memory>
#include "SpaceX.h"

void Monopoly::JailClass::setMoney2EscapeJail(unsigned long money2EscapeSetter) {
    money2EscapeJail = money2EscapeSetter;
}
void Monopoly::JailClass::setNumTurnsInJail (unsigned long numTurnsInJailSetter) {
    numTurnsInJail = numTurnsInJailSetter;
}

unsigned long Monopoly::JailClass::getMoney2EscapeJail() const {
    return money2EscapeJail;
}
unsigned long Monopoly::JailClass::getNumTurnsInJail() const {
    return numTurnsInJail;
}

void Monopoly::PayToBankSpaceClass::setAmtMoneyToPayBank( unsigned long AmtMoneyToPayBankSetter) {
    amtMoneyToPayBank = AmtMoneyToPayBankSetter;
}
unsigned long Monopoly::PayToBankSpaceClass::getAmtMoneyToPayBank() const {
    return amtMoneyToPayBank;
}


//Board
void Monopoly::BoardClass::setNumPlayers(unsigned long numPlayersSetter) {
    numPlayers = numPlayersSetter;
}
void Monopoly::BoardClass::setnumPlayersStillInGame(unsigned long numPlayersStillInGameSetter) {
    numPlayersStillInGame = numPlayersStillInGameSetter;
}
unsigned long Monopoly::BoardClass::getNumPlayers() const {
    return numPlayers;
}
unsigned long Monopoly::BoardClass::getnumPlayersStillInGame() const {
    return numPlayersStillInGame;
}
void Monopoly::BoardClass::setJailPosition (unsigned long i) {
    jailPosition = i;
}

unsigned long Monopoly::BoardClass::getJailPosition() {
    return jailPosition;
}
void Monopoly::BoardClass::setParkingPosition(unsigned long i) {
    parkingPosition = i;
}

unsigned long Monopoly::BoardClass::getParkingPosition () const {
    return parkingPosition;
}

void Monopoly::BoardClass::setPayToBankPosition (unsigned long i) {
    payToBankPosition = i;
}

unsigned long Monopoly::BoardClass::getPayToBankPosition() const  {
    return payToBankPosition;
}


// Jail
void Monopoly::BoardClass::readBoard(char *BOARD_FILENAME) {
    std::ifstream readIn(BOARD_FILENAME);

    std::string tempType;
    std::string tempName;
    unsigned long GOMoneyStorage;
    unsigned long SetIDStorage;
    unsigned long IntrasetIDStorage;
    unsigned long PropertyCostStorage;
    unsigned long PropertyHouseCostStorage;
    unsigned long PropertyHotelCostStorage;
    unsigned long PropertyRentStorage;
    unsigned long PropertyRentWithHouseStorage;
    unsigned long PropertyRentWithHotelStorage;
    unsigned long totalNumSpaces;
    unsigned long PaySpaceMoneyStorage;
    unsigned long numTurnsInJailStorage;
    unsigned long money2EscapeJailStorage;
    unsigned long positionOfJail;

    unsigned long numSpaces = 0;
    std::string line;
    std::ifstream myfile(BOARD_FILENAME);

    while (std::getline(myfile, line)) {
        numSpaces++;
    }

    char comma = ',';
    unsigned long i = 0;

    if (!readIn.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }

    readIn.ignore(256, ',');
    readIn >> totalNumSpaces;
    while (i < 4) {
        readIn.ignore(256, '\n');
        i++;
        numSpaces--;
    }

    // Read in "GO"
    getline(readIn, tempType, comma);
    // Discard "GO"
    boardSpaces.push_back(std::make_unique<GoSpaceClass>());
    boardSpaces.at(0)->setType("Go");
    tempType.clear();

    // Read in money
    readIn >> GOMoneyStorage;

    boardSpaces.at(0)->setGOMoney(GOMoneyStorage);
    readIn.ignore(256, ',');

    // Read in name
    getline(readIn, tempName, comma);
    boardSpaces[0]->setName(tempName);
    tempName.clear();
    boardSpaces[0]->setNumber(0);

    readIn.ignore(256, '\n');
    inTotal = numSpaces;
    //unsigned long j = 0;

    // Storing values for properties
    for (i = 1; i < numSpaces; i++) {

        getline(readIn, tempType, comma);
        if (tempType == "Pay") {
            getline(readIn, tempName, comma);

            boardSpaces.push_back(std::make_unique<PayToBankSpaceClass>());
            boardSpaces[i]->setNumber(i);
            boardSpaces[i]->setName(tempName);
            tempName.clear();
            readIn >> PaySpaceMoneyStorage;
            // FIXME - might need to i-- and i++;
            setPayToBankPosition(i);

            boardSpaces[i]->setAmtMoneyToPayBank(PaySpaceMoneyStorage);
            boardSpaces.at(0)->setType("Pay");
            tempType.clear();
            readIn.ignore(256, '\n');

        } else if (tempType == "FreeParking") {

            getline(readIn, tempName, comma);
            boardSpaces.push_back(std::make_unique<FreeParkingSpace>());
            boardSpaces[i]->setNumber(i);
            boardSpaces[i]->setName(tempName);
            tempName.clear();
            setParkingPosition(i);
            boardSpaces.at(0)->setType("FreeParking");
            tempType.clear();
            readIn.ignore(256, '\n');

        } else if (tempType == "Jail") {
            getline(readIn, tempName, comma);
            boardSpaces.push_back(std::make_unique<JailClass>());
            boardSpaces[i]->setNumber(i);
            jailPosition = i;
            boardSpaces[i]->setName(tempName);
            tempName.clear();
            setJailPosition(i);
            readIn >> numTurnsInJailStorage;
            boardSpaces[i]->setNumTurnsInJail(numTurnsInJailStorage);
            readIn.ignore(256, ',');
            readIn >> money2EscapeJailStorage;
            boardSpaces[i]->setMoney2EscapeJail(money2EscapeJailStorage);
            readIn.ignore(256, '\n');
            boardSpaces.at(i)->setType("Jail");
            tempType.clear();

        } else if (tempType == "GoToJail") {
            getline(readIn, tempName, comma);
            boardSpaces.push_back(std::make_unique<GoToJail>());
            boardSpaces[i]->setNumber(i);
            boardSpaces[i]->setName(tempName);
            tempName.clear();
            readIn >> positionOfJail;
            boardSpaces[i]->setJailSpace(positionOfJail);
            boardSpaces.at(i)->setType("GoToJail");
            tempType.clear();
            readIn.ignore(256, '\n');

        } else if (tempType == "Property") {
            boardSpaces.push_back(std::make_unique<PropertySpaceClass>());
            boardSpaces[i]->setNumber(i);
            boardSpaces.at(i)->setType("Property");
            tempType.clear();
            readIn >> SetIDStorage;
            boardSpaces[i]->setSetID(SetIDStorage);
            readIn.ignore(256, ',');
            readIn >> IntrasetIDStorage;
            boardSpaces[i]->setIntraSetID(IntrasetIDStorage);
            readIn.ignore(256, ',');
            getline(readIn, tempName, comma);
            boardSpaces[i]->setName(tempName);
            tempName.clear();

            readIn >> PropertyCostStorage;
            boardSpaces[i]->setCost(PropertyCostStorage);

            readIn.ignore(256, ',');

            readIn >> PropertyHouseCostStorage;
            boardSpaces[i]->setHouseCost(PropertyHouseCostStorage);

            readIn.ignore(256, ',');

            readIn >> PropertyHotelCostStorage;
            boardSpaces[i]->setHotelCost(PropertyHotelCostStorage);

            readIn.ignore(256, ',');

            readIn >> PropertyRentStorage;
            boardSpaces[i]->setRent(PropertyRentStorage);

            readIn.ignore(256, ',');

            readIn >> PropertyRentWithHouseStorage;
            boardSpaces[i]->setrentWithHouse(PropertyRentWithHouseStorage);

            readIn.ignore(256, ',');

            readIn >> PropertyRentWithHotelStorage;
            boardSpaces[i]->setrentWithHotel(PropertyRentWithHotelStorage);

            readIn.ignore(256, '\n');

            // Setting all the properties as not taken
            boardSpaces[i]->setTaken(false);
            // Setting all the properties taken by player NONE = 101
            boardSpaces[i]->setTakenByPlayer(101);
            // Setting all properties house upgrades to 0
            boardSpaces[i]->sethouseUpgrades(0);
            // Setting all properties hotel upgrades to 0
            boardSpaces[i]->sethotelUpgrades(0);
        }
    }
}

void Monopoly::BoardClass::readRules(char *RULES_FILENAME) {
    std::ifstream rulesIn(RULES_FILENAME);

    unsigned long StartingCashStorage;
    int TurnLimitStorage;
    unsigned long NumOfPlayerToEndGameStorage;
    unsigned long PropertySetMultiplierStorage;
    unsigned long NumHousesBeforeHotelsStorage;
    unsigned long SalMultiLandingOnGoStorage;
    unsigned long thisTotalRerollsAllowed;
    std::string BuildEvenlyStorage;
    std::string FreeParkingStorage;
    std::string AuctionStorage;

    if (!rulesIn.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }

    rulesIn.ignore(256, ':');

    rulesIn >> StartingCashStorage;
    rules.setStartingCash(StartingCashStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> TurnLimitStorage;
    if (TurnLimitStorage == -1) {
        TurnLimitStorage = 100000;
    }
    rules.setTurnLimit2endGame(static_cast<unsigned long>(TurnLimitStorage));

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> NumOfPlayerToEndGameStorage;
    rules.setNumOfPlayers2endGame(NumOfPlayerToEndGameStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> PropertySetMultiplierStorage;
    rules.setPropertySetMultiplier(PropertySetMultiplierStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> NumHousesBeforeHotelsStorage;
    rules.setNumberOfHouses_BeforeHotels(NumHousesBeforeHotelsStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> BuildEvenlyStorage;
    rules.setBHE(BuildEvenlyStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> FreeParkingStorage;
    rules.setFreeParkingOption(FreeParkingStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> AuctionStorage;
    rules.setAuction(AuctionStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> SalMultiLandingOnGoStorage;
    rules.setGOSalaryMultiplier(SalMultiLandingOnGoStorage);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> thisTotalRerollsAllowed;
    rules.setTotalRerollsAllowed(thisTotalRerollsAllowed);

}

void Monopoly::BoardClass::displayBoard(BoardClass &board) {
    unsigned long spaceNameWidth = 11;
    bool largestSpaceName = false;
    bool largestPlayerName = false;
    unsigned long ownerWidth = 6;
    std::vector<unsigned long> PropertyWidth(inTotal);
    std::vector<unsigned long> OwnerWidth(numPlayers);

    // Finding largest spaceName width
    for (unsigned long index = 0; index < inTotal; index++) {
        if (index == 0) {
            if (boardSpaces.at(0)->getName().length() > spaceNameWidth) {
                spaceNameWidth = boardSpaces.at(0)->getName().length();
            }
        } else {
            if (boardSpaces.at(index)->getName().length() > spaceNameWidth) {
                spaceNameWidth = boardSpaces.at(index)->getName().length();
            }
        }
    }

    // Finding largest owner width
    for (unsigned long kindex = 0; kindex < numPlayers; kindex++) {
        if (player.at(kindex).getRealName().length() > ownerWidth) {
            ownerWidth = player.at(kindex).getRealName().length();
        }
    }

    // Setting setw for OwnerWidth
    for (unsigned long pindex = 0; pindex < getNumPlayers(); pindex++) {
        if (player.at(pindex).getRealName().length() > ownerWidth) {
            OwnerWidth.at(pindex) = player.at(pindex).getRealName().length() - (ownerWidth + 2);
        } else {
            OwnerWidth.at(pindex) = (ownerWidth + 2) - player.at(pindex).getRealName().length();
        }

    }

    // Setting setw for GO Name
    if (boardSpaces.at(0)->getName().length() > spaceNameWidth) {
        PropertyWidth.at(0) = boardSpaces.at(0)->getName().length() - (spaceNameWidth + 1);
    } else {
        PropertyWidth.at(0) = (spaceNameWidth + 2) - boardSpaces.at(0)->getName().length();
    }

    // Setting setw for property name
    for (unsigned long k = 1; k < inTotal; k++) {
        if (boardSpaces.at(k)->getName().length() > spaceNameWidth) {
            PropertyWidth.at(k) = boardSpaces.at(k)->getName().length() - (spaceNameWidth + 1);
        } else {
            PropertyWidth.at(k) = (spaceNameWidth + 2) - boardSpaces.at(k)->getName().length();
        }
    }
    if (spaceNameWidth > 11) {
        largestSpaceName = true;
    }
    if (ownerWidth > 6) {
        largestPlayerName = true;
    }

    // # DISPLAY-BOARD MECHANICS

    std::cout << "Space Number " << "|" << " Space Name ";
    if (largestSpaceName) {
        for (unsigned long findex = 0; findex < (spaceNameWidth - 10); findex++) {
            std::cout << " ";
        }
    }
    std::cout << "|" << " Owner  ";
    if (largestPlayerName) {
        for (unsigned long cindex = 0; cindex < (ownerWidth - 5); cindex++) {
            std::cout << " ";
        }
    } else {
        std::cout << " ";
    }
    std::cout << "|" << " Upgrades ";
    std::cout << "|" << " Players" << std::endl;

    for (unsigned long i = 0; i < board.getInTotalSpaces(); i++)
        boardSpaces.at(1)->display(i, board);

}

void Monopoly::BoardClass::PlayerInitialization(BoardClass &board) {
    std::string playername;
    unsigned long playersPlaying;

    std::cout<<"Enter how many players will be playing: ";
    std::cin>>playersPlaying;
    board.setNumPlayers(playersPlaying);
    board.setnumPlayersStillInGame(playersPlaying);
    board.player.resize(playersPlaying);


    for (unsigned long i = 0; i < playersPlaying; i++) {
        // Setting position
        board.player.at(i).setPosition(0);
        // Setting starting cash
        board.player.at(i).setMoney(board.rules.getStartingCash());
        // Set position to 0
        board.player.at(i).setPosition(0);
        // Set player number to 1/2/3...
        board.player.at(i).setNumberName(i);
        // Set all players to be in Game
        board.player.at(i).setIsInGame(true);
        // Set all player's networth equal to 0
        board.player.at(i).setNetWorth(0);

        std::cout<<"Enter the name of player "<<(i+1)<<": ";
        std::cin>>playername;
        // Set the name of the player
        board.player.at(i).setRealName(playername);
        board.player.at(i).setReleasedFromJail(1);
    }
    if (board.rules.getTurnLimit2endGame() != 0) {
        board.displayBoard(board);
    }
}

unsigned long Monopoly::BoardClass::getCurrTurnNumber() const {
    return turnNumber;
}

void Monopoly::BoardClass::setCurrTurnNumber(unsigned long numberSetter){
    turnNumber = numberSetter;
}

// Space
void Monopoly::SpaceClass::display(unsigned long i, BoardClass &board) {
    unsigned long counter = 0;
    unsigned long spaceNameWidth = 11;
    unsigned long ownerWidth = 6;
    std::vector<unsigned long> PropertyWidth(board.getInTotalSpaces());
    std::vector<unsigned long> OwnerWidth(board.getNumPlayers());
    unsigned long inTotal = board.getInTotalSpaces();
    unsigned long numPlayers = board.getNumPlayers();

    // Finding largest spaceName width
    for (unsigned long index = 0; index < inTotal; index++) {
        if (index == 0) {
            if (board.boardSpaces.at(0)->getName().length() > spaceNameWidth) {
                spaceNameWidth = board.boardSpaces.at(0)->getName().length();
            }
        } else {
            if (board.boardSpaces.at(index)->getName().length() > spaceNameWidth) {
                spaceNameWidth = board.boardSpaces.at(index)->getName().length();
            }
        }
    }

    // Finding largest owner width
    for (unsigned long kindex = 0; kindex < numPlayers; kindex++) {
        if (board.player.at(kindex).getRealName().length() > ownerWidth) {
            ownerWidth = board.player.at(kindex).getRealName().length();
        }
    }

    // Setting setw for OwnerWidth
    for (unsigned long pindex = 0; pindex < numPlayers; pindex++) {
        if (board.player.at(pindex).getRealName().length() > ownerWidth) {
            OwnerWidth.at(pindex) = board.player.at(pindex).getRealName().length() - (ownerWidth + 2);
        } else {
            OwnerWidth.at(pindex) = (ownerWidth + 2) - board.player.at(pindex).getRealName().length();
        }

    }

    // Setting setw for GO Name
    if (board.boardSpaces.at(0)->getName().length() > spaceNameWidth) {
        PropertyWidth.at(0) = board.boardSpaces.at(0)->getName().length() - (spaceNameWidth + 1);
    } else {
        PropertyWidth.at(0) = (spaceNameWidth + 2) - board.boardSpaces.at(0)->getName().length();
    }

    // Setting setw for property name
    for (unsigned long k = 1; k < inTotal; k++) {
        if (board.boardSpaces.at(k)->getName().length() > spaceNameWidth) {
            PropertyWidth.at(k) = board.boardSpaces.at(k)->getName().length() - (spaceNameWidth + 1);
        } else {
            PropertyWidth.at(k) = (spaceNameWidth + 2) - board.boardSpaces.at(k)->getName().length();
        }
    }

    if (i == 0) {  //if space is GO
        std::cout << i  // Space number
                  << std::setw(14)
                  << "| "
                  << board.boardSpaces.at(i)->getName()  // Space Name
                  << std::setw(static_cast<int>(PropertyWidth.at(0)))
                  << "|"
                  << " None" << std::setw(static_cast<int>(ownerWidth - 2)) << "|"  // Owner
                  << "          |";  // Upgrades
        for (unsigned long j = 0; j < numPlayers; j++) {  // Players
            if (board.player.at(j).getPositionOnBoard() == i && board.player.at(j).getIsInGame()) {
                if (counter > 0) {
                    std::cout << ",";
                }
                std::cout << " [" << board.player.at(j).getRealName() << " : $"
                          << board.player.at(j).getMoney() << "]";
                counter++;
            }
        }
        std::cout << std::endl;
        counter = 0;

        // DISPLAY PROPERTY BOARD
    } else {
        std::cout << i  // Space number
                  << std::setw(14)
                  << "| "
                  << board.boardSpaces.at(i)->getName()  // Space Name
                  << std::setw(static_cast<int>(PropertyWidth.at(i)))
                  << "|";

        if (board.boardSpaces.at(i)->getTaken()) {  // Owner
            std::cout << " "
                      << board.player.at(board.boardSpaces.at(i)->getTakenByPlayer()).getRealName()
                      << std::setw(static_cast<int>(OwnerWidth.at(board.boardSpaces.at(i)->getTakenByPlayer()))) << "|";
        } else {
            std::cout << " None" << std::setw(static_cast<int>(ownerWidth - 2)) << "|";
        }
        // Upgrades
        // if hotel is present, print big H
        if (board.boardSpaces.at(i)->getType() == "Property") {

            if (board.boardSpaces.at(i)->gethotelUpgrades() > 0) {
                std::cout << " H        ";
                std::cout << "|";
                // otherwise if house > 0
            } else if (board.boardSpaces.at(i)->gethouseUpgrades() > 0) {
                std::cout << " ";
                for (unsigned long numberOfh = 0;
                     numberOfh < board.boardSpaces.at(i)->gethouseUpgrades(); numberOfh++) {
                    std::cout << "h";
                }
                std::cout << "|";
                // else if no house and no hotel upgrades are present
            } else if (board.boardSpaces.at(i)->gethouseUpgrades() == 0 &&
                       board.boardSpaces.at(i)->gethotelUpgrades() == 0) {
                std::cout << "          |";
                // Security: just in case, it fails all if-statements
            } else {
                std::cout << "          |";
            }
        } else {
            std::cout << "          |";
        }
        for (unsigned long j = 0; j < numPlayers; j++) {  // Players
            if (board.player.at(j).getPositionOnBoard() == i && board.player.at(j).getIsInGame()) {
                if (counter > 0) {
                    std::cout << ",";
                }
                std::cout << " [" << board.player.at(j).getRealName() << " : $"
                          << board.player.at(j).getMoney() << "]";
                counter++;
            }
        }
        counter = 0;
        std::cout << std::endl;
    }
}

void Monopoly::SpaceClass::setType(std::string TypeSetter) {
    typeName = TypeSetter;
}

std::string Monopoly::SpaceClass::getType() const {
    return typeName;
}

// Set the total number of spaces
void Monopoly::BoardClass::setInTotalSpaces (unsigned long inTotalSetter) {
    inTotal = inTotalSetter;
}

// Get the total number of spaces
unsigned long Monopoly::BoardClass::getInTotalSpaces() const {
    return inTotal;
};

void Monopoly::SpaceClass::setName(std::string SpaceNameSetter) {
    nameOfSpace = SpaceNameSetter;
}

std::string Monopoly::SpaceClass::getName() const {
    return nameOfSpace;
}

// Property
void Monopoly::PropertySpaceClass::setTaken(bool TakenSetter) {
    taken = TakenSetter;
}
void Monopoly::PropertySpaceClass::setSetID (unsigned long setIDSetter) {
    setID = setIDSetter;
}
void Monopoly::PropertySpaceClass::setIntraSetID(unsigned long IntraSetIDSetter) {
    IntraSetID = IntraSetIDSetter;
}
void Monopoly::SpaceClass::setCost(unsigned long costSetter) {}
void Monopoly::PropertySpaceClass::setCost (unsigned long costSetter) {
    cost = costSetter;
}
void Monopoly::PropertySpaceClass::setHouseCost (unsigned long houseCostSetter) {
    houseCost = houseCostSetter;
}
void Monopoly::PropertySpaceClass::setHotelCost (unsigned long hotelCostSetter) {
    hotelCost = hotelCostSetter;
}
void Monopoly::PropertySpaceClass::setRent (unsigned long rentSetter) {
    rent = rentSetter;
}
void Monopoly::PropertySpaceClass::setrentWithHouse(unsigned long rentWithHouseSetter) {
    rentWithHouse = rentWithHouseSetter;
}
void Monopoly::PropertySpaceClass::setrentWithHotel (unsigned long rentWithHotelSetter) {
    rentWithHotel = rentWithHotelSetter;
}
void Monopoly::PropertySpaceClass::setNumber(unsigned long numberSetter) {
    number = numberSetter;
}
void Monopoly::PropertySpaceClass::setPropName (std::string nameSetter) {
    name = nameSetter;
}
void Monopoly::PropertySpaceClass::setTakenByPlayer(unsigned long TakenByPlayerSetter) {
    takenByPlayer = TakenByPlayerSetter;
}
void Monopoly::PropertySpaceClass::sethouseUpgrades(unsigned long houseUpgradesSetter) {
    houseUpgrades = houseUpgradesSetter;
}
void Monopoly::PropertySpaceClass::sethotelUpgrades(unsigned long hotelUpgradesSetter) {
    hotelUpgrades = hotelUpgradesSetter;
}
void Monopoly::PropertySpaceClass::setNumberOfHousesBeforeHotels (unsigned long NumberOfHousesBeforeHotelsSetter) {
    NumberOfHousesBeforeHotels = NumberOfHousesBeforeHotelsSetter;
}

// Getters
unsigned long Monopoly::PropertySpaceClass::getSetID() const {
    return setID;
}
unsigned long Monopoly::PropertySpaceClass::getIntraSetID() const {
    return IntraSetID;
}

std::string Monopoly::PropertySpaceClass::getPropName() const {
    return name;
}

unsigned long Monopoly::PropertySpaceClass::getCost() const {
    return cost;
}
unsigned long Monopoly::PropertySpaceClass::getHouseCost() const {
    return houseCost;
}
unsigned long Monopoly::PropertySpaceClass::getHotelCost() const {
    return hotelCost;
}
unsigned long Monopoly::PropertySpaceClass::getRent() const {
    return rent;
}
unsigned long Monopoly::PropertySpaceClass::getRentWithHotel() const {
    return rentWithHotel;
}
unsigned long Monopoly::PropertySpaceClass::getRentWithHouse() const {
    return rentWithHouse;
}

unsigned long Monopoly::PropertySpaceClass::getNumber() const {
    return number;
}
unsigned long Monopoly::PropertySpaceClass::getTakenByPlayer() const {
    return takenByPlayer;
}

// Upgrades
unsigned long Monopoly::PropertySpaceClass::gethotelUpgrades() const {
    return hotelUpgrades;
}
unsigned long Monopoly::PropertySpaceClass::gethouseUpgrades () const {
    return houseUpgrades;
}
unsigned long Monopoly::PropertySpaceClass::getNumberOfHousesBeforeHotels() const {
    return NumberOfHousesBeforeHotels;
}
bool Monopoly::PropertySpaceClass::getTaken() const {
    return taken;
}

void Monopoly::GoSpaceClass::setGOMoney(unsigned long moneySetter){
    moneyForCrossing = moneySetter;
}

unsigned long Monopoly::GoSpaceClass::getGOMoney() const {
    return moneyForCrossing;
}

// Go to Jail
void Monopoly::GoToJail::setInJail( bool inJailSetter){
    inJail = inJailSetter;
}


bool Monopoly::GoToJail::getInJail() const{
    return inJail;
}

// Free parking
void Monopoly::FreeParkingSpace::setParkingMoney(unsigned long moneySetter) {
    parkingMoney = moneySetter;
}
unsigned long Monopoly::FreeParkingSpace::getParkingMoney () const {
    return parkingMoney;
};

//Go To Jail

void Monopoly::GoToJail::setJailSpace (unsigned long setter){
    JailSpace = setter;
}
unsigned long Monopoly::GoToJail::getJailSpace () const{
    return JailSpace;
}
