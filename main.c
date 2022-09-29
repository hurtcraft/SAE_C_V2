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
    int nb_matiere=0;



    init_formation(ma_commande,&commande_F);

    int nb_UE=commande_F.nb_UE;
    ma_commande=get_commande();

    
    
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);
    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);
    ma_commande=get_commande();
    create_epreuve(ma_commande,&commande_E,nb_UE,liste_mat,&nb_matiere);

    printf("--------------------------------------------------\n");    
    verif_coeff(ma_commande,liste_mat,nb_matiere,nb_UE);
    
    return 0;

}