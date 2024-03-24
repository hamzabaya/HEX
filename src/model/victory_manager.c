/**
 * \file victory_manager.c
 * \brief Fichier responsable de la gestion de la victoire.
 * \author simon.antropius@uha.fr
 * \author romain.bomba@uha.fr
 * \version 0.1
 *
 * Ce fichier contient des fonctions permettant de vérifier la victoire.
 */

// -------------------------Libraries-------------------------------------------

// ----- Internal files
#include "../../include/victory_manager.h"

// -------------------------Prototypes------------------------------------------

bool player1Victory(GameState game);

bool player2Victory(GameState game);

/**
 * \fn static bool pathExistsFromCell(GameState *game, int row, int col)
 * \brief Vérifie récursivement si un chemin continu est possible depuis la 
 * case donnée pour le joueur actuel.
 * 
 * Cette fonction vérifie récursivement si un chemin continu est possible 
 * depuis la case spécifiée par les coordonnées `row` et `col` pour le joueur 
 * actuel (PLAYER_1 ou PLAYER_2).
 * Elle marque les cases visitées pour éviter les boucles infinies et retourne 
 * `true` si un chemin continu atteint le bord opposé du plateau, sinon `false`.
 * 
 * \param game Un pointeur vers l'état actuel du jeu.
 * \param row La ligne de la case à partir de laquelle vérifier le chemin.
 * \param col La colonne de la case à partir de laquelle vérifier le chemin.
 * \return `true` si un chemin continu est possible depuis la case donnée pour 
 * le joueur actuel, sinon `false`.
 */
static bool pathExistsFromCell(GameState *game, int row, int col);

// -------------------------Body------------------------------------------------

bool victory(GameState game) {
    return player1Victory(game) || player2Victory(game);
}

bool player1Victory(GameState game) {
    // Parcours de la première colonne (côté gauche)
    for (int row = 0; row < GRID_SIZE; row++) {
        if (game.board[0][row] == PLAYER_1) {
            /* Si un pion 'X' est trouvé dans la première colonne, on 
            vérifie s'il peut atteindre le bord droit */
            if (pathExistsFromCell(&game, row, 0)) {
                return true;
            }
        }
    }

    return false;
}

bool player2Victory(GameState game) {
    // Parcours de la première ligne (en haut)
    for (int col = 0; col < GRID_SIZE; col++) {
        if (game.board[col][0] == PLAYER_2) {
            /* Si un pion 'O' est trouvé dans la première colonne, on 
            vérifie s'il peut atteindre le bord droit */
            if (pathExistsFromCell(&game, 0, col)) {
                return true;
            }
        }
    }

    return false;
}

static bool pathExistsFromCell(GameState *game, int row, int col) {
    // Conditions pour arrêter la récursion
    if (game->currentPlayer == PLAYER_1) {
        if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE || 
            game->board[col][row] != PLAYER_1) {
        return false;
        }
    } else {
        if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE || 
            game->board[col][row] != PLAYER_2) {
        return false;
        }
    }

    // Marquer la case comme visitée
    game->board[col][row] = VISITED;

    if (game->currentPlayer == PLAYER_1) {
        // Si on atteint le bord droit, le chemin existe
        if (col == GRID_SIZE - 1) {
            return true;
        }
    } else {
        // Si on atteint le bord du bas, le chemin existe
        if (row == GRID_SIZE - 1) {
            return true;
        }
    }

    // Recherche récursive des cases adjacentes en diagonale
    bool result = false;
    result = result || pathExistsFromCell(game, row - 1, col - 1);
    result = result || pathExistsFromCell(game, row - 1, col + 1);
    result = result || pathExistsFromCell(game, row + 1, col - 1);
    result = result || pathExistsFromCell(game, row + 1, col + 1);

    return result;
}
