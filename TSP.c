#include "TSP.h"


#include <math.h>

/*calcule la matrice avec les poids des aretes a partir du fichier avec la distance entre les sommets*/
Matrice matrice_of_fichier (FILE* fichier)
{
    int nombre_villes = 0;
    fscanf (fichier, "%d!", &nombre_villes);
    int sommet1 = 0;
    int sommet2 = 0;
    int i = 0;
    double distance_sommets = 0;
    Matrice matrice_poids = create_mat(nombre_villes);
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
    double d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return d;
}


/*calcule la matrice avec le poids de toutes les aretes en partant du fichier avec les coordonnees des villes*/
Matrice matrice_of_coordonnees (FILE* fichier)
{
    int nombre_villes = 0;
    fscanf (fichier, "%d!", &nombre_villes);
    int sommet = 0;
    double sommet_x, sommet_y;
    Matrice matrice_poids = create_mat (nombre_villes);
    int i = 0, j = 0;
    double* tableau = malloc (sizeof(double)*2*nombre_villes); //on stocke les coordonnees des villes dans un tableau pour que ce soit plus facile d'acces
    if (tableau == NULL)
    {
        printf("probleme d'allocation memoire dans la fonction matrice_of_coordonnees");
        exit(1);
    }

    for (i=0; i<nombre_villes; i++)
    {
        fscanf(fichier, "\n%d: %lf; %lf!", &sommet, &sommet_x, &sommet_y);
        tableau[2*(sommet-1)]= sommet_x; //on stocke les coordonnees de i dans les cases 2i et 2i+1
        tableau[2*(sommet-1) +1] = sommet_y;
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




