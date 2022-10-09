#ifndef __STRUCT_H
#define __STRUCT_H
#define MAX_CHAR 31
typedef enum BOOL {
    False,
    True,
}BOOL;

typedef struct Commande
{
    
    char nom_commande[MAX_CHAR];
    int nb_args;//nb d'argument qui suit la commande , la commande n'est pas pris en comtpe comme un argument
    char args[10][MAX_CHAR];//tableau en 2D pouvant contenir 10 arguments de type str dont la taille max est de MAX_CHAR chars
     
    
}Commande;
typedef struct Commande_Epreuve{
    unsigned int num_semestre;
    char nom_matiere[MAX_CHAR];
    char nom_epreuve[MAX_CHAR];
    float tab_coeff_UE[6]; 

    float note_etudiant;// cet attribut ne nous sert que dans le cas de la commande "notes"
}Commande_Epreuve;

typedef struct Matiere
{
    char nom[MAX_CHAR];
    int nb_epreuve;
    Commande_Epreuve liste_epr[5];
    
    int indice_epreuve; //cet attribut ne nous sert que dans la commande "note"
}Matiere;


typedef struct semestre
{
    int nb_note;
    int nb_matiere;
    Matiere liste_mat[10];

}semestre;

typedef struct Commande_Formation{
    BOOL nb_UE_is_def;
    unsigned int nb_UE;
    semestre liste_semestre[2];


}Commande_Formation;


typedef struct Etudiant
{
    char nom[MAX_CHAR];
    int nb_note;
    int nb_note_s1;
    int nb_note_s2;
    int nb_matiere_evalue;
    semestre liste_note_semestre[2];

    Matiere liste_evaluation_matiere[10];


    //char matiere_note[50][MAX_CHAR];// contient une chaine de char tel que "<matiere epreuve>" ex "programmation dst"
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