//
// Created by dodo on 22/06/17.
//

#ifndef BUSCA_SOLVER_HPP
#define BUSCA_SOLVER_HPP

#include <LinkedList.hpp>
#include "GameState.hpp"
#include "Game.hpp"

class Solver {
    virtual LinkedList<GameState> *solve(Game, GameState)=0;
};

#endif //BUSCA_SOLVER_HPP