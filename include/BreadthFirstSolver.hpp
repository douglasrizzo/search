/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-23
 * @brief  8-puzzle exploration based on a breadth-first search strategy
 */

#ifndef SEARCH_BREADTHFIRSTSOLVER_HPP
#define SEARCH_BREADTHFIRSTSOLVER_HPP

#include "Solver.hpp"
#include "DynamicQueue.hpp"

//! 8-puzzle exploration based on a breadth-first search strategy
class BreadthFirstSolver : public Solver {
 public:

  LinkedList<GameState *> solve(Game &game, GameState &g0) {
    // use a queue to organize states, states that were reached first will be the first ones to be evaluated
    DynamicQueue<GameState *> expanded;

    const clock_t start = clock();
    expanded.enqueue(&g0);

    int currentDepth = 0;

    cout << "Depth\tVisited\t\tExpanded\n";
    while (! expanded.isEmpty()) {
      GameState *currentGame = expanded.dequeue();

      // check for goal
      if (*game.getGoal() == *currentGame) {
        solved = true;
        return endSearch(currentGame, start);
      }

      // if new depth, output a line to stdout
      if (currentGame->getDepth() != currentDepth) {
        currentDepth = currentGame->getDepth();
        cout << currentGame->getDepth() << "\t\t" << visited.getSize() << "\t\t\t" << expanded.getSize() << endl;
      }

      //expand children
      LinkedList<GameState *> children = visit(currentGame);
      while (! children.isEmpty()) expanded.enqueue(children.remove(0));
    }
    throw invalid_argument("This game is unsolvable!");
  }
};

#endif // SEARCH_BREADTHFIRSTSOLVER_HPP
