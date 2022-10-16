#ifndef __FONCTIONS_H
#define __FONCTIONS_H
#include "struct.h"

void clear_str(char str[],int len);
BOOL commande_is_valid(Commande ma_commande);

int get_matiere_indice(char nom_matiere[],Matiere liste_mat[],int nb_matiere);
BOOL epreuve_already_exist(Commande_Epreuve commande_E,Matiere liste_mat[],int nb_matiere);
BOOL semestre_is_valid(int num_semestre);
int get_etudiant_indice(char nom_etudiant[],Etudiant liste_etu[],int nb_etudiant);
void affiche_erreur_note(int num_erreur);
void affiche_erreur_coeff(int num_erreur);
float *get_tab_coeff(int num_semestre,char nom_matiere[],char nom_epreuve[],Commande_Formation *ma_formation);
void print_entete_UE(int *nb_UE);
float get_somme_coeff(float tab_coeff[],int nb_UE);
char * add_space(char ma_chaine[],int nb_space);


#endif