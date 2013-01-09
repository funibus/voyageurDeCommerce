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
   int nb_villes = 0;
   Ville* tab_villes = create_tab_villes ("France_towns.txt", &nb_villes);
   FILE* fichier_chemin = NULL;
   FILE* chemin_villes_traversees = NULL;
   Matrice matrice_parcourt;

   voyageur_de_commerce_utilisateur (fichier_chemin, matrice_parcourt, "test_voyageur_de_commerce.txt");

   fichier_chemin = fopen ("chemin.txt", "r");

   Chemin chemin = chemin_of_fichier (fichier_chemin, tab_villes, nb_villes);

   fclose(fichier_chemin);

   villes_traversees(chemin, chemin, tab_villes, nb_villes);

   chemin_villes_traversees = fopen ("villes_traversees.txt", "w");
   fichier_of_chemin (chemin, chemin_villes_traversees);

   fclose (chemin_villes_traversees);
   liberer_chemin(chemin);
}
