/*
 * main.c
 *
 *  Created on: Nov 27, 2012
 *      Author: pierre
 */


#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#include "tas_min.h"
#include "prim.h"
#include "structure_matrice.h"

/**
 * prog arg1 arg2
 * arg1 : nom du fichier de coordonnée (par defaut testVerticesCoordinates.txt)
 * arg2 : non du ficier de sortie. (par defaut, à l'écran)
 * @param argc nombre d'argument transmit au programme (le nom du programme est envoyer comme argument)
 * @param argv tableau de chaine de carateres
 * @return
 */
int main (int argc, char *argv[]){
	FILE* input = NULL, *output = NULL;
	Matrice mat = NULL;
	if(argc >= 2){
		input = fopen(argv[1], "r");
	}
	else {

		input = fopen("intermediateTownsTest.txt", "r");
		if (input == NULL)
		{
			printf("probleme a l'ouverture du fichier");
			exit(1);
		};
	}
	mat = matrice_of_coordonnees(input);
	fclose(input);


	if(argc >= 3){
		output = fopen (argv[2], "w");
		if (output == NULL)
		{
			printf("probleme a l'ouverture du fichier");
			exit(1);
		};
	}
	else {
		output = stdout;
	}

	TSP (mat,output);
	liberer_mat(mat);
	fclose(output);
	return 0;
}
