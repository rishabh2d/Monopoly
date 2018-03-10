cmake_minimum_required(VERSION 3.8)
project(hoardingCpp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp readRules.cpp DiceRoll.cpp readRules.h Player.cpp Player.h Gamestate.cpp HousesHotel.cpp GameEnd.cpp SpaceX.cpp SpaceX.h)
add_executable(hoardingCpp ${SOURCE_FILES} readRules.cpp readRules.h Player.cpp Player.h Gamestate.cpp  HousesHotel.cpp GameEnd.cpp SpaceX.cpp SpaceX.h)