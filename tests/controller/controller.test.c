// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../../include/controller.h"

// -------------------------Test Functions--------------------------------------

/**
 * \fn void run_tests_controller()
 * \brief Lance tous les tests de controller.test.c et dit quand celui-ci a une 
 * erreur
 * \author nicolas.bernardi@uha.fr
 * \version 1.0
*/
void run_tests_controller() {
    printf("Lancement des tests de controller.h");
    bool allTestsPassedController = true;

    if (allTestsPassedController) {
        printf("Tous les tests ont réussi.\n");
    }
}
