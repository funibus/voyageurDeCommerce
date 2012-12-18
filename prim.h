
#ifndef PRIM_H_
#define PRIM_H_

#include "structure_arbre_couvrant.h"
#include "structure_matrice.h"
#include "tas_min.h"

element_liste* prim (Matrice matrice_poids);
Arete trouver_bonne_arete (Tas T, Matrice matrice_poids);
void TSP (Matrice matrice_poids);

#endif /* PRIM_H_ */
