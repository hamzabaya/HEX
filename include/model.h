/**
 * \file model.h
 * \brief Fichier responsable de la logique du jeu.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Ce fichier contient des fonctions permettant d'effectuer des actions simples 
 * sur le jeu comme initialiser le plateau, vérifier des données, placer un   
 * coup etc...
 */

#ifndef MODEL_H
#define MODEL_H

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdbool.h>
// ----- Internal files
#include "./shared_structures.h"
// ----- Game parameters
#include "./constants.h"

// -------------------------Structures------------------------------------------

/**
* \struct GameState
* \brief Représente l'état du jeu (plateau, joueur actif et numéro du tour)
*/
typedef struct {
    /*! Plateau des coups */
    char board[GRID_SIZE][GRID_SIZE];
    /*! Joueur actif */
    char currentPlayer;
    /*! Numéro du tour */
    int turnNumber;
} GameState;

// -------------------------Prototypes------------------------------------------

/**
 * \fn void initializeGame(GameState *game)
 * \brief Initialise le modèle de jeu en réinitialisant le plateau et en 
 * définissant le joueur actif et le numéro de tour.
 * 
 * Cette fonction initialise le modèle de jeu en réinitialisant le plateau du 
 * jeu en le remplissant d'espaces vides.
 * Elle définit également le joueur actif comme le joueur 1 (PLAYER_1) et 
 * initialise le numéro de tour à 1.
 * 
 * \param game Un pointeur vers la structure GameState pour initialiser le jeu.
 */
void initializeGame(GameState *game);

/**
 * \fn bool moveInField(Coordinates move)
 * \brief Vérifie si les coordonnées du coup se trouvent dans les limites du 
 * terrain de jeu.
 * 
 * Cette fonction vérifie si les coordonnées du coup spécifié se trouvent à 
 * l'intérieur des limites du terrain de jeu.
 * Elle retourne `true` si les coordonnées sont valides et à l'intérieur du 
 * terrain, sinon `false`.
 * 
 * \param move Les coordonnées du coup à vérifier.
 * \return `true` si les coordonnées sont valides et à l'intérieur du terrain, 
 * sinon `false`.
 */
bool moveInField(Coordinates move);

/**
 * \fn bool moveTaken(GameState game, Coordinates move)
 * \brief Vérifie si la case du plateau est déjà occupée par un pion.
 * 
 * Cette fonction vérifie si la case du plateau aux coordonnées spécifiées par 
 * `move` est déjà occupée par un pion.
 * Elle retourne `true` si la case est occupée (non vide) et `false` sinon.
 * 
 * \param game L'état actuel du jeu.
 * \param move Les coordonnées de la case à vérifier.
 * \return `true` si la case est déjà occupée, sinon `false`.
 */
bool moveTaken(GameState game, Coordinates move);

/**
 * \fn void makeMove(GameState *game, Coordinates move)
 * \brief Place un pion du joueur actif sur le plateau aux coordonnées 
 * spécifiées.
 * 
 * Cette fonction permet au joueur actif de placer un pion sur le plateau du 
 * jeu aux coordonnées spécifiées par `move`.
 * Elle met à jour le plateau en plaçant le pion du joueur actif à ces 
 * coordonnées.
 * 
 * \param game Un pointeur vers l'état actuel du jeu.
 * \param move Les coordonnées où le pion du joueur actif doit être placé.
 */
void makeMove(GameState *game, Coordinates move);

/**
 * \fn void convertCoordinatesFrom00ToA1(Coordinates move, char *moveA1Format)
 * \brief Convertit des coordonnées du format "00" au format "A1".
 * 
 * Cette fonction convertit les coordonnées spécifiées au format "00" (indices 
 * 0-based) en coordonnées au format "A1" (indices 1-based).
 * Elle remplit la chaîne `moveA1Format` avec les coordonnées converties.
 * 
 * \param move Les coordonnées à convertir du format "00".
 * \param moveA1Format Un pointeur vers une chaîne de caractères pour stocker 
 * les coordonnées converties au format "A1".
 */
void convertCoordinatesFrom00ToA1(Coordinates move, char *moveA1Format);

/**
 * \fn void copyGameState(GameState *destination, const GameState *source)
 * \brief Copie l'état de jeu source dans la destination.
 *
 * Cette fonction effectue une copie de l'état de jeu source dans la 
 * destination en utilisant la fonction `memcpy`.
 * 
 * \param destination Le pointeur vers l'état de jeu de destination.
 * \param source Le pointeur vers l'état de jeu source à copier.
 */
void copyGameState(GameState *destination, const GameState *source);

#endif
