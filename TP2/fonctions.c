/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include "affichage.h"
#include "fonctions.h"


/*
 * Fonction valider_liste_fichier(...)
 */
 
 int valider_liste_fichier(char **liste_fichier, int nombre_de_fichier)
 {
   assert(liste_fichier != NULL);
   assert(nombre_de_fichier > 0);
   for(int i = 0; i < nombre_de_fichier; i++) 
   {
    FILE * fichier_courrant = fopen(liste_fichier[i], "r");
    if(fichier_courrant == NULL) return 0;
	else 
	{
  	 fclose(fichier_courrant);
	}
   }
   return 1;
 }

 
/*
 * Fonction nbre_lignes_fichier(...)
 */
 
int nbre_lignes_fichier(FILE *fp)
{  

  assert(fp != NULL || printf("Erreur d'ouverture fichier, arret du programme.")); 
  rewind(fp);
  int nb_ligne = 0, caractere , last = EOF; 
  while (caractere != EOF)
  {
   if(caractere == '\n') nb_ligne++;
   last = caractere; 
   caractere = fgetc(fp);
  }
  if(last != '\n') nb_ligne++;
  return nb_ligne;
}


/*
 * Fonction get_vecteur(...)
 */

int * get_vecteur(FILE *file, int nombre_ligne)
{ 
  int *vecteur = malloc(nombre_ligne*sizeof(int)), max, j, k, u;
  char une_ligne[TAILLE_MAX_LIGNE];
  j = k = u = max = 0;
  rewind(file);

   while((fgets(une_ligne, TAILLE_MAX_LIGNE ,file)) != NULL)
   { 
    char * curr = strtok(une_ligne," "); 
	while(curr != NULL)
	{
	 if(*curr != '\n')	 u++;
	 curr = strtok(NULL, " ");
	}
	vecteur[j] = u;
	u = 0; j++;
	memset(une_ligne, 0 , sizeof(une_ligne));
  }  
  
  return vecteur;
}
 
 
/*
 * Fonction get_max_nb_colonne(...)
 */
 
int get_max_nb_colonne(int * vecteur , int v)
{
 if(vecteur == NULL) return 0;
 
 int max = vecteur[0];
 
 for(int i = 0; i < v; i++) 
 {
   if(max < vecteur[i])
   {  
     max = vecteur[i];
   }
 }
 return max;
}


/*
 * Fonction trouver_nombre_colonne_maximale(...)
 */
 
int trouver_nombre_colonne_maximale(int nb_fichier, struct tableau tableau_de_vecteur[] , int *index_max_colonne)
{
 int maximum_colonne = 0;
 for(int i = 0; i < nb_fichier; i++)
 {
   int max_relatif = get_max_nb_colonne(tableau_de_vecteur[i].vecteur, tableau_de_vecteur[i].taille);
   if(max_relatif > maximum_colonne)
   {
	maximum_colonne = max_relatif;
	*index_max_colonne = i;
   }
 }
 return maximum_colonne;
}


/*
 * Fonction trouver_nombre_ligne_maximale(...)
 */

int trouver_nombre_ligne_maximale(int nb_fichier, struct tableau tableau_de_vecteur[] , int * index_max_ligne)
{    
  
 assert(tableau_de_vecteur != NULL);
 assert(nb_fichier > 0);
 assert(index_max_ligne != NULL);
 
 int vrai_ligne = 0, max_ligne = 0;
 for(int k = 0; k < nb_fichier; k++)
 {
  for(int x = 0; x < tableau_de_vecteur[k].taille; x++)
  {
   if(tableau_de_vecteur[k].vecteur[x] != 0) vrai_ligne++;
   if(vrai_ligne > max_ligne)
   {
	max_ligne = vrai_ligne;
	*index_max_ligne = k;
   }
  }
  vrai_ligne = 0;
 } 
 return max_ligne;
}


/*
 * Fonction charger(...)
 */
 
char ** charger(FILE *fichier, int ligne, int colonne, char ** matrice, char option, int nombre_ligne)
{
 assert(ligne > 0 && colonne > 0);
 assert(fichier != NULL);
 
 matrice = malloc((ligne*colonne)*sizeof(char *));
 char une_ligne[TAILLE_LIGNE_COPIE];
 
 int u = 0;
 int j = 0;
 int line_counter = 0;
 
 rewind(fichier);
 
 while((fgets(une_ligne, TAILLE_LIGNE_COPIE ,fichier)) != NULL)
 { 
  line_counter++;
  
  if(une_ligne[0] == '\n' )continue;
  
  char * curr = strtok(une_ligne," ");  
  
  while(curr != NULL)
  {
   u++; 
   matrice[j++] = strcpy(malloc(sizeof(curr)),curr);
   curr = strtok(NULL, " ");
  }

  while(u++ < colonne) { matrice[j++] = strcpy(malloc(sizeof(" "))," "); }
  u = 0;
 }
 
  while(line_counter < ligne) 
  {
   int temp_colonne_counter = 0;
   while(temp_colonne_counter < colonne)
   {
    matrice[j++] = strcpy(malloc(sizeof(" "))," ");
    temp_colonne_counter++;
   }
   line_counter++;  
  }
  
  for(int i = 0; i < ligne*colonne; i++)
  {
   for(int z = 0; z < strlen(matrice[i]); z++)
   {
    if(matrice[i][z] == '\n')
    {
     matrice[i][z] = ' ';
    }
   }
  }
  return matrice; 
 
}


/*
 * Fonction fusionner_les_matrices( ... )
 */
 
 struct tab2D * fusionner_les_matrices(int nb_fichier, struct tab2D * tableau_de_matrice[], char sens_de_fusion)
 {
   assert(tableau_de_matrice != NULL);
   assert(nb_fichier > 0);
   assert(sens_de_fusion == 'H' || sens_de_fusion == 'h' || sens_de_fusion == 'V' || sens_de_fusion == 'v');
  
   int nombre_colonne_mega_matrice = 0;
   int nombre_ligne_mega_matrice = 0;    
   
   if(sens_de_fusion == 'H' || sens_de_fusion == 'h')
   {
     //il faut le meme nombre de ligne forall matrice
	 for(int i = 0; i < nb_fichier; i++)
	   nombre_colonne_mega_matrice += tableau_de_matrice[i]->colonnes;
	    
	 nombre_ligne_mega_matrice = tableau_de_matrice[0]->lignes; 
	  
	 struct tab2D * mega_matrice = malloc(sizeof(struct tab2D));  
	 
	 mega_matrice->colonnes = nombre_colonne_mega_matrice;
	 mega_matrice->lignes = nombre_ligne_mega_matrice;
	 mega_matrice->ptr = malloc(nombre_colonne_mega_matrice*nombre_ligne_mega_matrice * sizeof(char*));
	
    int index_mega = 0;
 
    for(int ligne = 1; ligne <= nombre_ligne_mega_matrice; ligne++)
    {
     for(int i = 0; i < nb_fichier; i++)
     {
       for(int count = tableau_de_matrice[i]->colonnes ; count >= 1 ; count--) 
       {
       int colonne = tableau_de_matrice[i]->colonnes;
 mega_matrice->ptr[index_mega++] = strcpy(malloc(sizeof(tableau_de_matrice[i]->ptr[(ligne*colonne)-count])), tableau_de_matrice[i]->ptr[(ligne*colonne)-count]);
                 
       }
     }
    }
    
    return mega_matrice;
   }

    if(sens_de_fusion == 'V' || sens_de_fusion == 'v')
   {
	 for(int i = 0; i < nb_fichier; i++)
	   nombre_ligne_mega_matrice += tableau_de_matrice[i]->lignes;
	   
	 nombre_colonne_mega_matrice = tableau_de_matrice[0]->colonnes;
   
     struct tab2D * mega_matrice = malloc(sizeof(struct tab2D));  
 	 mega_matrice->colonnes = nombre_colonne_mega_matrice;
	 mega_matrice->lignes = nombre_ligne_mega_matrice;
	 mega_matrice->ptr = malloc(nombre_colonne_mega_matrice*nombre_ligne_mega_matrice * sizeof(char*));   
     
	 int mega_matrix_counter = 0;
	 
	 for(int i = 0; i < nb_fichier; i++)
	 {
      for(int j = 0; j < tableau_de_matrice[i]->colonnes*tableau_de_matrice[i]->lignes; j++)
	  {
       mega_matrice->ptr[mega_matrix_counter++] = strcpy(calloc(sizeof(tableau_de_matrice[i]->ptr[j]),sizeof(char)) , tableau_de_matrice[i]->ptr[j]);
	  }
     }
	 return mega_matrice;
   }
  return NULL;
 }
 

/*
 * Fonction filter(...)
 */
 
struct tab2D *filter(struct tab2D *matrice, int *control_ligne, int *control_colonne, int ligne, int colonne)
{
  
  assert(matrice != NULL);
  assert(ligne > 0 && colonne > 0);
  
  //Alocation de la mémoire
  struct tab2D *matrice_reduite = malloc(sizeof(struct tab2D));
  int ligne_new = 0, colonne_new = 0;
  
  //Affectation Ligne
  if(control_ligne == NULL) ligne_new = ligne;
  else
	for(int i = 0; i < ligne ; i++) 
	{
	 if(control_ligne[i] == 0)
		ligne_new++;
	}

  //Affectation Colonne
  if(control_colonne == NULL) colonne_new = colonne;
  else
	for(int j = 0; j < colonne ; j++) 
	{
	 if(control_colonne[j] == 0) 
	    colonne_new++;
	}
  
  //Allocation nouvelle matrice
  matrice_reduite->lignes = ligne_new;
  matrice_reduite->colonnes = colonne_new;
  matrice_reduite->ptr = malloc(ligne_new*colonne_new * sizeof(char*));
  
  int index = 0;
  int indicateur = 0;
  int count = 0;
  
  //Si pas de ligne ni de colonne à enlever
  if(control_colonne == NULL && control_ligne == NULL) 
  {
   for(int i = 0; i < ligne_new*colonne_new; i++)
   { 
    matrice_reduite->ptr[i] = strcpy(malloc(sizeof(matrice->ptr[i])),matrice->ptr[i]);
   }
  }
  else 
   if(control_colonne == NULL && control_ligne != NULL)
   {
    for( ; count < ligne*colonne; count++) 
    {	
	 if((count % colonne_new) == 0)
	 { 
	   if(control_ligne[indicateur++] == 1)
	   {
		if(count + colonne >= ligne*colonne)
		 break;
		else   
 		  count += colonne; 
		count--; 
        continue; 
	   }
     }
      matrice_reduite->ptr[index++] = strcpy(malloc(sizeof(matrice->ptr[count])),matrice->ptr[count]);	 
	}
   }
   else if(control_colonne != NULL && control_ligne == NULL)
   {
    int index = 0;
	
    for(int i = 0; i < ligne; i++)
	{
	 for(int j = 0; j < colonne; j++)
	 { 	   
	   if(index >= ligne*colonne) break;
	   if(control_colonne[j] != 1) 
	   {
	     matrice_reduite->ptr[index++] = strcpy(malloc(sizeof(matrice->ptr[(i*colonne)+j])),matrice->ptr[(i*colonne)+j]);	 
	   }
	   else continue;
	 } 
    }	 
   }
   else if(control_colonne != NULL && control_ligne != NULL)
   {
   int index = 0;
	
    for(int i = 0; i < ligne; i++)
	{
	 for(int j = 0; j < colonne; j++)
	 { 	   
	   if(index >= ligne*colonne) break;
	   if(control_colonne[j] != 1 && control_ligne[i] != 1) 
	   {
	     matrice_reduite->ptr[index++] = strcpy(malloc(sizeof(matrice->ptr[(i*colonne)+j])),matrice->ptr[(i*colonne)+j]);	 
	   }
	   else continue;
	 } 
    }	 
   }
   
   return matrice_reduite;
}
