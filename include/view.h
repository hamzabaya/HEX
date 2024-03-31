/*
 * Ce fichier contient des fonctions permettant de demander des informations à 
 * l'utilisateur et d'afficher les données de jeu.
 */

#ifndef VIEW_H
#define VIEW_H

// -------------------------Libraries-------------------------------------------

// ----- Internal files
#include "./shared_structures.h"
// ----- Game parameters
#include "./constants.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn char getGameMode(char communicationMode)
 * \brief Demande au joueur de choisir le mode de jeu (humain-humain, 
 * humain-IA, IA-IA).
 * 
 * Cette fonction invite le joueur à choisir le mode de jeu en fonction du mode 
 * de communication (réseau vs local) spécifié en paramètre. En mode local, le 
 * joueur peut choisir entre jouer contre un autre humain (humain), jouer 
 * contre l'IA (IA), ou laisser l'IA jouer contre elle-même (IA-IA). En mode 
 * réseau, le joueur peut choisir de laisser l'IA jouer à sa place (IA) ou de 
 * jouer lui-même (humain).
 * 
 * \param communicationMode Le mode de communication (LOCAL ou ONLINE).
 * \return Le mode de jeu choisi par le joueur ('H' pour humain-humain, 'I' 
 * pour humain-IA, 'B' pour IA-IA en mode local, 'I' pour IA vs humain, 'H' 
 * pour humain vs humain en mode réseau).
 */
char getGameMode(char communicationMode);

/**
 * \fn char* getServerIP()
 * \brief Demande à l'utilisateur d'entrer l'adresse IP du serveur auquel se 
 * connecter.
 * 
 * Cette fonction invite l'utilisateur à entrer l'adresse IP du serveur auquel 
 * il souhaite se connecter. Elle alloue dynamiquement de la mémoire pour 
 * stocker cette adresse IP et la retourne sous forme de chaîne de caractères.
 * 
 * \return L'adresse IP du serveur sous forme de chaîne de caractères.
 */
char* getServerIP();

/**
 * \fn void displayBoard(char board[GRID_SIZE][GRID_SIZE])
 * \brief Affiche la grille de jeu avec les pions des joueurs.
 * 
 * Cette fonction affiche la grille de jeu en utilisant le tableau `board` 
 * spécifié, où chaque élément représente l'état d'une cellule de la grille. 
 * Les pions des joueurs sont affichés sous forme de caractères ('X' pour le 
 * joueur 1, 'O' pour le joueur 2) et les cases vides sont représentées par un 
 * point ('.').
 * 
 * \param board Le tableau représentant l'état de la grille de jeu.
 */
void displayBoard(char board[GRID_SIZE][GRID_SIZE]);

/**
 * \fn void displayTurnInfo(int turnNumber, char currentPlayer)
 * \brief Affiche les informations sur le tour en cours.
 * 
 * Cette fonction affiche les informations sur le tour en cours, notamment le 
 * numéro du tour et le joueur actif.
 * 
 * \param turnNumber Le numéro du tour en cours.
 * \param currentPlayer Le caractère représentant le joueur actif ('X' ou 'O').
 */
void displayTurnInfo(int turnNumber, char currentPlayer);

/**
 * \fn Coordinates getPlayerMove(char playerSymbol)
 * \brief Lit le coup joué par un joueur à partir de l'entrée utilisateur.
 * 
 * Cette fonction permet à un joueur spécifié par le symbole `playerSymbol` de 
 * saisir son coup en utilisant le format A1 (par exemple, A1, B2, etc.). Elle 
 * affiche un message invitant le joueur à entrer son coup, lit l'entrée 
 * utilisateur et la convertit en coordonnées internes de la grille (format 00).
 * 
 * \param playerSymbol Le caractère représentant le joueur qui joue ('X' ou 
 * 'O').
 * \return Les coordonnées du coup joué par le joueur au format 00.
 */
Coordinates getPlayerMove(char playerSymbol);

#endif
