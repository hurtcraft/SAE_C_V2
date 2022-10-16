#ifndef __COMMANDES_H
#define __COMMANDES_H
#include "struct.h"


Commande get_commande();

BOOL create_formation(Commande ma_commande,Commande_Formation *ma_formation);
BOOL create_epreuve(const Commande *ma_commande,Commande_Formation *ma_formation);
int verif_coeff(int num_semestre , Commande_Formation *ma_formation);
void add_note(const Commande *ma_commande,Commande_Formation *ma_formation,Etudiant liste_etu[],int *nb_etudiant);
int verif_note(int num_semestre ,char nom_etudiant[],Etudiant liste_etu[], Commande_Formation *ma_formation ,int nb_etudiant);
//int verif_note(const Commande *ma_commande,Etudiant liste_etu[], Commande_Formation *ma_formation ,int nb_etudiant);
void releve(int num_semestre,char nom_etudiant[], Etudiant liste_etu[], Commande_Formation *ma_formation,int nb_etudiant,BOOL do_affichage);
void decision(const Commande *ma_commande , Etudiant liste_etu[] , int nb_etudiant , Commande_Formation *ma_formation);

#endif