//
// Created by dodo on 24/06/17.
//

#ifndef SEARCH_GREEDYSOLVER_HPP
#define SEARCH_GREEDYSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

//! Implementation of a greedy exploration algorithm for the 8-puzzle game.
class GreedySolver : public Solver {
 private:

  Heuristic *heuristic;

 public:

  //! Initializes the solver
  //! \param h the heuristic to be used by the algorithm
  explicit GreedySolver(Heuristic *h) {
    heuristic = h;
  }

  ~GreedySolver() {
    delete heuristic;
  }

  //! Compares two states using the available heuristic.
  //! The greedy search takes into consideration only the sum of Manhattan distances between pieces in the
  //! current state to their goal state. The state that has the lowest heuristic is
  //! considered a more promising exploration candidate.
  //! \param a
  //! \param b
  //! \return 1 if h(a) < h(b), -1 if h(a) > h(b), 0 if h(a) = h(b)
  static int compare(GameState *a, GameState *b) {
    Manhattan h;

    if (h.calc(*a) < h.calc(*b)) return 1;

    if (h.calc(*a) > h.calc(*b)) return -1;

    return 0;
  }

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    // like A*, keep the states in an OrderedList, sorted by their heuristic value
    OrderedList<GameState *> expanded = OrderedList<GameState *>(compare);

    const clock_t start = clock();
    expanded.insert(&g0);
    while (!expanded.isEmpty()) {
      // need only remove the first element, since they are ordered
      GameState *currentGame = expanded.remove(0);

      // check for goal
      if (*game.getGoal()==*currentGame) {
        return endSearch(currentGame, start);
      }

      // expand children
      LinkedList<GameState *> children = visit(currentGame);
      while (!children.isEmpty()) {
        expanded.insert(children.remove(0));
      }
    }

    throw invalid_argument("This game is unsolvable!");
  }
};

#endif // ifndef SEARCH_GREEDYSOLVER_HPP
