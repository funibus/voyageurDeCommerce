/*
 * gui.c
 *
 *  Created on: Dec 24, 2012
 *      Author: pierre
 */

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "gui.h"
#include "structure_arbre_couvrant.h"

struct geometry
{
	int rayon;
	double heightGraph, widthGraph, orX, orY;
	double heightScreen, widthScreen;
};

void blit_sommet(Matrice G, SDL_Surface* formeSommet, SDL_Surface* surface, struct geometry Geom);
void blit_Tree(Matrice G, SDL_Surface* surface, struct geometry Geom);
void blit_Cycle(Matrice G, SDL_Surface* surface, struct geometry Geom);
void Graph2screeCoordonne(struct geometry Geom, Matrice G, SDL_Rect * rect, int sommet);

void Graph2screeCoordonne(struct geometry Geom, Matrice G, SDL_Rect * rect, int sommet){
	rect->x = (int)(Geom.widthScreen*(getXSommet(G,sommet) - Geom.orX)/Geom.widthGraph);
	rect->y = (int)(Geom.heightScreen*(getYSommet(G,sommet) - Geom.orY)/Geom.heightGraph);
}
void gui(Matrice G){


	SDL_putenv ("SDL_VIDEO_CENTERED=center");
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Rect position;
	int boucle_infini = 1;
	struct geometry Geom;
	Geom.widthScreen = 400.0;
	Geom.heightScreen = 400.0;
	Geom.rayon = 8;
	Geom.orX = getXmin(G);
	Geom.orY = getYmin(G);
	Geom.widthGraph =getXmax(G) - Geom.orX;
	Geom.heightGraph = getYmax(G) - Geom.orY;

	SDL_Event event;
	SDL_Surface* disque;
	SDL_Surface* screen = SDL_SetVideoMode( (int)Geom.widthScreen, (int)Geom.heightScreen, 32,
			SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "TSP - Projet C", 0 );

	//disque : une surface contenant un disque que l'on vas coller à l'empacement de chaque sommet
	disque = SDL_CreateRGBSurface(SDL_HWSURFACE,2*Geom.rayon+2,2*Geom.rayon+2,32,0,0,0,0);
	filledCircleRGBA(disque,
			Geom.rayon,Geom.rayon,Geom.rayon,
			255, 0, 0, 200);
	SDL_SetColorKey(disque, SDL_SRCCOLORKEY, SDL_MapRGB(disque->format, 0, 0, 0));


	blit_Tree(G, screen, Geom);
	blit_sommet(G,disque,screen, Geom);
	blit_Cycle(G,screen, Geom);
	SDL_Flip(screen);



	//Affichage des sommets
	while (boucle_infini)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
			boucle_infini = 0;
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button){
			case SDL_BUTTON_LEFT:
				position.x = event.button.x - Geom.rayon;
				position.y = event.button.y - Geom.rayon;
				SDL_BlitSurface(disque, NULL, screen, &position);
				SDL_Flip(screen);
				break;
			}
			break;
		}

	}
	SDL_FreeSurface(disque);
	SDL_Quit();
}

void blit_sommet(Matrice G, SDL_Surface* formeSommet, SDL_Surface* surface, struct geometry Geom){
	SDL_Rect position;
	int i;
	for (i = 0; i<getNbVilles(G); i++){
		Graph2screeCoordonne(Geom, G, &position, i);
		position.x -= Geom.rayon;
		position.y -= Geom.rayon;
		SDL_BlitSurface(formeSommet, NULL, surface, &position);
	}
}

void blit_Tree(Matrice G, SDL_Surface* surface, struct geometry Geom){
	SDL_Rect u, v;
	element_liste* tree;
	element_liste fils = NULL;
	int i;

	tree = getTree(G);
	for (i = 0; i<getNbVilles(G); i++){
		Graph2screeCoordonne(Geom, G, &u, i);
		fils = tree[i];
		while (fils != NULL){
			Graph2screeCoordonne(Geom, G, &v, getSommetNode(fils));
			lineRGBA(surface,u.x, u.y,	v.x, v.y, 255,255,255,255);
			fils = getNextSommetTree(fils);
		}

	}
}

void blit_Cycle(Matrice G, SDL_Surface* surface, struct geometry Geom){
	SDL_Rect u, v;
	element_liste cycle, ville_suivante;
	element_liste fils = NULL;
	int sommet;

	cycle = getCycle(G);

	while (cycle != NULL){
		Graph2screeCoordonne(Geom, G, &u, getSommetNode(cycle));
		ville_suivante = getNextSommetTree(cycle);
		if (ville_suivante == NULL){//on ferme le cycle
			Graph2screeCoordonne(Geom, G, &v, getSommetNode(getCycle(G)));
		}
		else{// lier les deux villes
			Graph2screeCoordonne(Geom, G, &v, getSommetNode(ville_suivante));
		}
		lineRGBA(surface,u.x, u.y,	v.x, v.y, 0,255,255,255);
		cycle = ville_suivante;
	}
}




