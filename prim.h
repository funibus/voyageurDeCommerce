
#ifndef PRIM_H_
#define PRIM_H_

#include "structure_arbre_couvrant.h"
#include "structure_matrice.h"
#include "tas_min.h"

void prim (Matrice matrice_poids);
void TSP (Matrice matrice_poids, FILE* output);

#endif /* PRIM_H_ */
