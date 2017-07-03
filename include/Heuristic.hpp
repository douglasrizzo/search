//
// Created by dodo on 23/06/17.
//

#ifndef SEARCH_HEURISTIC_HPP
#define SEARCH_HEURISTIC_HPP

#include "Game.hpp"

class Heuristic {
public:
    virtual int calc(GameState &currentState) =0;
};

class Manhattan : public Heuristic {
public:
    int calc(GameState &currentState) {
        int distance = 0, dimension = currentState.getDimension();
        for (int i = 0; i < pow(dimension, 2); i++) {
            int *pos = currentState.find(i);
            int x = pos[0], y = pos[1];
            delete[] pos;
            int x_opt = i != 0 ? (i - 1) / dimension : 2,
                    y_opt = i != 0 ? (i - 1) % dimension : 2;

            distance += abs(x - x_opt) + abs(y - y_opt);
        }
        return distance;
    }
};

class TileDifference : public Heuristic {
public:
    int calc(GameState &currentState) {
        int distance = 0, dimension = currentState.getDimension();
        for (int i = 0; i < pow(dimension, 2); i++) {
            int *pos = currentState.find(i);
            int x = pos[0], y = pos[1];
            delete[] pos;
            int x_opt = i != 0 ? (i - 1) / dimension : 2,
                    y_opt = i != 0 ? (i - 1) % dimension : 2;

            distance += x != x_opt || y != y_opt;
        }
        return distance;
    }
};

#endif //BUSCA_HEURISTIC_HPP
