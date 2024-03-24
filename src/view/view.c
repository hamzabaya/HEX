/**
 * \file view.c
 * \brief Fichier responsable de l'interaction avec l'utilisateur.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient des fonctions permettant de demander des informations à 
 * l'utilisateur et d'afficher les données de jeu.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ----- Internal files
#include "../../include/view.h"
// ----- Game parameters
#include "../../include/constants.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn void clearInputBuffer()
 * \brief Vide le tampon d'entrée du clavier.
 * 
 * Cette fonction permet de vider le tampon d'entrée du clavier en consommant 
 * tous les caractères restants jusqu'à la fin de la ligne ou la fin du fichier 
 * (EOF). Cela est utile pour éviter des problèmes de saisie utilisateur 
 * inattendue.
 */
static void clearInputBuffer();

/**
 * \fn Coordinates convertCoordinatesFromA1To00(char *move)
 * \brief Convertit des coordonnées du format A1 au format 00.
 * 
 * Cette fonction prend des coordonnées de coup au format A1 (par exemple, A1, 
 * B2, etc.) en tant que chaîne de caractères et les convertit en coordonnées 
 * internes de la grille au format 00 (par exemple, (0, 0), (1, 1), etc.).
 * 
 * \param move La chaîne de caractères représentant les coordonnées au format 
 * A1.
 * \return Les coordonnées converties au format 00.
 */
static Coordinates convertCoordinatesFromA1To00(char *move);

// -------------------------Body------------------------------------------------

char getGameMode(char communicationMode) {
    char gameMode;

    if (communicationMode == LOCAL) {
        do {
            char input[2];
            printf("Choisissez un mode de jeu (i pour vs IA, h pour vs humain, "
            "t pour IA vs IA): ");
            
            scanf("%1s", input);

            clearInputBuffer();

            gameMode = toupper(input[0]);
        } while (gameMode != HUMAN && gameMode != AI && gameMode != AI_AI);
    } else {
        do {
            char input[2];
            printf("Choisissez un mode de jeu (i pour laisser l'IA jouer, h "
            "pour jouer vous-même): ");
            
            scanf("%1s", input);

            clearInputBuffer();

            gameMode = toupper(input[0]);
        } while (gameMode != HUMAN && gameMode != AI);
    }
    
    return gameMode;
}

char* getServerIP() {
    char input[256]; /* Tableau de caractères pour stocker l'entrée 
    (n'importe quelle taille) */

    printf("Veuillez entrer l'adresse du serveur auquel vous connecter : ");
    scanf("%255s", input); /* Utilisation de %255s pour éviter le dépassement 
    de tampon */

    // Allocation de la mémoire pour stocker l'adresse IP et copie dans serverIP
    char *serverIP = (char *)malloc(strlen(input) + 1); /* +1 pour le caractère 
    nul */
    if (serverIP == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    strcpy(serverIP, input);

    return serverIP;
}

void displayBoard(char board[GRID_SIZE][GRID_SIZE]) {
    printf(" ");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf(RED_COLOR " %c" RESET_COLOR, (char)('A' + i)); // Lettres en bleu
    }
    printf("\n");
    for (int row = 0; row < GRID_SIZE; row++) {
        printf(BLUE_COLOR "%d" RESET_COLOR " ", row + 1); // Chiffres en bleu
        for (int col = 0; col < GRID_SIZE; col++) {
            char cellSymbol = board[col][row] == EMPTY ? '.' : board[col][row];
            if (cellSymbol == PLAYER_1) {
                printf(BLUE_COLOR "%c" RESET_COLOR " ", cellSymbol); /* Couleur 
                bleue */
            } else if (cellSymbol == PLAYER_2) {
                printf(RED_COLOR "%c" RESET_COLOR " ", cellSymbol); /* Couleur 
                rouge */
            } else {
                printf("%c ", cellSymbol);
            }
        }
        printf(BLUE_COLOR "|" RESET_COLOR "\n"); /* Ajout du caractère '|' en 
        bleu avant le retour à la ligne */
    }
    printf(RED_COLOR "  ");
    for (int i = 0; i < 11; i++) {
        printf("_");
    }
    printf("\n\n" RESET_COLOR);
}

void displayTurnInfo(int turnNumber, char currentPlayer) {
    printf("Tour %d - Joueur actif : %c\n\n", turnNumber, currentPlayer);
}

Coordinates getPlayerMove(char playerSymbol) {
    char move[3];
    printf("Joueur %c, entrez votre coup (ex: A1) : ", playerSymbol);
    scanf("%2s", move);

    clearInputBuffer();

    Coordinates coord = convertCoordinatesFromA1To00(move);
    
    return coord;
}

static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static Coordinates convertCoordinatesFromA1To00(char *move) {
    Coordinates coord;
    coord.x = move[0] - 'A';
    coord.y = move[1] - '1';
    return coord;
}

