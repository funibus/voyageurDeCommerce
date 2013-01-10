/*
 * structure_ville.h
 *
 *  Created on: Dec 18, 2012
 *      Author: pierre
 */

#ifndef STRUCTURE_VILLE_H_
#define STRUCTURE_VILLE_H_

struct ville;
typedef struct ville* Ville;

Ville create_ville (char* name, double x, double y);
void liberer_ville (Ville V);
void liberer_tab_villes (Ville *tab, int nombre_villes);

/*primitive d'aces*/
char * getNameVille(Ville V);
double getXVille(Ville V);
double getYVille(Ville V);
void SetNameVille(Ville V, char * name);
void SetXVille(Ville V, double x);
void SetYVille(Ville V, double y);


#endif /* STRUCTURE_VILLE_H_ */
