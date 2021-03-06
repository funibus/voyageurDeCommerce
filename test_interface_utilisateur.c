#include "test_interface_utilisateur.h"

/*test la fonction trouver_ville : elle doit repondre "Chatenay existe : 525eme position" */
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

/*fonction de test de la fonction interface_utilisateur, avec le fichier "France_towns.txt"
  Elle doit envoyer les villes choisies dans la console*/
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

/*fonction de test de la fonction voyageur de commerce, avec le fichier "France_towns.txt"
Elle ecrit le chemin parcouru dans le fichier "test_voyageur_de_commerce.txt"*/
void test_voyageur_de_commerce ()
{
   Matrice* matrice_parcourt = malloc(sizeof(matrice_parcourt));

   voyageur_de_commerce_utilisateur ("Francetowns.txt", matrice_parcourt, "test_voyageur_de_commerce.txt");

}
