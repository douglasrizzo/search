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
public:
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

            while (!children.isEmpty())
                expanded.push(children.remove(0));
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_DEPTHFIRSTSOLVER_HPP
