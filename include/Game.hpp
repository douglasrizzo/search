//
// Created by dodo on 22/06/17.
//

#ifndef BUSCA_GAME_HPP
#define BUSCA_GAME_HPP

#include "GameState.hpp"
#include "GameAction.hpp"

class Game {
private:
    GameState *goal;
public:
    ~Game() {
        delete goal;
    }

    explicit Game(int dimension) {
        goal = new GameState();
        int **representation = new int *[dimension];

        int val = 1;
        for (int x = 0; x < dimension; x++) {
            representation[x] = new int[dimension];
            for (int y = 0; y < dimension; y++) {
                representation[x][y] = val++ % (dimension * dimension);
            }
        }

        goal->setRepresentation(representation);
    }

    GameState *getGoal() const {
        return goal;
    }
};

#endif