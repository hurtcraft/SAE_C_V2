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
    int nb_matiere=1;
    int nb_etudiant=0;
    Etudiant etudiant;
    Matiere math;

    strcpy(math.nom,"math");
    strcpy(math.liste_epr[0].nom_epreuve,"dst");
    strcpy(math.liste_epr[1].nom_epreuve,"proj");
    math.nb_epreuve=2;
    liste_mat[0]=math;

    /*
    strcpy(etudiant.nom,"paul");
    strcpy(etudiant.liste_evaluation_matiere[0].nom,"math");
    strcpy(etudiant.liste_evaluation_matiere[0].liste_epr[0].nom_epreuve,"dst");
    etudiant.liste_evaluation_matiere[0].liste_epr[0].note_etudiant=12;
    liste_etu[0]=etudiant;
    nb_etudiant++;
    */
    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);
    ma_commande=get_commande();
    add_note(ma_commande,nb_matiere,liste_mat,liste_etu,&nb_etudiant);

    printf("note de %s au %s de %s : %f\n",liste_etu[nb_etudiant-1].nom,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].liste_epr[0].nom_epreuve,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].nom,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].liste_epr[0].note_etudiant);
    printf("note de %s au %s de %s : %f\n",liste_etu[nb_etudiant-1].nom,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].liste_epr[1].nom_epreuve,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].nom,liste_etu[nb_etudiant-1].liste_evaluation_matiere[0].liste_epr[1].note_etudiant);
    printf("%d\n",nb_etudiant);
    //init_formation(ma_commande,&commande_F);

    //int nb_UE=commande_F.nb_UE;
    /*
    int nb_UE=3;
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
    */
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