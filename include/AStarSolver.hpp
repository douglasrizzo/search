//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_ASTARSOLVER_HPP
#define BUSCA_ASTARSOLVER_HPP

#include "Solver.hpp"
#include "Heuristic.hpp"


class AStarSolver : public Solver {
private:
    Heuristic *heuristic;

public:
    AStarSolver(Heuristic *h) {
        heuristic = h;
    }

    ~AStarSolver() {
        delete heuristic;
    }

    LinkedList<GameState> *solve(Game game, GameState g0) {
        LinkedList<GameState> l;
        LinkedList<GameState> visited;

        l.insert(g0);

        GameAction actions[4]{UP, DOWN, LEFT, RIGHT};

        int depth = 0;

        while (!l.isEmpty()) {
            GameState currentGame = l.get(0);
            int toRemove = 0;
            for (int j = 0; j < l.getSize(); j++) {
                GameState tmp = l.get(j);
                if (heuristic->calc(tmp) + tmp.getDepth() < heuristic->calc(currentGame) + currentGame.getDepth()) {
                    currentGame = tmp;
                    toRemove = j;
                }
            }

            l.remove(toRemove);

            if (*game.getGoal() == currentGame) {
                LinkedList<GameState> *resultSteps = new LinkedList<GameState>();

                GameState *tmp = &currentGame;
                while (tmp != NULL) {
                    resultSteps->insert(*tmp);
                    tmp = tmp->getParent();
                }

//                for (int i = 0; i < resultSteps->getSize(); i++) {
//                    int x = l.getIndex(resultSteps->get(0));
//
//                    if (x != NULL) {
//                        tmp = l.remove(x);
//                        delete tmp;
//                    }
//                }

                return resultSteps;
            }

            visited.insert(currentGame);

            int newStates = 0;
            for (int i = 0; i < 4; i++) {
                GameAction currentAction = actions[i];
                if (currentGame.isValid(actions[i])) {
                    GameState *newState = new GameState(currentGame, actions[i]);

                    if(newState==newState->getParent())
                        cout<<"AHA";

                    if (!visited.contains(*newState)) {
                        newStates++;
                        l.insert(*newState);

//                        if (newStates == 4)
//                            cout << currentGame->to_line_string() << "\n" << newState->to_line_string() << "\n\n";
                    }
                    else
                        delete newState;
                }
            }

            if(newStates==4) {
                cout << currentGame.to_line_string() << "\t" << heuristic->calc(currentGame) << "\t"
                     << currentGame.getDepth() << "\t+" << newStates << " new states" << endl;
            }
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_BESTFIRSTSOLVER_HPP