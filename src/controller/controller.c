/*
 * Controlleur du jeu. C'est lui qui définit le déroulement d'un tour de jeu.   
 * Il est aidé par les modules view et model, auxquels il fait appel. Il gère 
 * également la partie réseau en faisant appel au module réseau.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// ----- Internal files
#include "../../include/ai.h"
#include "../../include/client.h"
#include "../../include/controller.h"
#include "../../include/message_display.h"
#include "../../include/model.h"
#include "../../include/server.h"
#include "../../include/victory_manager.h"
#include "../../include/view.h"
// ----- Game parameters
#include "../../include/constants.h"

// -------------------------Prototypes------------------------------------------

/**
 * \fn static void playLocal(GameState *game, char gameMode, char localSide)
 * \brief Joue une partie en mode local (humain contre humain ou humain contre 
 * IA).
 * 
 * Cette fonction permet de jouer une partie en mode local, où les joueurs 
 * peuvent être humains ou des intelligences artificielles (IA). La fonction 
 * gère les tours des joueurs, les mouvements, et vérifie l'état du jeu pour 
 * déterminer si la partie est terminée.
 * 
 * \param game Un pointeur vers l'état actuel du jeu.
 * \param gameMode Le mode de jeu (humain contre humain, humain contre IA, IA 
 * contre IA).
 * \param localSide Le côté local (BLUE ou RED) pour les joueurs humains en 
 * mode local.
 */
static void playLocal(GameState *game, char gameMode, char localSide);

/**
 * \fn static void playOnline(GameState *game, char gameMode, char onlineSide, 
 *                           char *serverIP, int port)
 * \brief Gère le jeu en mode en ligne (serveur ou client).
 * 
 * Cette fonction gère le jeu en mode en ligne, que ce soit en tant que 
 * serveur ou client. Elle configure la connexion en appelant 
 * `configureConnexion` 
 * pour établir la communication avec l'autre joueur. Ensuite, elle gère 
 * alternativement les tours des joueurs jusqu'à la fin du jeu. En fonction du 
 * côté en ligne (serveur ou client) et du joueur actuel, elle attend les 
 * mouvements de l'adversaire ou permet au joueur actuel de faire son 
 * mouvement. 
 * Elle envoie et reçoit les coups joués et met à jour le plateau de jeu 
 * en conséquence. Elle détecte également la fin du jeu en appelant 
 * `manageEndgame`.
 * 
 * \param game Un pointeur vers l'état actuel du jeu.
 * \param gameMode Le mode de jeu (HUMAN ou IA).
 * \param onlineSide Le côté du réseau (SERVER ou CLIENT).
 * \param serverIP L'adresse IP du serveur en mode en ligne.
 * \param port Le port utilisé pour la communication en mode en ligne.
 */
static void playOnline(GameState *game, char gameMode, char onlineSide, 
                       char *serverIP, int port);

/**
 * \fn static void configureConnexion(int *serverSocket, int *clientSocket, 
 * char onlineSide, char *serverIP, int port)
 * \brief Configure la connexion en mode en ligne (serveur ou client).
 * 
 * Cette fonction configure la connexion en mode en ligne en fonction du rôle 
 * (serveur ou client) spécifié par `onlineSide`. Si le jeu est configuré en 
 * tant que serveur, elle démarre un serveur sur le port spécifié par `port`, 
 * affiche l'adresse IP du serveur, attend qu'un client se connecte, et affiche 
 * un message de connexion réussie au client. Si le jeu est configuré en tant 
 * que client, elle affiche un message de tentative de connexion au serveur, se 
 * connecte au serveur distant en utilisant l'adresse IP spécifiée par 
 * `serverIP` et le port spécifié par `port`, puis affiche un message de 
 * connexion réussie au serveur.
 * 
 * \param serverSocket Un pointeur vers la variable qui stockera le socket du 
 * serveur (pour le serveur) ou le socket du client (pour le client).
 * \param clientSocket Un pointeur vers la variable qui stockera le socket du 
 * client (pour le serveur) ou le socket du serveur (pour le client).
 * \param onlineSide Le côté en ligne (SERVEUR ou CLIENT).
 * \param serverIP L'adresse IP du serveur distant (pour le client).
 * \param port Le port à utiliser pour la communication en mode en ligne.
 */
static void configureConnexion(int *serverSocket, int *clientSocket, char 
                               onlineSide, char *serverIP, int port);

/**
 * \fn static void closeConnexion(int *serverSocket, int *clientSocket, char 
 * onlineSide)
 * \brief Ferme la connexion avec le serveur/client en fonction du côté 
 * spécifié (serveur ou client).
 * 
 * Cette fonction ferme la connexion réseau en fonction du côté spécifié 
 * (serveur ou client) pour le jeu en ligne.
 * Elle ferme la connexion client et/ou le serveur en fonction de la valeur de 
 * `onlineSide`.
 * 
 * \param serverSocket Un pointeur vers le socket du serveur (pour le serveur).
 * \param clientSocket Un pointeur vers le socket du client (pour le client).
 * \param onlineSide Le côté spécifié pour la connexion (SERVER ou CLIENT).
 */
static void closeConnexion(int *serverSocket, int *clientSocket, char 
                           onlineSide);

/**
 * \fn static void makeAIChooseMove(GameState game, Coordinates *move)
 * \brief Fait choisir un mouvement par l'intelligence artificielle en fonction 
 * de l'état du jeu.
 * 
 * Cette fonction fait choisir un mouvement par l'intelligence artificielle en 
 * fonction de l'état actuel du jeu.
 * Elle utilise l'algorithme de recherche pour déterminer le meilleur coup à 
 * jouer et retourne les coordonnées du mouvement dans le paramètre `move`.
 * 
 * \param game L'état actuel du jeu.
 * \param move Un pointeur vers les coordonnées du mouvement choisi par l'IA 
 * (résultat de la fonction).
 */
static void makeAIChooseMove(GameState game, Coordinates *move);

/**
 * \fn static void makeActivePlayerChooseMove(GameState game, Coordinates 
 * *move, bool 
 * *inputError)
 * \brief Permet au joueur actif de choisir un coup et indique s'il est 
 * invalide.
 * 
 * Cette fonction permet au joueur actif de choisir un coup en fonction de 
 * l'état actuel du jeu.
 * Elle vérifie si le coup est valide en vérifiant si les coordonnées sont dans 
 * les limites du plateau et si la case n'est pas déjà occupée par un pion.
 * Elle indique si le coup est invalide en modifiant la valeur de `inputError` 
 * en conséquence.
 * 
 * \param game L'état actuel du jeu.
 * \param move Un pointeur vers les coordonnées du mouvement choisi par le 
 * joueur actif (résultat de la fonction).
 * \param inputError Un pointeur vers une variable booléenne qui indique si une 
 * erreur d'entrée a été détectée.
 */
static void makeActivePlayerChooseMove(GameState game, Coordinates *move, 
                                       bool *inputError);

/**
 * \fn static void manageEndgame(GameState game, bool *endgame)
 * \brief Vérifie si la fin du jeu est atteinte et affiche les messages de fin 
 * de jeu appropriés.
 * 
 * Cette fonction vérifie si la fin du jeu est atteinte en examinant l'état 
 * actuel du jeu.
 * Elle affiche les messages de fin de jeu appropriés en cas de victoire ou 
 * d'égalité.
 * Elle modifie la valeur de `endgame` pour indiquer si la partie est terminée.
 * 
 * \param game L'état actuel du jeu.
 * \param endgame Un pointeur vers une variable booléenne qui indique si la 
 * partie est terminée (résultat de la fonction).
 */
static void manageEndgame(GameState game, bool *endgame);

/**
 * \fn static void changeTurn(GameState *game)
 * \brief Passe au prochain tour en changeant le joueur actif et en 
 * incrémentant le numéro de tour.
 * 
 * Cette fonction permet de passer au prochain tour en changeant le joueur 
 * actif dans l'état du jeu et en incrémentant le numéro de tour.
 * Elle met à jour le joueur actif en fonction du joueur actuel (PLAYER_1 ou 
 * PLAYER_2).
 * 
 * \param game Un pointeur vers l'état actuel du jeu.
 */
static void changeTurn(GameState *game);

// -------------------------Body------------------------------------------------

void initializeAndPlayGame(char communicationMode, char onlineSide, 
                           char *serverIP, int port, char localSide) {
    GameState game;
    initializeGame(&game);

    char gameMode = getGameMode(communicationMode);
    
    if (communicationMode == LOCAL) {
        playLocal(&game, gameMode, localSide);
    } else if (communicationMode == ONLINE) {
        playOnline(&game, gameMode, onlineSide, serverIP, port);
    }
}

static void playLocal(GameState *game, char gameMode, char localSide) {
    bool endgame = false;
    displayBoard(game->board);
    while (!endgame) {
        displayTurnInfo(game->turnNumber, game->currentPlayer);
        Coordinates move;
        bool inputError = false;
        if (gameMode == AI_AI || (gameMode == AI &&
            ((game->currentPlayer == PLAYER_2 && localSide == BLUE) ||
            (game->currentPlayer == PLAYER_1 && localSide == RED)))) {
            makeAIChooseMove(*game, &move);
            displayWaitingAIMessage();
            sleep(10);
        } else {
            makeActivePlayerChooseMove(*game, &move, &inputError);
        }

        if (!inputError) {
            makeMove(game, move);
            displayBoard(game->board);

            manageEndgame(*game, &endgame);

            if (!endgame) {
                changeTurn(game);
            }
        }
    }
}

static void playOnline(GameState *game, char gameMode, char onlineSide, 
                       char *serverIP, int port) {
    int serverSocket = -1;
    int clientSocket = -1;
    configureConnexion(&serverSocket, &clientSocket, onlineSide, serverIP, 
                      port);

    bool endgame = false;
    displayBoard(game->board);
    while (!endgame) {
        displayTurnInfo(game->turnNumber, game->currentPlayer);
        Coordinates thisTurnMove;
        if ((onlineSide == SERVER && game->currentPlayer == PLAYER_1) || 
            (onlineSide == CLIENT && game->currentPlayer == PLAYER_2)) {
            // Tour adverse
            displayWaitingOpponentMessage();

            char opponentData[1024];
            
            if (onlineSide == SERVER) {
                receiveDataFromClient(clientSocket, opponentData, sizeof
                (opponentData));
            } else {
                receiveDataFromServer(clientSocket, opponentData, sizeof
                (opponentData));
            }

            thisTurnMove.x = opponentData[0] - '0';
            thisTurnMove.y = opponentData[1] - '0';

            char thisTurnMoveA1Format[3];
            convertCoordinatesFrom00ToA1(thisTurnMove, thisTurnMoveA1Format);
            displayOpponentMoveMessage(thisTurnMoveA1Format);

            makeMove(game, thisTurnMove);
            displayBoard(game->board);
        } else { // Notre tour
            bool inputError = false;
            if (gameMode == AI) {
                makeAIChooseMove(*game, &thisTurnMove);
                displayWaitingAIMessage();
                sleep(10);
            } else {
                makeActivePlayerChooseMove(*game, &thisTurnMove, &inputError);
            }

            if (inputError) {
                continue;
            }

            makeMove(game, thisTurnMove);
            char moveToSend[3];
            sprintf(moveToSend, "%d%d", thisTurnMove.x, thisTurnMove.y);

            if (onlineSide == SERVER) {
                sendDataToClient(clientSocket, moveToSend);
            } else {
                sendDataToServer(clientSocket, moveToSend);
            }

            char thisTurnMoveA1Format[3];
            convertCoordinatesFrom00ToA1(thisTurnMove, thisTurnMoveA1Format);
            displayMoveSentToOpponent(thisTurnMoveA1Format);
            displayBoard(game->board);
        }

        manageEndgame(*game, &endgame);

        if (!endgame) {
            changeTurn(game);
        }
    }

    closeConnexion(&serverSocket, &clientSocket, onlineSide);
}

static void configureConnexion(int *serverSocket, int *clientSocket, char 
                               onlineSide, char *serverIP, int port) {
    if (onlineSide == SERVER) {
        *serverSocket = startServer(port);

        displayServerIP();
        displayWaitingClientConnexionMessage();

        *clientSocket = acceptConnection(*serverSocket);
        displaySuccessfulConnexionToClientMessage();
    } else {
        displayTryToConnectToServerMessage(serverIP);
        *clientSocket = connectToServer(serverIP, port);
        displaySuccessfulConnexionToServerMessage();
    }
}

static void closeConnexion(int *serverSocket, int *clientSocket, char 
                           onlineSide) {
    if (onlineSide == SERVER) {
        serverCloseConnection(*clientSocket); // Fermer la connexion client
        serverCloseConnection(*serverSocket); // Fermer le serveur
    } else {
        clientCloseConnection(*clientSocket); // Fermer la connexion client
    }
    displayClosedConnexionMessage();
}

static void makeAIChooseMove(GameState game, Coordinates *move) {
    *move = findBestMove(game);
}

static void makeActivePlayerChooseMove(GameState game, Coordinates *move, 
                                       bool *inputError) {
    *move = getPlayerMove(game.currentPlayer);

    if (!moveInField(*move)) {
        displayErrorInvalidMove();
        *inputError = true;
        return;
    }

    if (moveTaken(game, *move)) {
        displayErrorCellOccupied();
        *inputError = true;
        return;
    }
}

static void manageEndgame(GameState game, bool *endgame) {
    if (victory(game)) { // Victoire
        displayVictoryMessage(game.currentPlayer);
        *endgame = true;
        return;
    } else if (game.turnNumber == NB_CELLS) { // Égalité
        displayEqualityMessage();
        *endgame = true;
        return;
    }
}

static void changeTurn(GameState *game) {
    if (game->currentPlayer == PLAYER_1) {
        game->currentPlayer = PLAYER_2;
    } else {
        game->currentPlayer = PLAYER_1;
    }
    game->turnNumber++;
}
