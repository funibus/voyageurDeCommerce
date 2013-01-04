#include <stddef.h>
#include "TSP_tests.h"
#include "structure_matrice.h"

void test_matrice_of_fichier ()
{
    FILE* fichier = NULL;
    fichier = fopen("testEdgesDistances.txt", "r");
    if (fichier == NULL)
    {
        printf("probleme a l'ouverture du fichier");
        exit(1);
    };

    Matrice matrice_poids = matrice_of_fichier(fichier);
    fclose(fichier);

    int i, j;
    for (i=0; i<13; i++)
    {
        for (j=i+1; j<14; j++)
        {
            printf("distance sommet %d, sommet %d = %f\n", i, j, getPoid(matrice_poids, i, j));
        };
    };
}



void test_matrice_of_coordonnees ()
{
    FILE* fichier = NULL;
    fichier = fopen("testVerticesCoordinates.txt", "r");
    if (fichier == NULL)
    {
        printf("probleme a l'ouverture du fichier");
        exit(1);
    };

    Matrice matrice_poids = matrice_of_coordonnees(fichier);
    fclose(fichier);

    int i, j;
    for (i=0; i<13; i++)
    {
        for (j=i+1; j<14; j++)
        {
            printf("distance sommet %d, sommet %d = %f\n", i, j, getPoid(matrice_poids, i, j));
        };
    };
}


void test_create_tab_villes ()
{
    int* nombre_villes;
    *nombre_villes = 0;
    Ville* tab_villes = create_tab_villes (nombre_villes);

    printf ("il y a %d villes\n", *nombre_villes);
    printf ("la 3eme ville est %s\n\n", getNameVille(tab_villes[2]));
}




