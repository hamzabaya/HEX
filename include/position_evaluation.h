/**
 * \file position_evaluation.h
 * \brief Fichier contenant la fonction d'évaluation de l'IA.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient la fonction permettant d'évaluer une position de jeu 
 * donnée selon des critères subjectifs.
 */

#ifndef POSITION_EVALUATION_H
#define POSITION_EVALUATION_H

// -------------------------Libraries-------------------------------------------

// ----- Internal files
#include "./model.h"
// ----- Game parameters
#include "./constants.h"

// -------------------------Prototypes------------------------------------------


/**
 * \fn int evaluatePosition(GameState game)
 * \brief Évalue la position actuelle du jeu en utilisant une approche basée 
 * sur des critères spécifiques.
 * 
 * Cette fonction évalue la position actuelle du jeu en utilisant une approche 
 * basée sur des critères spécifiques. Plus le score renvoyé est élevé, plus la 
 * position est forte pour le joueur actuel.
 * 
 * \param game L'état actuel du jeu.
 * \param depthLeft La profondeur de recherche restante.
 * \return Le score d'évaluation de la position.
 */
int evaluatePosition(GameState game, int depthLeft);

#endif
