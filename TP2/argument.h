/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */
 
#ifndef ARGUMENT_H
#define ARGUMENT_H


/*
 * @param argc le nombre d'argument à la ligne de commande du programme
 * @param argv le tableau de chaine de caractere représentant la liste d'argument. 
 * @param option l'option du programme soit H ou V
 * @return le nombre d'argument concernant l'option passé en parametre.
 */
 int get_nombre_fichier(int argc, char **argv, char * option);


/*
 * @param argv le tableau de chaine de caractere représentant la liste d'argument
 * @param argc le nombre d'argument passe au programme
 * @param nombre_de_fichier le nombre de fichier passé en argument à l'option H ou V 
 * @return La liste des noms des fichiers passé en argument du programme.
 */
 char ** get_noms_des_fichiers(char **argv, int argc, int nombre_de_fichier);

 
 /*
 * @param argc le nombre d'argument passer à la ligne de commande du programme
 * @param argv le tableau de chaine de caractere représentant la liste d'argument
 * @return 0 si le format est invalide 
 * @return 1 si le format est valide 
 */
 int validation_cli_argument(int argc,  char ** argv );
 
 
 /*
 * @param argv le tableau de chaine de caractere représentant la liste d'argument
 * @param argc le nombre d'argument passe au programme
 * @return 0 si validation échoue.
 * @return 1 si validation réussie.
 */
 int validation_ligne_commande(int argc, char **argv);
 
  
/*
 * @param argv la liste d'argument de la fonction principale
 * @param option le caracatere 'C' ou 'L' 
 * @return la position de l'option dans char **argv
 */
 int seek_option(char * argv[], char option);
 

 /*
 * @param argv la liste d'argument de la fonction principale
 * @param pos la position representant la position de l'argument dont nous cherchons la longeur 
 * @return la taille de la liste de domaine à partir argv[pos] 
 */
 int get_nbre_domaines(char * argv[], int pos);
 

 /*
  * @params max est utilisé pour que <nun>- represente le domaine <num>-max 
  * @return 1 si la syntaxe  de domaine est correcte et place le début et la fin du domaine dans debut et fin
  * @return 0 si la syntaxe  de domaine est incorrecte
 */ 
 int get_debut_fin_domaine(char *domaine, int max, int *debut, int *fin);
 
 
 /*
 * @param c est soit 'C', soit 'L'.
 * @param dim est censée représenter soit le nombre de lignes dans le tableau 2D soit le nombre de colonnnes.
 * @param argv représente le tableau pointant les paramères du programme.
 * @return un tableau d'entiers de taille dim rempli avec des 0 et des 1 :
 *  une case est remplie avec 0 si elle correspond à une ligne ou une colonne qui ne va pas 
 *  être supprimée selon argv et l'option c ;
 *  une case est remplie avec 1 si elle correspond à une ligne ou une colonne qui va 
 *  être supprimée selon argv et l'option c
 */
 int * control(char * argv[], int dim, char c);
 
 
#endif