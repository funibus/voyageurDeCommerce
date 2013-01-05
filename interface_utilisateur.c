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
        if (booleen == 1 && nom_ville[j] == '\0' && nom_ville2[j] == '\0')
        return i;
    }
    return -1;
}

void vider_buffer () //on vide le buffer avant d'utiliser la fonction fgets pour etre sur d'avoir bien ce que l'utilisateur rentre
{
    int c=getchar();
    while (c != EOF && c != '\n')
    {
        c=getchar();
    }
}

void reprendre_fgetc (char* mot) //la fonction fgets prend en compte le entree a la fin de la saisie, on parcourt donc le mot pour l'enlever
{
    int i = 0;
    char c = mot[i];

    while (c != '\0')
    {
        i++;
        c=mot[i];
    }

    if (i >0)
    {
        mot[i-1] = '\0';
    }
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
        printf ("Il n'y a pas assez de villes dans le fichier pour faire un tel parcourt.\nOn se limite a %d villes\n", nb_villes_total);
        *nombre_villes_parcourt = nb_villes_total;
    }
    else if (*nombre_villes_parcourt<0)
    {
        *nombre_villes_parcourt = 0;
        printf ("les negatifs c'est nul\n");
    }

    printf ("Parmi ces villes combien voulez-vous en rentrer a la main ?\n (maximum 40, les autres seront choisies au debut du fichier)\n");
    scanf ("%d", &nb_villes_main);

    if (nb_villes_main>(*nombre_villes_parcourt))
    {
        nb_villes_main = *nombre_villes_parcourt;
        printf ("trop de villes par rapport au nombre de villes du parcourt :\non se limite a %d villes\n", nb_villes_main);
    }

    else if (nb_villes_main<0)
    {
        nb_villes_main = 0;
        printf ("les negatifs c'est nul\n");
    }

    Ville* tab_parcourt = (Ville*) malloc (sizeof(Ville)*(*nombre_villes_parcourt));

/*debut de la saisie manuelle des villes*/
    i=0;
    while (i<nb_villes_main)
    {
        vider_buffer();
        printf ("rentrer une ville sans accent (%d restantes) : \n", (nb_villes_main-i));
        fgets(nom_ville, 100, stdin); //on utilise fgets plutot que scanf car scanf ne comprend pas quand il y a plusieurs mots : Le Creusot par exemple
        reprendre_fgetc(nom_ville);
        j = trouver_ville (tab_villes, nb_villes_total, nom_ville);
        if (j == -1)
        {
            printf ("La ville demandee (%s) n'existe pas  : \nTaper 1 pour recommencer la saisie \nou 2 pour rentrer manuellement ses coordonnees\n", nom_ville);
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
                k = trouver_ville (tab_parcourt, i, nom_ville);
                if (k!=-1)
                printf ("Cette ville a deja ete choisie, veuillez en choisir une autre\n\n");

                else
                {
                    tab_parcourt[i]=tab_villes[j];
                    printf ("ville trouvee : %s\nx=%f, y=%f\nAppuyez sur entree\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
                    i++;
                }
            }
            else
            {
                tab_parcourt[i]=tab_villes[j];
                printf ("ville trouvee : %s\nx=%f, y=%f\n\nAppuyez sur entree\n\n", getNameVille(tab_villes[j]), getXVille(tab_villes[j]), getYVille(tab_villes[j]));
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

void voyageur_de_commerce_utilisateur ()
{
    int nb_villes = 0;
    int* nombre_villes = &nb_villes;
    Ville* tab_villes = create_tab_villes (nombre_villes);
    int nb_villes_parcourt;

    Ville* tab_parcourt = interface_utilisateur(tab_villes, nombre_villes, &nb_villes_parcourt);


}
