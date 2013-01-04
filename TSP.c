#include <math.h>

#include "TSP.h"

double distance (double x1, double y1, double x2, double y2);


/*calcule la matrice avec les poids des aretes a partir du fichier avec la distance entre les sommets*/
Matrice matrice_of_fichier (FILE* fichier)
{
    int nombre_villes = 0;
    fscanf (fichier, "%d!", &nombre_villes);
    int sommet1 = 0;
    int sommet2 = 0;
    int i = 0;
    double distance_sommets = 0;
    Matrice matrice_poids = create_mat (nombre_villes);
    for (i=0; i<(nombre_villes*(nombre_villes-1)/2); i++)
    {
        fscanf(fichier, "%d %d: %lf!", &sommet1, &sommet2, &distance_sommets);
        setPoid(matrice_poids, sommet1-1, sommet2-1, distance_sommets);
    };
    return matrice_poids;
}

/*calcule la distance entre 2 points de coordonnees (x1, y1) et (x2,y2)*/
double distance (double x1, double y1, double x2, double y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


/*calcule la matrice avec le poids de toutes les aretes en partant du fichier avec les coordonnees des villes*/
Matrice matrice_of_coordonnees (FILE* fichier)
{
    int nombre_villes, i, j, sommet;
    char name[1000],c;
    double sommet_x, sommet_y;
    long curseur_init;
    double* tableau; // tableau dynamique pour les villes
    Matrice matrice_poids;
    /*
    les fichiers coordonnees sommets commencent par une ligne indiquant le nombre de sommets
    alors que les fichiers coordonnees villes n'indiquent pas le nombre de villes présentes dans le fichier.
    On va tester si le fichier contient cette indication, et ci c'est le cas, on va simplement l'ignorer (et lire le fichier jusqu'a la fin)
    */
    curseur_init = ftell(fichier);//position initial dans le fichier
    c = 'A'; //c un charatere different de '\n' et de ':'
    while (c != '\n' && c != ':'){
    	c = fgetc(fichier);
    }
    if (c == ':'){// fichier avec nom de ville
    	//on compte le nombre de villes presentess dans le fichier
    	nombre_villes=1;
    	while (c != EOF){
    		c = fgetc(fichier);
    		if (c == ':'){
    			nombre_villes++;
    		}
    	}
    	fseek(fichier, 0, curseur_init);//on revient a la position initial pour traiter la premier ligne
    }
    else{//fichier sommet
    	fseek(fichier, 0, curseur_init);//on revient a la position initial pour recuperer la taille exacte du tableau
    	fscanf (fichier, "%d!", &nombre_villes);
    	if (!feof(fichier))fgetc(fichier);// saut le \n
    }


    matrice_poids = create_mat (nombre_villes);
    tableau = malloc (sizeof(double)*2*nombre_villes); //on stocke les coordonnees des villes dans un tableau pour que ce soit plus facile d'acces
    if (tableau == NULL)
    {
        printf("probleme d'allocation memoire dans la fonction matrice_of_coordonnees");
        exit(1);
    }

    for (sommet=0; sommet<nombre_villes; sommet++)
    {
    	i = -1;
    	do{
    		i++;
    		name[i] = fgetc(fichier);
    	} while (name[i] != ':');
    	name[i] = '\0';
        fscanf(fichier, "%lf; %lf!", &sommet_x, &sommet_y);
        if (!feof(fichier))fgetc(fichier);// saut le \n
        tableau[2*(sommet)]= sommet_x; //on stocke les coordonnees de i dans les cases 2i et 2i+1
        tableau[2*(sommet) +1] = sommet_y;
        SetXSommet(matrice_poids, sommet, sommet_x);
        SetYSommet(matrice_poids, sommet, sommet_y);
        SetNameSommet(matrice_poids, sommet, name);
    }

    for (i = 0; i<nombre_villes; i++) //on calcule la distance entre chaque paire de sommet
    {
        for (j=i; j<nombre_villes; j++)
        {
        	setPoid(matrice_poids, i, j, distance (tableau[2*i], tableau[2*i+1], tableau[2*j], tableau[2*j+1]));
        }
    }
    free (tableau);
    return matrice_poids;

}



int compter_villes (FILE* fichier)
{
    char c = fgetc (fichier);
    int nb_villes = 0;

    while (c != EOF)
    {
        while (c != '!' && c != EOF)
        {
            c = fgetc (fichier);
        }
        if (c == EOF)
        return nb_villes;
        else
        {
            nb_villes++;
            c = fgetc (fichier);
        }

    }
    return nb_villes;

}

/* lit le fichier France_towns.txt et renvoie un tableau tab_villes contenant toutes les villes du fichier
 pour obtenir le nombre de ville a la fin, on donne un pointeur vers un entier nb_villes, que l'on modifiera dans la fonction*/
Ville* create_tab_villes (int* nombre_villes)
{
    FILE* fichier = fopen("FranceTowns.txt", "r");
    if (fichier == NULL)
    {
        printf("probleme a l'ouverture de FranceTowns.txt");
        exit(1);
    }
    int nb_villes = compter_villes(fichier);
    int taille_tab = nb_villes + 20; // prend un tableau un peu plus grand pour pouvoir rajouter des villes a la main
    fseek(fichier, 0, SEEK_SET); //on revient au debut

    char c = fgetc (fichier);
    int i=0;
    int j;

    Ville* tab_villes =(Ville*) malloc(sizeof(Ville)*taille_tab);
    if (tab_villes == NULL)
    {
        printf ("probleme d'allocation memoire pour le tableau de villes");
        exit (1);
    }

    char nom_ville[100];
    double pos_x, pos_y;


    for (j=0; j<nb_villes; j++)
    {
        i = 0;
        while (c != ':' && c != EOF) //on laisse c != EOF des fois que le fichier n'ait pas la forme voulu
        {
            nom_ville[i] = c;
            i++;
            c = fgetc (fichier);
        }
        nom_ville[i] = '\0';
        fscanf (fichier, " %lf; %lf!\n", &pos_x, &pos_y);
        tab_villes[j] = create_ville(nom_ville, pos_x, pos_y);

        c=fgetc (fichier);

    };

    fclose (fichier);
    *nombre_villes = nb_villes;
    return tab_villes;
}
