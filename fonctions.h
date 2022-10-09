#ifndef __FONCTIONS_H
#define __FONCTIONS_H
#include "struct.h"

void clear_str(char str[],int len);
BOOL commande_is_valid(Commande ma_commande);

int get_matiere_indice(char nom_matiere[],Matiere liste_mat[],int nb_matiere);
BOOL epreuve_already_exist(Commande_Epreuve commande_E,Matiere liste_mat[],int nb_matiere);
BOOL semestre_is_valid(Commande ma_commande);
int get_etudiant_indice(char nom_etudiant[],Etudiant liste_etu[],int nb_etudiant);


#endif