/*
 * gui.c
 *
 *  Created on: Dec 24, 2012
 *      Author: pierre
 */

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <float.h>

#include "gui.h"
#include "structure_arbre_couvrant.h"

struct geometry
{
	int rayon;
	double heightGraph, widthGraph, orX, orY;
	double heightScreen, widthScreen;
};

void blit_sommet_matrice(Matrice G, SDL_Surface* formeSommet, SDL_Surface* surface, struct geometry Geom);
void blit_Tree(Matrice G, SDL_Surface* surface, struct geometry Geom);
void blit_Cycle(Matrice G, SDL_Surface* surface, struct geometry Geom);
void Graph2screeCoordonne(struct geometry Geom, Matrice G, SDL_Rect * rect, int sommet);
void Screen2graphCoordonne(struct geometry Geom, SDL_Rect * rect);
void accutaliser_screen(SDL_Surface* screen, SDL_Surface* disque, Matrice G, struct geometry Geom, int aff_sommet, int aff_tree, int aff_cycle);
void Graph2screeCoordonne(struct geometry Geom, Matrice G, SDL_Rect * rect, int sommet){
	rect->x = (int)(Geom.widthScreen*(getXSommet(G,sommet) - Geom.orX)/Geom.widthGraph);
	rect->y = (int)(Geom.heightScreen - Geom.heightScreen*(getYSommet(G,sommet) - Geom.orY)/Geom.heightGraph);
}
/**
 *
 * @param Geom
 * @param rect entre sortie : contient initialement des coordonnée de l'ecran. Sera convertie en coordonnee entier de graph
 */
void Screen2graphCoordonne(struct geometry Geom, SDL_Rect * rect){
	rect->x = (int)((rect->x)*Geom.widthGraph/Geom.widthScreen + Geom.orX);
	rect->y = (int)(Geom.heightScreen - (rect->y)*Geom.heightGraph/Geom.heightScreen + Geom.orY);
}
void gui(Matrice G){
	int aff_sommet = 1, aff_tree = 1, aff_cycle = 1;
	SDL_putenv ("SDL_VIDEO_CENTERED=center");
	SDL_Init( SDL_INIT_VIDEO );
	int boucle_infini = 1;
	struct geometry Geom;
	Geom.widthScreen = 400.0;
	Geom.heightScreen = 400.0;
	Geom.rayon = RAYON;
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


	accutaliser_screen(screen, disque, G, Geom, aff_sommet, aff_tree, aff_cycle);


	//Affichage des sommets
	while (boucle_infini)
	{
		SDL_WaitEvent(&event);
		switch(event.type){
		case SDL_QUIT:
			boucle_infini = 0;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_c:
				aff_cycle = !aff_cycle;
				break;
			case SDLK_s:
				aff_sommet = !aff_sommet;
				break;
			case SDLK_t:
				aff_tree = !aff_tree;
				break;
			case SDLK_ESCAPE:
				boucle_infini = 0;
				break;
			default:
				break;
			}
			accutaliser_screen(screen, disque, G, Geom, aff_sommet, aff_tree, aff_cycle);
			break;
		}

	}
	SDL_FreeSurface(disque);
	SDL_Quit();
}

void gui_generer_ville(char *filename){

	FILE *output = fopen (filename, "w");
	if (output == NULL)
	{
		printf("probleme a l'ouverture du fichier\n");
		exit(1);
	};
	SDL_putenv ("SDL_VIDEO_CENTERED=center");
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Rect position;
	int nb_ville_cree=0;
	int boucle_infini = 1;
	struct geometry Geom;
	Geom.widthScreen = 400.0;
	Geom.heightScreen = 400.0;
	Geom.rayon = RAYON;
	Geom.orX = 0.0;
	Geom.orY = 0.0;
	Geom.widthGraph = 400.0 - Geom.orX;
	Geom.heightGraph = 400.0 - Geom.orY;

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
	//Affichage des sommets
	while (boucle_infini)
	{
		SDL_WaitEvent(&event);
		switch(event.type){
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
				nb_ville_cree++;
				Screen2graphCoordonne(Geom, &position);
				fprintf(output, "%d: %f; %f!\n", nb_ville_cree, (float)position.x, (float)position.y);
				break;
			}
			break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
				case SDLK_RETURN:
					boucle_infini = 0;
					break;
				default:
					break;
				}
				break;
		}

	}
	fclose(output);
	SDL_FreeSurface(disque);
	SDL_Quit();
}
void affichage_gui(char *filename){


	SDL_putenv ("SDL_VIDEO_CENTERED=center");
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Rect position;
	int boucle_infini = 1;
	struct geometry Geom;
	double xmin, ymin, xmax, ymax;
	Geom.widthScreen = 400.0;
	Geom.heightScreen = 400.0;
	Geom.rayon = RAYON;

	SDL_Event event;
	SDL_Surface* screen = SDL_SetVideoMode( (int)Geom.widthScreen, (int)Geom.heightScreen, 32,
			SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "TSP - Projet C", 0 );

	//disque : une surface contenant un disque que l'on vas coller à l'empacement de chaque sommet

	FILE *output = fopen (filename, "r");
	if (output == NULL)
	{
		printf("probleme a l'ouverture du fichier\n");
		exit(1);
	};
	int nombre_villes, i, sommet;
	char name[1000],c;
	double sommet_x, sommet_y;
	long curseur_init;
	/*
	    les fichiers coordonnées sommets commence par une ligne indiquant le nombre de sommet
	    tandis ce que les fichiers coordonnées villes n'indique pas le nombre de villes présentent dans le fichier.
	    On vas tester si le fichiers comporte cette indication, et ci c'est le cas, on va simplement l'ignoré (et lire le fichier jusqu'a la fin)
	 */
	curseur_init = ftell(output);//position initial dans le fichier
	c = 'A'; //c un charatere différent de '\n' et de ':'
	while (c != '\n' && c != ':'){
		c = fgetc(output);
	}
	if (c == ':'){// fichiers avec nom de ville
		//on compte le nombre de villes présentent dans le fichier
		nombre_villes=1;
		while (c != EOF){
			c = fgetc(output);
			if (c == ':'){
				nombre_villes++;
			}
		}
		fseek(output, 0, curseur_init);//on revient a la position initial pour traiter la premier ligne
	}
	else{//fichier sommet
		fseek(output, 0, curseur_init);//on revient a la position initial pour récupérer la taille exacte du tableau
		fscanf (output, "%d!", &nombre_villes);
		if (!feof(output))fgetc(output);// saut le \n
	}
	xmin = ymin = DBL_MAX;
	xmax = ymax = -DBL_MAX;
	for (sommet=0; sommet<nombre_villes; sommet++)
	{
		i = -1;
		do{
			i++;
			name[i] = fgetc(output);
		} while (name[i] != ':');
		name[i] = '\0';
		fscanf(output, "%lf; %lf!", &sommet_x, &sommet_y);
		if (sommet_x > xmax) xmax = sommet_x;
		if (sommet_x < xmin) xmin = sommet_x;
		if (sommet_y > ymax) ymax = sommet_y;
		if (sommet_y < ymin) ymin = sommet_y;
	}
	Geom.orX = xmin;
	Geom.orY = ymin;
	Geom.widthGraph =xmax - Geom.orX;
	Geom.heightGraph = ymax - Geom.orY;
	fseek(output, 0, curseur_init);
	for (sommet=0; sommet<nombre_villes; sommet++)
	{
		i = -1;
		do{
			i++;
			name[i] = fgetc(output);
		} while (name[i] != ':');
		name[i] = '\0';
		fscanf(output, "%lf; %lf!", &sommet_x, &sommet_y);
		if (!feof(output))fgetc(output);// saut le \n
		position.x = (int)(Geom.widthScreen*(sommet_x - Geom.orX)/Geom.widthGraph);
		position.y = (int)(Geom.heightScreen - Geom.heightScreen*(sommet_y - Geom.orY)/Geom.heightGraph);
		pixelRGBA(screen, position.x, position.y, 255,0,0,255);
	}
	SDL_Flip(screen);
	//Affichage des sommets
	while (boucle_infini)
	{
		SDL_WaitEvent(&event);
		switch(event.type){
		case SDL_QUIT:
			boucle_infini = 0;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				boucle_infini = 0;
				break;
			default:
				break;
			}
			break;
		}

	}
	fclose(output);
	SDL_Quit();
}

void accutaliser_screen(SDL_Surface* screen, SDL_Surface* disque, Matrice G, struct geometry Geom, int aff_sommet, int aff_tree, int aff_cycle){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
	if (aff_tree) blit_Tree(G, screen, Geom);
	if (aff_cycle) blit_Cycle(G,screen, Geom);
	if (aff_sommet) blit_sommet_matrice(G,disque,screen, Geom);
	SDL_Flip(screen);
}

void blit_sommet_matrice(Matrice G, SDL_Surface* formeSommet, SDL_Surface* surface, struct geometry Geom){
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
