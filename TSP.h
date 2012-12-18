#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "structure_matrice.h"

Matrice matrice_of_fichier (FILE* fichier);
double distance (double x1, double y1, double x2, double y2);
Matrice matrice_of_coordonnees (FILE* fichier);

#endif // TSP_H_INCLUDED
