#include "prim.h"

Arete trouver_bonne_arete (Tas T, Matrice matrice_poids);



/**
 * construit l'arbre couvrant et le stock dans matrice_poids
 * @param matrice_poids
 */
void prim (Matrice matrice_poids)
{
    int nombre_villes = getNbVilles(matrice_poids);
    int nombre_sommets_arbre = 0;
    element_liste* arbre = getTree(matrice_poids);
    Tas T = creer_tas (matrice_poids, nombre_villes*nombre_villes);
    int sommet, nouveau_sommet;
    Arete nouvelle_arete;



    /*on choisit un premier sommet qu'on met dans l'arbre, par exmeple le sommet 0*/

    setMarque(matrice_poids, 0); //ajout de 0 aux sommets de l'arbre
    nombre_sommets_arbre = 1;
    for (sommet=1; sommet<nombre_villes; sommet++) //ajout des aretes partant de 0 au tas
    {
        entasser_element(T, 0, sommet);
    }

    /*on remplit l'arbre tant que tous les sommets n'y sont pas*/

    while (nombre_sommets_arbre < nombre_villes)
    {
        nouvelle_arete = trouver_bonne_arete(T, matrice_poids);
        if (getMarque(matrice_poids,nouvelle_arete.u)){//si u appartient deja à l'arbre couvrant, on ajoute donc v
        	nouveau_sommet = nouvelle_arete.v;
        }
        else{//sinon, puisque l'arete est incidente a un sommet de l'arbre, cela veut dire que u est le sommet que l'on ajoute a l'arbre
        	nouveau_sommet = nouvelle_arete.u;
        }
        setMarque(matrice_poids, nouveau_sommet); //ajout du nouveau_sommet l'arbre
        nombre_sommets_arbre ++;
        inserer_element_arbre(arbre, nouvelle_arete.u, nouvelle_arete.v); //ajout de l'arete (u,v) a l'arbre

        //ajout des aretes incidentes au nouveau_sommet
        for (sommet=0; sommet<nombre_villes; sommet++){
        	if (getMarque(matrice_poids, sommet) == 0){//si sommet n'appartient pas a l'arbre couvrant minimal, on rajoute l'arrete (sommet, nouveau_sommet) dans le tas
        		entasser_element(T, nouveau_sommet, sommet);
        	}
        }

    }
    liberer_tas(T);
}

/**
 * quand on piohe l'arete de poids minimal, il faut vérifier qu'elle a bien une extremite
 * dans l'arbre et pas l'autre, si ce n'est pas le cas on recommence a piocher
 * jusqu'a tomber sur une arete qui convient
 * @param T un tas min qui contient des aretes n'appartenant pas a l'arbre
 * @param matrice_poids une matrice d'adjacence. Un sommet est "marque" si il appartient à l'arbre couvrant en construction
 * @return l'arrete minimal dont un seul sommet appartient a l'arbre couvrant
 */
Arete trouver_bonne_arete (Tas T, Matrice matrice_poids)
{
	Arete nouvelle_arete;
	//on cherche une arete tant que ses deux sommets sont dans l'arbre couvrant
	do{
		nouvelle_arete = extraire_min(T);
	} while (getMarque(matrice_poids, nouvelle_arete.u) && getMarque(matrice_poids, nouvelle_arete.v));

	return nouvelle_arete;
}


/**
 * cette fonction calcule un arbre couvrant minimum et ecrit le parcours correspondant
 * @param matrice_poids une matrice d'adjacence
 * @param output le flux dans le quel sera inscrit le parcours du voyageur.
 */
void TSP (Matrice matrice_poids, FILE* output)
{
    prim (matrice_poids);// arbre couvrant minimum
    parcourir_arbre(output, matrice_poids);
}
