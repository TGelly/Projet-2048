#include <stdio.h>
#include "affichage.h"

void affichePlateauSDL(int** plateau){
    //EN COURS DE DEV
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%4d ", plateau[i][j]);
        }
        printf("\n");
    }
}