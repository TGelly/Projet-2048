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

    //On ouvre le dossier 2048 et on propose à l'utilisateur d'ouvrir un des fichiers textes qu'il contient.
    DIR* FD;
    if (NULL == (FD = opendir ("/gamefiles"))){
        printf("Erreur: Echec de l'ouverture du dossier.\n");
    }

    //On ouvre le fichier choisi par l'utilisateur
    char* cheminFichier;
    FILE* fichier = fopen(cheminFichier, "r");

    //On rejoue la partie en l'affichant
    rejoueInitialisation(fichier);
    while(feof(fichier) == 0){
        rejoueCoup(fichier);
    }
    

    //FILE* fichier = fopen();
}