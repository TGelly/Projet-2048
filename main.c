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
    int choix;
    printf("Que voulez-vous faire?\n1 - Jouer une nouvelle partie\n2 - rejouer une ancienne partie\n");
    scanf("%d", choix);
    switch(choix){
        case 1:
            Joue();
            break;
        case 2:
            Rejoue();
            break;
        default:
            break;
    }
    return 0;
}