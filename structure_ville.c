/*
 * structure_ville.c
 *
 *  Created on: Dec 18, 2012
 *      Author: pierre
 */


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "structure_ville.h"

struct ville
{
    char * nom;//nom de la ville
    double x;//coordonnees
    double y;
};

/**
 * cree un element ville compose d'un nom et de ses coordonnes
 * @param name
 * @param x
 * @param y
 * @return une Ville
 */
Ville create_ville (char* name, double x, double y){
	Ville V = NULL;
	V = (struct ville*) malloc(sizeof(struct ville));
	if (V == NULL)
	{
		printf("problème d'allocation pour la ville %s", name);
		exit(1);
	};
	V->nom = NULL;
	SetNameVille(V, name);
	SetXVille(V, x);
	SetYVille(V, y);

	return V;
}
void liberer_ville (Ville V){
	if (V){
		if (V->nom)
			free(V->nom);
		free(V);
	}
}



void liberer_tab_villes (Ville *tab, int nombre_villes){
	int j;
    for (j=0; j<nombre_villes; j++){
    	liberer_ville(tab[j]);
    }
    free(tab);
}

char * getNameVille(Ville V){
	return V->nom;
}
double getXVille(Ville V){
	return V->x;
}
double getYVille(Ville V){
	return V->y;
}
/**
 * alloue de la memoire pour enregistrer le nom de la ville
 * @param V
 * @param name
 */
void SetNameVille(Ville V, char * name){
	int length=0;
	while (name[length] != '\0') length++;
	if (V->nom != NULL) free(V->nom);
	V->nom = (char *) malloc(sizeof(char)*(length+1));
	for (; length >=0; length--)
		V->nom[length] = name[length];
}
void SetXVille(Ville V, double x){
	V->x = x;
}
void SetYVille(Ville V, double y){
	V->y = y;
}
