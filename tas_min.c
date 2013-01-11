#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tas_min.h"

#define Parent(i) (i/2)
#define Fils_g(i) (2*i)
#define Fils_d(i) (2*i + 1)

double poid (Tas T, int position);

struct tas
{
	Arete ** tab;//tableau de pointeur d'arete represantant le tas
	Matrice graph;//matrice d'adjacence utilisee pour calculer le poid d'une arete
	int taille_tas_max;
	int taille_tas_courant;//indice de la premiere case non utilisee
};

double poid (Tas T, int position){
	return getPoid(T->graph, T->tab[position]->u, T->tab[position]->v);
}

/**
 * un tas contiendra au plus toutes les aretes du graphe
 * @param graph_arg matrice d'adjacence pour calculer le poids d'une arete
 * @param taille_tas_arg
 * @return le tas cree
 */
Tas creer_tas (Matrice graph_arg, int taille_tas_arg){
	Tas T = NULL;
	T = (Tas) malloc(sizeof(struct tas));
	if (T == NULL){
		fprintf(stderr, "erreur allocation tas min : pas assez de memoire");
		exit(1);
	}
	T->taille_tas_max = taille_tas_arg+1;
	T->taille_tas_courant = 1;
	T->graph = graph_arg;

	//(taille_tas_arg+1) car la premiere case ne sert pas (pour facilité la manipulation d'indice)
	T->tab = (Arete **) malloc(sizeof(Arete *)*(taille_tas_arg+1));
	if (T->tab == NULL){
		fprintf(stderr, "erreur allocation tas min : pas assez de memoire");
		exit(1);
	}
	return T;
}

void liberer_tas (Tas T){
	int i;
	//Libérer les aretes inutilisée
	for (i = 1;  i < T->taille_tas_courant; i++) {
		free(T->tab[i]);
	}
	free (T->tab);
	free (T);
}

/**
 * insert un element (l'arete (u,v))en bas du tas et le fait remonter jusqu'a ce que le poids de son parent soit plus petit que son propre poids lui
 * @param T
 * @param u
 * @param v
 */
void entasser_element (Tas T, int u, int v){
	int indice, parent;
	Arete * tmp;
	//rappel : taille_tas_courant pointe sur la premiere case vide du tableau. si le tableau est plein, l'indice depace les bornes du tableau
	if (T->taille_tas_max + 1 == T->taille_tas_courant){
		fprintf(stderr, "erreur tas min plein");
		exit(1);
	}

	indice = T->taille_tas_courant;//position ou l'on insert l'arete uv

	T->tab[T->taille_tas_courant] = (Arete *) malloc(sizeof(Arete));
	if (T->tab[T->taille_tas_courant] == NULL){
		fprintf(stderr, "erreur allocation memoire tas min");
		exit(1);
	}
	T->tab[indice]->u = u;
	T->tab[indice]->v = v;

	parent = indice / 2;
	//tant que l'element n'est pas la racine du tas, et qu'il est moins lourd que son pere, on les echanges.
	while (parent > 0 && poid(T, indice) < poid(T, parent)){
		tmp = T->tab[indice];
		T->tab[indice] = T->tab[parent];
		T->tab[parent] = tmp;

		indice = parent;
		parent = indice / 2;
	}
	T->taille_tas_courant++;
}

/**
 * si on suppose que les fils de i sont tous deux des tas min, actualise_tas actualise le tel de sorte que le tas de racine i soit un tas min
 * @param T un tas
 * @param indice du noeud a partir du quel traiter le tas
 */
void acutalise_tas (Tas T, int indice){
	//fait descendre un element qui est plus petit que l'un de ces fils
	int indice_gauche, indice_droit;
	int min_indice;// l'indice de l'element le plus petit entre indice est ses deux fils
	Arete * tmp;

	indice_gauche = Fils_g(indice);
	indice_droit = Fils_d(indice);
	min_indice = (indice_gauche < T->taille_tas_courant && poid(T, indice_gauche) < poid(T, indice))? indice_gauche : indice;
	if (indice_droit < T->taille_tas_courant && poid(T, indice_droit) < poid(T, min_indice)) min_indice = indice_droit;
	//echange indice min avec indice
	if (indice != min_indice){
		tmp = T->tab[indice];
		T->tab[indice] = T->tab[min_indice];
		T->tab[min_indice] = tmp;
		acutalise_tas(T, min_indice);
	}
}

/**
 * on renvois la racine du tas min T,
 * puis on place le dernier element de l'arbe a la racine
 * et enfin, on actualise le tas pour qu'il redevienne un tas min
 * @param T un tas min
 * @return la racine de T (le plus petit element du tas)
 */
Arete extraire_min(Tas T){
	Arete ret;
	if (T->taille_tas_courant == 1){
		fprintf(stderr, "erreur extraire min sur un tas vide");
		exit(1);
	}
	ret = *(T->tab[1]);
	free(T->tab[1]);
	T->taille_tas_courant--;
	if (T->taille_tas_courant > 1){ // Tas non vide
		T->tab[1] = T->tab[T->taille_tas_courant];
		acutalise_tas(T,1);
	}
	return ret;
}

void afficher_tas(Tas T, int indice){
	if (T->taille_tas_courant > indice){
		if (indice * 2 < T->taille_tas_courant){
			printf("(");
			afficher_tas(T, indice*2);
			printf(", (%d,%d _ %f), ", T->tab[indice]->u, T->tab[indice]->v, poid(T, indice));
			afficher_tas(T, indice*2 + 1);
			printf(")");
		}
		else
			printf("(%d,%d _ %f)", T->tab[indice]->u, T->tab[indice]->v, poid(T, indice));
	}

}
