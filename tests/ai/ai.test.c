

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../../include/ai.h"

// -------------------------Test Functions--------------------------------------

/**
 * \fn bool testFindBestMove(Gamestate game)
 * \brief Test de findBestMove qui vérifie que les coordonnées soient valides
*/
bool testFindBestMove(GameState game) {
    printf("Test de findBestMove...\n");
    // Test pour vérifier que les coordonnées soient valides
    Coordinates move;
    move = findBestMove(game);
    if (0 > move.x  || move.x > 5){
        if (0 > move.y  || move.y > 5){
            return false;
        };
    };
    return true;
}

// -------------------------Main Function---------------------------------------

/**
 * \fn void run_tests_ai()
 * \brief Lance toutes les fonctions de ai.test.c et dit quand celui-ci a une 
 * erreur 
*/
void run_tests_ai() {
    printf("Lancement des tests de ai.h");
    bool allTestsPassedAi = true;
    GameState game;

    if (!testFindBestMove(game)) {
        allTestsPassedAi = false;
        printf("Le test de findBestMove a trouvé une erreur");
    }

    if (allTestsPassedAi) {
        printf("Tous les tests ont réussi.\n");
    }
}
