//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_BREADTHFIRSTSOLVER_HPP
#define BUSCA_BREADTHFIRSTSOLVER_HPP

#include "Solver.hpp"
#include "DynamicQueue.hpp"

class BreadthFirstSolver : public Solver {
public:
    LinkedList<GameState *> solve(Game &game, GameState &g0) {
        DynamicQueue<GameState *> expanded;

        const clock_t start = clock();
        expanded.enqueue(&g0);
        while (!expanded.isEmpty()) {
            GameState *currentGame = expanded.dequeue();

            if (*game.getGoal() == *currentGame) {
                return endSearch(currentGame, start);
            }

                LinkedList<GameState *> children = visit(currentGame);

            while (!children.isEmpty())
                expanded.enqueue(children.remove(0));
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_BREADTHFIRSTSOLVER_HPP
