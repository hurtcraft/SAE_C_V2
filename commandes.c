
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

void exit_prog(){
    
    exit(EXIT_SUCCESS);
}



BOOL create_formation(Commande ma_commande,Commande_Formation *commande_F){
    /* return True si la formation à pu se créer
    */

    int nb_UE=atoi(ma_commande.args[0]);


    if (commande_F->nb_UE_is_def==True){
        printf("Le nombre d'UE est deja defini\n");
        return False;
    }
    
    else if(nb_UE>=3 && nb_UE<=6){
        printf("Le nombre d'UE est defini\n");
        commande_F->nb_UE_is_def = True;
        commande_F->nb_UE = nb_UE;
        return True;
        
    }
    else{
        printf("Le nombre d'UE est incorrect\n");
        commande_F->nb_UE_is_def=False;
        return False;
    }

}


BOOL create_epreuve(Commande ma_commande ,int nb_UE,Commande_Formation *ma_formation){
    if (semestre_is_valid(ma_commande) == False){
        return False;
    }

    int nb_coeff_equal_zero = 0;
    float mon_coeff = 0.;
    Commande_Epreuve commande_E;
    
    commande_E.num_semestre = atoi(ma_commande.args[0]);   
    strcpy(commande_E.nom_matiere,ma_commande.args[1]);
    strcpy(commande_E.nom_epreuve,ma_commande.args[2]); 
    Matiere *liste_mat=ma_formation->liste_semestre[commande_E.num_semestre-1].liste_mat;
    int nb_matiere=ma_formation->liste_semestre[commande_E.num_semestre-1].nb_matiere;
    

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
        commande_E.tab_coeff_UE[i] = mon_coeff;
    }

    int matiere_indice=get_matiere_indice(commande_E.nom_matiere,liste_mat,nb_matiere);
    Matiere ma_matiere;
    if (epreuve_already_exist(commande_E,liste_mat,nb_matiere)==True)
    {
        printf("Une meme epreuve existe deja\n");
        return False;
    }
    if(nb_coeff_equal_zero==nb_UE){
        printf("Au moins un des coefficients est incorrect\n");
        return False;
    }
        
    if (matiere_indice==-1){
        // creation matiere
        
        ma_matiere.nb_epreuve=0;
        strcpy(ma_matiere.nom,commande_E.nom_matiere);
        ma_matiere.liste_epr[ma_matiere.nb_epreuve]=commande_E;
        ma_matiere.nb_epreuve+=1;
        liste_mat[nb_matiere]=ma_matiere;
        nb_matiere+=1;
        printf("Matiere ajoutee a la formation\n");

        ma_formation->liste_semestre[commande_E.num_semestre-1].nb_matiere++;
        
    }
    else{
        liste_mat[matiere_indice].liste_epr[liste_mat[matiere_indice].nb_epreuve] = commande_E;
        liste_mat[matiere_indice].nb_epreuve += 1;
    }
    printf("Epreuve ajoutee a la formation\n");
    return True;
}

int verif_coeff(Commande ma_commande ,Commande_Formation ma_formation){
    if (semestre_is_valid(ma_commande)==False)
    {
        return -1;
    }
    int num_semestre=atoi(ma_commande.args[0]);
    int nb_UE=ma_formation.nb_UE;
    int nb_matiere = ma_formation.liste_semestre[num_semestre-1].nb_matiere;
    Matiere *liste_mat=ma_formation.liste_semestre[num_semestre-1].liste_mat;
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
    if (nb_matiere==0)
    {

        return 1;
    }

    for (size_t i = 0; i < nb_UE; i++)
    {
        if (tab_UE[i]==0)
        {

            return 2;
        }
        
    }
    
    return 0;   
}


void add_note(Commande ma_commande,Commande_Formation ma_formation,Etudiant liste_etu[],int *nb_etudiant){
    if (semestre_is_valid(ma_commande)==False)
    {
        return;
    }

    int num_semestre=atoi(ma_commande.args[0]);
    char nom_etudiant[MAX_CHAR];
    char nom_matiere[MAX_CHAR];
    char nom_epreuve[MAX_CHAR];
    float note = atof(ma_commande.args[4]);
    strcpy(nom_etudiant,ma_commande.args[1]);
    strcpy(nom_matiere,ma_commande.args[2]);
    strcpy(nom_epreuve,ma_commande.args[3]);

    Etudiant mon_etudiant;
    Matiere *liste_mat=ma_formation.liste_semestre[num_semestre-1].liste_mat;
    BOOL matiere_exist=False;
    BOOL epreuve_exist=False;
    int etudiant_indice=-1;
    int nb_matiere = ma_formation.liste_semestre[num_semestre-1].nb_matiere;
    for (size_t i = 0; i < nb_matiere; i++)
    {
        if (strcmp(liste_mat[i].nom,nom_matiere)==0)
        {
            matiere_exist=True;
        }

        for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
        {
            if (strcmp(liste_mat[i].liste_epr[j].nom_epreuve, nom_epreuve)==0)
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

    if ( note>20 || note<0)
    {
        printf("Note incorrecte\n");
        return;
    }

    
    for (size_t z = 0; z < *nb_etudiant; z++)
    {
        if (strcmp(liste_etu[z].nom, nom_etudiant)==0)
        {
            etudiant_indice=z;
            for (size_t i = 0; i < nb_matiere; i++)
            {//parcours des matieres
                if (strcmp(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[i].nom, nom_matiere)==0)
                {
                    for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
                    {
                        if (strcmp(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[i].liste_epr[j].nom_epreuve, nom_epreuve)==0)
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

    int indice_epreuve;
    if (etudiant_indice==-1)
    {
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_note=0;
        // ici
        mon_etudiant.nb_matiere_evalue=0;
        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].indice_epreuve=0;

        indice_epreuve = mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].indice_epreuve;
        strcpy(mon_etudiant.nom, nom_etudiant);

        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].liste_epr[indice_epreuve].note_etudiant = note;
        strcpy(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].liste_epr[indice_epreuve].nom_epreuve, nom_epreuve);
        strcpy(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].nom ,  nom_matiere);
        
        
        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[mon_etudiant.nb_matiere_evalue].indice_epreuve+=1;
        mon_etudiant.nb_matiere_evalue+=1;
        //mon_etudiant.nb_note+=1;
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_note+=1;
        
        liste_etu[*nb_etudiant]=mon_etudiant;
        *nb_etudiant+=1;

        printf("Etudiant ajoute a la formation\n");
        
    }
    // jusquici ok 
    else{
        
        strcpy(liste_etu[etudiant_indice].nom, nom_etudiant);
        // on regarde si l'etudiant a une note dans la matiere en question
        int indice_matiere=get_matiere_indice(nom_matiere,liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat , liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_matiere);
        printf("matiere indice %d matiere nom %s ",indice_matiere,nom_matiere);
        if (indice_matiere==-1)
        {
            indice_matiere = liste_etu[etudiant_indice].nb_matiere_evalue;
            liste_etu[etudiant_indice].nb_matiere_evalue+=1;
        }
        indice_epreuve = liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve;
        strcpy(liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].nom_epreuve, nom_epreuve);
        strcpy(liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].nom_matiere, nom_matiere);
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].note_etudiant = note;
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].num_semestre = num_semestre;
        //liste_etu[etudiant_indice].nb_note+=1;
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve+=1;
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_note+=1;
        

    }
    //printf("nb_matiere %s note %s ",liste_etu[*nb_etudiant-1].nom , liste_etu[*nb_etudiant-1].liste_note_semestre[0].liste_mat[0].liste_epr[1].nom_epreuve);  
    printf("Note ajoutee a l'etudiant\n");
}



int verif_note(Commande ma_commande,Etudiant liste_etu[], Commande_Formation ma_formation ,int nb_etudiant){
    
    if(semestre_is_valid(ma_commande)==False){
        return -1;
    }

    char nom_etudiant[MAX_CHAR];
    strcpy(nom_etudiant,ma_commande.args[1]);
    int nb_note_total_semestre=0;
    int indice_etudiant=get_etudiant_indice(nom_etudiant,liste_etu,nb_etudiant);
    int num_semestre=atoi(ma_commande.args[0]);
    Matiere *liste_mat=ma_formation.liste_semestre[num_semestre-1].liste_mat;
    int nb_matiere=ma_formation.liste_semestre[num_semestre-1].nb_matiere;


    if (indice_etudiant==-1)
    {
        //printf("Etudiant inconnu\n");
        return 1;
    }
    for (size_t i = 0; i < nb_matiere; i++)
    {
        nb_note_total_semestre+=liste_mat[i].nb_epreuve;
    }

    int nombre_note_etudiant=liste_etu[indice_etudiant].liste_note_semestre[num_semestre-1].nb_note ;
    if (nombre_note_etudiant < nb_note_total_semestre)
    {
        //printf("Il manque au moins une note pour cet etudiant\n");
        return 2;
    }

    //printf("Notes correctes\n");
    return 0;

}
    


void affichage_releve(Commande ma_commande, Etudiant liste_etu[],Commande_Formation ma_formation,int nb_etudiant){
    if (semestre_is_valid(ma_commande)==False)
    {
        return;
    }
    char nom_etudiant[MAX_CHAR];
    strcpy(nom_etudiant,ma_commande.args[1]);
    int num_semestre=atoi(ma_commande.args[0]);
    int indice_etudiant=get_etudiant_indice(nom_etudiant,liste_etu,nb_etudiant);

    Matiere *liste_mat_etudiant=liste_etu[indice_etudiant].liste_note_semestre[num_semestre-1].liste_mat;
    int nb_matiere = ma_formation.liste_semestre[num_semestre-1].nb_matiere;
    int nb_UE = ma_formation.nb_UE;

    if (indice_etudiant==-1)
    {
        printf("Etudiant inconnu\n");
        return;
    }
    if (verif_coeff(ma_commande,ma_formation)==2)
    {
        printf("Les coefficients de ce semestre sont incorrects");
        return;
    }
    if (verif_note(ma_commande,liste_etu,ma_formation,nb_etudiant)==2)
    {
        printf("Il manque au moins une note pour cet etudiant\n");
        return;
    }
    for (size_t i = 1; i < nb_UE+1 ; i++)
    {
        if(i==1){
            printf("              UE%d",i);
        }
        else if (i<nb_UE){
            printf("   UE%d",i);
        }
        else{
            printf("   UE%d\n",i);
        }
    }
    // tkt frero check l'ennoncer a partir de la tva comprendre 
    printf("mat 1%s \n",liste_mat_etudiant[0].liste_epr[1].nom_epreuve);
    //printf("mat 2%s \n",liste_mat_etudiant[1].nom);
    for (size_t i = 0; i < nb_matiere; i++)
    {
        //printf("%s \n",liste_mat_etudiant[i+1].nom);
        /*
        for (size_t j = 0; j < liste_mat_etudiant[i].nb_epreuve; j++)
        {
            printf("etudiant %s a eu %d coeff %d ",liste_mat_etudiant[i].liste_epr[j].note_etudiant,liste_mat_etudiant[i].liste_epr[j].);
        }
        */
    }
    
    
    
}











