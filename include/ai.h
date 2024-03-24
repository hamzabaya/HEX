/**
 * \file ai.h
 * \brief Fichier contenant l'IA du jeu.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient la fonction permettant de trouver le meilleur possible 
 * selon l'IA.
 */

#ifndef AI_H
#define AI_H

// -------------------------Libraries-------------------------------------------

// ----- Internal files
#include "./model.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn Coordinates findBestMove(GameState game)
 * \brief Trouve et retourne le meilleur coup pour le joueur actif en utilisant 
 * notre intelligence artificielle.
 * 
 * Cette fonction détermine le meilleur coup à jouer pour le joueur actif en 
 * utilisant notre algorithme d'intelligence artificielle.
 * 
 * \param game L'état actuel du jeu.
 * 
 * \return Les coordonnées du meilleur coup à jouer.
 */
Coordinates findBestMove(GameState game);

#endif