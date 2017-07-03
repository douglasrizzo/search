//
// Created by dodo on 24/06/17.
//

#ifndef SEARCH_GREEDYSOLVER_HPP
#define SEARCH_GREEDYSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

class GreedySolver : public Solver {
private:
    Heuristic *heuristic;
public:
    explicit GreedySolver(Heuristic *h) {
        heuristic = h;
    }

    ~GreedySolver() {
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

        const clock_t start = clock();
        expanded.insert(&g0);
        while (!expanded.isEmpty()) {
            GameState *currentGame = expanded.remove(0);

            if (*game.getGoal() == *currentGame) {
                return endSearch(currentGame, start);
            }

            LinkedList<GameState *> children = visit(currentGame);

            while (!children.isEmpty()) {
                expanded.insert(children.remove(0));
            }
        }

        throw invalid_argument("This game is unsolvable!");
    }
};

#endif
