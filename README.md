# Aquarium de poissons

Ce projet représente notre implémentation pour le projet de réseaux (RE203) qui consiste à implémenter un aquarium centralisé de poissons composé d'un programme d’affichage et d'un contrôleur.

## Installation

Lancer la commande suivante dans le dossier `controleur` pour générer l'exécutable nécessaire au lancement du serveur :

```shell
make server
```

L'exécutable nécessaire au lancement du client a déjà été crée et se trouve dans le dossier `affichage` sous le nom `client.jar`.

## Utilisation
Commencer par lancer le serveur, utiliser la commande suivante (à lancer dans le dossier `controleur`):
```shell
./serveur
```
Il est également possible de générer l'exécutable `server` et lancer le serveur en redirigeant la sortie erreur (les messages de log) vers le fichier `debug.log`. Cece peut se faire avec la commande suivante : 
```shell
make launch_server
```

Le contrôleur est crée avec un aquarium vide. Utiliser les commandes dans le sujet pour importer un aquarium ou ajouter de nouvelles vues. Ensuite, il est possible de connecter un client. Mais avant, il faut modifier le `Makefile` dans le dossier `affichage` en remplaçant le contenu de la variable `JAVAFX_LIB_DIR` par le chemin vers la bibliothèque de `JavaFX`. Ensuite, utiliser la commande suivante (à lancer dans le dossier `affichage`) :
```shell
make client
```

## Contributeurs
Ce projet a été réalisé par les membres suivants :
- Jalal IZEKKI
- Mohammed Boudali
- Hugo Bernard
- Mouhcine El Hammadi
- Hicham Zghari
