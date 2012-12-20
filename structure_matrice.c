
#include <stdio.h>
#include <stdlib.h>
#include "structure_matrice.h"

/*utilise pour representer un graph avec une matrice d'adjacence*/
typedef struct matrice
{
	int nb_villes;// nombre de sommet dans le graph
	double ** graph;//matrice d'adjacence
	int * marque;//tableau indiquant si un sommet est dans l'arbre couvrant
	Ville * liste_name;// tableau associatif entre sommet et nom du sommet
};


/**
 * @param nb_villes_arg
 * @return une structure Matrice vide
 */
Matrice create_mat (int nb_villes_arg){
	Matrice ret = NULL;
	int i;
	char tmp[100];

	ret = (struct matrice*) malloc(sizeof(struct matrice));
	ret->nb_villes = nb_villes_arg;
	if (ret == NULL ){
		fprintf(stderr, "erreur allocation matrice : pas assez de memoire");
		exit(1);
	}
	ret->marque = (int *) malloc(sizeof(int)*nb_villes_arg);
	ret->graph = (double **) malloc(sizeof(double*)*nb_villes_arg);
	ret->liste_name = (Ville *) malloc(sizeof(Ville)*nb_villes_arg);
	if (ret->graph == NULL || ret->marque == NULL || ret->liste_name == NULL){
		fprintf(stderr, "erreur allocation matrice : pas assez de memoire");
		exit(1);
	}
	for (i = 0; i < nb_villes_arg; i++){
		ret->marque[i] = 0;// a l'etat initiale, aucun sommet n'est dans l'arbre couvrant
		ret->graph[i] = (double *) malloc(sizeof(double)*nb_villes_arg);
		if (ret->graph[i] == NULL){
			fprintf(stderr, "erreur allocation matrice : pas assez de memoire");
			exit(1);
		}
		sprintf(tmp,"%d",i);
		ret->liste_name[i] = create_ville(tmp, 0, 0);
	}
	return ret;
}

/**
 * libere l'espace utilise pour la matrice des villes
 * @param G pointeur sur structure de matrice
 */
void liberer_mat (Matrice G)
{
	int i = 0;
	for (i=0; i<G->nb_villes; i++)
	{
		free ((G->graph)[i]);
		liberer_ville(G->liste_name[i]);
	}
	free (G->graph);
	free (G->marque);
	free (G->liste_name);
	free (G);
}

/*Accesseurs*/
double ** getGraph(Matrice G){
	return G->graph;
}

void setMarque(Matrice G, int s){
	(G->marque)[s] = 1;
}

int getMarque(Matrice G, int s){
	return (int) (G->marque)[s];
}

int getNbVilles(Matrice G){
	return G->nb_villes;
}
double getPoid(Matrice G, int u, int v){
	return (G->graph)[u][v];
}
void setPoid(Matrice G, int u, int v, double w){
	(G->graph)[u][v] = w;
	(G->graph)[v][u] = w;
}

char * getNameSommet(Matrice G, int sommet){
	return getNameVille(G->liste_name[sommet]);
}
double getXSommet(Matrice G, int sommet){
	return getXVille(G->liste_name[sommet]);
}
double getYSommet(Matrice G, int sommet){
	return getYVille(G->liste_name[sommet]);
}
void SetNameSommet(Matrice G, int sommet, char * name){
	SetNameVille(G->liste_name[sommet], name);
}
void SetXSommet(Matrice G, int sommet, double x){
	SetXVille(G->liste_name[sommet], x);
}
void SetYSommet(Matrice G, int sommet, double y){
	SetYVille(G->liste_name[sommet], y);
}
