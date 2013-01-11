#include "test_prim.h"

/*teste la fonction TPS, retourne la liste de sommets : "1, 6, 2, 4, 7, 8, 5, 9, 10, 11, 14, 3, 13, 12"
dans le fichier chemin.txt*/
void test_TSP ()
{
  FILE* fichier = NULL;
  fichier = fopen("testVerticesCoordinates.txt", "r");
  if (fichier==NULL)
  {
    printf("probleme d'ouverture de testVerticesCoordinates.txt");
    exit(1);
  }
  Matrice matrice_poids = matrice_of_coordonnees (fichier);
  double distance = 0.;

  FILE* chemin = fopen ("chemin.txt", "w");
  TSP(matrice_poids,chemin);
  fprintf(chemin,"\n");
  fclose (chemin);
  fclose(fichier);

}

