#ifndef __STRUCT_H
#define __STRUCT_H

typedef enum BOOL {
    False,
    True,
}BOOL;
enum {
NB_SEMESTRES = 2,
MIN_UE = 3,
MAX_UE = 6,
MAX_MATIERES = 10,
MAX_EPREUVES = 5,
MAX_ETUDIANTS = 100,
MAX_CHAR = 31
};
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
    float tab_coeff_UE[MAX_UE]; 

    float note_etudiant;// cet attribut ne nous sert que dans le cas de la commande "notes"
}Commande_Epreuve;

typedef struct Matiere
{
    char nom[MAX_CHAR];
    int nb_epreuve;
    Commande_Epreuve liste_epr[MAX_EPREUVES];
    
    int indice_epreuve; //cet attribut ne nous sert que dans la commande "note"
}Matiere;


typedef struct semestre
{
    int nb_note;
    int nb_matiere;
    Matiere liste_mat[MAX_MATIERES];

}semestre;
typedef struct Etudiant
{
    char nom[MAX_CHAR];
    semestre liste_note_semestre[NB_SEMESTRES];
    float releve_note[NB_SEMESTRES][MAX_UE];

}Etudiant;

typedef struct Commande_Formation{
    BOOL nb_UE_is_def;
    unsigned int nb_UE;
    semestre liste_semestre[NB_SEMESTRES];


}Commande_Formation;





#endif