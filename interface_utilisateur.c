#include "interface_utilisateur.h"

/*cette fonction renvoie -1 si nom_ville n'est pas une ville du tableau, sinon elle renvoie sa position dans le tableau*/
int trouver_ville (Ville* tab_villes, int nombre_villes, char* nom_ville)
{
	int i = 0, j=0;
	int booleen = 0;
	for (i=0; i<nombre_villes; i++)
	{
		char* nom_ville2 = getNameVille(tab_villes[i]);
		booleen = 1;
		j=0;
		do
		{
			if (nom_ville[j] != nom_ville2[j])
				booleen = 0;
			j++;
		}
		while (nom_ville2[j]!='\0' && nom_ville[j] != '\0');
		if (booleen == 1 && nom_ville[j] == '\0' && nom_ville2[j] == '\0')
			return i;
	}
	return -1;
}

/*on vide le buffer avant d'utiliser la fonction fgets pour etre sur d'avoir bien ce que l'utilisateur rentre*/
void vider_buffer ()
{
	int c=getchar();
	while (c != EOF && c != '\n')
	{
		c=getchar();
	}
}

/*la fonction fgets prend en compte le "entree" a la fin de la saisie,
avec cette fonction on parcourt le mot pour l'enlever*/
void reprendre_fgetc (char* mot)
{
	int i = 0;
	char c = mot[i];

	while (c != '\0')
	{
		i++;
		c=mot[i];
	}

	if (i >0)
	{
		mot[i-1] = '\0';
	}
}

/*Cette fonction prend en entree un vecteur avec des villes, un pointeur vers le nombre de villes totale du tableau
(qui peut etre modifie si l'utilisateur veut rajouter des villes a la main) et un pointeur vers un entier
dans lequel on mettra le nombre de villes que l'utilisateur souhaite parcourir.
L'utilisateur peut choisir dans la console le nombre de villes a parcourir, le nombre de villes qu'il veut choisir personnelement.
Il peut soit choisir des villes deja existentes, soit les ajouter a la main avec leurs coordonnees*/
Ville* interface_utilisateur (Ville* tab_villes, int* nombre_villes_total, int* nombre_villes_parcourt)
{
	int nb_villes_total = *nombre_villes_total;
	int nb_villes_main = 0;
	int i,j,k,reponse=1;
	double pos_x, pos_y;
	char nom_ville[100];
	printf ("Combien de villes voulez-vous parcourir ?\n");
	scanf ("%d", nombre_villes_parcourt);
	if (*nombre_villes_parcourt > nb_villes_total)
	{
		printf ("Il n'y a pas assez de villes dans le fichier pour faire un tel parcourt.\nOn se limite a %d villes\n", nb_villes_total);
		*nombre_villes_parcourt = nb_villes_total;
	}
	else if (*nombre_villes_parcourt<0)
	{
		*nombre_villes_parcourt = 0;
		printf ("les negatifs c'est nul\n");
	}

	printf ("Parmi ces villes combien voulez-vous en rentrer a la main ?\n (maximum 40, les autres seront choisies au debut du fichier)\n");
	scanf ("%d", &nb_villes_main);

	if (nb_villes_main>(*nombre_villes_parcourt))
	{
		nb_villes_main = *nombre_villes_parcourt;
		printf ("trop de villes par rapport au nombre de villes du parcourt :\non se limite a %d villes\n", nb_villes_main);
	}

	else if (nb_villes_main<0)
	{
		nb_villes_main = 0;
		printf ("les negatifs c'est nul\n");
	}

	Ville* tab_parcourt = (Ville*) malloc (sizeof(Ville)*(*nombre_villes_parcourt));

	/*debut de la saisie manuelle des villes*/
	i=0;
	while (i<nb_villes_main)
	{
		vider_buffer();
		printf ("rentrer une ville sans accent (%d restantes) : \n", (nb_villes_main-i));
		fgets(nom_ville, 100, stdin); //on utilise fgets plutot que scanf car scanf ne comprend pas quand il y a plusieurs mots : Le Creusot par exemple
		reprendre_fgetc(nom_ville);
		j = trouver_ville (tab_villes, nb_villes_total, nom_ville);
		if (j == -1)
		{
			printf ("La ville demandee (%s) n'existe pas  : \nTaper 1 pour recommencer la saisie \nou 2 pour rentrer manuellement ses coordonnees\n", nom_ville);
			scanf ("%d", &reponse);

			while (reponse !=1 && reponse !=2)
			{
				printf ("Ce n'est pas ce que j'ai demande, il faut repondre 1 ou 2 !\nJe vais boucler infiniement jusqu'a ce que j'obtienne un 1 ou un 2.\n\n");
				scanf ("%d", &reponse);
			}
			if (reponse == 2)
			{
				printf ("rentrer la coordonnee en x : \n");
				scanf ("%lf", &pos_x);
				printf ("rentrer la coordonnee en y : \n");
				scanf ("%lf", &pos_y);
				printf ("nouvelle ville ajoutee: %s\nx=%f, y=%f\n\n", nom_ville, pos_x, pos_y);

				tab_parcourt[i] = create_ville (nom_ville, pos_x, pos_y);
				tab_villes[nb_villes_total] = create_ville (nom_ville, pos_x, pos_y);
				nb_villes_total++;
				i++;
			}
		}

		else if (j>=0 && j<nb_villes_total)
		{
			if (i>0)
			{
				k = trouver_ville (tab_parcourt, i, nom_ville);
				if (k!=-1){
					printf ("Cette ville a deja ete choisie, veuillez en choisir une autre\n\n");
				}
				else
				{
					tab_parcourt[i]=create_ville (getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));;
					if (i!=(nb_villes_main-1))
						printf ("ville trouvee : %s\nx=%f, y=%f\nAppuyez sur entree\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
					else
						printf ("ville trouvee : %s\nx=%f, y=%f\n\nPatientez (plus ou moins longtemps)\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));

					i++;
				}
			}
			else
			{
				tab_parcourt[i]=create_ville (getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));;
				if (i!=(nb_villes_main-1))
					printf ("ville trouvee : %s\nx=%f, y=%f\nAppuyez sur entree\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
				else
					printf ("ville trouvee : %s\nx=%f, y=%f\n\nPatientez (plus ou moins longtemps)\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
				i++;
			}
		}

		else
		{
			printf("Probleme, veuillez choisir une autre ville\n\n");
		}

	}
	/*fin de la saisie manuelle des villes*/

	/*saisie automatique du reste des villes*/
	j=0;
	while (i<(*nombre_villes_parcourt))
	{
		char* nom = getNameVille(tab_villes[j]);
		k = trouver_ville(tab_parcourt, i, nom);

		if (k==-1)
		{
			tab_parcourt[i] = create_ville (getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
			i++;
		}
		j++;
	}
	/*fin de la saisie automatique des villes*/

	*nombre_villes_total = nb_villes_total;
	return tab_parcourt;
}

/**
 * permet à l'utilisateur de choisir sa liste de ville parmi une liste de villes stoker dans le fichier input
 * et d'éventuellement en rajouter. Ecrit le chemin parcouru dans le fichier output
 * @param output fichier dans le quel sera inscrit le cycle issue de l'algorithme TSP
 * @param input fichier contenant des villes et leur coordonnées
 * @param mat_parcourt Matrice dans la quelle seront stokees les villes selectionnees par l'utilisateur
 */
void voyageur_de_commerce_utilisateur (char *input, Matrice *mat_parcourt, char* output)
{
    int nb_villes = 0;
    Ville* tab_villes = create_tab_villes (input, &nb_villes);
    int nb_villes_parcourt;
    int i,j;
    double d;

    Ville* tab_parcourt = interface_utilisateur(tab_villes, &nb_villes, &nb_villes_parcourt);

    *mat_parcourt = create_mat (nb_villes_parcourt);

    for (i=0; i<nb_villes_parcourt; i++)
    {
        SetNameSommet( *mat_parcourt, i, getNameVille(tab_parcourt[i]));
        SetXSommet( *mat_parcourt, i, getXVille(tab_parcourt[i]));
        SetYSommet( *mat_parcourt, i, getYVille(tab_parcourt[i]));
    }

    for (i=0; i<nb_villes_parcourt; i++)
    {
        for (j=0; j<nb_villes_parcourt; j++)
        {
            d = distance (getXSommet(*mat_parcourt, i), getYSommet (*mat_parcourt, i), getXSommet(*mat_parcourt, j), getYSommet(*mat_parcourt, j));
            setPoid (*mat_parcourt, i, j, d);
        }
    }

    FILE* fichier_chemin= NULL;

    fichier_chemin = fopen (output, "w");
    if (fichier_chemin == NULL)
    {
        printf ("probleme a l'ouverture de %s", output);
        exit(1);
    }

   //on ecrit le chemin dans output
    TSP(*mat_parcourt, fichier_chemin);
    fclose (fichier_chemin);

    //on transforme le chemin ecrit dans output en liste de villes
    fichier_chemin = fopen (output, "r");
    Chemin chemin = chemin_of_fichier (fichier_chemin, tab_villes, nb_villes);
    fclose (fichier_chemin);

    //on reecrit le chemin avec les villes traversees mais non demandees par l'utilisateur
    villes_traversees (chemin, chemin, tab_villes, nb_villes);
    fichier_chemin = fopen (output, "w");
    fichier_of_chemin (chemin, fichier_chemin);
    fclose (fichier_chemin);
    liberer_chemin (chemin);

	liberer_tab_villes (tab_villes, nb_villes);
	liberer_tab_villes (tab_parcourt, nb_villes_parcourt);



}
