/*
 * Ce fichier contient toutes les fonctions nécéssaires à la connexion au 
 * réseau côté client.
 */

#ifndef CLIENT_H
#define CLIENT_H

// -------------------------Prototypes------------------------------------------

/**
 * \fn int connectToServer(const char *server_ip, int port)
 * \brief Établit une connexion avec un serveur distant via TCP/IP.
 * 
 * Cette fonction crée un socket TCP/IP, configure l'adresse du serveur avec 
 * l'adresse IP spécifiée et le port, puis établit une connexion avec le 
 * serveur distant.
 * En cas d'erreur lors de la création du socket ou de la connexion au serveur, 
 * la fonction génère une erreur et quitte le programme.
 * 
 * \param serverIp L'adresse IP du serveur distant auquel se connecter.
 * \param port Le port du serveur distant auquel se connecter.
 * \return Le descripteur de fichier du socket client pour la connexion établie.
 */
int connectToServer(const char *serverIp, int port);

/**
 * \fn int receiveDataFromServer(int client_socket, char *buffer, int 
 * buffer_size)
 * \brief Reçoit des données du serveur via une connexion client.
 * 
 * Cette fonction permet de recevoir des données du serveur distant via la 
 * connexion client spécifiée. Les données reçues sont stockées dans le tampon 
 * (`buffer`) fourni.
 * En cas d'erreur lors de la réception des données, la fonction génère une 
 * erreur et quitte le programme.
 * 
 * \param clientSocket Le descripteur de fichier du socket client à partir 
 * duquel recevoir les données.
 * \param buffer Un pointeur vers le tampon où stocker les données reçues.
 * \param bufferSize La taille du tampon (`buffer`) en octets.
 * \return Le nombre d'octets de données reçues.
 */
int receiveDataFromServer(int clientSocket, char *buffer, int bufferSize);

/**
 * \fn int sendDataToServer(int clientSocket, const char *data)
 * \brief Envoie des données au serveur via une connexion client.
 * 
 * Cette fonction permet d'envoyer des données spécifiées (`data`) au serveur 
 * distant via la connexion client spécifiée. Les données sont envoyées en 
 * utilisant le socket client.
 * En cas d'erreur lors de l'envoi des données, la fonction génère une erreur 
 * et quitte le programme.
 * 
 * \param clientSocket Le descripteur de fichier du socket client à travers 
 * lequel envoyer les données.
 * \param data Un pointeur vers les données à envoyer au serveur.
 * \return Le nombre d'octets de données envoyées.
 */
int sendDataToServer(int clientSocket, const char *data);

/**
 * \fn void clientCloseConnection(int socket)
 * \brief Ferme le côté client d'une connexion réseau.
 * 
 * Cette fonction permet de fermer le côté client d'une connexion réseau en 
 * utilisant le descripteur de fichier du socket spécifié. Elle termine la 
 * connexion réseau côté client.
 * 
 * \param socket Le descripteur de fichier du socket client à fermer.
 */
void clientCloseConnection(int socket);

#endif
