#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//fichiers custom
#include "fonctions.h"
#include "joue.h"
#include "rejoue.h"
#include "affichage.h"

int main(){
    int choix, err=1;
    printf("Que voulez-vous faire?\n1 - Jouer une nouvelle partie\n2 - rejouer une ancienne partie\n");
    scanf("%d", choix);
    while (err==1)
    {
        switch(choix){
            case 1:
                Joue();
                err=0;
                break;
            case 2:
                Rejoue();
                err=0;
                break;
            default:
                printf("Erreur, la saisie est incorrecte, veuillez recommencer.\n");
                printf("Que voulez-vous faire?\n1 - Jouer une nouvelle partie\n2 - rejouer une ancienne partie\n");
                scanf("%d", choix);
                break;
        }
    }
    return 0;
}