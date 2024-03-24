/**
 * \file model.test.c
 * \brief Tests des fonctions de model.h
 * \author simon.antropius@uha.fr
 * \version 0.1
*/

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../../include/model.h"

// -------------------------Test Functions--------------------------------------

/**
 * \fn bool testInitializeGame()
 * \brief Test de initializeGame qui vérifie si le plateau est bien initialisé
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
bool testInitializeGame() {
    printf("Test de initializeGame...\n");
    GameState game;
    initializeGame(&game);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (game.board[i][j] != ' ') {
                printf("Erreur: La case (%d, %d) n'est pas vide.\n", i, j);
                return false;
            }
        }
    }

    if (game.currentPlayer != PLAYER_1) {
        printf("Erreur: Le joueur courant n'est pas PLAYER_1.\n");
        return false;
    }

    if (game.turnNumber != 1) {
        printf("Erreur: Le numéro de tour n'est pas 1.\n");
        return false;
    }

    printf("Test de initializeGame réussi.\n");
    return true;
}

/**
 * \fn bool testMoveTaken()
 * \brief Test de moveTaken qui vérifie si une case est prise
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
bool testMoveTaken() {
    printf("Test de moveTaken...\n");
    GameState game;
    initializeGame(&game);

    Coordinates move = {0, 0};
    makeMove(&game, move);

    if (!moveTaken(game, move)) {
        printf("Erreur: La case (%d, %d) est censée être occupée.\n", move.x, move.y);
        return false;
    }

    Coordinates emptyMove = {1, 1};
    if (moveTaken(game, emptyMove)) {
        printf("Erreur: La case (%d, %d) est censée être vide.\n", emptyMove.x, emptyMove.y);
        return false;
    }

    printf("Test de moveTaken réussi.\n");
    return true;
}

/**
 * \fn bool testMoveInField()
 * \brief Test de moveInField qui vérifie si le coup est bien dans le plateau
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
bool testMoveInField() {
    printf("Test de moveInField...\n");
    Coordinates validMove = {2, 2};
    Coordinates invalidMove = {10, 10};

    if (!moveInField(validMove)) {
        printf("Erreur: Le coup (%d, %d) est censé être valide.\n", validMove.x, validMove.y);
        return false;
    }

    if (moveInField(invalidMove)) {
        printf("Erreur: Le coup (%d, %d) est censé être invalide.\n", invalidMove.x, invalidMove.y);
        return false;
    }

    printf("Test de moveInField réussi.\n");
    return true;
}

/**
 * \fn bool testMakeMove()
 * \brief Test de makeMove qui vérifie si le pion est correctement placé sur le 
 * plateau
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
bool testMakeMove() {
    printf("Test de makeMove...\n");
    GameState game;
    initializeGame(&game);

    Coordinates move = {0, 0};
    makeMove(&game, move);

    if (game.board[move.x][move.y] != PLAYER_1) {
        printf("Erreur: Le pion n'a pas été placé correctement sur le plateau.\n");
        return false;
    }

    printf("Test de makeMove réussi.\n");
    return true;
}

// -------------------------Main Function---------------------------------------

/**
 * \fn void run_tests_model()
 * \brief Lance tous les tests de model.test.c et dit quand celui-ci a une 
 * erreur
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
void run_tests_model() {
    printf("Lancement des tests de model.h");
    bool allTestsPassedModel = true;

    if (!testInitializeGame()) {
        allTestsPassedModel = false;
        printf("Le test de initializeGame a trouvé une erreur");
    }

    if (!testMoveTaken()) {
        allTestsPassedModel = false;
        printf("Le test de moveTaken a trouvé une erreur");
    }

    if (!testMoveInField()) {
        allTestsPassedModel = false;
        printf("Le test de moveInField a trouvé une erreur");
    }

    if (!testMakeMove()) {
        allTestsPassedModel = false;
        printf("Le test de makeMove a trouvé une erreur");
    }

    if (allTestsPassedModel) {
        printf("Tous les tests ont réussi.\n");
    }
}