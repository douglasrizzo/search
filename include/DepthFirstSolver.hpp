//
// Created by dodo on 23/06/17.
//

#ifndef BUSCA_DEPTHFIRSTSOLVER_HPP
#define BUSCA_DEPTHFIRSTSOLVER_HPP

#include <LinkedList.hpp>
#include <DynamicStack.hpp>
#include "Solver.hpp"
#include "GameAction.hpp"
#include "Heuristic.hpp"

class DepthFirstSolver : public Solver {
public:
    LinkedList<GameState *> *solve(Game *game, GameState *g0) {
        DynamicStack<GameState *> s;
        LinkedList<GameState *> visited;

        s.push(g0);

        GameAction actions[4]{UP, DOWN, LEFT, RIGHT};

        int depth = 0;

        while (!s.isEmpty()) {
            GameState *currentGame = s.pop();
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
                        s.push(newState);
                    else delete newState;
                }
            }

            visited.insert(currentGame);
        }
        throw invalid_argument("This game is unsolvable!");
    }
};

#endif //BUSCA_DEPTHFIRSTSOLVER_HPP
