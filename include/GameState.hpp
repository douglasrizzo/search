/**
 * @author Douglas De Rizzo Meneghetti (douglasrizzom@gmail.com)
 * @date   2017-6-22
 * @brief  Describes a single state in the 8-puzzle.
 */


#ifndef SEARCH_GAMESTATE_HPP
#define SEARCH_GAMESTATE_HPP

#include <string>
#include <iostream>
#include "GameAction.hpp"

using namespace std;

//!Describes a single state in the 8-puzzle.
class GameState {
 private:

  int **representation;
  int depth, dimension;
  GameState *parent;

  //! Turns a string representation of an 8-puzzle into an array
  //! \param s string representation of an 8-puzzle
  //! \return Pointer to an int array containing the state of the puzzle
  int *toIntArray(string s) {

    //count spaces in string
    int spaces = 1;
    for (int i = 0; i < s.length(); i++) {
      if (s[i]==' ') spaces++;
    }

    //create array
    int *ret = new int[spaces];

    int currentInt = 0;
    string intString = "";
    for (int i = 0; i < s.length(); i++) {

      //glues it number together until a space is found
      if (s[i]!=' ') {
        intString += s[i];
      }

      //space means end of number, turn it into an int and put it in the return array
      if ((s[i]==' ') || (i==s.length() - 1)) {
        ret[currentInt++] = stoi(intString);
        intString = "";
      }
    }
    return ret;
  }

 public:

  //!Default constructor, everything starts as 0 or NULL
  GameState() {
    depth = dimension = 0;
    representation = NULL;
    parent = NULL;
  }

  //! Creates a GameState from a string, where tile numbers are separated by spaces in a single line
  //! \param s string representation on an 8-puzzle state
  explicit GameState(string s) {
    depth = 0;
    parent = NULL;

    // converts string to int[]
    int *conversion = toIntArray(s);

    // calculates puzzle dimension from array size
    dimension = sizeof(conversion)/sizeof(conversion[0]) + 1;

    // searches for duplicate numbers inside the array
    for (int i = 0; i < dimension*dimension - 1; i++) {
      for (int j = i + 1; j < dimension*dimension; j++) {
        if (conversion[i]==conversion[j]) {
          cout << conversion[i] << conversion[j] << i << j;
          throw invalid_argument(s);
        }
      }
    }

    // initializes array of arrays to keep the 8-puzzle state
    representation = new int *[dimension];

    //iterates through rows and columns, adding the numbers converted from the input string
    int val = 0;
    for (int x = 0; x < dimension; x++) {
      representation[x] = new int[dimension]; // initialize inner arrays

      for (int y = 0; y < dimension; y++) {
        representation[x][y] = conversion[val++];
      }
    }

    delete[] conversion;
  }

  //! Copy constructor of the class
  //! \param obj object that will be copied
  GameState(const GameState &obj) {
    dimension = obj.dimension;
    depth = obj.depth;

    representation = new int *[dimension];

    for (int x = 0; x < dimension; x++) {
      representation[x] = new int[dimension];

      for (int y = 0; y < dimension; y++) {
        representation[x][y] = obj.representation[x][y];
      }
    }

    parent = obj.parent;
  }

  //! Creates a new state based on a given previous state and applying an action to it
  //! \param previous the previous state
  //! \param action the action to be applied to the previous state
  GameState(GameState *previous, GameAction action) {
    //dimension is the same, depth is one lower, parent is the state passed in the argument
    dimension = previous->dimension;
    depth = previous->depth + 1;
    parent = previous;
    representation = new int *[dimension];

    // first, copy the state
    for (int x = 0; x < dimension; x++) {
      representation[x] = new int[dimension];

      for (int y = 0; y < dimension; y++) {
        representation[x][y] = previous->representation[x][y];
      }
    }

    //find the 0
    int *pos_0 = find(0);
    int x = pos_0[0], y = pos_0[1];
    delete[] pos_0;
    int tmp = 0;

    // validate action
    if (action!=RIGHT and action!=LEFT and action!=UP and action!=DOWN)
      throw invalid_argument("No previous action to build the new GameState.");

    if (!isValid(action)) {
      throw invalid_argument("Invalid action for current game state.");
    }

    // move the 0 according to the given action
    // keep the value of the tile where the 0 is being move to in tmp
    switch (action) {
      case RIGHT:tmp = previous->representation[x + 1][y];
        representation[x + 1][y] = 0;
        break;

      case LEFT:tmp = previous->representation[x - 1][y];
        representation[x - 1][y] = 0;
        break;

      case UP:tmp = previous->representation[x][y - 1];
        representation[x][y - 1] = 0;
        break;

      case DOWN:tmp = previous->representation[x][y + 1];
        representation[x][y + 1] = 0;
        break;
    }

    //put the value in tmp where the 0 was
    representation[x][y] = tmp;
  }

  //!Destructor of GameState
  ~GameState() {
    // erase inner arrays
    // since the value of `dimension` is lost, calculate it here
    int dim = sizeof(representation[0])/sizeof(representation[0][0]) + 1;
    for (int i = 0; i < dim; i++)
      delete[] representation[i];

    //erase outer array
    delete[] representation;
  }

  //! Checks whether an action is valid for this state.
  //! Actions are invalid if they'd move the 0 tile outside of the board.
  //! \param action the action to be validated
  //! \return true if the action can be applied in this state, otherwise false
  bool isValid(GameAction action) {
    if (action!=RIGHT and action!=LEFT and action!=UP and action!=DOWN)
      return false;

    int *pos_0 = find(0);
    int x = pos_0[0], y = pos_0[1];

    delete[] pos_0;

    return !(action==RIGHT and x==dimension - 1 ||
        action==LEFT and x==0 ||
        action==UP and y==0 ||
        action==DOWN and y==dimension - 1);
  }

  //! Checks whether two GameState objects are equal.
  //! They are equal if they have the same board dimensions and the same values in the same positions of their board.
  //! \param other The GameState to be compared to
  //! \return true if equal, otherwise false
  bool operator==(const GameState &other) const {
    if (dimension!=other.dimension) return false;

    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        if (representation[x][y]!=other.representation[x][y]) return false;
      }
    }
    return true;
  }

  //! Counts the number of inversions in the puzzle.
  //! An inversion occurs whenever a number comes before a smaller number in the puzzle.
  //! \return number of inversions in this states of the puzzle
  int countInversions() {
    int inv_count = 0;

    int rasterDimension = dimension*dimension;
    int *raster = new int[rasterDimension];

    int current = 0;
    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        raster[current++] = representation[x][y];
      }
    }

    for (int i = 0; i < rasterDimension - 1; i++)
      for (int j = i + 1; j < rasterDimension; j++)
        if (raster[i]!=0 and raster[j]!=0 and raster[i] > raster[j])
          inv_count++;

    delete[] raster;

    return inv_count;
  }

  //! Check if the state is solvable.
  //! \return a state is solvable if the number of inversions in it is even.
  bool isSolvable() {
    return countInversions()%2==0;
  }

  //! Compares two GameState objects. Tile numbers are compared in order. If this[i,j] < other[i,j], this < other.
  //! This operator is useful in case objects need to be sorted inside a data structure, for example.
  //! \param other The GameState to be compared to
  //! \return true if this < other, otherwise false
  bool operator<(const GameState &other) const {
    if (dimension!=other.dimension) throw invalid_argument("Puzzles of different dimensions aren't comparable");

    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        if (representation[x][y] < other.representation[x][y]) return true;
      }
    }
    return false;
  }

  //! Inequality operator for GameState. This is the negation of the equality operator.
  //! \param other The GameState to be compared to
  //! \return false if equal, otherwise true
  bool operator!=(const GameState &other) const {
    return !(*this==other);
  }

  int getDimension() const {
    return dimension;
  }

  //! Returns a multi-line string representation of the 8-puzzle board state
  //! \return multi-line string representation of the state
  string to_string() const {
    string tmp = "";

    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        tmp.append(std::to_string(representation[x][y])).append(" ");
      }
      tmp.append("\n");
    }
    return tmp;
  }

  //! Returns a single line string representation of the 8-puzzle board state
  //! \return single line string representation of the state
  string to_line_string() const {
    string tmp = "";

    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        tmp.append(std::to_string(representation[x][y])).append(" ");
      }
    }
    return tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
  }

  //! Finds the position of a tile in the board
  //! \param value the value of the tile to look for
  //! \return int array where [0] contains x position and [1] y position of the number
  int *find(int value) {
    for (int x = 0; x < dimension; x++) {
      for (int y = 0; y < dimension; y++) {
        if (representation[x][y]==value) return new int[2]{x, y};
      }
    }

    throw invalid_argument("Inexistent number.");
  }

  void setRepresentation(int **representation) {
    this->representation = representation;

    //dimension must be recalculated
    dimension = sizeof(representation[0])/sizeof(representation[0][0]) + 1;
  }

  GameState *getParent() const {
    return parent;
  }

  int getDepth() const {
    return depth;
  }
};

#endif // SEARCH_GAMESTATE_HPP
