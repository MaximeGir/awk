#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define OUVERTURE_FICHIER_ERREUR 0

//Fichier ne comporte aucun entier
#define FICHIER_SANS_DONNEE_ERREUR 1

// Les parmètres du programmes conformes 
// mais erreur de syntaxe dans l'un des domaines
#define SYNTAX_DOMAIN_ERREUR 2

//Cette erreur indique les paramètres du programme 
//ne sont pas conformes au format défini
//Ce cas est autre que la syntax des domaines
#define OPTION_ERREUR 3

//deux présences ou plus  de -C ou de -L 
// -C devrait exister 0 ou 1 fois 
// -L devrait exister 0 ou 1 fois 
#define OPTION_DUPLIQUEE_ERREUR 4

//Les résultat est un tableau vide
#define TABLEAU2D_VIDE_ERREUR 5


//Cette structure offre un type de donnée repésentant un tableau 2D
struct tab2D{
int lignes; //nombre de lignes du tableau 2D
int colonnes; //nombre de colonnes du tableau 2D
char ** ptr; // représente un tableau de char* celui est interprété comme
             // un tableau 2D de taille lignes x colonnes
}; 

/**
* affiche une varaible de type struct tab2d
*
*@param mat le tableau 2D à afficher
*/
void affiche_Tab2D(struct tab2D mat);


// cette fonction est fournie
//affiche un message d'erreur sur le canal d'erreur selon les cas définis
/**
* Affiche un message d'erreur sur le canal d'erreur selon les cas définis
*
*@param err l'erreur à signaler
*/
void signaler_erreur(int err);

#endif