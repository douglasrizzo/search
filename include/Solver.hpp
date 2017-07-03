//
// Created by dodo on 22/06/17.
//

#ifndef SEARCH_SOLVER_HPP
#define SEARCH_SOLVER_HPP

#include <time.h>
#include <LinkedList.hpp>
#include "GameState.hpp"
#include "Game.hpp"

class Solver {
protected:
    LinkedList<GameState *> visited;
    int visitedNodes, maxDepth, solutionDepth;
    float secondsToSolve;

    bool isVisited(GameState &g) {
        Iterator<GameState *> iter = visited.iterator();
        while (iter.hasNext()) {
            if (*iter.next() == g) {
                return true;
            }
        }
        return false;
    }

    LinkedList<GameState *> visit(GameState *current) {
        LinkedList<GameState *> retornus;
        GameAction actions[4]{RIGHT, DOWN, LEFT, UP};

        visited.insert(current);
        if (current->getDepth() > maxDepth)
            maxDepth = current->getDepth();

        for (int i = 0; i < 4; i++) {
            if (current->isValid(actions[i])) {
                GameState *newState = new GameState(current, actions[i]);
                if (!isVisited(*newState))
                    retornus.insert(newState);
                else
                    delete newState;
            }
        }

        if (retornus.getSize() == 4 && current->getDepth() > 0) {
            throw invalid_argument("Duplicate states being visited.");
        }

        return retornus;
    }

public:

    double getSecondsToSolve() const {
        return secondsToSolve;
    }

    int getVisitedNodes() const {
        return visitedNodes;
    }

    int getMaxDepth() const {
        return maxDepth;
    }

    int getSolutionDepth() const {
        return solutionDepth;
    }

    Solver() {
        visited = LinkedList<GameState *>();
        secondsToSolve = visitedNodes = maxDepth = solutionDepth = 0;
    }

    virtual LinkedList<GameState *> solve(Game &, GameState &)=0;

    string to_string() {
        return string(
                "\t\t\t\tSeconds: ").append(std::to_string(getSecondsToSolve())).append(
                "\n\t\t Solution depth: ").append(
                std::to_string(getSolutionDepth())).append("\n\t Max depth explored: ").append(
                std::to_string(getMaxDepth())).append("\nNumber of visited nodes: ").append(
                std::to_string(getVisitedNodes())).append("\n");
    }

    LinkedList<GameState *> endSearch(GameState *currentGame, const clock_t start) {
        secondsToSolve = float(clock() - start) / CLOCKS_PER_SEC;

        LinkedList<GameState *> resultSteps;

        GameState *tmp = currentGame;
        solutionDepth = currentGame->getDepth();
        visitedNodes = visited.getSize();

        while (tmp != NULL) {
            resultSteps.insert(tmp, resultSteps.getSize());
            tmp = tmp->getParent();
        }

        return resultSteps;
    }
};

#endif //BUSCA_SOLVER_HPP