#ifndef VILLES_TRAVERSEES_H_INCLUDED
#define VILLES_TRAVERSEES_H_INCLUDED

#include "interface_utilisateur.h"
#include "structure_ville.h"
#include "structure_matrice.h"

typedef struct chemin* Chemin;

Chemin ajouter_chemin (Ville ville, Chemin suite_du_chemin);
void liberer_chemin (Chemin chemin);
Chemin chemin_of_fichier (FILE* fichier, Ville* tab_villes, int nb_villes);
void villes_traversees (Chemin premiere_ville, Chemin ville_en_court, Ville* tab_villes, int nb_villes);
void fichier_of_chemin (Chemin chemin, FILE* fichier);

#endif // VILLES_TRAVERSEES_H_INCLUDED
