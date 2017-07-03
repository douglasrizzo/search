/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-22
 * @brief  Abtract class for heuristic functions.
 */

#ifndef SEARCH_HEURISTIC_HPP
#define SEARCH_HEURISTIC_HPP

#include "Game.hpp"

//!Abtract class for heuristic functions.
class Heuristic {
 public:

  //! Calculates the heuristic value for a state.
  //! \param currentState the state to be evaluated
  //! \return heuristic value for currentState
  virtual int calc(GameState &currentState) = 0;
};

//! Implementation of the Manhattan distance for the 8-puzzle
class Manhattan : public Heuristic {
 public:

  int calc(GameState &currentState) {
    int distance = 0, dimension = currentState.getDimension();

    for (int i = 0; i < pow(dimension, 2); i++) {
      int *pos = currentState.find(i);
      int x = pos[0], y = pos[1];
      delete[] pos;
      int x_opt = i!=0 ? (i - 1)/dimension : 2,
          y_opt = i!=0 ? (i - 1)%dimension : 2;

      distance += abs(x - x_opt) + abs(y - y_opt);
    }
    return distance;
  }
};

//! Implementation of the tile difference heuristic for the 8-puzzle
class TileDifference : public Heuristic {
 public:

  int calc(GameState &currentState) {
    int distance = 0, dimension = currentState.getDimension();

    // adds 1 for every tile that is not in its goal position
    for (int i = 0; i < pow(dimension, 2); i++) {
      int *pos = currentState.find(i);
      int x = pos[0], y = pos[1];
      delete[] pos;
      int x_opt = i!=0 ? (i - 1)/dimension : 2,
          y_opt = i!=0 ? (i - 1)%dimension : 2;

      distance += x!=x_opt || y!=y_opt;
    }
    return distance;
  }
};

#endif // SEARCH_HEURISTIC_HPP
