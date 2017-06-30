//
// Created by dodo on 23/06/17.
//

#ifndef BUSCA_DEPTHFIRSTSOLVER_HPP
#define BUSCA_DEPTHFIRSTSOLVER_HPP

#include <LinkedList.hpp>
#include <DynamicStack.hpp>
#include "Solver.hpp"
#include "GameAction.hpp"
#include "Heuristic.hpp"

class DepthFirstSolver : public Solver {
private:
    int maxDepth;
public:

    DepthFirstSolver() {
        maxDepth = -1;
    }

    explicit DepthFirstSolver(int maxDepth) {
        this->maxDepth = maxDepth > -1 ? maxDepth : -1;
    }

    LinkedList<GameState *> solve(Game &game, GameState &g0) {
        DynamicStack<GameState *> expanded;

        const clock_t start = clock();
        expanded.push(&g0);
        while (!expanded.isEmpty()) {
            GameState *currentGame = expanded.pop();

            if (*game.getGoal() == *currentGame) {
                return endSearch(currentGame, start);
            }

            LinkedList<GameState *> children = visit(currentGame);

            while (!children.isEmpty()) {
                GameState *child = children.remove(0);

                if (maxDepth == -1 or child->getDepth() <= maxDepth)
                    expanded.push(child);
            }
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_DEPTHFIRSTSOLVER_HPP
