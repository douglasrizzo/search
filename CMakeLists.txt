cmake_minimum_required(VERSION 3.7)
project(search)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include ../data_structures/include)

set(SOURCE_FILES src/main.cpp include/Solver.hpp include/GameState.hpp include/Game.hpp include/GameAction.hpp include/Heuristic.hpp include/DepthFirstSolver.hpp include/BreadthFirstSolver.hpp include/BestFirstSolver.hpp)
add_executable(search ${SOURCE_FILES})
