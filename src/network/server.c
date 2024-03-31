/*
 * Ce fichier contient toutes les fonctions nécéssaires à la connexion au  
 * réseau côté serveur.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ----- Internal files
#include "../../include/server.h"

// -------------------------Body------------------------------------------------

int startServer(int port) {
    int serverSocket;
    struct sockaddr_in serverAddr;

    // Création du socket TCP
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Liaison du socket à l'adresse
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) 
       == -1) {
        perror("Erreur lors de la liaison du socket");
        exit(EXIT_FAILURE);
    }

    // Mise du socket en mode écoute
    if (listen(serverSocket, 5) == -1) {
        perror("Erreur lors de la mise en mode écoute du socket");
        exit(EXIT_FAILURE);
    }

    return serverSocket;
}

void displayServerIP() {
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;

    if (getifaddrs(&ifap) == -1) {
        perror("Erreur lors de la récupération des informations sur les "
        "interfaces réseau");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL || (ifa->ifa_flags & IFF_UP) == 0 || 
        (ifa->ifa_flags & IFF_LOOPBACK) != 0) {
            continue; // Ignore les interfaces inactives ou de bouclage
        }

        if (ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *)ifa->ifa_addr;
            printf("Adresse IP du serveur : %s\n", inet_ntoa(sa->sin_addr));
        }
    }

    freeifaddrs(ifap);
}

int acceptConnection(int serverSocket) {
    int clientSocket;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Accepter une connexion entrante
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, 
                         &clientAddrLen);
    if (clientSocket == -1) {
        perror("Erreur lors de l'acceptation de la connexion");
        exit(EXIT_FAILURE);
    }

    return clientSocket;
}

int receiveDataFromClient(int clientSocket, char *buffer, int bufferSize) {
    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived == -1) {
        perror("Erreur lors de la réception des données");
        exit(EXIT_FAILURE);
    }
    buffer[bytesReceived] = '\0'; // Ajouter un terminateur nul
    return bytesReceived;
}

int sendDataToClient(int clientSocket, const char *data) {
    int bytesSent = send(clientSocket, data, strlen(data), 0);
    if (bytesSent == -1) {
        perror("Erreur lors de l'envoi des données");
        exit(EXIT_FAILURE);
    }
    return bytesSent;
}

void serverCloseConnection(int socket) {
    close(socket);
}
