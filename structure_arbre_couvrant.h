#ifndef STRUCTURE_ARBRE_COUVRANT_H_INCLUDED
#define STRUCTURE_ARBRE_COUVRANT_H_INCLUDED

typedef struct element_liste* element_liste;

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "structure_matrice.h"



element_liste* creer_arbre (int nombre_villes);
element_liste insertion_tete(element_liste head, int element);
void inserer_element_arbre (element_liste arbre[], int sommet1, int sommet2);
void liberer_liste (element_liste element);
void liberer_arbre (element_liste arbre[], int nombre_villes);
void parcourir_arbre (FILE* fichier, Matrice matrice_poids);
double distance_parcourue (FILE* fichier, Matrice matrice_poids);
int getSommetNode(element_liste l);
element_liste getNextSommetTree(element_liste l);

#endif // STRUCTURE_ARBRE_COUVRANT_H_INCLUDED
