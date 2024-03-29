/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-22
 * @brief  Base class for all 8-puzzle solvers.
 */

#ifndef SEARCH_SOLVER_HPP
#define SEARCH_SOLVER_HPP

#include <time.h>
#include <LinkedList.hpp>
#include <OrderedList.hpp>
#include "GameState.hpp"
#include "Game.hpp"

//!Base class for all 8-puzzle solvers.
class Solver {
 private:

  static int compare(GameState *a, GameState *b) {
    return *a < *b;
  }

 protected:

  // linked list to keep visited states
  OrderedList<GameState *> visited = OrderedList<GameState *>(compare);

  // other values to keep as statistics of the solve
  int visitedNodes, maxDepth, solutionDepth;
  float secondsToSolve;

  // used in case the solver is incomplete
  bool solved;

  //! Checks whether a node has already been visited by the solver.
  //! \param g The state to look for
  //! \return true if g has been visited, otherwise false
  bool isVisited(GameState &g) {
    return visited.contains(&g);
  }

  LinkedList<GameState *> visit(GameState *current) {
    return visit(current, true);
  }

  //! Visit a game state, adding it to the list of visited states and returning its valid child states.
  //! \param current the state to be visited
  //! \return a list of the valid child states. A valid child state is the result state of applying a valid action to the current state. Only states that have not been visited before by the solver are returned.
  LinkedList<GameState *> visit(GameState *current, bool keepVisited) {
    LinkedList<GameState *> children;
    GameAction actions[4]{RIGHT, DOWN, LEFT, UP};

    // add current state to the list of visited states
    if (keepVisited)
      visited.insert(current);

    // keep a record of the maximum depth the solver has explored
    if (current->getDepth() > maxDepth) maxDepth = current->getDepth();

    // iterate through the 4 actions
    for (int i = 0; i < 4; i ++) {
      // check if the action is valid
      if (current->isValid(actions[i])) {
        // generate a child state from the valid action
        // and add it to the return list, only if the
        // child node has not been visited by the solver before
        GameState *newState = new GameState(current, actions[i]);

        if (! isVisited(*newState)) children.insert(newState);
        else delete newState;
      }
    }

    // throws an exception in case all actions give valid states,
    // since at least one state was already visited
    if (keepVisited && (children.getSize() == 4) && (current->getDepth() > 0)) {
      throw invalid_argument("Duplicate states being visited.");
    }

    return children;
  }

  //! End the search, generating the steps from the initial state to the goal
  // state.
  //! \param currentGame the state containing the goal
  //! \param start the time the solve began, in order to calculate its time
  // span
  //! \return list containing the steps from the initial state to the goal
  // state
  LinkedList<GameState *> endSearch(GameState *currentGame, const clock_t start) {
    secondsToSolve = float(clock() - start) / CLOCKS_PER_SEC;

    LinkedList<GameState *> resultSteps;

    GameState *tmp = currentGame;
    solutionDepth = currentGame->getDepth();

    // memoryless process don't work with a list of visited nodes, they
    // increment this variable on the fly
    visitedNodes = visitedNodes != 0 ? visitedNodes : visited.getSize();

    while (tmp != NULL) {
      resultSteps.insert(tmp, resultSteps.getSize());
      tmp = tmp->getParent();
    }

    return resultSteps;
  }

 public:

  double getSecondsToSolve() const {
    return secondsToSolve;
  }

  int getVisitedNodes() const {
    return visitedNodes;
  }

  int getMaxDepth() const {
    return maxDepth;
  }

  int getSolutionDepth() const {
    return solutionDepth;
  }

  bool isSolved() {
    return solved;
  }

  Solver() {
    visited = OrderedList<GameState *>(compare);
    secondsToSolve = visitedNodes = maxDepth = solutionDepth = 0;
    solved = false;
  }

  //! Explores the game tree in search of the goal state.
  //! Exploration is done by applying one of the four valid actions of the 8-puzzle to intermediate,
  //! non-goal states until the goal state is reached.
  //! \param g A description of the game.
  //! \param gs The initial state of the game.
  //! \return list containing all states explored, from the initial state to the goal state.
  virtual LinkedList<GameState *> solve(Game &g, GameState &gs) = 0;

  //! Generates a string containing useful information from the solver run.
  //! \return string representation of the state-space exploration
  string to_string() {
    return string(
        "\t\t\t\tSeconds: ").append(std::to_string(getSecondsToSolve())).append(
        "\n\t\t Solution depth: ").append(
        std::to_string(getSolutionDepth())).append("\n\t Max depth explored: ").
        append(
        std::to_string(getMaxDepth())).append("\nNumber of visited nodes: ").append(
        std::to_string(getVisitedNodes())).append("\n");
  }
};

#endif // SEARCH_SOLVER_HPP
