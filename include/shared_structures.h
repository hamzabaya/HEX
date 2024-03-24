/**
 * \file shared_structures.h
 * \brief Fichier contenant les structures partagées par la plupart des  
 * fichiers.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Fichier contenant les structures utilisées par la plupart des 
 * fichiers, qui doivent être partagées à tous.
 */

#ifndef SHARED_STRUCTURES_H
#define SHARED_STRUCTURES_H

// -------------------------Structures------------------------------------------

/**
* \struct Coordinates
* \brief Représente des coordonnées (x correspond aux colonnes, y aux lignes, 
* le 00 est en haut à gauche)
*/
typedef struct {
    /*! Indice des colonnes */
    int x;
    /*! Indice des lignes */
    int y;
} Coordinates;

#endif
