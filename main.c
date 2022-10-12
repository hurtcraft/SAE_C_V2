#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include "fonctions.h"
#include "commandes.h"

int main(){

    Commande ma_commande;
    Etudiant liste_etu[MAX_ETUDIANTS];
    Commande_Formation ma_formation;
    Commande_Epreuve commande_E;
    Matiere liste_mat[MAX_MATIERES];
    
    int nb_etudiant=0;


    int nb_UE;
    do
    {
        ma_commande=get_commande();
        if (strcmp(ma_commande.nom_commande,"e")==0)
        {
            break;
        }
        
        if (strcmp(ma_commande.nom_commande,"formation")==0)
        {
            if(create_formation(ma_commande,&ma_formation)==True)
            {
                
                nb_UE=ma_formation.nb_UE;
                
                semestre s1;
                semestre s2;
                s1.nb_matiere=0;
                s2.nb_matiere=0;
                ma_formation.liste_semestre[0]=s1;
                ma_formation.liste_semestre[1]=s2;

            };
            //continue; on a pas besoin de faire le reste si la formation n'est pas cree
        }
        if (ma_formation.nb_UE_is_def==True)
        {
            
            if (strcmp(ma_commande.nom_commande,"epreuve")==0)
            {
                create_epreuve(ma_commande,nb_UE,&ma_formation);
            }
                    
            else if(strcmp(ma_commande.nom_commande,"coefficients")==0) {                
                affiche_erreur_coeff(verif_coeff(ma_commande,ma_formation));
            }
            else if (strcmp(ma_commande.nom_commande,"note")==0){
                add_note(ma_commande,ma_formation,liste_etu,&nb_etudiant);
                //printf("nom etu %d ",liste_etu[nb_etudiant-1].liste_note_semestre[0].nb_matiere);
                /*
                int nb_matiere=liste_etu[nb_etudiant-1].liste_note_semestre[atoi(ma_commande.args[0])].nb_matiere;
                int nb_epre=liste_etu[nb_etudiant-1].liste_note_semestre[atoi(ma_commande.args[0])].liste_mat[nb_matiere].nb_epreuve;
                printf("%s a eu %f au %s de %s",liste_etu[nb_etudiant-1].nom,liste_etu[nb_etudiant-1].liste_note_semestre[atoi(ma_commande.args[0])].liste_mat[nb_matiere].liste_epr[nb_epre].note_etudiant,liste_etu[nb_etudiant-1].liste_note_semestre[atoi(ma_commande.args[0])].liste_mat[nb_matiere].liste_epr[nb_epre].nom_epreuve,liste_etu[nb_etudiant-1].liste_note_semestre[atoi(ma_commande.args[0])].liste_mat[nb_matiere].nom);
                */
            }
            
            else if (strcmp(ma_commande.nom_commande,"notes")==0){
                affiche_erreur_note(verif_note(ma_commande,liste_etu,ma_formation,nb_etudiant));
            }
            else if (strcmp(ma_commande.nom_commande,"releve")==0){
                affichage_releve(ma_commande,liste_etu,ma_formation,nb_etudiant);
            }
        }
        else{
            printf("Le nombre d'UE n'est pas defini\n");
        }

       
    } while (True);
    

    return 0;

}