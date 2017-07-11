/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-26
 * @brief  Implementation of a hill-climbing optimization algorithm for the 8-puzzle.
 */

#ifndef SEARCH_HILLCLIMBINGSOLVER_HPP
#define SEARCH_HILLCLIMBINGSOLVER_HPP

#include <OrderedList.hpp>
#include "Solver.hpp"
#include "Heuristic.hpp"

//! Implementation of a hill-climbing optimization algorithm for the 8-puzzle.
class HillClimbingSolver : public Solver {
 private:

  Heuristic *heuristic;
  bool steepest;

 public:

  //! Initializes a regular hill-climbing 8-puzzle solver
  //! \param h the heuristic to be minimized
  explicit HillClimbingSolver(Heuristic *h) : heuristic(h), steepest(false) {
    // not steep by default
  }

  //! Initializes a hill-climbing 8-puzzle solver
  //! \param h the heuristic to be minimized
  //! \param steepest if true, always look for the best among all child states, otherwise choose the first one that is better than the parent state.
  explicit HillClimbingSolver(Heuristic *h, bool steepest) : heuristic(h), steepest(steepest) {
  }

  ~HillClimbingSolver() {
    delete heuristic;
  }

  //! Compares two states using the available heuristic.
  //! The state that has the lowest heuristic is considered a more promising exploration candidate.
  //! \param a
  //! \param b
  //! \return 1 if h(a) < h(b), -1 if h(a) > h(b), 0 if h(a) = h(b)
  static int compare(GameState *a, GameState *b) {
    Manhattan h;

    if (h.calc(*a) < h.calc(*b)) return 1;

    if (h.calc(*a) > h.calc(*b)) return - 1;

    return 0;
  }

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    // this algorithm has no memory, so no data structure to keep expanded states
    GameState *only_one = &g0;
    const clock_t start = clock();

    while (true) {
      // check for goal
      if (*game.getGoal() == *only_one) {
        solved = true;
        return endSearch(only_one, start);
      }

      // expand children
      LinkedList<GameState *> children = visit(only_one);

      //variable to keep whether a child node has been chosen for exploration next
      bool changed = false;
      while (! children.isEmpty()) {
        GameState *child = children.remove(0);

        // compare child with parent
        if (compare(only_one, child) < 0) {
          changed = true;
          only_one = child;

          // if not steepest, stop after the first child that is better than the parent is found
          if (! steepest) break;
        }
      }

      // if no new child nodes have been found, a local maximum has been found
      if (! changed) {
        cout << "WARNING: hill climbing procedure reached a local minimum\n";
        solved = false;
        return endSearch(only_one, start);
      }
    }
  }
};

#endif
