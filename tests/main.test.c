// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
#include <stdio.h>
// ----- Internal files
#include "../include/ai.test.h"
#include "../include/position_evaluation.test.h"
#include "../include/controller.test.h"
#include "../include/model.test.h"
#include "../include/victory_manager.test.h"
#include "../include/message_display.test.h"
#include "../include/view.test.h"

// -------------------------Main Function---------------------------------------

/**
 * \fn void main()
 * \brief Appelle toutes les fonctions run_tests_*
 */
int main()
{
    run_tests_ai();
    run_tests_position_evaluation();
    run_tests_model();
    run_tests_victory_manager();
    run_tests_controller();
    run_tests_message_display();
    run_tests_view();
        return 0;
}
