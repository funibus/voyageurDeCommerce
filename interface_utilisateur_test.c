#include "interface_utilisateur_test.h"

void test_trouver_ville ()
{
    int nb_villes = 0;
    int* nombre_villes = &nb_villes;
    Ville* tab_villes = create_tab_villes ("FranceTowns.txt", nombre_villes);

    int i = trouver_ville (tab_villes, *nombre_villes, "Chatenay-Malabry"); //525eme position

    if (i>=0)
    printf ("Chatenay existe : %d eme position", i);
    else
    printf ("Chatenay n'existe pas");
}

void test_interface_utilisateur ()
{
    int nb_villes = 0;
    int* nombre_villes = &nb_villes;
    Ville* tab_villes = create_tab_villes ("FranceTowns.txt", nombre_villes);
    int nb_villes_parcourt;
    int i;

    Ville* tab_parcourt = interface_utilisateur(tab_villes, nombre_villes, &nb_villes_parcourt);

    printf("les villes choisies sont :\n");
    for (i=0; i<nb_villes_parcourt; i++)
    {
        printf ("%s, ", getNameVille(tab_parcourt[i]));
    }
    printf("\n");
}

void test_voyageur_de_commerce ()
{
   FILE* chemin = NULL;
   chemin = fopen ("test_voyageur_de_commerce.txt", "w");
   Matrice matrice_parcourt = NULL;
   voyageur_de_commerce_utilisateur ("FranceTowns.txt",  &matrice_parcourt);
   TSP (matrice_parcourt, chemin);
   liberer_mat (matrice_parcourt);
}
