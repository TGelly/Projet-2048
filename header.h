#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct position{
    int x;
    int y;
};
typedef struct position stposition;

stposition generePositionRandom();
int** creerPlateau(FILE* fichier);
void decaleADroite(int** plateau, stposition p, int dejaMerge);
void joueADroite(int** plateau);
void decaleAGauche(int** plateau, stposition p, int dejaMerge);
void joueAGauche(int** plateau);
void decaleEnHaut(int** plateau, stposition p, int dejaMerge);
void joueEnHaut(int** plateau);
void decaleEnBas(int** plateau, stposition p, int dejaMerge);
void joueEnBas(int** plateau);
void ajoutCase(int** plateau, FILE* fichier);
int verifLoose(int** plateau);
void affichePlateau(int** plateau);

//  IMPERFECTION détectée: lorsqu'il y a 0 2 2 4 sur une ligne et que l'on joue 'gauche', tous les nombres se mergent 
//  en commençant par la gauche et on obtient 8 0 0 0 au lieu d'obtenir 4 4 0 0

stposition generePositionRandom(){
    stposition P;
    P.x = (rand()%4);
    P.y = (rand()%4);
    return P;
}

int** creerPlateau(FILE* fichier){
    //on alloue l'espace mémoire pour le plateau
    int** plateau = malloc(4*sizeof(int*));
    for(int i=0; i<4; i++){
        plateau[i] = malloc(4*sizeof(int));
        for(int j=0; j<4; j++){
            plateau[i][j] = 0;
        }
    }
    //on ajoute la génération aléatoire des cases remplies au début du jeu
    stposition P1 = generePositionRandom();
    plateau[P1.x][P1.y] = 2;
    stposition P2 = generePositionRandom();
    //gestion du cas où les coordonnées générées aléatoirement sont identiques
    if(P1.x==P2.x && P1.y == P2.y){
        plateau[P2.y][P2.x] = 2;
        /*Dans ce cas, la génération ne sera donc pas vraiment aléatoire,
        mais les cases remplies seront distinctes. Considérant que cela ne
        représente que 1/16² = 1/256 = 0,39% des cas, on applique l'algorithme
        de l'autruche. https://en.wikipedia.org/wiki/Ostrich_algorithm */
    }
    else{
        plateau[P2.x][P2.y] = 2;
    }
    fprintf(fichier, "%d %d %d %d\n", P1.x, P1.y, P2.x, P2.y);
    return plateau;
}

void decaleADroite(int** plateau, stposition p, int dejaMerge){
    //Si on a pas deja merge ET on est pas au bord ET (la case à droite est vide OU la case à droite a la même valeur)
    if(dejaMerge == 0 && p.y != 3 && (plateau[p.x][p.y+1] == 0 || plateau[p.x][p.y+1] == plateau[p.x][p.y])){
        if(plateau[p.x][p.y+1] == plateau[p.x][p.y]){
            dejaMerge = 1;
        }
        plateau[p.x][p.y+1] += plateau[p.x][p.y];
        plateau[p.x][p.y] = 0;
        p.y++;
        decaleADroite(plateau, p, dejaMerge);
    }
}

void joueADroite(int** plateau){
    //On parcourt le tableau vers le bord gauche en partant de l'avant-dernière colonne
    stposition p;
    int dejaMerge;
    for(p.y=2; p.y>-1; p.y--){
        for(p.x=0; p.x<4; p.x++){
            if(plateau[p.x][p.y] != 0){
                dejaMerge = 0;
                decaleADroite(plateau, p, dejaMerge);
            }
        }
    }
}

void decaleAGauche(int** plateau, stposition p, int dejaMerge){
    if(dejaMerge == 0 && p.y != 0 && (plateau[p.x][p.y-1] == 0 || plateau[p.x][p.y-1] == plateau[p.x][p.y])){
        if(plateau[p.x][p.y-1] == plateau[p.x][p.y]){
            dejaMerge = 1;
        }
        plateau[p.x][p.y-1] += plateau[p.x][p.y];
        plateau[p.x][p.y] = 0;
        p.y--;
        decaleAGauche(plateau, p, dejaMerge);
    }
}

void joueAGauche(int** plateau){
    stposition p;
    int dejaMerge;
    for(p.y=1; p.y<4; p.y++){
        for(p.x=0; p.x<4; p.x++){
            if(plateau[p.x][p.y] != 0){
                dejaMerge = 0;
                decaleAGauche(plateau, p, dejaMerge);
            }
        }
    }
}

void decaleEnHaut(int** plateau, stposition p, int dejaMerge){
    if(dejaMerge == 0 && p.x !=0 && (plateau[p.x-1][p.y] == 0 || plateau[p.x-1][p.y] == plateau[p.x][p.y])){
        if(plateau[p.x-1][p.y] == plateau[p.x][p.y]){
            dejaMerge = 1;
        }
        plateau[p.x-1][p.y] += plateau[p.x][p.y];
        plateau[p.x][p.y] = 0;
        p.x--;
        decaleEnHaut(plateau, p, dejaMerge);
    }
}

void joueEnHaut(int** plateau){
    stposition p;
    int dejaMerge;
    for(p.x=1; p.x<4; p.x++){
        for(p.y=0; p.y<4; p.y++){
            if(plateau[p.x][p.y] != 0){
                dejaMerge = 0;
                decaleEnHaut(plateau, p, dejaMerge);
            }
        }
    }
}

void decaleEnBas(int** plateau, stposition p, int dejaMerge){
    if(dejaMerge == 0 && p.x !=3 && (plateau[p.x+1][p.y] == 0 || plateau[p.x+1][p.y] == plateau[p.x][p.y])){
        if(plateau[p.x+1][p.y] == plateau[p.x][p.y]){
            dejaMerge = 1;
        }
        plateau[p.x+1][p.y] += plateau[p.x][p.y];
        plateau[p.x][p.y] = 0;
        p.x++;
        decaleEnBas(plateau, p, dejaMerge);
    }
}

void joueEnBas(int** plateau){
    stposition p;
    int dejaMerge;
    for(p.x=2; p.x>-1; p.x--){
        for(p.y=0; p.y<4; p.y++){
            if(plateau[p.x][p.y] != 0){
                dejaMerge = 0;
                decaleEnBas(plateau, p, dejaMerge);
            }
        }
    }
}

void ajoutCase(int** plateau, FILE* fichier){
    //on créé une valeur aléatoire: 2 ou 4
    int valeur = (rand()%2+1)*2;
    stposition p=generePositionRandom();
    while(plateau[p.x][p.y] != 0){
        p=generePositionRandom();
    }
    //on est maintenant sûr que la position contenue dans p est libre
    plateau[p.x][p.y] = valeur;
    fprintf(fichier, "%d %d %d\n", p.x, p.y, valeur);
}

int verifLoose(int** plateau){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(plateau[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

void affichePlateau(int** plateau){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}