/**
 * \file ai.c
 * \brief Fichier contenant l'IA du jeu.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient la fonction permettant de trouver le meilleur coup 
 * possible selon l'IA.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <limits.h>
#include <stdlib.h>
// ----- Internal files
#include "../../include/ai.h"
#include "../../include/position_evaluation.h"
#include "../../include/victory_manager.h"
// ----- Game parameters
#include "../../include/constants.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn static int minimaxAlphaBeta(GameState node, int depth, int alpha, int 
 * beta, bool 
 * maximizingPlayer)
 * \brief Implémente l'algorithme minimax avec élagage alpha-beta de manière 
 * récursive.
 * 
 * Cette fonction effectue une recherche récursive dans l'arbre de jeu en 
 * utilisant l'algorithme minimax avec élagage alpha-beta.
 * 
 * \param node L'état du jeu à partir duquel la recherche commence.
 * \param depth La profondeur de recherche dans l'arbre.
 * \param alpha La valeur minimale attendue par le joueur cherchant à maximiser 
 * son coup. Utilisez un nombre significativement supérieur aux scores attendus 
 * lors du premier appel.
 * \param beta La valeur maximale attendue par le joueur cherchant à minimiser 
 * son coup. Utilisez un nombre significativement inférieur aux scores attendus 
 * lors du premier appel.
 * \param maximizingPlayer true si le joueur actif du nœud cherche à maximiser 
 * son coup, false sinon.
 * 
 * \return La plus haute valeur trouvée à partir du nœud donné à la profondeur 
 * maximale spécifiée (ou la plus basse si maximizingPlayer est défini à false).
 */
static int minimaxAlphaBeta(GameState node, int depth, int *alpha, int *beta, 
                            bool maximizingPlayer);

// -------------------------Body------------------------------------------------

Coordinates findBestMove(GameState game) {
    int bestScore = INT_MIN;
    Coordinates bestMove;
    bestMove.x = -1;
    bestMove.y = -1;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (game.board[i][j] == EMPTY) {
                GameState childNode;
                copyGameState(&childNode, &game);
                childNode.board[i][j] = childNode.currentPlayer;
                childNode.turnNumber++;

                int score = minimaxAlphaBeta(childNode, DEPTH - 1, &alpha, 
                                             &beta, false);

                if (score > bestScore) {
                    bestScore = score;
                    bestMove.x = i;
                    bestMove.y = j;
                }
            }
        }
    }

    return bestMove;
}

static int minimaxAlphaBeta(GameState node, int depth, int *alpha, int *beta, 
                            bool maximizingPlayer) {
    if (depth == 0 || victory(node) || node.turnNumber == NB_CELLS) {
        return evaluatePosition(node, depth);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (node.board[i][j] == EMPTY) {
                    GameState childNode;
                    copyGameState(&childNode, &node);
                    childNode.board[i][j] = childNode.currentPlayer;
                    childNode.currentPlayer = (childNode.currentPlayer == 
                                               PLAYER_1) ? PLAYER_2 : PLAYER_1;
                    childNode.turnNumber++;

                    int childValue = minimaxAlphaBeta(childNode, depth - 1, 
                                                      alpha, beta, false);
                    maxEval = (childValue > maxEval) ? childValue : maxEval;

                    if (*beta <= maxEval) {
                        return maxEval; // Élagage alpha-beta
                    }
                    *alpha = (*alpha > maxEval) ? *alpha : maxEval;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (node.board[i][j] == EMPTY) {
                    GameState childNode;
                    copyGameState(&childNode, &node);
                    childNode.board[i][j] = childNode.currentPlayer;
                    childNode.currentPlayer = (childNode.currentPlayer == 
                                               PLAYER_1) ? PLAYER_2 : PLAYER_1;
                    childNode.turnNumber++;

                    int childValue = minimaxAlphaBeta(childNode, depth - 1, 
                                                      alpha, beta, true);
                    minEval = (childValue < minEval) ? childValue : minEval;

                    if (minEval <= *alpha) {
                        return minEval; // Élagage alpha-beta
                    }
                    *beta = (*beta < minEval) ? *beta : minEval;
                }
            }
        }
        return minEval;
    }
}
