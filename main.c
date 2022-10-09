#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include "fonctions.h"
#include "commandes.h"

int main(){

    
    const int NB_EPR_MAX=5;
    const int NB_MAT_MAX=10;
    Commande ma_commande;
    Commande_Formation ma_formation;
    Commande_Epreuve commande_E;
    Matiere liste_mat[NB_MAT_MAX];
    Etudiant liste_etu[100];
    int nb_matiere=0;
    int nb_etudiant=0;
    Etudiant etudiant;
    Matiere math;
    Matiere fr;
    /*
    strcpy(math.nom,"math");
    strcpy(math.liste_epr[0].nom_epreuve,"dst");
    strcpy(math.liste_epr[1].nom_epreuve,"proj");
    math.nb_epreuve=2;
    math.liste_epr[0].num_semestre=1;
    math.liste_epr[1].num_semestre=1;
    liste_mat[0]=math;
    nb_matiere++;

    strcpy(fr.nom,"fr");
    strcpy(fr.liste_epr[0].nom_epreuve,"dst");
    strcpy(fr.liste_epr[1].nom_epreuve,"oral");
    fr.liste_epr[0].num_semestre=1;
    fr.liste_epr[1].num_semestre=1;
    fr.nb_epreuve=2;
    liste_mat[1]=fr;
    nb_matiere++;
    
    Etudiant paul;
    strcpy(paul.nom,"paul");
    liste_etu[0]=paul;
    nb_etudiant++;
    printf("etu %s\n",liste_etu[0].nom);
    ma_commande=get_commande();
    verif_note(ma_commande,liste_etu,liste_mat,nb_etudiant,nb_matiere);
    */
   
    //init_formation(ma_commande,&ma_formation);

    int nb_UE;
    do
    {
        ma_commande=get_commande();

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
                verif_coeff(ma_commande,ma_formation);
            }
            else if (strcmp(ma_commande.nom_commande,"note")==0){
                add_note(ma_commande,ma_formation,liste_etu,&nb_etudiant);
                //printf("nom etu %d\n",liste_etu[nb_etudiant-1].liste_note_semestre[0].nb_note);
                //printf("nb_note etud %d \n",liste_etu[nb_etudiant-1].liste_note_semestre[0].);
            }
            
            else if (strcmp(ma_commande.nom_commande,"notes")==0){
                verif_note(ma_commande,liste_etu,ma_formation,nb_etudiant);
            }
        }
        else{
            printf("Le nombre d'UE n'est pas defini\n");
        }

       
    } while (True);

    return 0;

}