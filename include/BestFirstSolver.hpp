//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_BESTFIRSTSOLVER_HPP
#define BUSCA_BESTFIRSTSOLVER_HPP

#include "Solver.hpp"
#include "Heuristic.hpp"

class BestFirstSolver : public Solver {
private:
    Heuristic *heuristic;
public:
    BestFirstSolver(Heuristic *h) {
        heuristic = h;
    }

    ~BestFirstSolver() {
        delete heuristic;
    }

    LinkedList<GameState *> *solve(Game *game, GameState *g0) {
        LinkedList<GameState *> l;
        LinkedList<GameState *> visited;

        l.insert(g0);

        GameAction actions[4]{UP, DOWN, LEFT, RIGHT};

        int depth = 0;

        while (!l.isEmpty()) {
            GameState *currentGame = l.get(0);
            for (int i = 1; i < l.getSize(); i++) {
                GameState *tmp = l.get(i);
                if (heuristic->calc(tmp) < heuristic->calc(currentGame)) {
                    currentGame = tmp;
                }
            }

            if (*(game->getGoal()) == *currentGame) {
                LinkedList<GameState *> *resultSteps = new LinkedList<GameState *>();

                GameState *tmp = currentGame;
                while (tmp != NULL) {
                    resultSteps->insert(tmp);
                    tmp = tmp->getParent();
                }

                return resultSteps;
            }

            for (int i = 0; i < 4; i++) {
                GameAction currentAction = actions[i];
                if (currentGame->isValid(actions[i])) {
                    GameState *newState = new GameState(currentGame, actions[i]);

                    // cout << "INDEX: " << visited.getIndex(newState)<<endl;

                    if (!visited.contains(newState))
                        l.insert(newState);
                    else delete newState;
                }
            }

            visited.insert(currentGame);
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_BESTFIRSTSOLVER_HPP
