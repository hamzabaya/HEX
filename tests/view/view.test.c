// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>

// ----- Internal files
#include "../../include/view.h"

// -------------------------Test Functions-------------------------------------


/**
 * \fn bool testGetGameMode()
 * \brief Test de getGameMode qui vérifie si on obtient AI ou HUMAN ou AI_AI
 * \author nicolas.bernardi@uha.fr
 * \version 1.0
*/
bool testGetGameMode() {
    printf("Test de getGameMode...\n");
    char modeLocal = getGameMode(LOCAL);
    printf("Mode de jeu choisi en local : %c\n", modeLocal);
    char modeOnline = getGameMode(ONLINE);
    printf("Mode de jeu online choisi : %c\n", modeOnline);
    if (modeLocal == AI || modeLocal == HUMAN || modeLocal == AI_AI){
        if (modeOnline == AI || modeOnline == HUMAN){
            return true;
        }
    }
    return false;
}

// -------------------------Main Function--------------------------------------

/**
 * \fn void run_tests_view()
 * \brief Lance tous les tests de view.test.c et dit quand celui-ci a une erreur
 * \author nicolas.bernardi@uha.fr
 * \version 1.0
*/

void run_tests_view() {
    printf("Lancement des tests de view.c");
    bool allTestsPassedView = true;

    if (!testGetGameMode()){
        printf("Une erreur est apparue dans getGameMode\n");
        allTestsPassedView = false;
    }

    if (allTestsPassedView) {
        printf("Tous les tests ont réussi.\n");
    }
}
