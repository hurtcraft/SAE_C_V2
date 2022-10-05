#ifndef __STRUCT_H
#define __STRUCT_H

typedef enum BOOL {
    False,
    True,
}BOOL;

typedef struct Commande
{
    
    char nom_commande[30];
    int nb_args;//nb d'argument qui suit la commande , la commande n'est pas pris en comtpe comme un argument
    char args[10][30];//tableau en 2D pouvant contenir 10 arguments de type str dont la taille max est de 30 chars
     
    
}Commande;

typedef struct Commande_Formation{
    BOOL nb_UE_is_def;
    unsigned int nb_UE;

}Commande_Formation;

typedef struct Commande_Epreuve{
    unsigned int num_semestre;
    char nom_matiere[30];
    char nom_epreuve[30];
    float tab_coeff_UE[6]; 

    float note_etudiant;// cet attribut ne nous sert que dans le cas de la commande "notes"
}Commande_Epreuve;


typedef struct Commande_Note
{
    int num_semestre;
    char nom_etudiant[30];
    char nom_matiere[30];
    char nom_epreuve[30];
    float note;
    
}Commande_Note;


typedef struct Matiere
{
    char nom[30];
    int nb_epreuve;
    Commande_Epreuve liste_epr[5];
    
    int indice_epreuve; //cet attribut ne nous sert que dans la commande "note"
}Matiere;

typedef struct Etudiant
{
    char nom[30];
    int nb_note;
    int nb_note_s1;
    int nb_note_s2;
    int nb_matiere_evalue;
    Matiere liste_evaluation_matiere[10];


    //char matiere_note[50][30];// contient une chaine de char tel que "<matiere epreuve>" ex "programmation dst"
    //int note[50];
    /*
        ici on fait une projection entre "matiere note" et "note"
        c'est a dire que note[0] va correspondre a la note attribuer 
        a matiere_note[0];

        ex : matiere_note[0] <-- "math DST"
             note[0] <-- 12
             ici la note de l'etudiant pour le DST de math sera de 12

        
    */
}Etudiant;


#endif