//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_BESTFIRSTSOLVER_HPP
#define BUSCA_BESTFIRSTSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

class BestFirstSolver : public Solver {
private:
    Heuristic *heuristic;
public:
    explicit BestFirstSolver(Heuristic *h) {
        heuristic = h;
    }

    ~BestFirstSolver() {
        delete heuristic;
    }

    static int compare(GameState *a, GameState *b) {
        Manhattan h;
        if (h.calc(*a) < h.calc(*b))
            return 1;
        if (h.calc(*a) > h.calc(*b))
            return -1;
        return 0;
    }

    LinkedList<GameState *> solve(Game &game, GameState &g0) {
        OrderedList<GameState *> expanded = OrderedList<GameState *>(compare);

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
