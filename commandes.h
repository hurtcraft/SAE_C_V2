#ifndef __COMMANDES_H
#define __COMMANDES_H
#include "struct.h"


Commande get_commande();
void exit_prog();

BOOL create_formation(Commande ma_commande,Commande_Formation *ma_formation);
BOOL create_epreuve(Commande ma_commande, int nb_UE,Commande_Formation *ma_formation);

BOOL verif_coeff(Commande ma_commande ,Commande_Formation ma_formation);
void add_note(Commande ma_commande,Commande_Formation ma_formation,Etudiant liste_etu[],int *nb_etudiant);

BOOL verif_note(Commande ma_commande,Etudiant liste_etu[], Commande_Formation ma_formation ,int nb_etudiant);
void affichage_releve(Commande ma_commande, Etudiant liste_etu[],Commande_Formation ma_formation,int nb_etudiant);
#endif