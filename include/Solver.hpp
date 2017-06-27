//
// Created by dodo on 22/06/17.
//

#ifndef BUSCA_SOLVER_HPP
#define BUSCA_SOLVER_HPP

#include <LinkedList.hpp>
#include "GameState.hpp"
#include "Game.hpp"

class Solver {
protected:
    LinkedList<GameState *> visited;
    int visitedNodes, maxDepth, solutionDepth;
    double secondsToSolve;
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

    bool isVisited(GameState &g) {
        for (int i = 0; i < visited.getSize(); i++) {
            GameState tmp = *visited.get(i);
            if (tmp == g) {
                return true;
            }
        }
        return false;
    }

    LinkedList<GameState *> resultSteps(GameState *currentGame) {
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

    LinkedList<GameState *> visit(GameState *current) {
        LinkedList<GameState *> retornus;
        GameAction actions[4]{UP, DOWN, LEFT, RIGHT};

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
        return retornus;
    }

    string to_string() {
        return string(
                "\t\t\t\tSeconds: ").append(std::to_string(getSecondsToSolve())).append(
                "\n\t\t Solution depth: ").append(
                std::to_string(getSolutionDepth())).append("\n\t Max depth explored: ").append(
                std::to_string(getMaxDepth())).append("\nNumber of visited nodes: ").append(
                std::to_string(getVisitedNodes())).append("\n");
    }
};

#endif //BUSCA_SOLVER_HPP