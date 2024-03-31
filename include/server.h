/*
 * Ce fichier contient toutes les fonctions nécéssaires à la connexion au  
 * réseau côté serveur.
 */

#ifndef SERVER_H
#define SERVER_H

// -------------------------Prototypes------------------------------------------

/**
 * \fn int startServer(int port)
 * \brief Initialise et démarre un serveur TCP/IP sur le port spécifié.
 * 
 * Cette fonction initialise et démarre un serveur TCP/IP en créant un socket 
 * serveur, en configurant son adresse pour écouter sur le port spécifié, en 
 * liant le socket à l'adresse, et en mettant le socket en mode écoute pour 
 * accepter les connexions entrantes.
 * En cas d'erreur lors de l'initialisation ou du démarrage du serveur, la 
 * fonction génère une erreur et quitte le programme.
 * 
 * \param port Le port sur lequel le serveur doit écouter les connexions 
 * entrantes.
 * \return Le descripteur de fichier du socket serveur initialisé et en mode 
 * écoute.
 */
int startServer(int port);

/**
 * \fn void displayServerIP()
 * \brief Affiche l'adresse IP du serveur.
 * 
 * Cette fonction récupère et affiche l'adresse IP du serveur en utilisant la 
 * bibliothèque système pour obtenir les informations sur les interfaces réseau 
 * disponibles. Elle parcourt les interfaces réseau actives et non de bouclage 
 * pour trouver l'adresse IP du serveur, puis l'affiche à l'écran.
 * En cas d'erreur lors de la récupération des informations sur les interfaces 
 * réseau, la fonction génère une erreur et quitte le programme.
 */
void displayServerIP();

/**
 * \fn int acceptConnection(int serverSocket)
 * \brief Accepte une connexion entrante depuis un client sur un socket serveur.
 * 
 * Cette fonction permet d'accepter une connexion entrante depuis un client sur 
 * le socket serveur spécifié. Elle retourne le descripteur de fichier du 
 * socket client nouvellement accepté.
 * En cas d'erreur lors de l'acceptation de la connexion, la fonction génère 
 * une erreur et quitte le programme.
 * 
 * \param serverSocket Le descripteur de fichier du socket serveur à partir 
 * duquel accepter la connexion entrante.
 * \return Le descripteur de fichier du socket client nouvellement accepté.
 */
int acceptConnection(int serverSocket);

/**
 * \fn int receiveDataFromClient(int clientSocket, char *buffer, int bufferSize)
 * \brief Reçoit des données du client via une connexion client-serveur.
 * 
 * Cette fonction permet de recevoir des données du client connecté via une 
 * connexion client-serveur en utilisant le socket client spécifié. Les données 
 * reçues sont stockées dans le tampon (`buffer`) fourni.
 * En cas d'erreur lors de la réception des données, la fonction génère une 
 * erreur et quitte le programme.
 * 
 * \param clientSocket Le descripteur de fichier du socket client à partir 
 * duquel recevoir les données.
 * \param buffer Un pointeur vers le tampon où stocker les données reçues.
 * \param bufferSize La taille du tampon (`buffer`) en octets.
 * \return Le nombre d'octets de données reçues.
 */
int receiveDataFromClient(int clientSocket, char *buffer, int bufferSize);

/**
 * \fn int sendDataToClient(int clientSocket, const char *data)
 * \brief Envoie des données au client via une connexion client-serveur.
 * 
 * Cette fonction permet d'envoyer des données spécifiées (`data`) au client 
 * connecté via une connexion client-serveur en utilisant le socket client 
 * spécifié. Les données sont envoyées au client, et la fonction retourne le 
 * nombre d'octets de données envoyées.
 * En cas d'erreur lors de l'envoi des données, la fonction génère une erreur 
 * et quitte le programme.
 * 
 * \param clientSocket Le descripteur de fichier du socket client à travers 
 * lequel envoyer les données.
 * \param data Un pointeur vers les données à envoyer au client.
 * \return Le nombre d'octets de données envoyées.
 */
int sendDataToClient(int clientSocket, const char *data);

/**
 * \fn void serverCloseConnection(int socket)
 * \brief Ferme la connexion du côté serveur d'une connexion client-serveur.
 * 
 * Cette fonction permet de fermer la connexion du côté serveur d'une connexion 
 * client-serveur en utilisant le descripteur de fichier du socket spécifié. 
 * Elle termine la connexion côté serveur.
 * 
 * \param socket Le descripteur de fichier du socket serveur à fermer.
 */
void serverCloseConnection(int socket);

#endif
