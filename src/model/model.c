/**
 * \file model.c
 * \brief Fichier responsable de la logique du jeu.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient des fonctions permettant d'effectuer des actions simples 
 * sur le jeu comme initialiser le plateau, vérifier des données, placer un 
 * coup etc...
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdio.h>
#include <string.h>
// ----- Internal files
#include "../../include/model.h"

// -------------------------Body------------------------------------------------

void initializeGame(GameState *game) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }
    game->currentPlayer = PLAYER_1;
    game->turnNumber = 1;
}

bool moveInField(Coordinates move) {
    if (move.x >= 0 && move.x < GRID_SIZE && move.y >= 0 && move.y < GRID_SIZE) 
    {
        return true;
    }
    return false;
}

bool moveTaken(GameState game, Coordinates move) {
    if (game.board[move.x][move.y] == EMPTY) {
        return false;
    }
    return true;
}

void makeMove(GameState *game, Coordinates move) {
    game->board[move.x][move.y] = game->currentPlayer;
}

void convertCoordinatesFrom00ToA1(Coordinates move, char *moveA1Format) {
    char letter = 'A' + move.x;
    char number = move.y + 1;
    sprintf(moveA1Format, "%c%d", letter, number);
}

void copyGameState(GameState *destination, const GameState *source) {
    memcpy(destination, source, sizeof(GameState));
}
