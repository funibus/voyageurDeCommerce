#include "structure_arbre_couvrant.h"

struct element_liste
{
  int sommet;
  element_liste suivant;
};


/*cree un tableau dont chaque case represente un sommet et contient la liste des sommets voisins*/
element_liste* creer_arbre (int nombre_villes)
{
  element_liste* arbre = malloc (sizeof(element_liste) * nombre_villes);
  if (arbre == NULL)
    {
      printf("problème d'allocation pour l'arbre");
      exit(1);
    };
  int i = 0;
  for (i=0; i<nombre_villes; i++)
    {
      arbre[i] = NULL;
    };
   return arbre;
};


/*insere l'arete allant du sommet1 au sommet2 dans l'arbre*/
void inserer_element_arbre (element_liste* arbre, int sommet1, int sommet2)
{
  element_liste nouveau_voisin_1 = malloc (sizeof(struct element_liste));
  nouveau_voisin_1->sommet = sommet2;
  nouveau_voisin_1->suivant = arbre[sommet1];
  arbre[sommet1] = nouveau_voisin_1;

  element_liste nouveau_voisin_2 = malloc (sizeof(struct element_liste));
  nouveau_voisin_2->sommet = sommet1;
  nouveau_voisin_2->suivant = arbre[sommet2];
  arbre[sommet2] = nouveau_voisin_2;
}


/*libere la place occupee par une liste*/
void liberer_liste (element_liste element)
{
  if (element != 0)
    {
      liberer_liste (element->suivant);
      free (element);
    };
}

/*libere la place occupee par un arbre*/
void liberer_arbre (element_liste* arbre, int nombre_villes)
{
  int i = 0;
  for (i=0; i<nombre_villes; i++)
    {
      liberer_liste (arbre[i]);
    };
}


/*parcourt l'arbre en partant d'un sommet donné, sans passer par le sommet du père, et renvoie la liste des sommets dans l'ordre du parcours,
  en ne notant un sommet que la premiere fois qu'on passe dessus*/
void parcourir_arbre_aux (FILE* fichier, element_liste* arbre, int sommet, int pere, int b)
{
  if(b==0)
  fprintf (fichier, "%d", sommet);

  else
  fprintf (fichier, ", %d", sommet);

  element_liste fils = arbre[sommet];
  while (fils != NULL)
    {
      if ((fils->sommet) != pere)
	{
	  parcourir_arbre_aux (fichier, arbre, (fils->sommet), sommet, 1);
	};
      fils = fils->suivant;
    };
}


/*cette fonction parcourt l'arbre, en inscrivant une seule fois chaque sommet, et en partant du sommet 0*/
void parcourir_arbre (FILE* fichier, element_liste* arbre)
{
  parcourir_arbre_aux (fichier, arbre, 0, -1, 0);
}


double distance_parcourue (FILE* fichier, Matrice matrice_poids)
{
  int nombre_villes = getNbVilles (matrice_poids);
  int i = 0;
  double distance = 0.;
  int sommet1;
  fscanf (fichier, "%d", &sommet1);
  int sommet2;
  for (i=1; i<nombre_villes; i++)
    {
        fscanf (fichier, ", %d", &sommet2);
        distance = distance + getPoid(matrice_poids, sommet1, sommet2);
        sommet1 = sommet2;
    };
    return distance;
}


