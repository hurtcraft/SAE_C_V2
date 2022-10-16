
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "commandes.h"
#include "fonctions.h"

Commande get_commande(){
    Commande ma_commande;
    char buffer[256];
    char temp[30]={0};
    
    ma_commande.nb_args=0;
    
    scanf(" %[^\n]",buffer);


    /*
    if(buffer[strlen(buffer)+1]==' '){
        buffer[strlen(buffer)]='\0';
    }
    */
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

//========================Commande Formation================================

BOOL create_formation(Commande ma_commande,Commande_Formation *commande_F){
    /* 
        return True si la formation à pu se créer
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

//===================================Commande Epreuve=============================
BOOL create_epreuve(const Commande *ma_commande ,Commande_Formation *ma_formation){
    /*
        return True si l'epreuve a pu se cree False sinon
    */
    int num_semestre=atoi(ma_commande->args[0]);
    if (semestre_is_valid(num_semestre) == False){
        return False;
    }
    int nb_UE=ma_formation->nb_UE;
    int nb_coeff_equal_zero = 0;
    float mon_coeff = 0.;
    Commande_Epreuve commande_E;
    
    commande_E.num_semestre = atoi(ma_commande->args[0]);   
    strcpy(commande_E.nom_matiere,ma_commande->args[1]);
    strcpy(commande_E.nom_epreuve,ma_commande->args[2]); 
    Matiere *liste_mat=ma_formation->liste_semestre[commande_E.num_semestre-1].liste_mat;
    // liste_mat contient la liste de toutes les matieres de la formation pour un semestre donnée
    int nb_matiere=ma_formation->liste_semestre[commande_E.num_semestre-1].nb_matiere;
    

    for (size_t i = 0; i < nb_UE; i++)
    {
        mon_coeff=strtof(ma_commande->args[i+3],NULL);
        if(mon_coeff==0){
            nb_coeff_equal_zero++;
        }
        else if (mon_coeff<0){
            printf("Au moins un des coefficients est incorrect\n");
            return False;
        }
        commande_E.tab_coeff_UE[i] = mon_coeff;
    }

    int matiere_indice=get_matiere_indice(commande_E.nom_matiere,liste_mat,nb_matiere);//recuperation de l'indice de la matiere rechercher
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
//===================================Commande Coefficients=============================

int verif_coeff(int num_semestre , Commande_Formation *ma_formation){
    /*
        retourne un nombre et en fonction du nombre que verif_coeff retourne
        on pourra gérer l'affichage avec "void affiche_erreur_coeff(int num_erreur)"
    */
    if (semestre_is_valid(num_semestre)==False)
    {
        return -1;
    }
    
    int nb_UE=ma_formation->nb_UE;
    int nb_matiere = ma_formation->liste_semestre[num_semestre-1].nb_matiere;
    Matiere *liste_mat=ma_formation->liste_semestre[num_semestre-1].liste_mat;
    int *tab_UE=NULL;// tab_UE[x] va etre incrementer de 1 a chaque fois que le coefficient d'une UE 
                    //d'un semestre donner sera > 0 donc si tab_UE[x]==0
                    //sa voudra dire que tout les coefficients de cet UE de ce semestre sont nul 
    tab_UE=calloc(nb_UE,sizeof(int));
    if (tab_UE==NULL)
    {
        printf("allocation echouer");
        exit(EXIT_FAILURE);
    }
    
    int count=0;
    for (size_t i = 0; i < nb_matiere; i++)
    {   //parcours matieres
    
        for (size_t j = 0; j < liste_mat[i].nb_epreuve; j++)
        {   //parcours epreuves
            /*
            if(liste_mat[i].liste_epr[j].num_semestre==num_semestre){
                if (liste_mat[i].nb_epreuve==0)
                {
                    count++;
                    continue;
                }
            */
                for (size_t z = 0; z < nb_UE; z++)
                {
                    //parcours UE
                    if(liste_mat[i].liste_epr[j].tab_coeff_UE[z]>0.)
                    {
                        tab_UE[z]+=1;
                    }
                
                }
        
            //}

            
        }
    }
    if (nb_matiere==0)
    {
        return 1;//"Le semestre ne contient aucune epreuve\n"
    }

    for (size_t i = 0; i < nb_UE; i++)
    {
        if (tab_UE[i]==0)
        {
            return 2;//"Les coefficients d'au moins une UE de ce semestre sont tous nuls\n"
        }
        
    }
    free(tab_UE);
    
    return 0;//"Coefficients corrects\n"
}


void add_note(const Commande *ma_commande,Commande_Formation *ma_formation,Etudiant liste_etu[],int *nb_etudiant){
    /*
        ajoute des notes a un etudiant
    */
    int num_semestre=atoi(ma_commande->args[0]);
    if (semestre_is_valid(num_semestre)==False)
    {
        return;
    }


    char nom_etudiant[MAX_CHAR];
    char nom_matiere[MAX_CHAR];
    char nom_epreuve[MAX_CHAR];
    double note = atof(ma_commande->args[4]);
    strcpy(nom_etudiant,ma_commande->args[1]);
    strcpy(nom_matiere,ma_commande->args[2]);
    strcpy(nom_epreuve,ma_commande->args[3]);

    Etudiant mon_etudiant;
    Matiere *liste_mat=ma_formation->liste_semestre[num_semestre-1].liste_mat;
    BOOL matiere_exist=False;
    BOOL epreuve_exist=False;
    int etudiant_indice=-1;
    int nb_matiere = ma_formation->liste_semestre[num_semestre-1].nb_matiere;
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
    int indice_matiere;
    if (etudiant_indice == -1)
    {
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_note=0;
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_matiere=0;

        indice_matiere = mon_etudiant.liste_note_semestre[num_semestre-1].nb_matiere;
        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve=0;

        indice_epreuve = mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve;
        strcpy(mon_etudiant.nom, nom_etudiant);

        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].note_etudiant = note;
        strcpy(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].nom_epreuve, nom_epreuve);
        strcpy(mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].nom ,  nom_matiere);

        
        mon_etudiant.liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve+=1;
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_matiere+=1;
        mon_etudiant.liste_note_semestre[num_semestre-1].nb_note+=1;
        
        liste_etu[*nb_etudiant] = mon_etudiant;
        *nb_etudiant += 1;

        printf("Etudiant ajoute a la formation\n");
        
    }
    else{
        
        strcpy(liste_etu[etudiant_indice].nom, nom_etudiant);
        // on regarde si l'etudiant a une note dans la matiere en question
        indice_matiere=get_matiere_indice(nom_matiere,liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat , liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_matiere);
        if (indice_matiere == -1)
        {
            indice_matiere = liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_matiere;
            liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_matiere += 1;
        }
        indice_epreuve = liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve;
        strcpy(liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].nom_epreuve, nom_epreuve);
        strcpy(liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].nom,nom_matiere);

        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].note_etudiant = note;
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].liste_epr[indice_epreuve].num_semestre = num_semestre;

        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].liste_mat[indice_matiere].indice_epreuve+=1;
        liste_etu[etudiant_indice].liste_note_semestre[num_semestre-1].nb_note+=1;
        

    }
    printf("Note ajoutee a l'etudiant\n");
}



int verif_note(int num_semestre ,char nom_etudiant[],Etudiant liste_etu[], Commande_Formation *ma_formation ,int nb_etudiant){

    if(semestre_is_valid(num_semestre)==False){
        return -1;
    }
    
    int nb_note_total_semestre=0;
    int indice_etudiant=get_etudiant_indice(nom_etudiant,liste_etu,nb_etudiant);
    Matiere *liste_mat=ma_formation->liste_semestre[num_semestre-1].liste_mat;
    int nb_matiere=ma_formation->liste_semestre[num_semestre-1].nb_matiere;


    if (indice_etudiant==-1)
    {
        
        return 1;//"Etudiant inconnu\n"
    }
    for (size_t i = 0; i < nb_matiere; i++)
    {
        nb_note_total_semestre += liste_mat[i].nb_epreuve;
    }

    int nombre_note_etudiant = liste_etu[indice_etudiant].liste_note_semestre[num_semestre-1].nb_note ;
    if (nombre_note_etudiant < nb_note_total_semestre)
    {
        return 2;//"Il manque au moins une note pour cet etudiant\n"
    }

    
    return 0;//"Notes correctes\n"

}
    


void releve(int num_semestre,char nom_etudiant[], Etudiant liste_etu[], Commande_Formation *ma_formation,int nb_etudiant,BOOL do_affichage){
    /* la variable do_affichage est un booleen qui lorsque elle est a True , fera les affichages ,
        et lorsque cette variable est a False , elle ne fera pas les affichages , cela nous permettera
        d'utilisé la fonction "releve" dans la fonction decision plus bas
    */
    if (semestre_is_valid(num_semestre)==False)
    {
        return;
    }
    
    int indice_etudiant=get_etudiant_indice(nom_etudiant,liste_etu,nb_etudiant);

    Matiere *liste_mat_etudiant=liste_etu[indice_etudiant].liste_note_semestre[num_semestre-1].liste_mat;
    int nb_matiere = ma_formation->liste_semestre[num_semestre-1].nb_matiere;
    nb_matiere=liste_etu[0].liste_note_semestre[0].nb_matiere;
    int nb_UE = ma_formation->nb_UE;

    if (indice_etudiant==-1 && do_affichage)
    {
        printf("Etudiant inconnu\n");
        return;
    }
    if (verif_coeff(num_semestre,ma_formation)==2 && do_affichage)
    {
        printf("Les coefficients de ce semestre sont incorrects\n");
        return;
    }
    if (verif_note(num_semestre,nom_etudiant,liste_etu,ma_formation,nb_etudiant)==2 && do_affichage)
    {
        printf("Il manque au moins une note pour cet etudiant\n");
        return;
    }
    if (do_affichage)
    {
        print_entete_UE(&nb_UE);
    }
    int nb_espace=17;

    char nom_matiere[MAX_CHAR];
    char nom_epreuve[MAX_CHAR];

    float somme_coeff=0;
    float somme_note=0;

    float *tab_coeff;// pointeur sur un tableau de coefficients d'une epreuve , 
                    //pour une matiere et un semestre donner
    float *somme_coeff_moyenne_UE=NULL;// chaque case du tableau va contenir la somme des coefficients
                                      //  de chaque UE , cela nous sera utiles lorsqu'on va faire des moyennes
    somme_coeff_moyenne_UE=calloc(nb_UE,sizeof(float));
    if (somme_coeff_moyenne_UE==NULL)
    {
        printf("Allocation echouer");
        exit(EXIT_FAILURE);
    }
    
    float *somme_note_moyenne_UE=NULL;// chaque case du tableau va contenir la somme des notes 
                                     //  de chaque UE , cela nous sera utiles lorsqu'on va faire des moyennes

    somme_note_moyenne_UE=calloc(nb_UE,sizeof(float));
    if (somme_note_moyenne_UE==NULL)
    {
        printf("Allocation echouer");
        exit(EXIT_FAILURE);
    }
    

    for (size_t i = 0; i < nb_matiere; i++){

        if (do_affichage)
        {
            printf("%s",add_space(liste_mat_etudiant[i].nom,nb_espace));
        }
        
        for (size_t k = 0; k <ma_formation->nb_UE ; k++)
        {
            for (size_t j = 0; j < liste_mat_etudiant[i].indice_epreuve; j++){
                strcpy(nom_matiere , liste_mat_etudiant[i].nom);
                strcpy(nom_epreuve , liste_mat_etudiant[i].liste_epr[j].nom_epreuve) ;
                
                tab_coeff=get_tab_coeff(num_semestre-1 , nom_matiere , nom_epreuve , &*ma_formation);
                
                somme_coeff+=tab_coeff[k];
                somme_note+=liste_mat_etudiant[i].liste_epr[j].note_etudiant*tab_coeff[k];
                
            }
            if (somme_coeff==0 && do_affichage)
            {
                printf("  ND  ");
            }
            else if (somme_coeff>0 && do_affichage){
                printf(" %.1f ",floorf((somme_note/somme_coeff)*10)/10);
            }

            somme_coeff_moyenne_UE[k]+=somme_coeff;
            somme_note_moyenne_UE[k]+=somme_note;

            somme_note=0;
            somme_coeff=0;
        }
        if (do_affichage)
        {
            printf("\n");
        }
        
        
    }
    if (do_affichage)
    {
            
        printf("--\n");
        printf("%s",add_space("Moyennes",nb_espace));
    }

    float moyenne;

    for (size_t i = 0; i < nb_UE; i++)
    {
        moyenne=somme_note_moyenne_UE[i]/somme_coeff_moyenne_UE[i];
        liste_etu[indice_etudiant].releve_note[num_semestre-1][i]=moyenne;
        // on stock les moyennes de chaque etudiant dans son attribut "releve_note"
        // cela nous sera utile pour la prochaine commande
        if (do_affichage)
        {
            
            printf(" %.1f ",floorf(moyenne*10)/10);
        }
        
        
    }
    if (do_affichage)
    {
        printf("\n");
    }
    
    //on libere la mémoire qu'on a alloué
    free(somme_note_moyenne_UE);
    free(somme_coeff_moyenne_UE);
    free(tab_coeff);
}
void decision(const Commande *ma_commande , Etudiant liste_etu[] , int nb_etudiant , Commande_Formation *ma_formation){
    char nom_etudiant[MAX_CHAR];
    strcpy(nom_etudiant,ma_commande->args[0]);
    int indice_etudiant = get_etudiant_indice(nom_etudiant,liste_etu,nb_etudiant);
    
    if (indice_etudiant==-1)
    {
        printf("Etudiant inconnu\n");
        return;
    }
    for (size_t i = 1; i < NB_SEMESTRES+1; i++)
    {
        if (verif_coeff(i,&*ma_formation)!=0)
        {
            printf("Les coefficients d'au moins un semestre sont incorrects\n");
            return;
        }
    }
    for (size_t i = 1; i < NB_SEMESTRES+1; i++)
    {
        if (verif_note(i,nom_etudiant,liste_etu,&*ma_formation,nb_etudiant)==2)
        {
            printf("Il manque au moins une note pour cet etudiant\n");
            return;
        }
    }
    print_entete_UE(&ma_formation->nb_UE);
    float *tab_moyennes_annuelles = NULL;
    tab_moyennes_annuelles = calloc(ma_formation->nb_UE,sizeof(float));

    if(tab_moyennes_annuelles==NULL){
        printf("allocation echouer");
        exit(EXIT_FAILURE);
    }

    float moyenne_UE;
    for (size_t i = 1; i < NB_SEMESTRES+1; i++)
    {
        releve(i,nom_etudiant,liste_etu,&*ma_formation,nb_etudiant,False);
        printf("s%c               ",i+'0');
        for (size_t j = 0; j < ma_formation->nb_UE; j++)
        {
            moyenne_UE = liste_etu[indice_etudiant].releve_note[i-1][j];
            tab_moyennes_annuelles[j] += moyenne_UE;
            
            printf("  %.1f",floorf(moyenne_UE*10)/10);
        }
        printf("\n");
    }
    
    for (size_t i = 0; i < ma_formation->nb_UE; i++)
    {
        tab_moyennes_annuelles[i]/=NB_SEMESTRES;
    }
    
    printf("--\n");
    printf("%s",add_space("Moyennes annuelles",18));

    for (size_t i = 0; i < ma_formation->nb_UE; i++)
    {
        printf(" %.1f ",floorf(tab_moyennes_annuelles[i]*10)/10);
    }

    printf("\n%s",add_space("Acquisition",18));
    
    int nb_UE_valide=0;
    for (size_t i = 0; i < ma_formation->nb_UE; i++)
    {
        if (tab_moyennes_annuelles[i]>10)
        {
            printf(" UE%d ",i+1);
            if (i<ma_formation->nb_UE-1)
            {
                printf(",");
            }
            nb_UE_valide+=1;
            
        }
        if (i==ma_formation->nb_UE-1)
        {
            if (nb_UE_valide==0)
            {
                printf(" Aucune");
            }
            
            printf("\n%s",add_space("Devenir",18));
            if(nb_UE_valide>(ma_formation->nb_UE/2)){
                printf(" Passage");
            }
            else{
                printf(" Redoublement");
            }
        }
        
    }

    
    printf("\n");

    free(tab_moyennes_annuelles);
    
}

    
    
    












