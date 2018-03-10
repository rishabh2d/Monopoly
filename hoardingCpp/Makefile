hoarding.out: main.o DiceRoll.o GameEnd.o Gamestate.o HousesHotel.o Player.o readRules.o SpaceX.o
	g++ -g -Wall -Werror -std=c++14 -o hoarding.out main.o DiceRoll.o GameEnd.o Gamestate.o HousesHotel.o Player.o readRules.o SpaceX.o

main.o: main.cpp SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c main.cpp

DiceRoll.o: SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c DiceRoll.cpp

GameEnd.o: SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c GameEnd.cpp

Gamestate.o: SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c Gamestate.cpp

HousesHotel.o: SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c HousesHotel.cpp

Player.o: Player.h
	g++ -g -Wall -Werror -std=c++14 -c Player.cpp

readRules.o: readRules.h
	g++ -g -Wall -Werror -std=c++14 -c readRules.cpp

SpaceX.o: SpaceX.h
	g++ -g -Wall -Werror -std=c++14 -c SpaceX.cpp

clean:
	rm -f *.o *.out