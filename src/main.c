/**
 * \file main.c
 * \brief Fichier principal jeu de HEX.
 * \author simon.antropius@uha.fr
 * \version 0.1
 *
 * Fichier principal du jeu. Appelez main pour le lancer.
 * Le jeu s'articule autour d'une architecture MVC (Model-Vue-Controller) à 
 * laquelle on a ajouté une partie réseau. La vue contrôle l'intéraction avec 
 * l'utilisateur, le modèle contient la logique du jeu et le controlleur fait 
 * le lien entre vue et modèle.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ----- Internal files
#include "../include/controller.h"
#include "../include/view.h"

// -------------------------Body------------------------------------------------

/**
 * \brief Point d'entrée principal du jeu HEX.
 *
 * Cette fonction gère le lancement du jeu HEX avec différentes options de 
 * configuration.
 *
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Tableau d'arguments de la ligne de commande.
 *
 * \return 0 si le jeu s'est terminé avec succès, 1 en cas d'erreur d'argument 
 * ou d'exécution.
 *
 * Cette fonction analyse les options de ligne de commande pour configurer le 
 * mode de communication,
 * le côté en ligne (serveur ou client), l'adresse IP du serveur et d'autres 
 * paramètres de jeu en mode local. Elle appelle ensuite la fonction 
 * `initializeAndPlayGame` avec ces paramètres pour lancer le jeu.
 *
 * Exemple d'utilisation :
 * ```
 * ./hex -s pppp               # Mode en ligne, serveur sur le port pppp
 * ./hex -c hh.hh.hh.hh:pppp   # Mode en ligne, client se connectant au serveur 
 *                               hh.hh.hh.hh sur le port pppp 
 *                               (IP locale: 127.0.0.1)
 * ./hex -l bleu               # Mode local, jouer localement en tant que bleu 
 * ./hex -l rouge              # Mode local, jouer localement en tant que rouge
 * ```
 */
int main(int argc, char *argv[]) {
    char communicationMode = NONE;
    char onlineSide = NONE;
    char *serverIP = NULL;
    int port = 0;
    char localSide = NONE;

    int opt;
    while ((opt = getopt(argc, argv, "s:c:l:")) != -1) {
        switch (opt) {
            case 's':
                communicationMode = ONLINE;
                onlineSide = SERVER;
                port = atoi(optarg);
                break;
            case 'c':
                communicationMode = ONLINE;
                onlineSide = CLIENT;
                // Séparation de l'adresse IP et du port de l'argument
                char *colonPos = strchr(optarg, ':');
                if (colonPos != NULL) {
                    *colonPos = '\0';
                    serverIP = optarg;
                    port = atoi(colonPos + 1);
                } else {
                    fprintf(stderr, "Option -c invalide : %s\n", optarg);
                    return 1;
                }
                break;
            case 'l':
                communicationMode = LOCAL;
                if (strcmp(optarg, "bleu") == 0) {
                    localSide = BLUE;
                } else if (strcmp(optarg, "rouge") == 0) {
                    localSide = RED;
                } else {
                    fprintf(stderr, "Option -l invalide : %s\n", optarg);
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Utilisation : %s [-s port] [-c adresse:port] "
                "[-l bleu|rouge]\n", argv[0]);
                return 1;
        }
    }

    printf("Bienvenue dans votre jeu de HEX !\n");

    initializeAndPlayGame(communicationMode, onlineSide, serverIP, port, 
                         localSide);

    printf("Merci d'avoir joué !\n");

    return 0;
}
