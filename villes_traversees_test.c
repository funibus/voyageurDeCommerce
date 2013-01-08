#include "villes_traversees_test.h"

/*Cree une liste de villes a partir d'un fichier ou est ecrit le chemin, puis reecrit le chemin dans un autre fichier
a partir de la liste de villes.
Normalement il doit retourner un fichier resultat_chemin.txt ou les villes de chemin_test.txt apparaissent dans l'ordre inverse*/
void test_creation_chemin ()
{
   FILE* fichierChemin = NULL;
   FILE* fichier = NULL;
   fichierChemin = fopen ("chemin_test.txt", "r");

   if (fichierChemin == NULL)
   {
       printf("probleme a l'ouverture de chemin_test.txt");
       exit(1);
   }

   int nb_villes = 0;
   Ville* tab_villes = create_tab_villes (&nb_villes);

   Chemin chemin = chemin_of_fichier (fichierChemin, tab_villes, nb_villes);

   fclose(fichierChemin);

   fichier = fopen ("resultat_chemin.txt", "w");
   fichier_of_chemin (chemin, fichier);

   fclose (fichier);
   liberer_chemin(chemin);
}


/*test pour ecrire les villes entre paris et lyon : le fichier chemin_test2 contient "Paris, Lyon"
et le programme ecrit les villes intermediaires dans resultat_chemin2 :
"Lyon, Bousset, Challement, Villiers-Saint-Benoit, Avon, Ivry-sur-Seine, Paris*/
void test_villes_traversees ()
{
   FILE* fichierChemin = NULL;
   FILE* fichier = NULL;
   fichierChemin = fopen ("chemin_test2.txt", "r");

   if (fichierChemin == NULL)
   {
       printf("probleme a l'ouverture de chemin_test2.txt");
       exit(1);
   }

   int nb_villes = 0;
   Ville* tab_villes = create_tab_villes (&nb_villes);

   Chemin chemin = chemin_of_fichier (fichierChemin, tab_villes, nb_villes);

   fclose(fichierChemin);

   villes_traversees(chemin, chemin, tab_villes, nb_villes);

   fichier = fopen ("resultat_chemin2.txt", "w");
   fichier_of_chemin (chemin, fichier);

   fclose (fichier);
   liberer_chemin(chemin);

}

