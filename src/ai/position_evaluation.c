/*
 * Ce fichier contient la fonction permettant d'évaluer une position de jeu 
 * donnée selon des critères subjectifs.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <limits.h>
// ----- Internal files
#include "../../include/position_evaluation.h"
#include "../../include/victory_manager.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn static int evaluatePath(GameState game)
 * \brief Évaluation de la formation de chemins pour un joueur donné (plus il y 
 * a de pions en diagonale, meilleur est le score).
 * 
 * Cette fonction évalue la formation de chemins pour un joueur donné en 
 * comptant le nombre de pions du joueur en diagonale.
 * Plus il y a de pions en diagonale, meilleur est le score.
 * 
 * \param game L'état actuel du jeu.
 * \return Le score d'évaluation de la formation de chemins.
 */
static int evaluatePath(GameState game);

/**
 * \fn static int evaluateCenter(GameState game)
 * \brief Évalue le centre de la grille de jeu.
 * 
 * Cette fonction évalue le centre de la grille de jeu en attribuant des points
 * pour chaque pion du joueur courant présent dans le centre de la grille.
 * Le centre de la grille est défini comme une zone délimitée par les
 * coordonnées (2, 2) et (GRID_SIZE - 3, GRID_SIZE - 3) incluses.
 * 
 * \param game L'état actuel du jeu à évaluer.
 * \return La valeur d'évaluation basée sur la présence de pions du joueur
 * courant dans le centre de la grille.
 */ 
static int evaluateCenter(GameState game);

/**
 * \fn static int evaluateVictory(GameState game, int depthLeft)
 * \brief Évalue l'état actuel du jeu pour déterminer s'il y a une victoire.
 * 
 * Cette fonction examine l'état du jeu actuel pour déterminer s'il y a une 
 * victoire pour l'un des joueurs.
 * 
 * \param game L'état actuel du jeu à évaluer.
 * \param depthLeft La profondeur restante de l'arbre de recherche.
 * \return La valeur d'évaluation basée sur l'état du jeu. Si le joueur 1 
 * gagne, le score est positif,
 * sinon s'il perd, le score est négatif. La valeur absolue du score augmente 
 * avec la profondeur restante.
 * Si le jeu n'est pas encore terminé, le score est égal à 0.
 */
static int evaluateVictory(GameState game, int depthLeft);

// -------------------------Body------------------------------------------------

int evaluatePosition(GameState game, int depthLeft) {
    int score = 0;
    
    score += evaluatePath(game);
    score += evaluateCenter(game);
    score += evaluateVictory(game, depthLeft);

    return score;
}

static int evaluatePath(GameState game) {
    int score = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (game.board[i][j] == game.currentPlayer) {
                if ((i - 1 >= 0 && j - 1 >= 0 
                    && game.board[i - 1][j - 1] == game.currentPlayer) ||
                    (i - 1 >= 0 && j + 1 < GRID_SIZE 
                    && game.board[i - 1][j + 1] == game.currentPlayer) ||
                    (i + 1 < GRID_SIZE && j - 1 >= 0 
                    && game.board[i + 1][j - 1] == game.currentPlayer) ||
                    (i + 1 < GRID_SIZE && j + 1 < GRID_SIZE 
                    && game.board[i + 1][j + 1] == game.currentPlayer)) {
                    score += 1;
                }
            }
        }
    }

    return score;
}

static int evaluateCenter(GameState game) {
    int score = 0;

    for (int i = 2; i < GRID_SIZE - 2; i++) {
        for (int j = 2; j < GRID_SIZE - 2; j++) {
            if (game.board[i][j] == game.currentPlayer) {
                score += 2;
            }
        }
    }

    return score;
}

static int evaluateVictory(GameState game, int depthLeft) {
    if ((player1Victory(game) && game.currentPlayer == PLAYER_1) ||
        (player2Victory(game) && game.currentPlayer == PLAYER_2)) {
        int score = 50+50*depthLeft;
        return score;
    }
    if ((player1Victory(game) && game.currentPlayer == PLAYER_2) ||
        (player2Victory(game) && game.currentPlayer == PLAYER_1)) {
        int score = -50-50*depthLeft;
        return score;
    }
    return 0;
}
