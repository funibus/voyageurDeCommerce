#ifndef STRUCTURE_ARBRE_COUVRANT_H_INCLUDED
#define STRUCTURE_ARBRE_COUVRANT_H_INCLUDED


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "structure_matrice.h"

typedef struct element_liste* element_liste;


element_liste* creer_arbre (int nombre_villes);
void inserer_element_arbre (element_liste arbre[], int sommet1, int sommet2);
void liberer_arbre (element_liste arbre[], int nombre_villes);
void parcourir_arbre (FILE* fichier, element_liste* arbre, Matrice matrice_poids);
double distance_parcourue (FILE* fichier, Matrice matrice_poids);

#endif // STRUCTURE_ARBRE_COUVRANT_H_INCLUDED
