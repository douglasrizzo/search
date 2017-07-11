/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-23
 * @brief  8-puzzle exploration based on a depth-first search strategy
 */

#ifndef SEARCH_DEPTHFIRSTSOLVER_HPP
#define SEARCH_DEPTHFIRSTSOLVER_HPP

#include <LinkedList.hpp>
#include <DynamicStack.hpp>
#include "Solver.hpp"
#include "GameAction.hpp"

//! 8-puzzle exploration based on a depth-first search strategy
class DepthFirstSolver : public Solver {
 private:

  int maxDepth;

 public:

  DepthFirstSolver() : maxDepth(- 1) {
    // no limits in depth
  }

  //! \param maxDepth the maximum depth allowed for exploration
  explicit DepthFirstSolver(int maxDepth) : maxDepth(maxDepth > - 1 ? maxDepth : - 1) {
  }

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    // use a stack to organize states, states that were reached last will be the
    // first ones to be evaluated
    DynamicStack<GameState *> expanded;

    const clock_t start = clock();
    expanded.push(&g0);
    int currentMaxDepth = 0;

    while (! expanded.isEmpty()) {
      GameState *currentGame = expanded.pop();

      if (currentGame->getDepth() > currentMaxDepth) {
        currentMaxDepth = currentGame->getDepth();
      }

      // useful only for debugging
      // cout << currentGame->getDepth() << '\t' << visited.getSize() << '\t' << expanded.getSize() << endl;

      // check for goal
      if (*game.getGoal() == *currentGame) {
        solved = true;
        return endSearch(currentGame, start);
      }

      // expand children, but check the maximum allowed depth before inserting
      // them in the exploration stack
      LinkedList<GameState *> children = visit(currentGame);

      if ((maxDepth == - 1) || (currentGame->getDepth() < maxDepth)) {
        while (! children.isEmpty()) {
          expanded.push(children.remove(0));
        }
      }
    }
    throw invalid_argument("This game is unsolvable!");
  }
};

#endif // SEARCH_DEPTHFIRSTSOLVER_HPP
