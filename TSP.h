#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "structure_matrice.h"
#include "structure_ville.h"

Matrice matrice_of_fichier (FILE* fichier);
Matrice matrice_of_coordonnees (FILE* fichier);
Ville* create_tab_villes (int* nombre_villes);

#endif // TSP_H_INCLUDED
