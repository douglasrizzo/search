//
// Created by dodo on 22/06/17.
//

#ifndef BUSCA_GAME_HPP
#define BUSCA_GAME_HPP

#include "GameState.hpp"
#include "GameAction.hpp"

class Game {
private:
    int dimension;
    GameState *goal;
public:
    static bool isValid(GameAction action, GameState *gs) {
        int *pos_0 = gs->find(0);
        int x = pos_0[0], y = pos_0[1];
        int dimension = gs->getDimension();

        delete[] pos_0;

        return action == RIGHT and x == 0 ||
               action == LEFT and x == dimension - 1 ||
               action == UP and y == 0 ||
               action == DOWN and y == dimension - 1;
    }

    static bool isInverse(GameAction a, GameAction b) {
        return b == getInverse(a);
    }

    static GameAction getInverse(GameAction a) {
        if (a == LEFT)
            return RIGHT;
        if (a == RIGHT)
            return LEFT;
        if (a == UP)
            return DOWN;

        return UP;
    }

    ~Game() {
        delete goal;
    }

    explicit Game(int dimension) {
        goal = new GameState();

        this->dimension = dimension;
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

    void setGoal(GameState *goal) {
        this->goal = goal;
    }

    int getDimension() const {
        return dimension;
    }

    void setDimension(int dimension) {
        this->dimension = dimension;
    }
};

#endif