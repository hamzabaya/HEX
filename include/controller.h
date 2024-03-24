/**
 * \file controller.h
 * \brief Controlleur du jeu.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Controlleur du jeu. C'est lui qui définit le déroulement d'un tour de jeu.  
 * Il est aidé par les modules view et model, auxquels il fait appel. Il gère 
 * également la partie réseau en faisant appel au module réseau.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

// -------------------------Prototypes------------------------------------------

/**
 * \fn void initializeAndPlayGame(char communicationMode, char onlineSide, 
 *                                char *serverIP, int port, char localSide)
 * \brief Initialise le jeu et démarre la partie en fonction du mode de 
 * communication.
 * 
 * Cette fonction initialise le jeu en créant une instance de `GameState` et 
 * en appelant `initializeGame` pour réinitialiser le plateau. Ensuite, elle 
 * démarre la partie en fonction du mode de communication spécifié. Si le mode 
 * est local (`communicationMode == LOCAL`), la partie est jouée en mode 
 * local en appelant `playLocal`. Si le mode est en ligne (`communicationMode 
 * == ONLINE`), la partie est jouée en mode en ligne en appelant `playOnline`. 
 * Dans ce dernier cas, les paramètres `onlineSide`, `serverIP`, et `port` sont 
 * utilisés pour configurer la connexion en ligne.
 * 
 * \param communicationMode Le mode de communication, soit LOCAL soit ONLINE.
 * \param onlineSide Le côté du réseau (SERVER ou CLIENT) en mode en ligne.
 * \param serverIP L'adresse IP du serveur en mode en ligne.
 * \param port Le port utilisé pour la communication en mode en ligne.
 * \param localSide Le côté local (BLUE ou RED) en mode local.
 */
void initializeAndPlayGame(char communicationMode, char onlineSide, 
                           char *serverIP, int port, char localSide);

#endif
