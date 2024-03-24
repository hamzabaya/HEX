/**
 * \file message_display.c
 * \brief Fichier permettant d'afficher des messages à l'utilisateur.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient des fonctions affichant des messages à l'utilisateur sur 
 * la fin de jeu, les erreurs et le réseau.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdio.h>

// -------------------------Body------------------------------------------------

// ----- Endgame

void displayVictoryMessage(char player) {
    printf("Joueur %c a gagné !\n\n", player);
}

void displayEqualityMessage() {
    printf("Égalité ! Personne ne gagne.\n\n");
}

// ----- Errors

void displayErrorInvalidMove() {
    printf("Coup invalide. Réessayez.\n\n");
}

void displayErrorCellOccupied() {
    printf("Case déjà occupée. Réessayez.\n\n");
}

// ----- Network

void displayWaitingClientConnexionMessage() {
    printf("Attente d'une connexion client...\n");
}

void displaySuccessfulConnexionToClientMessage() {
    printf("Connexion au client réussie. Lancement du jeu.\n\n");
}

void displayTryToConnectToServerMessage(char *serverIP) {
    printf("Essaie de connexion à l'adresse IP suivante : %s\n", serverIP);
}

void displaySuccessfulConnexionToServerMessage() {
    printf("Connexion au serveur réussie. Lancement du jeu.\n\n");
}

void displayWaitingOpponentMessage() {
    printf("Attente du coup de l'adversaire...\n");
}

void displayWaitingAIMessage() {
    printf("IA entrain de choisir un coup...\n");
}

void displayMoveSentToOpponent(char *sentMove) {
    printf("Coup envoyé à l'adversaire : %s\n\n", sentMove);
}

void displayOpponentMoveMessage(char *opponentMove) {
    printf("Coup joué par l'adversaire : %s\n\n", opponentMove);
}

void displayClosedConnexionMessage() {
    printf("Connexion fermée.\n");
}

