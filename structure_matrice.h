#ifndef STRUCTURE_MATRICE_H_INCLUDED
#define STRUCTURE_MATRICE_H_INCLUDED

#include "structure_ville.h"

typedef struct matrice* Matrice;


Matrice create_mat (int nb_villes);
void liberer_mat (Matrice G);
void marquer_sommet(Matrice G, int sommet);
double ** getGraph(Matrice G);
void setMarque(Matrice G, int s);//indique que le sommet s appartient a l'arbre couvrant
int getMarque(Matrice G, int s);
int getNbVilles(Matrice G);
double getPoid(Matrice G, int u, int v);
void setPoid(Matrice G, int u, int v, double w);

char * getNameSommet(Matrice G, int sommet);
double getXSommet(Matrice G, int sommet);
double getYSommet(Matrice G, int sommet);
void SetNameSommet(Matrice G, int sommet, char * name);
void SetXSommet(Matrice G, int sommet, double x);
void SetYSommet(Matrice G, int sommet, double y);



#endif // STRUCTURE_MATRICE_H_INCLUDED
