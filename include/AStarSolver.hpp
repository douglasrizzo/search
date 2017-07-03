//
// Created by dodo on 24/06/17.
//

#ifndef SEARCH_ASTARSOLVER_HPP
#define SEARCH_ASTARSOLVER_HPP

#include "Solver.hpp"
#include "Heuristic.hpp"
#include "OrderedList.hpp"

//! 8-puzzle exploration based on the A* search algorithm
class AStarSolver : public Solver {
 private:

  Heuristic *heuristic;

 public:
//! \param h the heuristic to be used by A*
  explicit AStarSolver(Heuristic *h) {
    heuristic = h;
  }

  ~AStarSolver() {
    delete heuristic;
  }

  //! Compares two states using the available heuristic.
  //! A* takes into consideration the sum of Manhattan distances between pieces in the
  //! current state to their goal state and the number of steps taken to reach the
  //! current state. The state that has the lowest sum of both of these values is
  //! considered a more promising exploration candidate.
  //! \param a
  //! \param b
  //! \return 1 if h(a) + f(a) < h(b) + f(b), -1 if h(a) + f(a) > h(b) + f(b), 0 if h(a) + f(a) = h(b) + f(b)
  static int compare(GameState *a, GameState *b) {
    Manhattan h;

    if (h.calc(*a) + a->getDepth() < h.calc(*b) + b->getDepth()) return 1;

    if (h.calc(*a) + a->getDepth() > h.calc(*b) + b->getDepth()) return -1;

    return 0;
  }

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    //big improvement: insert states in an OrderedList based on their heuristic value
    OrderedList<GameState *> expanded = OrderedList<GameState *>(compare);

    const clock_t start = clock();
    expanded.insert(&g0);

    while (!expanded.isEmpty()) {
      // need only get the first state in the list, since they are ordered! SO FAST
      GameState *currentGame = expanded.remove(0);

      // has the goal state been found?
      if (*game.getGoal()==*currentGame) {
        return endSearch(currentGame, start);
      }

      // otherwise, expand children and insert them in the ordered
      // list in the position where they belong
      LinkedList<GameState *> children = visit(currentGame);
      while (!children.isEmpty()) {
        expanded.insert(children.remove(0));
      }
    }

    throw invalid_argument("This game is unsolvable!");
  }
};

#endif // SEARCH_BESTFIRSTSOLVER_HPP
