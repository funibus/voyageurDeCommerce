/*
 * tas_min.c
 *
 *  Created on: Dec 4, 2012
 *      Author: pierre
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tas_min.h"

#define Parent(i) (i/2)
#define Fils_g(i) (2*i)
#define Fils_d(i) (2*i + 1)

struct tas
{
	Arete ** tab;//tableau de pointeur d'arete
	Matrice graph;//matrice d'adjacence utilisee pour calculer le poid d'une arete
	int taille_tas_max;
	int taille_tas_courant;//indice de la premiere case non utilisee
};

double poid (Tas T, Arete * e){
	return getPoid(T->graph, e->u, e->v);
}

Tas creer_tas (Matrice graph_arg, int taille_tas_arg){
	Tas T = NULL;
	T = (Tas) malloc(sizeof(struct tas));
	if (T == NULL){
		fprintf(stderr, "erreur allocation tas min : pas assez de memoire");
		exit(1);
	}
	T->taille_tas_max = taille_tas_arg+1;
	T->taille_tas_courant = 1;
	T->graph = graph_arg;
	//(taille_tas_arg+1) car la premiere case ne sert pas (pour facilité la manipulation d'indice)
	T->tab = (Arete **) malloc(sizeof(Arete *)*(taille_tas_arg+1));
	if (T->tab == NULL){
		fprintf(stderr, "erreur allocation tas min : pas assez de memoire");
		exit(1);
	}
	return T;
}
void liberer_tas (Tas T){
	free (T->tab);
	free (T);
}

/**
 * insert un element en bas du tas et le fait remonter jusqu'a ce que son parent soit plus petit que lui
 * @param T
 * @param u
 * @param v
 */
void entasser_element (Tas T, int u, int v){
	int indice, parent;
	Arete * tmp;
	if (T->taille_tas_max + 1 == T->taille_tas_courant){
		fprintf(stderr, "erreur tas min plein");
		exit(1);
	}
	indice = T->taille_tas_courant;
	(T->tab)[T->taille_tas_courant] = (Arete *) malloc(sizeof(Arete));
	if ((T->tab)[T->taille_tas_courant] == NULL){
		fprintf(stderr, "erreur allocation memoire tas min");
		exit(1);
	}
	(T->tab)[indice]->u = u;
	(T->tab)[indice]->v = v;

	parent = indice / 2;
	//s'arretera forcement, car si l'element remonte jusqu'a la racine, il ne sera pas plus petit que lui meme
	while (parent > 0 && poid(T, (T->tab)[indice]) < poid(T, (T->tab)[parent])){
		tmp = (T->tab)[indice];
		(T->tab)[indice] = (T->tab)[parent];
		(T->tab)[parent] = tmp;

		indice = parent;
		parent = indice / 2;
	}
	T->taille_tas_courant++;
}
/**
 * si on suppose que les fils de i sont tous deux des tas min, actualise_tas actualise le ta de sorte que le tas de racine i soit un tas min
 * @param T un tas
 * @param indice du noeud a partire du quel traiter le tas a traiter
 */
void acutalise_tas (Tas T, int indice){
	//fait descendre un element qui est plus petit que l'un de ces fils
	int indice_gauche, indice_droit;
	Arete * tmp;
	int min_indice;

	indice_gauche = Fils_g(indice);
	indice_droit = Fils_d(indice);
	min_indice = (indice_gauche < T->taille_tas_courant && poid(T, T->tab[indice_gauche]) < poid(T, T->tab[indice]))? indice_gauche : indice;
	if (indice_droit < T->taille_tas_courant && poid(T, T->tab[indice_droit]) < poid(T, T->tab[min_indice])) min_indice = indice_droit;
	//echange indice min
	if (indice != min_indice){
		tmp = T->tab[indice];
		T->tab[indice] = T->tab[min_indice];
		T->tab[min_indice] = tmp;
		acutalise_tas(T, min_indice);
	}
}

Arete extraire_min(Tas T){
	Arete ret;
	if (T->taille_tas_courant == 1){
		fprintf(stderr, "erreur extraire min sur un tas vide");
		exit(1);
	}
	ret = *(T->tab[1]);
	free(T->tab[1]);
	T->taille_tas_courant--;
	if (T->taille_tas_courant > 1){ // Tas non vide
		T->tab[1] = T->tab[T->taille_tas_courant];
		acutalise_tas(T,1);

	}
	return ret;
}

void afficher_tas(Tas T, int indice){
	if (T->taille_tas_courant > indice){
		if (indice * 2 < T->taille_tas_courant){
			printf("(");
			afficher_tas(T, indice*2);
			printf(", (%d,%d _ %f), ", (T->tab)[indice]->u, (T->tab)[indice]->v, poid(T,(T->tab)[indice]));
			afficher_tas(T, indice*2 + 1);
			printf(")");
		}
		else
			printf("(%d,%d _ %f)", (T->tab)[indice]->u, (T->tab)[indice]->v, poid(T,(T->tab)[indice]));
	}

}
