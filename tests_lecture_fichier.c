#include <stddef.h>
#include "tests_lecture_fichier.h"
#include "structure_matrice.h"

/*teste la lecture dans le fichier "testEdgesDistances.txt"
Ecrit le resultat de la lecture dans la console*/
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


/*Teste la lecture de fichier avec le fichier "testVerticesCoordinates.txt"
Elle doit aussi afficher ce qu'elle a lu dans la console*/
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


/*on doit trouver 100107*/
void test_compter_villes ()
{
    FILE* fichier = fopen("FranceTowns.txt", "r");
    if (fichier == NULL)
    {
        printf("probleme a l'ouverture de FranceTowns.txt");
        exit(1);
    }

    int nb_villes = compter_villes (fichier);
    fclose (fichier);

    printf ("il y a %d villes\n", nb_villes);

}

/*Teste la lecture dans le fichier "FranceTowns.txt"
la 1235eme ville est Goderville*/
void test_create_tab_villes ()
{
    int nb_villes = 0;
    int* nombre_villes = &nb_villes;
    Ville* tab_villes = create_tab_villes ("FranceTowns.txt", nombre_villes);

    printf ("il y a %d villes\n", *nombre_villes);
    printf ("la 1235eme ville est %s\n\n", getNameVille(tab_villes[1234]));
    printf ("de coordonnees x = %f, y = %f\n", getXVille(tab_villes[1234]), getYVille(tab_villes[1234]));
}



