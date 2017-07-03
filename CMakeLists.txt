cmake_minimum_required(VERSION 3.7)
project(search)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include data_structures/include)

set(SOURCE_FILES test/main.cpp include/Solver.hpp include/GameState.hpp include/Game.hpp include/GameAction.hpp include/Heuristic.hpp include/DepthFirstSolver.hpp include/BreadthFirstSolver.hpp include/GreedySolver.hpp include/HillClimbingSolver.hpp include/AStarSolver.hpp)
add_executable(search ${SOURCE_FILES})
