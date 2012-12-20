#include "prim.h"


element_liste* prim (Matrice matrice_poids)
{
    int nombre_villes = getNbVilles(matrice_poids);
    element_liste* arbre = creer_arbre (nombre_villes);
    Tas T = creer_tas (matrice_poids, nombre_villes*nombre_villes);
    int i;
    int nombre_sommets_arbre = 0;
    Arete nouvelle_arete;



    /*on choisit un premier sommet qu'on met dans l'arbre, par exmeple le sommet 0*/

    setMarque(matrice_poids, 0); //ajout de 0 aux sommets de l'arbre
    nombre_sommets_arbre = 1;
    for (i=1; i<nombre_villes; i++) //ajout des aretes partant de 0 au tas
    {
        entasser_element(T, 0, i);
    };

    /*on remplit l'arbre tant que tous les sommets n'y sont pas*/

    while (nombre_sommets_arbre < nombre_villes)
    {
        nouvelle_arete = trouver_bonne_arete(T, matrice_poids);
        setMarque(matrice_poids, nouvelle_arete.u); //ajout de u et v a l'arbre (on ne sait pas laquelle y est deja alors on ajoute les 2)
        setMarque(matrice_poids, nouvelle_arete.v);
        nombre_sommets_arbre ++;
        inserer_element_arbre(arbre, nouvelle_arete.u, nouvelle_arete.v); //ajout de l'arete (u,v) a l'arbre

    };


    liberer_tas(T);
    return arbre;
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
    element_liste* arbre = prim (matrice_poids);// arbre couvrant minimum
    parcourir_arbre(output, arbre);
    liberer_arbre(arbre, getNbVilles(matrice_poids));
}
