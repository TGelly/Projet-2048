#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "fonctions.h"
#include "rejoue.h"

//Ceci a été modifié par thibault

int** rejoueInitialisation(FILE* fichier){

    //on récupère les coordonnées des cases remplies
    stposition un, deux;
    fscanf(fichier, "%d %d %d %d", &un.x, &un.y, &deux.x, &deux.y);

    //on créé un plateau
    int** plateau = malloc(4*sizeof(int*));
    for(int i=0; i<4; i++){
        plateau[i] = malloc(4*sizeof(int));
        for(int j=0; j<4; j++){
            plateau[i][j] = 0;
        }
    }

    //on remplit les deux cases de départ
    plateau[un.x][un.y] = 2;
    plateau[deux.x][deux.y] = 2;

    //on renvoit le plateau créé pour l'affichage et pour les lignes suivantes
    return plateau;
}

void rejoueCoup(FILE* fichier, int** plateau){

    //on récupère la direction
    char direction;
    fscanf(fichier, "%c", &direction);
    //on applique le mouvement dans cette direction
    switch(direction){
        case 'h':
            joueEnHaut(plateau);
            fprintf(fichier, "%s\n", "h");
            break;
        case 'b':
            joueEnBas(plateau);
            fprintf(fichier, "%s\n", "b");
            break;
        case 'g':
            joueAGauche(plateau);
            fprintf(fichier, "%s\n", "g");
            break;
        case 'd':
            joueADroite(plateau);
            fprintf(fichier, "%s\n", "d");
            break;
        default:
            break;
    }

    //on récupère la position et la valeur de la case ajoutée
    int x = 0, y = 0, value = 0;
    fscanf(fichier, "%d %d %d", &x, &y, &value);
    //on ajoute la case
    plateau[x][y] = value;
}



void Rejoue(){

    /*
        Le but de ces lignes était d'ouvrir le dossier gamefiles et de proposer à l'utilisateur d'ouvrir un des fichiers
        texte à l'intérieur. Comme expliqué à la ligne 17 de joue.c, ce n'est pas possible.
    DIR* FD;
    if (NULL == (FD = opendir ("gamefiles/"))){
        printf("Erreur: Echec de l'ouverture du dossier.\n");
    }
    */

    //On recherche donc les fichiers de jeu dans le dossier principal:

    /*
        Le but de cette partie du code était de laisser choisir à l'utilisateur quel fichier il voulait ouvrir
        en lui montrant les noms des fichiers. Ce code provoque une erreur de segmentation, nous allons donc
        utiliser un fichier type et le nommer "rejouable.txt" et c'est celui-ci qui sera rejoué.

    //ouverture du dossier
    DIR* dossier;
    printf("Ouverture du dossier.\n");
    if (NULL == (dossier = opendir ("/"))){
        printf("Erreur: Echec de l'ouverture du dossier.\n");
    }
    printf("Succès de l'ouverture du dossier.\n");

    //scan des fichiers et proposition à l'utilisateur
    struct dirent * scanFichier;
    scanFichier = readdir(dossier);

    while ((scanFichier = readdir(dossier)) != NULL) {
        printf("%s", scanFichier->d_name);
    }

    //On ouvre le fichier choisi par l'utilisateur
    char* nomFichier;
    FILE* fichier = fopen(nomFichier, "r");
    */

    //On ouvre le fichier
    FILE* fichier = fopen("rejouable.txt", "r");

    //On rejoue la partie en l'affichant
    int** plateau = rejoueInitialisation(fichier);
    affichePlateau(plateau);
    int compteur = 0;
    while(feof(fichier) == 0){
        compteur++;
        printf("On joue le coup %d.\n", compteur);
        rejoueCoup(fichier, plateau);
        affichePlateau(plateau);
    }
    /*
    ! Il y a un problème: le redéroulement de la partie ne fonctionne pas car la plupart des valeurs 
    ! sont remplacées par des zéro. Je ne sais pas d'où provient ce bug.
    */
}