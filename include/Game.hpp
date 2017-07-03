//
// Created by dodo on 22/06/17.
//

#ifndef SEARCH_GAME_HPP
#define SEARCH_GAME_HPP

#include "GameState.hpp"
#include "GameAction.hpp"

//! Class representing the rules of a game.
//! Used to generalize the search algorithms to any dimension of the 8-puzzle game.
class Game {
 private:

  GameState *goal;

 public:

  ~Game() {
    delete goal;
  }

  //! Creates a game representation and keeps a GameState of the goal state.
  //! \param dimension dimensions of the puzzle board.
  explicit Game(int dimension) {
    goal = new GameState();
    int **representation = new int *[dimension];

    int val = 1;

    for (int x = 0; x < dimension; x++) {
      representation[x] = new int[dimension];

      for (int y = 0; y < dimension; y++) {
        representation[x][y] = val++%(dimension*dimension);
      }
    }

    goal->setRepresentation(representation);
  }

  GameState *getGoal() const {
    return goal;
  }
};

#endif // ifndef SEARCH_GAME_HPP
