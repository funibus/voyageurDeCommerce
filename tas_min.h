/*
 * tas_min.h
 *
 *  Created on: Dec 4, 2012
 *      Author: pierre
 */

#ifndef TAS_MIN_H_
#define TAS_MIN_H_

#include "structure_matrice.h"
typedef struct arete
{
	//arete non orienter (u,v)
    int u;
    int v;
} Arete;
typedef struct tas* Tas;

Tas creer_tas (Matrice graph_arg, int taille_tas);
void liberer_tas (Tas T);
void acutalise_tas (Tas T, int indice);
void entasser_element (Tas T, int u, int v);
Arete extraire_min(Tas T);

void afficher_tas(Tas T, int indice);


#endif /* TAS_MIN_H_ */
