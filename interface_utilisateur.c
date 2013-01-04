#include "interface_utilisateur.h"

/*cette fonction renvoie -1 si nom_ville n'est pas une ville du tableau, sinon elle renvoie sa position dans le tableau*/
int trouver_ville (Ville* tab_villes, int nombre_villes, char* nom_ville)
{
    int i = 0, j=0;
    int booleen = 0;
    for (i=0; i<nombre_villes; i++)
    {
        char* nom_ville2 = getNameVille(tab_villes[i]);
        booleen = 1;
        j=0;
        do
        {
            if (nom_ville[j] != nom_ville2[j])
            booleen = 0;
            j++;
        }
        while (nom_ville2[j]!='\0' && nom_ville[j] != '\0');
        if (booleen == 1)
        return i;
    }
    return -1;
}

Ville* interface_utilisateur (Ville* tab_villes, int* nombre_villes_total, int* nombre_villes_parcourt)
{
    int nb_villes_total = *nombre_villes_total;
    int nb_villes_main = 0;
    int i,j,k,reponse=1;
    double pos_x, pos_y;
    char nom_ville[100];
    printf ("Combien de villes voulez-vous parcourir ?\n");
    scanf ("%d", nombre_villes_parcourt);
    if (*nombre_villes_parcourt > nb_villes_total)
    {
        printf ("Il n'y a pas assez de villes dans le fichier pour faire un tel parcourt.\nOn se limite a %d villes", nb_villes_total);
        *nombre_villes_parcourt = nb_villes_total;
    }

    printf ("Parmi ces villes combien voulez-vous en rentrer a la main ?\n (les autres seront choisies au debut du fichier)\n");
    scanf ("%d", &nb_villes_main);

    Ville* tab_parcourt = (Ville*) malloc (sizeof(Ville)*(*nombre_villes_parcourt));

/*debut de la saisie manuelle des villes*/
    i=0;
    while (i<nb_villes_main)
    {
        printf ("rentrer une ville (%d restantes) : \n", (nb_villes_main-i));
        scanf("%s", nom_ville);
        j = trouver_ville (tab_villes, nb_villes_total, nom_ville);
        if (j == -1)
        {
            printf ("La ville demandee n'existe pas  : \nTaper 1 pour recommencer la saisie \nou 2 pour rentrer manuellement ses coordonnees\n");
            scanf ("%d", &reponse);

            while (reponse !=1 && reponse !=2)
            {
                printf ("Ce n'est pas ce que j'ai demande, il faut repondre 1 ou 2 !\nJe vais boucler infiniement jusqu'a ce que j'obtienne un 1 ou un 2.\n\n");
                scanf ("%d", &reponse);
            }
            if (reponse == 2)
            {
                printf ("rentrer la coordonnee en x : \n");
                scanf ("%lf", &pos_x);
                printf ("rentrer la coordonnee en y : \n");
                scanf ("%lf", &pos_y);
                printf ("nouvelle ville ajoutee: %s\nx=%f, y=%f\n\n", nom_ville, pos_x, pos_y);

                tab_parcourt[i] = create_ville (nom_ville, pos_x, pos_y);
                tab_villes[nb_villes_total] = create_ville (nom_ville, pos_x, pos_y);
                nb_villes_total++;
                i++;
            }
        }

        else if (j>=0 && j<nb_villes_total)
        {
            if (i>0)
            {
                k = trouver_ville (tab_parcourt, i-1, nom_ville);
                if (k!=-1)
                printf ("Cette ville a deja ete choisie, veuillez en choisir une autre\n\n");

                else
                {
                    tab_parcourt[i]=tab_villes[j];
                    printf ("ville trouvee : %s\nx=%f, y=%f\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
                    i++;
                }
            }
            else
            {
                tab_parcourt[i]=tab_villes[j];
                printf ("ville trouvee : %s\nx=%f, y=%f\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
                i++;
            }
        }

        else
        {
            printf("Probleme, veuillez choisir une autre ville\n\n");
        }

    }
    /*fin de la saisie manuelle des villes*/

    /*saisie automatique du reste des villes*/
    j=0;
    while (i<(*nombre_villes_parcourt))
    {
        char* nom = getNameVille(tab_villes[j]);
        k = trouver_ville(tab_parcourt, i, nom);

        if (k==-1)
        {
            tab_parcourt[i] = tab_villes[j];
            i++;
        }
        j++;
    }
    /*fin de la saisie automatique des villes*/

    *nombre_villes_total = nb_villes_total;
    return tab_parcourt;


}
