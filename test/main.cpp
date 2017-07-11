#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "AStarSolver.hpp"
#include "DepthFirstSolver.hpp"
#include "BreadthFirstSolver.hpp"
#include "GreedySolver.hpp"
#include "HillClimbingSolver.hpp"

int myRandom(int max) {
  time_t result = time(nullptr);
  mt19937_64 r;
  r.seed((unsigned long) std::localtime(&result));
  return abs((int) r() % max);
}

//! Reads an input file, transforming it into a list of strings
//! \return the list of strings
LinkedList<string> *getPuzzles() {
  LinkedList<string> *puzzles = new LinkedList<string>();
  string line;
  ifstream myfile("inputs");

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      puzzles->insert(line);
    }
    myfile.close();
  }
  return puzzles;
}

//! Checks if the goal state is correctly generated
//! \return 0 if success
int testGoalCreation() {
  Game game = Game(3);

  std::cout << game.getGoal()->to_string() << std::endl;
  return 0;
}

//! Gets a puzzle and performs a series of actions in it to test transitions
//! \return 1 if success
int testStateTransitions() {
  GameState *gs = new GameState(getPuzzles()->get(0));

  cout << gs->to_string() << endl;

  GameAction *a = new GameAction[4]{DOWN, RIGHT, UP, LEFT};

  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < 4; j ++)
      if (gs->isValid(a[j])) {
        GameState *gs2 = new GameState(gs, a[j]);
        delete gs;
        gs = gs2;
        break;
      }
  }
  delete[]a;
  return 0;
}

//! Tests the solvability of the puzzles in the input file.
//! Must output 1 for all of them.
void testSolvability() {
  LinkedList<string> *l = getPuzzles();

  while (! l->isEmpty())
    cout << GameState(l->remove(0)).isSolvable() << endl;
}

//! Tests the overloaded equality operator for GameState
void testEquality() {
  GameState gs1 = GameState("1 2 3 4 5 6 7 8 0"),
      gs2 = GameState("1 2 3 4 5 6 7 8 0"),
      gs3 = GameState("0 1 3 2 4 8 6 7 5"),
      gs4 = GameState("0 1 3 2 4 8 6 7 5");

  if (gs1 != gs1 or gs2 != gs2 or gs3 != gs3 or gs4 != gs4 or gs1 != gs2 or gs3 != gs4 or
      gs1 == gs3 or gs1 == gs4 or gs2 == gs3 or gs2 == gs4) {
    throw exception();
  }
}

//! Tests the generation of GameState objects from the input file strings
int testStateFromFile() {
  LinkedList<string> *l = getPuzzles();

  while (! l->isEmpty()) {
    cout << GameState(l->remove(l->getSize() - 1)).to_string() << "\n";
  }

  delete l;
  return 0;
}

//! Generic function to test a single solver and print its output
int testSingleSolver(Solver *s, Game &g, GameState &gs, bool verbose) {
  LinkedList<GameState *> results = s->solve(g, gs);

  if (verbose) {
    while (! results.isEmpty())
      cout << results.remove(results.getSize() - 1)->to_string() << endl;

    cout << s->to_string() << endl;
  }

  return 0;
}

//! Tests the fastest solvers against all of the puzzles.
void testFastSolvers() {
  LinkedList<string> *l = getPuzzles();

  Game g = Game(3);

  int n1, n2, n3, n4, totalPuzzles = l->getSize();
  n1 = n2 = n3 = n4 = 0;

  while (! l->isEmpty()) {
    cout << l->getSize() << "/" << totalPuzzles << endl;
    GameState gs = GameState(l->remove(myRandom(l->getSize())));

    AStarSolver *s1 = new AStarSolver(new Manhattan());
    GreedySolver *s2 = new GreedySolver(new Manhattan());
    HillClimbingSolver *s3 = new HillClimbingSolver(new Manhattan(), false);
    HillClimbingSolver *s4 = new HillClimbingSolver(new Manhattan(), true);

    testSingleSolver(s1, g, gs, false);
    testSingleSolver(s2, g, gs, false);
    testSingleSolver(s3, g, gs, false);
    testSingleSolver(s4, g, gs, false);

    n1 += s1->isSolved();
    n2 += s2->isSolved();
    n3 += s3->isSolved();
    n4 += s4->isSolved();

    delete s1, s2, s3, s4;

  }

  cout << "                    A*: " << n1 << "/" << totalPuzzles
       << "\n                Greedy: " << n2 << "/" << totalPuzzles
       << "\n         Hill Climbing: " << n3 << "/" << totalPuzzles
       << "\nSteepest Hill Climbing: " << n4 << "/" << totalPuzzles << endl;

  delete l;
}

//! Creates one of each solver, randomly selects a puzzle from the
//! input file and tests all solvers against it.
//! Non-informed solvers might take too long to finish some states.
int testAllSolvers() {
  Game game = Game(3);

  // this is just a known tractable problem with solution in depth 18
  GameState gs = GameState("0 3 6 4 7 5 2 1 8");

  GreedySolver *s1 = new GreedySolver(new Manhattan());
  AStarSolver *s2 = new AStarSolver(new Manhattan());
  HillClimbingSolver *s3 = new HillClimbingSolver(new Manhattan());
  HillClimbingSolver *s4 = new HillClimbingSolver(new Manhattan(), true);
  BreadthFirstSolver *s5 = new BreadthFirstSolver();
  DepthFirstSolver *s6 = new DepthFirstSolver();

  testSingleSolver(s1, game, gs, true);
  testSingleSolver(s2, game, gs, true);
  testSingleSolver(s3, game, gs, true);
  testSingleSolver(s4, game, gs, true);
  testSingleSolver(s5, game, gs, true);
  testSingleSolver(s6, game, gs, true);

  return 0;
}

int main() {
//  testGoalCreation();
//  testStateFromFile();
//  testStateTransitions();
//  testEquality();
//  testSolvability();
  testFastSolvers();
//  testAllSolvers();
  return 0;
}
