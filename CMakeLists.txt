cmake_minimum_required(VERSION 3.21)
project(MM_Bracket_Maker)

set(CMAKE_CXX_STANDARD 17)

add_executable(MM_Bracket_Maker main.cpp Matchup.h Team.h Tournament.h Bracket.h)
