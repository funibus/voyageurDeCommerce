#define GUI_ENABLE //commenter cette ligne pour desactiver l'interface graphique

#include <stdio.h>
#include <stdlib.h>


#include "tas_min.h"
#include "prim_TSP.h"
#include "lecture_fichier.h"
#include "structure_matrice.h"
#include "interface_utilisateur.h"

#ifdef GUI_ENABLE
#include "gui.h"
#endif


int generation (char *nom_file, Matrice *mat);

int main (int argc, char *argv[]){
	int continuer = 10;
#ifdef GUI_ENABLE
	int afficher;
#endif
	char nom_file[1000];
	Matrice mat = NULL;
	FILE *input = NULL;
	FILE *output = stdout;
	FILE *nullstream = stdout;
	nullstream = fopen ("nullstream", "w");
	if (nullstream == NULL){
		printf("probleme a l'ouverture du fichier\n");
		exit(1);
	}

	if(argc >= 2){
		output = fopen (argv[1], "w");
		if (output == NULL){
			printf("probleme a l'ouverture du fichier\n");
			exit(1);
		}
	}

	while (continuer){
		printf("TSP : selectionner l'action a executer :\n");
		printf("\t1 : generer une liste de ville\n");
		printf("\t2 : appliquer l'algorithme prim à un fichier de ville\n");
#ifdef GUI_ENABLE
		printf("\t3 : afficher une liste de ville (aucune action possible -> efficace pour de grand nombre de villes)\n");
#endif
		printf("\t0 : quitter le programme\n");
		scanf("%d", &continuer);

		switch(continuer){
		case 1 :
			continuer = generation(nom_file, &mat);
			break;
		case 2 :
			printf("entrer le nom du fichier :\n");
			scanf("%s", nom_file);
			input = fopen (nom_file, "r");
			if (input == NULL)
			{
				printf("probleme a l'ouverture du fichier\n");
				exit(1);
			}
			mat = matrice_of_coordonnees(input);
			fclose(input);
			TSP (mat,output);
			fprintf(output,"\n");
			continuer = 13;
			break;
#ifdef GUI_ENABLE
		case 3 :
			printf("entrer le nom du fichier :\n");
			scanf("%s", nom_file);
			affichage_gui(nom_file);
			break;
#endif
		case 0 :
			break;
		default :
			continuer = 10;
			break;
		}

#ifdef GUI_ENABLE
		/*propose l'affichage graphique, et initialise la matrice en fonction des choix fait par l'utilisateur*/
		afficher = 0;
		switch(continuer){
		case 13:
		case 12:
		case 11:
			do{
				printf("voulez vous afficher graphiquement le resultat ? (oui = 1, non = 0) ");
				scanf("%d", &afficher);
			}while (afficher != 0 && afficher != 1);
			break;
		}
		if (afficher){
			printf("\ncommande :\nla pression des touches suivantes permet d'afficher ou masquer : \n"
					"c(ycle) : le chemin calculé par l'algorithme\n"
					"t(ree) : l'arbre couvrant minimum\n"
					"s(ommet) : les sommets representant les villes\n"
					"Appuyez sur esc pour fermer l'interface graphique\n");
			switch(continuer){
			case 12://un fichier liste de ville (nom_file) vient d'etre cree.
				input = fopen(nom_file, "r");
				if (input == NULL)
				{
					printf("probleme a l'ouverture du fichier\n");
					exit(1);
				}
				mat = matrice_of_coordonnees(input);
				fclose(input);
				//break omis volontairement
			case 11:// la matrice est initialisee, il suffit d'afficher le cycle
				TSP (mat, nullstream);
				fprintf(nullstream,"\n");
				//break omis volontairement
			case 13:
				gui(mat);
				break;
			}
		}
#endif
		if (mat){
			liberer_mat(mat);
			mat = NULL;
		}
	}
	fclose(nullstream);
	if (argc >= 2)fclose(output);
	return 0;
}

int generation (char *nom_file, Matrice *mat){
	char source[1000];
	char output[1000];
	int continuer = 10;

	while (continuer){
		printf("\t\t1 : depuis la console en se basant sur une liste de villes existante\n");
#ifdef GUI_ENABLE
		printf("\t\t2 : depuis l'interface graphique\n");
#endif
		printf("\t\t0 : revenir au menu precedent\n");
		scanf("%d", &continuer);

		switch(continuer){
		case 1 :
			printf("\n\tentrez le nom du fichier a partir duquel vous souhaitez creer votre liste de villes :\n");
			scanf("%s", source);
			printf("\n\tentrez le nom du fichier de sortie. Le cycle y sera inscrit:\n");
			scanf("%s", output);
			voyageur_de_commerce_utilisateur (source,  mat, (output)?output:"blop.txt");
			return 13;
			break;
#ifdef GUI_ENABLE
		case 2 :
			printf("\n\tentrez le nom du fichier de sortie :\n");
			scanf("%s", nom_file);
			printf("Cliquez a l'ecran pour placer une ville.\nAppuyez sur esc ou entree pour stopper la saisie\n\n");
			gui_generer_ville(nom_file);
			return 12;
			break;
#endif
		case 0 :
			break;
		default :
			continuer = 10;
			break;
		}
	}
	return 10;

}

