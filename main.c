#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include "fonctions.h"
#include "commandes.h"

int main(){
    
    const int NB_EPR_MAX=5;
    const int NB_MAT_MAX=10;
    Commande ma_commande;
    Commande_Formation commande_F;
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
   
    
    init_formation(ma_commande,&commande_F);

    int nb_UE=commande_F.nb_UE;

    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);

    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);

    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);

    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);
    ma_commande=get_commande();
    verif_coeff(ma_commande,liste_mat,nb_matiere,nb_UE);

    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);
    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);
    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);
    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);
    
    ma_commande=get_commande();
    verif_note(ma_commande,liste_etu,liste_mat,nb_etudiant,nb_matiere);
    
    //add_note(ma_commande,nb_matiere);
    







    /*
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);
    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);
    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);

    printf("--------------------------------------------------\n");    
    verif_coeff(ma_commande,liste_mat,nb_matiere,nb_UE);
    */
    return 0;

}