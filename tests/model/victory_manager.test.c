// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../../include/victory_manager.h"

// -------------------------Test Functions--------------------------------------

/**
 * \fn bool testVictory()
 * \brief Test de victory qui vérifie si une victoire est bien détectée ou non
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
bool testVictory() {
    printf("Test de victory...\n");
    GameState game;
    initializeGame(&game);

    game.currentPlayer = PLAYER_1;
    game.board[0][0] = PLAYER_1;
    game.board[1][1] = PLAYER_1;
    game.board[2][2] = PLAYER_1;
    game.board[3][3] = PLAYER_1;
    game.board[4][4] = PLAYER_1;
    game.board[5][5] = PLAYER_1;

    bool result = victory(game);

    if (result) {
        printf("Le joueur 1 a gagné. Le test réussit.\n");
        return true;
    } else {
        printf("Erreur: Le test a échoué. Le joueur 1 devrait avoir gagné.\n");
        return false;
    }
}

// -------------------------Main Function---------------------------------------

/**
 * \fn void run_tests_victory_manager()
 * \brief Lance tous les tests de victory_manager.test.c et dit quand celui-ci 
 * a une erreur
 * \author simon.antropius@uha.fr
 * \version 0.1
*/
void run_tests_victory_manager() {
    printf("Lancement des tests de victory_manager.h");
    bool allTestsPassedVictoryManager = true;

    if (!testVictory()) {
        allTestsPassedVictoryManager = false;
        printf("Le test de victory a trouvé une erreur");
    }

    if (allTestsPassedVictoryManager) {
        printf("Tous les tests ont réussi.\n");
    }
}
