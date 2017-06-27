//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_ASTARSOLVER_HPP
#define BUSCA_ASTARSOLVER_HPP

#include "Solver.hpp"
#include "Heuristic.hpp"
#include "OrderedList.hpp"

class AStarSolver : public Solver {
private:
    Heuristic *heuristic;

public:
    explicit AStarSolver(Heuristic *h) {
        heuristic = h;
    }

    ~AStarSolver() {
        delete heuristic;
    }

    static int compare(GameState *a, GameState *b) {
        Manhattan h;
        if (h.calc(*a) + a->getDepth() < h.calc(*b) + b->getDepth())
            return 1;
        if (h.calc(*a) + a->getDepth() > h.calc(*b) + b->getDepth())
            return -1;
        return 0;
    }

    LinkedList<GameState *> solve(Game &game, GameState &g0) {
        OrderedList<GameState *> expanded= OrderedList<GameState*> (compare);

        const time_t start = time(NULL);
        expanded.insert(&g0);
        while (!expanded.isEmpty()) {
            GameState *currentGame = expanded.remove(0);

            if (*game.getGoal() == *currentGame) {
                secondsToSolve = difftime(time(NULL), start);
                return resultSteps(currentGame);
            }

            LinkedList<GameState *> children = visit(currentGame);

            while (!children.isEmpty()) {
                expanded.insert(children.remove(0));
            }
        }

        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_BESTFIRSTSOLVER_HPP