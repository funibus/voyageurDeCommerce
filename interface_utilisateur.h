#ifndef INTERFACE_UTILISATEUR_H_INCLUDED
#define INTERFACE_UTILISATEUR_H_INCLUDED

#include "structure_ville.h"
#include "lecture_fichier.h"
#include "prim_TSP.h"
#include "structure_matrice.h"
#include "villes_traversees.h"

int trouver_ville (Ville* tab_villes, int nombre_villes, char* nom_ville);
Ville* interface_utilisateur (Ville* tab_villes, int* nombre_villes_total, int* nombre_villes_parcourt);
void vider_buffer ();
void reprendre_fgetc (char* mot);
void voyageur_de_commerce_utilisateur (char *input, Matrice *mat_parcourt, char* output);

#endif // INTERFACE_UTILISATEUR_H_INCLUDED
