# Projet_Phylogenetique

## Membre du groupe
Loth Antoine
Meligua Lévy
Beigaud Anne

## Présentation des fichiers
Le programme est constitué de 5 fichier .c, 1 fichier .h et un fichier .md (il s'agit du readme que vous êtes en train de lire).
Les 5 fichiers .c du programme sont :
- main.c : Procédure mère qui fait appelle à l'ensemble des autres fichiers, chaques fichiers ayant sont propre rôle dans le programme.
- sequence.c : Lire et afficher les différentes séquences.
- alignement.c : Réaliser un alignement des séquences avec ou sans algorithme de Needleman-Wunsh
- matrice_distance.c : Construction d'une matrice de distance pour construire des arbres phylogénétiques
- tree.c : Réalisation d'arbres phylogénétiques


## Lancer le script

Pour pouvoir utilisé le script, il est en premier temps nécéssaire de l'avoir télécharger.
Pour compiler et exécuter le script : 

1) Ouvrir un terminal Unix ou équivalent (WSL par exemple).
2) Naviguer dans les dossier afin d'être dans le fichier du projet (utilisation de la commande ```cd``` pour naviguer).
3) Compiler le script avec la commande ```make```.
4) Exécuter le script via la commande ```./phylo```.