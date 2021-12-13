#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>

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

#endif