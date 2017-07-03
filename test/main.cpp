#include <iostream>
#include <fstream>
#include <random>
#include "AStarSolver.hpp"
#include "DepthFirstSolver.hpp"
#include "BreadthFirstSolver.hpp"
#include "GreedySolver.hpp"
#include "HillClimbingSolver.hpp"

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

int testGoalCreation() {
  Game game = Game(3);

  std::cout << game.getGoal()->to_string() << std::endl;
  return 0;
}

int testStateTransitions() {
  GameState *gs = new GameState(getPuzzles()->get(0));

  cout << gs->to_string() << endl;

  GameAction *a = new GameAction[4]{DOWN, RIGHT, UP, LEFT};

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 4; j++)
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

void testEquality() {
  GameState gs1 = GameState("1 2 3 4 5 6 7 8 0"),
      gs2 = GameState("1 2 3 4 5 6 7 8 0"),
      gs3 = GameState("0 1 3 2 4 8 6 7 5"),
      gs4 = GameState("0 1 3 2 4 8 6 7 5");

  if (!(gs1==gs1) or !(gs2==gs2) or !(gs3==gs3) or !(gs4==gs4) or !(gs1==
      gs2) or (gs1==gs3) or (gs1==gs4) or (gs2==gs3) or (gs2==gs4) or !(gs3==gs4)) {
    throw exception();
  }
}

int testStateFromFile() {
  LinkedList<string> *l = getPuzzles();

  while (!l->isEmpty()) {
    cout << GameState(l->remove(l->getSize()-1)).to_string() << "\n";
  }

  delete l;
  return 0;
}
int testSingleSolver(Solver *s, Game &g, GameState &gs) {
  LinkedList<GameState *> results = s->solve(g, gs);

  while (!results.isEmpty())
    cout << results.remove(results.getSize()-1)->to_string() << endl;

  cout << s->to_string() << endl;

  return 0;
}

int testAllSolvers() {
  LinkedList<string> *puzzles = getPuzzles();
  time_t result = time(nullptr);

  mt19937_64 myRandom;
  myRandom.seed((unsigned long) std::localtime(&result));
  Game game = Game(3);
  int chosen_one = abs((int) myRandom()%puzzles->getSize());
  GameState gs = GameState(puzzles->remove(chosen_one));

  delete puzzles;

  GreedySolver *s1 = new GreedySolver(new Manhattan());
  AStarSolver *s2 = new AStarSolver(new Manhattan());
  HillClimbingSolver *s3 = new HillClimbingSolver(new Manhattan());
  HillClimbingSolver *s4 = new HillClimbingSolver(new Manhattan(), true);
  BreadthFirstSolver *s5 = new BreadthFirstSolver();
  DepthFirstSolver *s6 = new DepthFirstSolver();

  testSingleSolver(s1, game, gs);
  testSingleSolver(s2, game, gs);
  testSingleSolver(s3, game, gs);
  testSingleSolver(s4, game, gs);
  testSingleSolver(s5, game, gs);
  testSingleSolver(s6, game, gs);

  return 0;
}

int testSolverMulti() {
  LinkedList<string> *puzzles = getPuzzles();

  Game game = Game(3);
  int count = 0;

  while (!puzzles->isEmpty()) {
    cout << ++count;
    GameState gs = GameState(puzzles->remove(0));
    AStarSolver solver = AStarSolver(new Manhattan());
    LinkedList<GameState *> results = solver.solve(game, gs);
    cout << solver.to_string();
  }
  delete puzzles;
  return 0;
}

int main() {
//  testEquality();
//  testGoalCreation();
//  testStateTransitions();
//  testStateFromFile();
  testAllSolvers();
  //  testSolverMulti();
  return 0;
}
