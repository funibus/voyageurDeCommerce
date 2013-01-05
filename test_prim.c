#include "test_prim.h"


void test_prim_4_villes ()
{
  FILE* fichier = NULL;
  fichier = fopen("testVerticesCoordinates.txt", "r");
  if (fichier==NULL)
  {
    printf("problème d'ouverture de testVerticesCoordinates.txt");
    exit(1);
  }
  Matrice matrice_poids = matrice_of_coordonnees (fichier);
  double distance = 0.;

  FILE* chemin = fopen ("chemin.txt", "w");
  TSP(matrice_poids,chemin);
  fclose (chemin);
  fclose(fichier);

 /*on rajoute la distance parcourue à la fin du fichier chemin.txt*/
  FILE* chemin = NULL;
  chemin = fopen("chemin.txt", "r");
  if (chemin==NULL)
  {
    printf("problème d'ouverture de chemin.txt");
    exit(1);
  }
  distance = distance_parcourue (chemin, matrice_poids);
  fclose(chemin);

  chemin = NULL;
  chemin = fopen("chemin.txt", "a");
  if (chemin==NULL)
  {
    printf("problème d'ouverture de chemin.txt");
    exit(1);
  }
  fprintf(chemin, "\ndistance parcourue : %f \n", distance);
  fclose(chemin);

}

