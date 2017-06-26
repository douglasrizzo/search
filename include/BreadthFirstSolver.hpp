//
// Created by dodo on 24/06/17.
//

#ifndef BUSCA_BREADTHFIRSTSOLVER_HPP
#define BUSCA_BREADTHFIRSTSOLVER_HPP

#include "Solver.hpp"
#include "DynamicQueue.hpp"

class BreadthFirstSolver: public Solver{
public:
    LinkedList<GameState *> *solve(Game *game, GameState *g0) {
        DynamicQueue<GameState *> q;
        LinkedList<GameState *> visited;

        q.enqueue(g0);

        GameAction actions[4]{UP, DOWN, LEFT, RIGHT};

        int depth = 0;

        while (!q.isEmpty()) {
            GameState *currentGame = q.dequeue();
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
                        q.enqueue(newState);
                    else delete newState;
                }
            }

            visited.insert(currentGame);
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_BREADTHFIRSTSOLVER_HPP
