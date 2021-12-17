#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "rejoue.h"

//Ceci a été modifié par thibault

void rejoueInitialisation(FILE* fichier){

}

void rejoueCoup(FILE* fichier){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

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
    //ouverture du dossier
    DIR* dossier;
    printf("Ouverture du dossier.\n");
    if (NULL == (dossier = opendir ("/"))){
        printf("Erreur: Echec de l'ouverture du dossier.\n");
    }
    printf("Succès de l'ouverture du dossier.\n");
    //scan des fichiers et proposition à l'utilisateur
    printf("0");
    struct dirent * scanFichier;
    printf("1");
    scanFichier = readdir(dossier);
    printf("2");

    /*
    while ((scanFichier = readdir(dossier)) != NULL) {
        printf("%s", scanFichier->d_name);
    }
    */


    //On ouvre le fichier choisi par l'utilisateur
    char* nomFichier;
    FILE* fichier = fopen(nomFichier, "r");

    //On rejoue la partie en l'affichant
    rejoueInitialisation(fichier);
    while(feof(fichier) == 0){
        rejoueCoup(fichier);
    }
}