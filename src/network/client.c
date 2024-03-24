/**
 * \file client.c
 * \brief Fichier responsable de la partie client du réseau.
 * \author simon.antropius@uha.fr
 * \author romain.bomba@uha.fr
 * \version 0.1
 *
 * Ce fichier contient toutes les fonctions nécéssaires à la connexion au 
 * réseau côté client.
 */

// -------------------------Libraries-------------------------------------------

// ----- Standard libraries
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// ----- Internal files
#include "../../include/client.h"

// -------------------------Body------------------------------------------------

int connectToServer(const char *serverIp, int port) {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Création du socket TCP
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);
    serverAddr.sin_port = htons(port);

    // Connection au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof
               (serverAddr)) == -1) {
        perror("Erreur lors de la connexion au serveur");
        exit(EXIT_FAILURE);
    }

    return clientSocket;
}

int receiveDataFromServer(int clientSocket, char *buffer, int bufferSize) {
    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived == -1) {
        perror("Erreur lors de la réception des données");
        exit(EXIT_FAILURE);
    }
    buffer[bytesReceived] = '\0'; // Ajouter un terminateur nul
    return bytesReceived;
}

int sendDataToServer(int clientSocket, const char *data) {
    int bytesSent = send(clientSocket, data, strlen(data), 0);
    if (bytesSent == -1) {
        perror("Erreur lors de l'envoi des données");
        exit(EXIT_FAILURE);
    }
    return bytesSent;
}

void clientCloseConnection(int socket) {
    close(socket);
}
