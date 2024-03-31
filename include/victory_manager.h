/*
 * Ce fichier contient des fonctions permettant de vérifier la victoire.
 */

#ifndef ENDGAME_MANAGER_H
#define ENDGAME_MANAGER_H

// -------------------------Libraries-------------------------------------------

// ----- Internal files
#include "./model.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn bool victory(GameState game)
 * \brief Vérifie si la partie est terminée avec une victoire pour le joueur 
 * actif.
 * 
 * Cette fonction vérifie si la partie est terminée avec une victoire pour le 
 * joueur actif (PLAYER_1 ou PLAYER_2).
 * Elle parcourt le plateau pour trouver un pion du joueur actif dans une 
 * position stratégique et vérifie si ce pion peut atteindre le bord opposé.
 * Si un tel chemin existe, la fonction retourne `true`, indiquant une 
 * victoire, sinon elle retourne `false`.
 * 
 * \param game L'état actuel du jeu.
 * \return `true` si la partie est terminée avec une victoire pour le joueur 
 * actif, sinon `false`.
 */
bool victory(GameState game);

/**
 * \fn bool player1Victory(GameState game)
 * \brief Détermine si le joueur 1 a remporté la partie.
 *
 * Cette fonction vérifie si le joueur 1 (représenté par 'X' sur le plateau) a 
 * remporté la partie en
 * vérifiant s'il existe un chemin depuis l'une des positions de la première 
 * colonne jusqu'au bord droit du plateau.
 * 
 * \param game L'état actuel du jeu à évaluer.
 * \return true si le joueur 1 a gagné la partie, sinon false.
 */
bool player1Victory(GameState game);

/**
 * \fn bool player2Victory(GameState game)
 * \brief Détermine si le joueur 2 a remporté la partie.
 *
 * Cette fonction vérifie si le joueur 2 (représenté par 'O' sur le plateau) a remporté la partie en
 * vérifiant s'il existe un chemin depuis l'une des positions de la première ligne jusqu'au bord inférieur du plateau.
 * 
 * \param game L'état actuel du jeu à évaluer.
 * \return true si le joueur 2 a gagné la partie, sinon false.
 */
bool player2Victory(GameState game);

#endif
