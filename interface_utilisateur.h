#ifndef INTERFACE_UTILISATEUR_H_INCLUDED
#define INTERFACE_UTILISATEUR_H_INCLUDED

#include "structure_ville.h"
#include "TSP.h"

int trouver_ville (Ville* tab_villes, int nombre_villes, char* nom_ville);
Ville* interface_utilisateur (Ville* tab_villes, int* nombre_villes_total, int* nombre_villes_parcourt);

#endif // INTERFACE_UTILISATEUR_H_INCLUDED
