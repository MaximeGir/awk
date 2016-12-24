/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */
 
#ifndef FONCTIONS_H
#define FONCTIONS_H

#define TAILLE_MAX_LIGNE 64999
#define TAILLE_MAX_NOM_FICHIER 100
#define TAILLE_MAX_MOT 100
#define TAILLE_LIGNE_COPIE 1000


struct tableau {
  int taille;  
  int est_max_ligne; 
  int est_max_colonne;
  int * vecteur;
}; 


/*
 * @param liste_fichier la liste des fichiers passer en argument du programme
 * @return 0 si un / des fichiers sont absent
 * @return 1 si tous les fichiers éxistent.
 */ 
 int valider_liste_fichier(char **liste_fichier, int nombre_de_fichier);


/*
 * @param FILE * fp : fichier 
 * @return le nombre de ligne du fichier texte en parametre (fp) 
 */ 
 int nbre_lignes_fichier(FILE *fp);
 

/*
 * @param file le fichier à analyser
 * @param nombre_ligne le nombre de ligne correspondant à la taille du vecteur.
 * @return un pointeur d'entier , qui correspond au vecteur.
 */
 int * get_vecteur(FILE *file, int nombre_ligne);

 
/*
 * @param vecteur le vecteur qui represente le fichier a traiter
 * @param taille_vecteur la taille du vecteur à traiter
 * @return le max du tableau pointé par vecteur et de taille v
 * @return 0 si le tableau est vide (NULL)
 */
 int get_max_nb_colonne(int * vecteur , int taille_vecteur);
 
 
/*
 * @param nb_fichier , nombre de fichier a traiter, correspond à taille de tableau_de_vecteur
 * @param tableau_de_vecteur, le tableau de structure contenant les vecteurs à analyser
 * @param index_max_colonne l'index de tableau_de_vecteur correspondant au vecteur contenant le max de colonne
 * @return le maximum des colonne trouver dans le tableau_de_vecteur.
 */
 int trouver_nombre_colonne_maximale(int nb_fichier, struct tableau tableau_de_vecteur[], int *index_max_colonne);

 
/*  
 * @param nb_fichier , nombre de fichier à traiter , correspond à taille de tableau_de_vecteur
 * @param tableau_de_vecteur, le tableau de structure contenant les vecteurs à analyser
 * @return le maximum des colonne trouver dans le tableau_de_vecteur.
 */
 int trouver_nombre_ligne_maximale(int nb_fichier, struct tableau tableau_de_vecteur[], int * index_max_ligne);
 

/*
 * @param fichier le fichier duquel nous allons construire la structure
 * @param vecteur le pointeur sur le vecteur contenant le meta-data du fichier
 * @param ligne entier representant la taille du vecteur 
 * @param colonne entier representant le nombre de colonne
 * @return tableau de pointeur de char 
 */
 char ** charger(FILE *fichier, int ligne, int colonne, char **matrice, char option, int nombre_ligne);

 
 /*
  * @param nb_fichier le nombre de fichier à fusionner
  * @param tableau_de_matrice[] un tableau de type struct tab2D * contenant les pointeurs sur les matrices
  *        représenter en structure. (pointeur de structure)
  * @param sens_de_fusion est soit 'V' ou 'H' et détermine l'algoritme de fusion (horizontale ou vertical)
  * @return un pointeur de structure tab2D représentant la matrice fusionné à filtrer.
  */
  struct tab2D * fusionner_les_matrices(int nb_fichier, struct tab2D * tableau_de_matrice[], char sens_de_fusion); 
 
 
 /*
  * @param matrice la structure tab2D à réduire
  * @param control_colonne le vecteur specifiant les colonne à enlever (1) et à garder (0)
  * @param control_ligne le vecteur specifiant les lignes à enlever (1) et à garder(0)
  * @return un pointeur de structure tab2D représentant la matrice réduite à envoyer à l'affichage.
  */
  struct tab2D *filter(struct tab2D *matrice,int *control_ligne, int *control_colonne, int ligne, int colonne);

#endif