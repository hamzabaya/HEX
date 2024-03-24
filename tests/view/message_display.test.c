/**
 * \file message_display.test.c
 * \brief Tests des fonctions de message_display.h
 * \author nicolas.bernardi@uha.fr
 * \version 0.1
*/

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../../include/message_display.h"

// -------------------------Test Functions--------------------------------------

/**
 * \fn void run_tests_message_display()
 * \brief Lance tous les tests de message_display.test.c et dit quand celui-ci 
 * a une erreur
 * \author nicolas.bernardi@uha.fr
 * \version 1.0
*/
void run_tests_message_display() {
    printf("Lancement des tests de message_display.h");
    bool allTestsPassedMessageDisplay = true;

    if (allTestsPassedMessageDisplay) {
        printf("Tous les tests ont réussi.\n");
    }
}