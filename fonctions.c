#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>
void clear_str(char str[],int len){
    for (size_t i = 0; i < len+1; i++){
        str[i]=0;
    }
}
BOOL commande_is_valid(Commande ma_commande){
    if (ma_commande.nom_commande[0]==-1){
        printf("Commande non reconnue ou manque d'argument \n");
        return False;
    }   
    return True;
}
int get_matiere_indice(char nom_matiere[],Matiere liste_mat[],int nb_matiere){
    /*
        return l'indice qui a était attribuer à la matiere dans liste_mat[] 
        sinon renvoie -1 si la matiere n'existe pas 
    */
    for (size_t i = 0; i < nb_matiere; i++){
        if(strcmp(nom_matiere,liste_mat[i].nom)==0){
            
            return i;
        }
    }
    
    return -1;
}


BOOL epreuve_already_exist(Commande_Epreuve commande_E,Matiere liste_mat[],int nb_matiere){

    int indice=get_matiere_indice(commande_E.nom_matiere,liste_mat,nb_matiere);
    if (indice!=-1)
    {
        for (size_t i = 0; i < liste_mat[indice].nb_epreuve; i++)
        {
            if (strcmp(liste_mat[indice].liste_epr[i].nom_epreuve,commande_E.nom_epreuve)==0)
            {
                return True;
            }
        }
        
    }
    
    return False;
    
}
BOOL semestre_is_valid(Commande ma_commande){
    //on sait que si une commande a besoin du numero de semestre , ce dernier sera toujours le premier arg
    if (atoi(ma_commande.args[0])>2 || atoi(ma_commande.args[0])<1 ){
        printf("Le numero de semestre est incorrect\n");
        return False;
    }
    return True;
}
int get_etudiant_indice(char nom_etudiant[],Etudiant liste_etu[],int nb_etudiant){
    // return l'indice de l'etudiant dans la liste d'etudiant
    // si l'etudiant n'existe pas on renvoie -1
    int indice_etudiant=-1;//si l'etudiant n'est pas dans la liste

    for (size_t i = 0; i < nb_etudiant; i++)
    {
        if (strcmp(liste_etu[i].nom,nom_etudiant)==0)
        {
            indice_etudiant=i;
            break;
            
        }
        
    }
    return indice_etudiant;
}
void affiche_erreur_note(int num_erreur){
    switch (num_erreur)
    {
    case 0:
        printf("Notes correctes\n");
        break;
    case 1:
        printf("Etudiant inconnu\n");
        break;
    case 2:
        printf("Il manque au moins une note pour cet etudiant\n");
        break;
    default:
        break;
    }
}
void affiche_erreur_coeff(int num_erreur){
    switch (num_erreur)
    {
    case 0:
        printf("Coefficients corrects\n");
        break;
    case 1:
        printf("Le semestre ne contient aucune epreuve\n");
        break;
    case 2:
        printf("Les coefficients d'au moins une UE de ce semestre sont tous nuls\n");
        break;
    default:
        break;
    }
}