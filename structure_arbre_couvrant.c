#include "structure_arbre_couvrant.h"

/*
 * liste chainee d'entiers utilisee pour representer les voisins d'un sommet dans l'arbre couvrant
 */
struct element_liste
{
	int sommet;
	element_liste suivant;
};

element_liste parcourir_arbre_aux (FILE* fichier, element_liste* arbre, Matrice G, element_liste cycle, int sommet, int pere, int b);

/**
 * cree un tableau dont chaque case represente un sommet et contient la liste des sommets voisins
 * l'arbre couvrant contiendra toutes les villes, il est donc pertinant de le representer dans un tableau
 * @param nombre_villes : la taille du tableau à cree
 */
element_liste* creer_arbre (int nombre_villes)
{
	element_liste* arbre = calloc (sizeof(element_liste), nombre_villes);//auto initialise a NULL
	if (arbre == NULL)
	{
		printf("problème d'allocation pour l'arbre\n");
		exit(1);
	}
	return arbre;
};

/*insere l'element element au debut de la liste qui commencait par head*/
element_liste insertion_tete(element_liste head, int element)
{
	element_liste new_head = (element_liste) malloc (sizeof(struct element_liste));
	if (new_head == NULL)
		{
			printf("probleme d'allocation pour la creation d'un element_liste\n");
			exit(1);
		}
	new_head->sommet = element;
	new_head->suivant = head;
	return new_head;
}

/*insere l'arete allant du sommet1 au sommet2 dans l'arbre*/
void inserer_element_arbre (element_liste arbre[], int sommet1, int sommet2)
{
	arbre[sommet1] = insertion_tete(arbre[sommet1], sommet2);
	arbre[sommet2] = insertion_tete(arbre[sommet2], sommet1);
}


/*libere la place occupee par une liste*/
void liberer_liste (element_liste element)
{
	element_liste tmp1 = element, tmp2;
	while (tmp1 != NULL) {
		tmp2 = tmp1;
		tmp1 = tmp1->suivant;
		free(tmp2);
	}
}

/*libere la place occupee par un arbre*/
void liberer_arbre (element_liste arbre[], int nombre_villes)
{
	int i = 0;
	for (i=0; i<nombre_villes; i++)
	{
		liberer_liste (arbre[i]);
	}
	free(arbre);
}


/*parcourt l'arbre en partant d'un sommet donné, sans passer par le sommet du pere, et renvoie la liste des sommets dans l'ordre du parcours,
  en ne notant un sommet que la premiere fois que l'on passe dessus*/
element_liste parcourir_arbre_aux (FILE* fichier, element_liste* arbre, Matrice G, element_liste cycle, int sommet, int pere, int b)
{
	element_liste fils,tete_cycle;
	if(b==0) //le booleen b sert a savoir si c'est la premiere ville ou pas : si c'est la premiere ville on ne met pas de "," avant
	{
		fprintf (fichier, "%s", getNameSommet(G, sommet));
	}
	else
	{
		fprintf (fichier, ", %s", getNameSommet(G, sommet));
	}
	tete_cycle = insertion_tete(cycle, sommet);
	fils = arbre[sommet];
	while (fils != NULL)
	{
		if ((fils->sommet) != pere)
		{
			tete_cycle = parcourir_arbre_aux (fichier, arbre, G, tete_cycle, (fils->sommet), sommet, 1);
		}
		fils = fils->suivant;
	}
	return tete_cycle;
}


/*cette fonction parcourt l'arbre, en inscrivant une seule fois chaque sommet, et en partant du sommet 0*/
void parcourir_arbre (FILE* fichier, Matrice matrice_poids)
{
	element_liste tete_cycle = NULL;
	if (getNbVilles(matrice_poids))
		tete_cycle = parcourir_arbre_aux (fichier, getTree(matrice_poids), matrice_poids, tete_cycle, 0, -1, 0);
	setCycle(matrice_poids, tete_cycle);
}


/*
 * primitives d'acces
 */
int getSommetNode(element_liste l){
	return l->sommet;
}
element_liste getNextSommetTree(element_liste l){
	return l->suivant;
}



