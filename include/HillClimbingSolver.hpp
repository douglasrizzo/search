//
// Created by dodo on 24/06/17.
//

#ifndef SEARCH_HILLCLIMBINGSOLVER_HPP
#define SEARCH_HILLCLIMBINGSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

class HillClimbingSolver : public Solver {
private:
    Heuristic *heuristic;
    bool steepest;
public:
    explicit HillClimbingSolver(Heuristic *h) {
        heuristic = h;
        steepest = false;
    }

    explicit HillClimbingSolver(Heuristic *h, bool steepest) {
        heuristic = h;
        this->steepest = steepest;
    }

    ~HillClimbingSolver() {
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
        GameState *only_one = &g0;
        const clock_t start = clock();
        while (true) {
            if (*game.getGoal() == *only_one) {
                return endSearch(only_one, start);
            }

            LinkedList<GameState *> children = visit(only_one);

            bool changed = false;
            while (!children.isEmpty()) {
                GameState *child = children.remove(0);
                if (compare(only_one, child) < 0) {
                    changed = true;
                    only_one = child;
                    if (!steepest)
                        break;
                }
            }

            if (!changed) {
                cout << "WARNING: hill climbing procedure reached a local minimum\n";
                return endSearch(only_one, start);
            }
        }
    }
};

#endif