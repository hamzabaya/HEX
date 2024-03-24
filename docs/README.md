# HEX Game - Version MVC (Modèle-Vue-Contrôleur) - Groupe n°1

Cette version du jeu HEX est implémentée selon le modèle MVC (Modèle-Vue-Contrôleur) et est conçue pour une utilisation en mode console uniquement.

## Contenu du Projet

Le projet est organisé en plusieurs dossiers :

- **docs** : Contient le fichier README.
- **doxygen_files** : Contient le fichier nécéssaires à la création de la documentation avec doxygen.
- **include** : Contient uniquement les fichiers d'en-tête (.h) qui déclarent les éléments publics nécessaires à l'interface d'un module ou d'une 
bibliothèque.
- **src** : Contient le code source des modules, y compris les fichiers .c du modèle MVC (model, view, controller), ainsi que le fichier principal main.c.
- **tests** : Contient les fichiers de tests pour les fichiers .c.
- **build** : Créé à la compilation. Contiendra les fichiers objets générés lors de la compilation.

## Générer la documentation

1. Placez-vous dans le répertoire principal (utilisez `cd`).
2. Exécutez la commande `make docs`.

## Compilation

Pour compiler l'application, suivez ces étapes :

1. Placez-vous dans le répertoire principal (utilisez `cd`).
2. Exécutez la commande `make`. Le Makefile générera l'application en créant les fichiers objets dans le dossier "build" et le fichier exécutable dans le 
dossier source puis effacera le dossier "build".

## Exécution

Pour exécuter le programme, suivez ces étapes :

1. Placez-vous dans le répertoire principal (utilisez `cd`).
2. Exécutez l'une des commandes suivantes:
- ./hex -s pppp               # Mode en ligne, serveur sur le port pppp
- ./hex -c hh.hh.hh.hh:pppp   # Mode en ligne, client se connectant au serveur hh.hh.hh.hh sur le port pppp (IP locale: 127.0.0.1)
- ./hex -l bleu               # Mode local, jouer localement en tant que bleu 
- ./hex -l rouge              # Mode local, jouer localement en tant que rouge

## Liste des commandes make

Vous pouvez exécuter les commandes make suivantes depuis le répertoire principal :

- make                        # Construit le fichier exécutable et détruit les .o
- make clean                  # Détruit les fichiers .o générés lors de la création de l'exécutable
- make cleanall               # Détruit tous les fichiers générés lors de la création de l'exécutable, exécutable compris
- make docs                   # Génère la documentation dans le dossier docs
- make keep                   # Construit le fichier exécutable et garde les .o
- make rebuild                # Reconstruit entièrement l'exécutable
- make test                   # Construit le fichier de tests exécutable et détruit les .o (ne marche pas actuellement)

## Section SVN, utile aux personnes travaillant sur l'application

### Partage des Modifications avec SVN

L'utilisation du Makefile permet de séparer les fichiers générés (fichiers objets et exécutables) du reste du code. Avant de partager vos modifications, 
assurez-vous d'effectuer les étapes suivantes :

1. Vérifiez les changements effectués avec `svn diff` (ou `svn diff <ressource>` pour limiter à une ressource).
2. Ajoutez les nouveaux fichiers ou répertoires avec `svn add <fichier|répertoire>`.
3. Annulez l'ajout d'un fichier ou d'un répertoire avec `svn revert <ressource>` (ou `svn revert <ressource> --depth infinity` pour les répertoires).
4. Mettez vos modifications à disposition en utilisant `svn commit -m '<un message>'`.

### Commandes SVN Principales

Voici quelques commandes SVN utiles :

- Pour récupérer une nouvelle copie du projet : `svn checkout <adresse>`.
- Pour mettre à jour votre copie : `svn update`.
- Pour déplacer, effacer ou copier un fichier : utilisez les commandes `svn mv`, `svn rm`, et `svn cp`.

N'hésitez pas à utiliser ces commandes pour gérer vos fichiers dans le dépôt SVN.

Bonne utilisation du jeu HEX !
