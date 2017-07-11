/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-7-7
 * @brief  Memoryless solver that randomly searches the state space.
 */

#ifndef SEARCH_MONTECARLOSOLVER_HPP
#define SEARCH_MONTECARLOSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

//! Memoryless solver that randomly searches the state space.
class MonteCarloSolver : public Solver {
 private:
  mt19937_64 r;

  int rnd(int max) {
    return abs((int) r() % max);
  }

 public:
  MonteCarloSolver() {
    time_t result = time(nullptr);
    r.seed((unsigned long) std::localtime(&result));
  }

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    // this algorithm has no memory, so no data structure to keep expanded states
    GameState *only_one = &g0;
    const clock_t start = clock();

    while (*game.getGoal() != *only_one) {
      LinkedList<GameState *> children = visit(only_one, false);
      only_one = children.remove(rnd(children.getSize()));

      while (! children.isEmpty()) {
        GameState *child = children.remove(0);
        delete child;
      }
    }

    solved = true;
    return endSearch(only_one, start);
  }
};

#endif
