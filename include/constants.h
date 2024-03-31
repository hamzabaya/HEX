/*
 * Fichier contenant les constantes du jeu.
 */

#ifndef CONSTANTS
#define CONSTANTS

// -------------------------Constants------------------------------------------

// ----- View --------------------------

#define BLUE_COLOR "\033[34m"
#define RED_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"

// ----- Logic -------------------------

// ----- Grid
#define GRID_SIZE 6
#define NB_CELLS (GRID_SIZE * GRID_SIZE)

// ----- Cells states
#define EMPTY ' '
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define VISITED 'V' // Pour la vérification de victoire

// ----- AI
#define DEPTH 5

// ----- Game mode ---------------------

// ----- Communication mode
#define ONLINE 'O'
#define LOCAL 'L'

// ----- Game mode
#define HUMAN 'H'
#define AI 'I'
#define AI_AI 'T'

// ----- Local side
#define BLUE 'B'
#define RED 'R'

// ----- Online side
#define SERVER 'S'
#define CLIENT 'C'

// ----- Default value -----------------

#define NONE 'N'

#endif
