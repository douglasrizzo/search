#include <iostream>
#include <fstream>
#include <thread>
#include <AStarSolver.hpp>
#include <random>

int testGoalCreation() {
    Game game = Game(3);
    std::cout << game.getGoal()->to_string() << std::endl;
    return 0;
}

int testStateTransitions() {
    string line;
    ifstream myfile("../inputs");

    if (myfile.is_open() && getline(myfile, line)) {
        GameState gs = GameState(line);
        myfile.close();
        cout << gs.to_string() << endl;

        for (int i = 0; i < 100; i++) {
            GameState gs2 = GameState(gs, RIGHT);
            gs = gs2;
            cout << gs.to_string() << endl;
        }
    }

    return 0;
}

void testEquality() {
    GameState gs1 = GameState("1 2 3 4 5 6 7 8 0"),
            gs2 = GameState("1 2 3 4 5 6 7 8 0"),
            gs3 = GameState("0 1 3 2 4 8 6 7 5"),
            gs4 = GameState("0 1 3 2 4 8 6 7 5");

    cout << (gs1 == gs2) << (gs1 == gs3) << (gs1 == gs4) <<
             (gs2 == gs3) << (gs2 == gs4) << (gs3 == gs4);
}

LinkedList<string> *getPuzzles() {
    LinkedList<string> *puzzles = new LinkedList<string>();
    string line;
    ifstream myfile("../inputs");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            puzzles->insert(line);
        }
        myfile.close();
    }
    return puzzles;
}

int testStateFromFile() {
    string line;
    ifstream myfile("../inputs");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << GameState(line).to_string() << "\n";
        }
        myfile.close();
        return 0;
    }

    cout << "Unable to open file";
    return 1;
}

int testSolver() {
    mt19937_64 orelha;
    time_t result = time(nullptr);
    orelha.seed((unsigned long) std::localtime(&result));

    LinkedList<string> *puzzles = getPuzzles();
    int chosen_one = abs((int) orelha() % puzzles->getSize());

    Game game = Game(3);
    GameState gs = GameState(puzzles->get(chosen_one));
    LinkedList<GameState> *results = AStarSolver(new Manhattan()).solve(game, gs);

    for (int i = results->getSize() - 1; i >= 0; i--)
        cout << results->get(i).to_string() << endl;

        delete puzzles;
    return 0;
}

int testSolverMulti() {
    LinkedList<string> *puzzles = getPuzzles();

    Game game = Game(3);
    int count = 0;
    while (!puzzles->isEmpty()) {
        cout << ++count;
        GameState gs = GameState(puzzles->remove(0));
        LinkedList<GameState> *results = AStarSolver(new Manhattan()).solve(game, gs);

        delete results;
    }
    delete[]puzzles;
    return 0;
}

int main() {
//     testEquality();
//    testGoalCreation();
//    testStateTransitions();
//    testStateFromFile();
    testSolver();
//    testSolverMulti();
    return 0;
}
