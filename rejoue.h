#ifndef REJOUE_H
#define REJOUE_H

#include <stdio.h>

int** rejoueInitialisation(FILE* fichier);
void rejoueCoup(FILE* fichier, int** plateau);
void Rejoue();

#endif