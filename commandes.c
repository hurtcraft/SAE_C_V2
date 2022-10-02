
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commandes.h"
#include "fonctions.h"
#define nb_args_min_epr 3 //on définie ici le nombre minimum d'argument que prend la commande épreuve
                          //soit 3 (num_semestre nom_matiere nom épreuve)
Commande get_commande(){
    Commande ma_commande;
    char buffer[256];
    char temp[30]={0};
    
    ma_commande.nb_args=0;
    
    scanf(" %[^\n]",buffer);

    if (strcmp(buffer,"exit")==0)
    {
        /* si l'utilisateur ecrit "exit"--> sortie programme 
        pas besoin d'executé le reste*/
        exit_prog();
    }

    if(buffer[strlen(buffer)+1]==' '){
        buffer[strlen(buffer)]='\0';
    }
    unsigned int i =0;
    unsigned int count=0;
    strcat(buffer," ");//l'ajout d'un espace est necessaire
                       //-->voir fonctionnement de la boucle 
    while (buffer[i]!='\0')
    {

        if (buffer[i]==' '){
            
            if (ma_commande.nb_args==0){
                strcpy(ma_commande.nom_commande,temp);
                
            }
            else{
                strcpy(ma_commande.args[ma_commande.nb_args-1],temp);
            }
            
            ma_commande.nb_args++;
            count=0;
            clear_str(temp,strlen(temp));
            
        }
        else{
            temp[count]=buffer[i];
            ++count;
        }
        ++i;
    }
    strcpy(ma_commande.args[ma_commande.nb_args-1],temp);
    //pour ajouté le dernier args qui n'est pas pris en compte par la boucle
    --ma_commande.nb_args;
    return ma_commande;

}

void analyse_commande(Commande ma_commande){

    if(strcmp(ma_commande.nom_commande,"epreuve")==0 ){

        printf("sqds");
    
    }

}
void exit_prog(){
    printf("programme terminé :)\n");
    exit(EXIT_SUCCESS);
}



BOOL create_formation(Commande ma_commande,Commande_Formation *commande_F){
    /* return True si la formation à pu se créer
    */
    if (ma_commande.nb_args!=1)
    {
        printf("trop ou pas assez de d'argument pour la commande <formation>\n ex: <formation> <nb_UE:INT>\n");
        return False;
    }
    int nb_UE;
    if (*ma_commande.args[0]>=48 && *ma_commande.args[0]<=57)
    //ma_commande.args doit etre compris entre 0 et 9 soit 48 et 57 dans la table ascii
    {
        nb_UE=atoi(ma_commande.args[0]);
    }
    else{
        printf("saisie incorrect <formation> <nb_UE:INT>\n");
        return False;
    }

    if (commande_F->nb_UE_is_def==True){
        printf("Le nombre d'UE est deja definie\n");
        return False;
    }
    
    else if(nb_UE>=3 && nb_UE<=6){
        printf("Le nombre d'UE est definie\n");
        commande_F->nb_UE_is_def=True;
        commande_F->nb_UE=nb_UE;
        return True;
        
    }
    else{
        printf("Le nombre d'UE est incorrect\n");
        commande_F->nb_UE_is_def=False;
        return False;
    }

}

void init_formation(Commande ma_commande,Commande_Formation *commande_F){
    commande_F->nb_UE_is_def=False;
    BOOL formation_is_valid=False;
    
    while (formation_is_valid==False)
    {

        ma_commande=get_commande();
        if(strcmp(ma_commande.nom_commande,"formation")!=0 ){
            printf("Le nombre d'UE n'est pas definie\n");
            continue;
        }
        else{
            formation_is_valid=create_formation(ma_commande,&*commande_F);
            
                    
            if(commande_F->nb_UE_is_def==False){
                printf("le nombre d'UE n'est pas definie\n");
                continue;
            }
        }

    }

}

BOOL create_epreuve(Commande ma_commande , Commande_Epreuve *commande_E, int nb_UE,Matiere liste_mat[],int *nb_matiere){
    int nb_coeff_equal_zero=0;
    float mon_coeff=0.;
    

    if(ma_commande.nb_args!=nb_args_min_epr+nb_UE){
        printf("Trop ou pas assez d'argument : \n ex : <epreuve> <num_semestre> <nom_matiere> <nom_epreuve><1_coeff_par_UE>il y'a %d UE\n",nb_UE);
        return False;
    }
    commande_E->num_semestre=atoi(ma_commande.args[0]);   
    strcpy(commande_E->nom_matiere,ma_commande.args[1]);
    strcpy(commande_E->nom_epreuve,ma_commande.args[2]); 

    for (size_t i = 0; i < nb_UE; i++)
    {
        mon_coeff=strtof(ma_commande.args[i+3],NULL);
        if(mon_coeff==0){
            nb_coeff_equal_zero++;
        }
        else if (mon_coeff<0){
            printf("Au moins un des coefficients est incorrect\n");
            return False;
        }
        commande_E->tab_coeff_UE[i]=mon_coeff;
    }

    if(nb_coeff_equal_zero==nb_UE){
        printf("Au moins un des coefficients doit etre positif\n");
        return False;
    }
    if (semestre_is_valid(ma_commande)==False){
        return False;
    }


    int matiere_indice=get_matiere_indice(*commande_E,liste_mat,*nb_matiere);
    Matiere ma_matiere;
    if (epreuve_already_exist(*commande_E,liste_mat,*nb_matiere)==True){
        printf("Une meme epreuve existe deja\n");
        return False;

    }
    if (matiere_indice==-1){
        // creation matiere
        
        ma_matiere.nb_epreuve=0;
        strcpy(ma_matiere.nom,commande_E->nom_matiere);
        ma_matiere.liste_epr[ma_matiere.nb_epreuve]=*commande_E;
        ma_matiere.nb_epreuve+=1;
        liste_mat[*nb_matiere]=ma_matiere;
        *nb_matiere+=1;
        printf("Matiere ajoutee a la formation\n");
        
    }
    else{
        
        ma_matiere.liste_epr[ma_matiere.nb_epreuve]=*commande_E;
        ma_matiere.nb_epreuve+=1;
        liste_mat[matiere_indice]=ma_matiere;
        
    }
    printf("Epreuve ajoutee a la formation\n");
    return True;


}
   
BOOL verif_coeff(Commande ma_commande ,Matiere liste_mat[],int nb_matiere, int nb_UE){
    if (semestre_is_valid(ma_commande)==False)
    {
        return False;
    }
    int num_semestre=atoi(ma_commande.args[0]);

    int *tab_UE=calloc(nb_UE,sizeof(int));
    int count=0;
    for (size_t i = 0; i < nb_matiere; i++)
    {   //parcours matieres
    
        for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
        {   //parcours epreuves
            if(liste_mat[i].liste_epr[j].num_semestre==num_semestre){
                if (liste_mat[i].nb_epreuve==0)
                {
                    count++;
                    continue;
                    
                }
                
                for (size_t z = 0; z < nb_UE; z++)
                {
                    
                    if(liste_mat[i].liste_epr[j].tab_coeff_UE[z]>0.){
                        tab_UE[z]+=1;
                    }
                
                }
        
            }
            
        }
    }
    if (count!=0)
    {
        printf("Le semestre ne contient aucune epreuve\n");
        return False;
    }
    
    for (size_t i = 0; i < nb_UE; i++)
    {
        if (tab_UE[i]==0)
        {
            printf("Les coefficients d’au moins une UE de ce semestre sont tous nuls\n");
            return False;
        }
        
    }
    
    
    
    
    printf("Coefficients corrects\n");

    return True;   
}

void add_note(Commande ma_commande,int nb_matiere,Matiere liste_mat[],Etudiant liste_etu[],int *nb_etudiant){
    if (semestre_is_valid(ma_commande)==False)
    {
        return;
    }
    
    Commande_Note ma_note;
    // on met les données de "ma_commande" dans "ma_note"
    ma_note.num_semestre=atoi(ma_commande.args[0]);
    strcpy(ma_note.nom_etudiant,ma_commande.args[1]);
    strcpy(ma_note.nom_matiere,ma_commande.args[2]);
    strcpy(ma_note.nom_epreuve,ma_commande.args[3]);
    ma_note.note=atoi(ma_commande.args[4]);
    Etudiant mon_etudiant;

    BOOL matiere_exist=False;
    BOOL epreuve_exist=False;
    int etudiant_indice=-1;
    for (size_t i = 0; i < nb_matiere; i++)
    {
        if (strcmp(liste_mat[i].nom,ma_note.nom_matiere)==0)
        {
            matiere_exist=True;
        }

        for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
        {
            if (strcmp(liste_mat[i].liste_epr[j].nom_epreuve,ma_note.nom_epreuve)==0)
            {
                epreuve_exist=True;
            }
            
        }
        
    }
    if (matiere_exist==False)
    {
        printf("Matiere inconnue\n");
        return;
    }
    if (epreuve_exist==False)
    {
        printf("Epreuve inconnue\n");
        return;
    }

    if (ma_note.note>20 && ma_note.note<0)
    {
        printf("Note incorrecte\n");
        return;
    }
    // pb "une note deja ajouter a letudiant"
        

    
    for (size_t z = 0; z < *nb_etudiant; z++)
    {
        if (strcmp(liste_etu[z].nom,ma_note.nom_etudiant)==0)
        {
            etudiant_indice=z;
            for (size_t i = 0; i < nb_matiere; i++)
            {//parcours des matieres
                if (strcmp(mon_etudiant.liste_evaluation_matiere[i].nom,ma_note.nom_matiere)==0)
                {
                    for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
                    {
                        if (strcmp(mon_etudiant.liste_evaluation_matiere[i].liste_epr[j].nom_epreuve,ma_note.nom_epreuve)==0)
                        {
                            printf("Une note est deja definie pour cet etudiant\n");
                            return;
                        }

                        
                    }
                }
            
            }
    
            break;// on fait un break ici car lorsqu'on trouve l'etudiant en question, on a plus besoin de parcourir le reste de la liste d'etu
        }
        
    }
    //creation nv etudiant si il n'est pas dans la liste
    //strcpy(mon_etudiant.liste_evaluation_matiere[0].nom,"math");
    //strcpy(mon_etudiant.liste_evaluation_matiere[0].liste_epr[0].nom_epreuve,"dst");
    //strcpy(mon_etudiant.liste_evaluation_matiere[0].liste_epr[1].nom_epreuve,"proj");
    int indice_epreuve;
    if (etudiant_indice==-1)
    {

        strcpy(mon_etudiant.nom,ma_note.nom_etudiant);
        mon_etudiant.nb_matiere_evalue=0;
        mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].indice_epreuve=0;
        indice_epreuve=mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].indice_epreuve;


        
        mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].liste_epr[indice_epreuve].num_semestre=ma_note.num_semestre;
        mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].liste_epr[indice_epreuve].note_etudiant=ma_note.note;
        strcpy(mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].liste_epr[indice_epreuve].nom_epreuve,ma_note.nom_epreuve);
        strcpy(mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].nom,ma_note.nom_matiere);
        
        mon_etudiant.nb_matiere_evalue+=1;
        mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].indice_epreuve+=1;
        printf("%d\n",mon_etudiant.liste_evaluation_matiere[mon_etudiant.nb_matiere_evalue].indice_epreuve);
        liste_etu[*nb_etudiant]=mon_etudiant;
        *nb_etudiant+=1;
        
    }
    else{
        strcpy(liste_etu[etudiant_indice].nom,ma_note.nom_etudiant);
        
        //les ligne du bas la
        indice_epreuve=liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].indice_epreuve;
        printf("indice : %d\n ",etudiant_indice);
        liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].liste_epr[indice_epreuve].num_semestre=ma_note.num_semestre;
        liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].liste_epr[indice_epreuve].note_etudiant=ma_note.note;
        printf("note %f\n",liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].liste_epr[indice_epreuve].note_etudiant);
        strcpy(liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].liste_epr[indice_epreuve].nom_epreuve,ma_note.nom_epreuve);
        
        strcpy(liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].nom,ma_note.nom_matiere);
        liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].indice_epreuve+=1;
        printf("%d\n",liste_etu[etudiant_indice].liste_evaluation_matiere[liste_etu[etudiant_indice].nb_matiere_evalue].indice_epreuve);


    }


}