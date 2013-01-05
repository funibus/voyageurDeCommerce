#include <stdio.h>
#include <stdlib.h>
#include "structure_ville.h"

struct chemin
{
    Ville ville;
    struct chemin* ville_suivante;
};

typedef struct chemin* Chemin;


Chemin ajouter_chemin (Ville ville, Chemin suite_du_chemin)
{
    Chemin nouvelle_ville = (struct chemin*) malloc(sizeof(struct chemin));
    if (nouvelle_ville == NULL)
    {
        printf("probleme d'allocation memoire pour le chemin");
        exit(1);
    }
    nouvelle_ville->ville = ville;
    nouvelle_ville->ville_suivante = suite_du_chemin;

    return nouvelle_ville;
}

void liberer_chemin (Chemin chemin)
{
    if (chemin != NULL)
    {
        liberer_chemin (chemin->ville_suivante);
        free (chemin);
    }
}




//prend en entree un tableau avec les coordonnees de toutes les villes, et le chemin initial du voyageur de commerce
//(avec au moins une ville dedans).
//rajoute au chemin les villes traversees par le voyageur de commerce mais non demandees
void villes_traversees (Chemin premiere_ville, Chemin ville_en_court, Ville* tab_villes, int nb_villes)
{
    int i;
    double x1,y1,x2,y2,x3,y3;
    double aire; //on calcule l'aire du triangle formee par 3 ville
    double aire_max = 0; //pour acceptre une ville sur le chemin, il faut que cette aire soit plus petite qu'une valeur qu'on se fixe
    double dmin; //plus petite distance trouvee entre une la ville en court et une ville sur le chemin
    int tmp = -1; //meilleure ville trouvee pour l'instant, l'entier represente sa position dans le tableau
    if (ville_en_court->ville_suivante != NULL)
    {
        x1 = getXVille(ville_en_court->ville);
        y1 = getYVille(ville_en_court->ville);
        x2 = getXVille(ville_en_court->ville_suivante->ville);
        y2 = getYVille(ville_en_court->ville_suivante->ville);
        dmin = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2); //on considere les distances au carre pour economiser la racine
                                               //si on trouve une ville sur le chemin, la distance entre cette ville et la ville
                                               //de depart sera plus courte qu'entre la ville de depart et celle d'arrivee
        for (i=0; i<nb_villes; i++)
        {
            x3 = getXVille(tab_villes[i]);
            y3 = getYVille(tab_villes[i]);
            aire = (x3-x1)*(y3-y2)-(y3-y1)*(x3-x2);
            aire = aire*aire/((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1)); //on prend les carres pour avoir des resultats positifs
                                                               //et on quotiente par la distance pour eviter des resultats aberrants
            if (aire<=aire_max && ((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))<dmin && ((x3-x1)*(x2-x1)+(y3-y1)*(y2-y1))>0)
            /*il faut que le point soit proche de la droite, moins loin que le point trouve precedement et bien sur le segment et pas
              n'importe ou sur la droite*/
            {
                dmin = ((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
                tmp = i;
            }
        };
        if (tmp != -1) //si on a trouve une ville sur le chemin, on la rajoute entre la ville en court et la suivante
        {
            Chemin nouvelle_ville = (struct chemin*) malloc(sizeof(struct chemin));
            if (nouvelle_ville == NULL)
            {
                printf("probleme d'allocation memoire pour le chemin");
                exit(1);
            }
            nouvelle_ville->ville = tab_villes[tmp];
            nouvelle_ville->ville_suivante = ville_en_court->ville_suivante;
            ville_en_court->ville_suivante = nouvelle_ville;

            villes_traversees (premiere_ville, nouvelle_ville, tab_villes, nb_villes);
        }
        else
        {
            villes_traversees (premiere_ville, ville_en_court->ville_suivante, tab_villes, nb_villes);
        }

    }
}

