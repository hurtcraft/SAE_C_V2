#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>
void clear_str(char str[], int len)
{
    // met tout les cases d'une chaine de charactere à 0
    for (size_t i = 0; i < len + 1; i++)
    {
        str[i] = 0;
    }
}

int get_matiere_indice(char nom_matiere[], Matiere liste_mat[], int nb_matiere)
{
    /*
        return l'indice qui a été attribuer à la matiere dans liste_mat[]
        sinon renvoie -1 si la matiere n'existe pas
    */
    for (size_t i = 0; i < nb_matiere; i++)
    {
        if (strcmp(nom_matiere, liste_mat[i].nom) == 0)
        {

            return i;
        }
    }

    return -1;
}

BOOL epreuve_already_exist(Commande_Epreuve commande_E, Matiere liste_mat[], int nb_matiere)
{
    /*
        renvoie True si l'epreuve existe deja False sinon
    */
    int indice = get_matiere_indice(commande_E.nom_matiere, liste_mat, nb_matiere);
    if (indice != -1)
    {
        for (size_t i = 0; i < liste_mat[indice].nb_epreuve; i++)
        {
            if (strcmp(liste_mat[indice].liste_epr[i].nom_epreuve, commande_E.nom_epreuve) == 0)
            {
                return True;
            }
        }
    }

    return False;
}
BOOL semestre_is_valid(int num_semestre)
{
    /*
        renvoie False si le numero de semestre est incorrect
    */
    if (num_semestre > 2 || num_semestre < 1)
    {
        printf("Le numero de semestre est incorrect\n");
        return False;
    }
    return True;
}
int get_etudiant_indice(char nom_etudiant[], Etudiant liste_etu[], int nb_etudiant)
{
    // return l'indice de l'etudiant dans la liste d'etudiant
    // si l'etudiant n'existe pas on renvoie -1
    int indice_etudiant = -1; // si l'etudiant n'est pas dans la liste

    for (size_t i = 0; i < nb_etudiant; i++)
    {
        if (strcmp(liste_etu[i].nom, nom_etudiant) == 0)
        {
            indice_etudiant = i;
            break;
        }
    }
    return indice_etudiant;
}
void affiche_erreur_note(int num_erreur)
{
    /*
        num_erreur sera le numero de l'erreur retourner
        par notre fonction verif_note . De ce fait on pourra
        traité et afficher l'erreur en question.
    */
    switch (num_erreur)
    {
    case 0:
        printf("Notes correctes\n");
        break;
    case 1:
        printf("Etudiant inconnu\n");
        break;
    case 2:
        printf("Il manque au moins une note pour cet etudiant\n");
        break;
    default:
        break;
    }
}
void affiche_erreur_coeff(int num_erreur)
{
    /*
        num_erreur sera le numero de l'erreur retourner
        par notre fonction verif_coeff . De ce fait on pourra
        traité et afficher l'erreur en question.
    */
    switch (num_erreur)
    {
    case 0:
        printf("Coefficients corrects\n");
        break;
    case 1:
        printf("Le semestre ne contient aucune epreuve\n");
        break;
    case 2:
        printf("Les coefficients d'au moins une UE de ce semestre sont tous nuls\n");
        break;
    default:
        break;
    }
}

float *get_tab_coeff(int num_semestre, char nom_matiere[], char nom_epreuve[], Commande_Formation *ma_formation)
{
    /*
        retourne le tableau de coefficient pour une epreuve d'une matiere et d'un semestre donné
    */
    static float *tab_coeff = NULL;
    tab_coeff = calloc(ma_formation->nb_UE, sizeof(float));
    if (tab_coeff == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Matiere *liste_mat = ma_formation->liste_semestre[num_semestre].liste_mat;
    int nb_matiere = ma_formation->liste_semestre[num_semestre].nb_matiere;
    int matiere_indice = get_matiere_indice(nom_matiere, liste_mat, nb_matiere);
    for (size_t i = 0; i < liste_mat[matiere_indice].nb_epreuve; i++)
    {
        if (strcmp(liste_mat[matiere_indice].liste_epr[i].nom_epreuve, nom_epreuve) == 0)
        {
            for (size_t j = 0; j < ma_formation->nb_UE; j++)
            {
                tab_coeff[j] = liste_mat[matiere_indice].liste_epr[i].tab_coeff_UE[j];
            }
            break;
        }
    }
    return tab_coeff;
}

void print_entete_UE(int *nb_UE)
{
    /*
        affiche les entete d'UE dans les commandes 7 et 8
    */
    for (size_t i = 1; i < *nb_UE + 1; i++)
    {
        if (i == 1)
        {
            printf("                   UE%d", i);
        }
        else if (i < *nb_UE)
        {
            printf("  UE%d ", i);
        }
        else
        {
            printf("  UE%d \n", i);
        }
    }
}
char *add_space(char ma_chaine[], int nb_space)
{
    /*
        permet d'ajouté des espaces en fin
        d'une chaine de charactere , cela facilitera
        les affichages dans les commandes 7 et 8
    */
    static char buffer[MAX_CHAR];
    strcpy(buffer, ma_chaine);
    while (strlen(buffer) < nb_space)
    {
        strncat(buffer, " ", 1);
    }
    return buffer;
}