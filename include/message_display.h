/*
 * Ce fichier contient des fonctions affichant des messages à l'utilisateur sur 
 * la fin de jeu, les erreurs et le réseau.
 */

#ifndef ERROR_MESSAGE_DISPLAY_H
#define ERROR_MESSAGE_DISPLAY_H

// -------------------------Prototypes------------------------------------------

// ----- Endgame

/**
 * \fn void displayVictoryMessage(char player)
 * \brief Affiche un message de victoire pour le joueur spécifié.
 * 
 * Cette fonction permet d'afficher un message de victoire pour le joueur 
 * spécifié. Le message indique le joueur gagnant en utilisant son caractère de 
 * joueur.
 * 
 * \param player Le caractère du joueur gagnant.
 */
void displayVictoryMessage(char player);

/**
 * \fn void displayEqualityMessage()
 * \brief Affiche un message d'égalité.
 * 
 * Cette fonction permet d'afficher un message d'égalité, indiquant que la 
 * partie s'est terminée sans qu'aucun joueur ne gagne.
 */
void displayEqualityMessage();

// ----- Errors

/**
 * \fn void displayErrorInvalidMove()
 * \brief Affiche un message d'erreur indiquant un coup invalide.
 * 
 * Cette fonction permet d'afficher un message d'erreur indiquant qu'un coup 
 * invalide a été tenté par un joueur. Le message invite le joueur à réessayer.
 */
void displayErrorInvalidMove();

/**
 * \fn void displayErrorCellOccupied()
 * \brief Affiche un message d'erreur indiquant qu'une case est déjà occupée.
 * 
 * Cette fonction permet d'afficher un message d'erreur indiquant qu'une case 
 * du plateau de jeu est déjà occupée par un pion. Le message invite le joueur 
 * à réessayer.
 */
void displayErrorCellOccupied();

// ----- Network

/**
 * \fn void displayWaitingClientConnexionMessage()
 * \brief Affiche un message indiquant l'attente d'une connexion client.
 * 
 * Cette fonction permet d'afficher un message indiquant que le serveur est en 
 * attente de la connexion d'un client. Le message informe les utilisateurs que 
 * le serveur est prêt à accepter une connexion entrante.
 */
void displayWaitingClientConnexionMessage();

/**
 * \fn void displaySuccessfulConnexionToClientMessage()
 * \brief Affiche un message indiquant que la connexion au client a réussi.
 * 
 * Cette fonction permet d'afficher un message indiquant que la connexion au 
 * client a été établie avec succès. Le message informe les utilisateurs que le 
 * jeu va maintenant être lancé.
 */
void displaySuccessfulConnexionToClientMessage();

/**
 * \fn void displayTryToConnectToServerMessage(char *serverIP)
 * \brief Affiche un message d'essai de connexion au serveur avec une adresse 
 * IP spécifiée.
 * 
 * Cette fonction permet d'afficher un message indiquant qu'une tentative de 
 * connexion au serveur est en cours. Le message affiche l'adresse IP du 
 * serveur à laquelle la connexion est tentée.
 * 
 * \param serverIP L'adresse IP du serveur auquel la connexion est tentée.
 */
void displayTryToConnectToServerMessage(char *serverIP);

/**
 * \fn void displaySuccessfulConnexionToServerMessage()
 * \brief Affiche un message indiquant que la connexion au serveur a réussi.
 * 
 * Cette fonction permet d'afficher un message indiquant que la connexion au 
 * serveur a été établie avec succès. Le message informe les utilisateurs que 
 * le jeu va maintenant être lancé.
 */
void displaySuccessfulConnexionToServerMessage();

/**
 * \fn void displayWaitingOpponentMessage()
 * \brief Affiche un message indiquant l'attente du coup de l'adversaire.
 * 
 * Cette fonction permet d'afficher un message indiquant que le joueur est en 
 * attente du coup de son adversaire. Le message informe les utilisateurs que 
 * c'est le tour de l'adversaire de jouer.
 */
void displayWaitingOpponentMessage();

/**
 * \fn void displayWaitingAIMessage()
 * \brief Affiche un message indiquant l'attente de l'IA en train de choisir un 
 * coup.
 * 
 * Cette fonction permet d'afficher un message indiquant que l'IA est en train 
 * de choisir un coup à jouer. Le message informe les utilisateurs que c'est le 
 * tour de l'IA de prendre une décision.
 */
void displayWaitingAIMessage();

/**
 * \fn void displayMoveSentToOpponent(char *sentMove)
 * \brief Affiche le coup joué envoyé à l'adversaire.
 * 
 * Cette fonction permet d'afficher le coup qui a été joué et envoyé à 
 * l'adversaire sous forme d'un message. Le message informe les utilisateurs du 
 * coup qui a été transmis à l'adversaire.
 * 
 * \param sentMove Le coup joué qui a été envoyé à l'adversaire.
 */
void displayMoveSentToOpponent(char *sentMove);

/**
 * \fn void displayOpponentMoveMessage(char *opponentMove)
 * \brief Affiche le coup joué par l'adversaire.
 * 
 * Cette fonction permet d'afficher le coup qui a été joué par l'adversaire 
 * sous forme d'un message. Le message informe les utilisateurs du coup joué 
 * par l'adversaire.
 * 
 * \param opponentMove Le coup joué par l'adversaire.
 */
void displayOpponentMoveMessage(char *opponentMove);

/**
 * \fn void displayClosedConnexionMessage()
 * \brief Affiche un message indiquant la fermeture de la connexion.
 * 
 * Cette fonction permet d'afficher un message indiquant que la connexion a été 
 * fermée. Le message informe les utilisateurs que la connexion a été 
 * interrompue ou fermée.
 */
void displayClosedConnexionMessage();

#endif
