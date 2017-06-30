//
// Created by dodo on 22/06/17.
//

#ifndef BUSCA_GAMESTATE_HPP
#define BUSCA_GAMESTATE_HPP

#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "GameAction.hpp"

using namespace std;

class GameState {
private:
    int **representation;
    int depth, dimension;
    GameState *parent;

    int *toIntArray(string s) {
        int spaces = 1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ' ')
                spaces++;
        }

        int *ret = new int[spaces];
        int currentInt = 0;
        string intString = "";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != ' ') {
                intString += s[i];
            }
            if (s[i] == ' ' || i == s.length() - 1) {
                ret[currentInt++] = stoi(intString);
                intString = "";
            }
        }
        return ret;
    }

public:
    GameState() {
        depth = dimension = 0;
        representation = NULL;
        parent = NULL;
    }

    explicit GameState(string s) {
        depth = 0;
        parent = NULL;
        int *conversion = toIntArray(s);

        dimension = sizeof(conversion) / sizeof(conversion[0]) + 1;

        for (int i = 0; i < dimension * dimension - 1; i++) {
            for (int j = i + 1; j < dimension * dimension; j++) {
                if (conversion[i] == conversion[j]) {
                    cout << conversion[i] << conversion[j] << i << j;
                    throw invalid_argument(s);
                }
            }
        }

        representation = new int *[dimension];

        int val = 0;
        for (int x = 0; x < dimension; x++) {
            representation[x] = new int[dimension];
            for (int y = 0; y < dimension; y++) {
                representation[x][y] = conversion[val++];
            }
        }

        delete[] conversion;
    }

    GameState(const GameState &obj) {
        dimension = obj.dimension;
        depth = obj.depth;

        representation = new int *[dimension];

        for (int x = 0; x < dimension; x++) {
            representation[x] = new int[dimension];
            for (int y = 0; y < dimension; y++) {
                representation[x][y] = obj.representation[x][y];
            }
        }

        parent = obj.parent;
    }

    GameState(GameState *previous, GameAction action) {
        dimension = previous->dimension;
        depth = previous->depth + 1;
        parent = previous;
        representation = new int *[dimension];

        for (int x = 0; x < dimension; x++) {
            representation[x] = new int[dimension];
            for (int y = 0; y < dimension; y++) {
                representation[x][y] = previous->representation[x][y];
            }
        }

        int *pos_0 = find(0);
        int x = pos_0[0], y = pos_0[1];
        delete[] pos_0;
        int tmp = 0;

        if (action != RIGHT and action != LEFT and action != UP and action != DOWN)
            throw invalid_argument("No previous action to build the new GameState.");

        if (!isValid(action)) {
            throw invalid_argument("Invalid action for current game state.");
        }

        switch (action) {
            case RIGHT:
                tmp = previous->representation[x + 1][y];
                representation[x + 1][y] = 0;
                break;
            case LEFT:
                tmp = previous->representation[x - 1][y];
                representation[x - 1][y] = 0;
                break;
            case UP:
                tmp = previous->representation[x][y - 1];
                representation[x][y - 1] = 0;
                break;
            case DOWN:
                tmp = previous->representation[x][y + 1];
                representation[x][y + 1] = 0;
                break;
        }

        representation[x][y] = tmp;
    }

    ~GameState() {
        delete[] representation;
    }

    bool isValid(GameAction action) {
        if (action != RIGHT and action != LEFT and action != UP and action != DOWN)
            return false;

        int *pos_0 = find(0);
        int x = pos_0[0], y = pos_0[1];

        delete[] pos_0;

        return !(action == RIGHT and x == dimension - 1 ||
                 action == LEFT and x == 0 ||
                 action == UP and y == 0 ||
                 action == DOWN and y == dimension - 1);
    }

    bool operator==(const GameState &other) const {
        if (dimension != other.dimension)
            return false;

        for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                if (representation[x][y] != other.representation[x][y])
                    return false;
            }
        }
        return true;
    }

    int getDimension() const {
        return dimension;
    }

    string to_string() const {
        string tmp = "";

        for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                tmp.append(std::to_string(representation[x][y])).append(" ");
            }
            tmp.append("\n");
        }
        return tmp;
    }

    string to_line_string() const {
        string tmp = "";

        for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                tmp.append(std::to_string(representation[x][y])).append(" ");
            }
        }
        return tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
    }

    int *find(int value) {
        for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                if (representation[x][y] == value)
                    return new int[2]{x, y};
            }
        }

        return NULL;
    }

    void setRepresentation(int **representation) {
        this->representation = representation;
        dimension = sizeof(representation[0]) / sizeof(representation[0][0]) + 1;
    }

    GameState *getParent() const {
        return parent;
    }

    int getDepth() const {
        return depth;
    }
};

#endif //BUSCA_GAMESTATE_HPP
