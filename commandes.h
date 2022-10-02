#ifndef __COMMANDES_H
#define __COMMANDES_H
#include "struct.h"


Commande get_commande();
void analyse_commande(Commande ma_commande);
void exit_prog();

BOOL create_formation(Commande ma_commande,Commande_Formation *commande_F);
void init_formation(Commande ma_commande,Commande_Formation *commande_F);

BOOL create_epreuve(Commande ma_commande , Commande_Epreuve *commande_E, int nb_UE,Matiere liste_mat[],int *nb_matiere);
BOOL verif_coeff(Commande ma_comande,Matiere liste_mat[], int nb_matiere,int nb_UE);

void add_note(Commande ma_commande,int nb_matiere,Matiere liste_mat[],Etudiant liste_etu[],int *nb_etudiant);

#endif