#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"
#include "commandes.h"

int main()
{

    Commande ma_commande;
    Etudiant liste_etu[MAX_ETUDIANTS];
    Commande_Formation ma_formation;
    Commande_Epreuve commande_E;
    Matiere liste_mat[MAX_MATIERES];

    int nb_etudiant = 0;
    int num_semestre;
    char nom_etudiant[MAX_CHAR];
    
    do
    {

        ma_commande=get_commande();
        if (strcmp(ma_commande.nom_commande,"exit")==0)
        {
            exit(EXIT_SUCCESS);
        }
        
        if (strcmp(ma_commande.nom_commande,"formation")==0)
        {
            if (create_formation(ma_commande, &ma_formation) == True)
            {

                semestre s1;
                semestre s2;
                s1.nb_matiere=0;
                s2.nb_matiere=0;
                ma_formation.liste_semestre[0]=s1;
                ma_formation.liste_semestre[1]=s2;
            }
            continue;// on a pas besoin de faire le reste si la formation n'est pas cree
        }

        if (ma_formation.nb_UE_is_def == True)
        {

            if (strcmp(ma_commande.nom_commande, "epreuve") == 0)
            {
                create_epreuve(&ma_commande, &ma_formation);
            }

            else if (strcmp(ma_commande.nom_commande, "coefficients") == 0)
            {
                num_semestre = atoi(ma_commande.args[0]);
                affiche_erreur_coeff(verif_coeff(num_semestre, &ma_formation));
            }
            else if (strcmp(ma_commande.nom_commande, "note") == 0)
            {
                add_note(&ma_commande, &ma_formation, liste_etu, &nb_etudiant);
            }

            else if (strcmp(ma_commande.nom_commande, "notes") == 0)
            {
                num_semestre = atoi(ma_commande.args[0]);
                strcpy(nom_etudiant, ma_commande.args[1]);

                affiche_erreur_note(verif_note(num_semestre, nom_etudiant, liste_etu, &ma_formation, nb_etudiant));
            }
            else if (strcmp(ma_commande.nom_commande, "releve") == 0)
            {
                num_semestre = atoi(ma_commande.args[0]);
                strcpy(nom_etudiant, ma_commande.args[1]);
                releve(num_semestre, nom_etudiant, liste_etu, &ma_formation, nb_etudiant, True);
            }
            else if (strcmp(ma_commande.nom_commande, "decision") == 0)
            {
                decision(&ma_commande, liste_etu, nb_etudiant, &ma_formation);
            }
        }
        else
        {
            printf("Le nombre d'UE n'est pas defini\n");
        }

       
    } while (True);
    

    return 0;
}