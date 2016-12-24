/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */
 
     #include <assert.h>
     #include <string.h>
	 #include <ctype.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>
     #include "affichage.h"
     #include "argument.h"

	 
	 /*
	  *  Fonction get_nombre_fichier(...)
	  */

     int get_nombre_fichier(int argc, char **argv, char * option)
     {
	  int nb_argument = 0;
	  
	  assert(strcmp(argv[1],"-V") == 0 || strcmp(argv[1],"-H") == 0);
	  
	  if(strcmp(argv[1],"-V") == 0) *option = 'V';
  	  if(strcmp(argv[1],"-H") == 0) *option = 'H';
	  
	  for(int i = 0; i < argc-2; i++)
	  {
	   if(strcmp(argv[2+i],"-C") == 0 || strcmp(argv[2+i],"-L") == 0)
         return nb_argument;
	   else 
	     nb_argument++;
	  }
	  return nb_argument;
	 }
	 
    /*
	 *  Fonction get_noms_des_fichiers(...)
	 */
	 
	char ** get_noms_des_fichiers(char **argv, int argc, int nombre_de_fichier)
	{
	  assert(nombre_de_fichier >= 1 || printf("Fichier manquant, arret du programme.\n"));
 
	  char ** liste = malloc(nombre_de_fichier*(sizeof(char*)));
	  
	  for(int i = 0; i < nombre_de_fichier; i++)
	  {
 	   liste[i] = malloc(strlen(argv[2+i]));
	   strcpy(liste[i], argv[2+i]);
	  }
	  return liste;
	}
   
   
   /*
	*  Fonction validation_cli_argument(...)
	*/
	
	int validation_cli_argument(int argc,  char ** argv )
	{
	 if(strcmp(argv[1],argv[2]) == 0) return 0;
	 if(strcmp(argv[1], "-H") == 0)
	  if(strcmp(argv[2], "-H") == 0 || strcmp(argv[2], "-V") == 0) return 0;
	 if(strcmp(argv[1], "-V") == 0)
	  if(strcmp(argv[2], "-V") == 0 || strcmp(argv[2], "-H") == 0) return 0; 
	 return 1;
	}
	
	
   /*
	*  Fonction validation_ligne_commande(...)
	*/
	
	int validation_ligne_commande(int argc, char ** argv)
	{
	 if(argc < 3)
	 {
	  signaler_erreur(OUVERTURE_FICHIER_ERREUR);
	  return 0; 
	 }

	 if(validation_cli_argument(argc, argv) == 0)
	 { 
	  signaler_erreur(SYNTAX_DOMAIN_ERREUR);
	  return 0; 
	 }
	 if(validation_cli_argument(argc, argv) == -1)
	 {
	  signaler_erreur(OPTION_ERREUR);
	  return 0;
	 }
	 return 1;
    } 
	
	
   /*
	*  Fonction seek_option(...)
	*/
	
	int seek_option(char * argv[], char option)
	{
	  int index = 0, index_relatif = 0, occurence = 0;
	  char intru;
	  while(argv[index])
	  {
		if(*argv[index] == '-')
		{
		 if(*(argv[index]+1) == option)
		 {
		   ++occurence;
		   index_relatif = index;
		 }
		 
		 switch(*(argv[index]+1))
		 {
		 case 'L': break;
		 case 'C': break;
		 default: 
		   if(*(argv[index]+1) != intru && (*(argv[index]+1) <= 9 && *(argv[index]+1)))
		   {
			intru = *(argv[index]+1);
			signaler_erreur(OPTION_ERREUR);		
			break;
		   }
		 }
		}
		if(argv[index+1] == NULL) break;
		index++;
	  }
	  
	  if(occurence == 1) 
	  { 
	   return index_relatif;
	  }
	  else if(occurence > 1) signaler_erreur(OPTION_DUPLIQUEE_ERREUR);
	  else if(occurence == 0) return 0;
	  return -1;
	}

	
   /*
	*  Fonction get_nbre_domaines(...)
	*/
	
	int get_nbre_domaines(char * argv[], int pos)
	{
	 int i = pos, count = 0;
	 while(argv[i])
	 {
	  char * argument = argv[i++];
	  if(argument[0] == '-') 
	  {
	   if(argument[1] == 'C' || argument[1] == 'L') 
	   {
		while((argument = argv[i++]))
		{
		 if(argument[0] == '-') 
		 {
		  if(argument[1] == 'C' || argument[1] == 'L')
		  {
		   break;
		  }
		  else if(argument[1]-'0') { count++; break; }	  
		 }
		 else count++;
		}
	   }
	   break;
	  }
	 }
	 return count;
	}

	
   /*
	*  Fonction get_debut_fin_domaine(...)
	*/
	
	int get_debut_fin_domaine(char *domaine, int max, int *debut, int *fin)
	{
	  int i = 0;
	  while(domaine[i])
	  {
	   if(domaine[i] == '-' && isdigit(domaine[i+1]))
	   {
		 *debut = 0;
		 *fin = domaine[i+1]-'0';
		 return 1;	
	   } 
	   if(isdigit(domaine[i]) && domaine[i+1] == '-' && !domaine[i+2])
	   {
		 *debut = domaine[i]-'0';
		 *fin = max-1;
		 return 1;
	   }
	   if(isdigit(domaine[i]) && domaine[i+1] == '-' && isdigit(domaine[i+2]))
	   {
		*debut = domaine[i]-'0';
		*fin = domaine[i+2]-'0';
		return 1;
	   }
	   if(isdigit(domaine[i]) && !domaine[i+1]) 
	   {
		*debut = domaine[i]-'0';
		*fin = 0;
		return 1;
	   }
	   return 0;
	  }
	 return 0;
	}

	
   /*
	*  Fonction control(...)
	*/
	
int * control(char * argv[], int dim, char c)
{   
 if(c == 'C')
  {
   int index_colonne = seek_option(argv, 'C');
   int domaine_colonne = 0,debut = 0, fin = 0;
   
   if(index_colonne == -1 || index_colonne == 0){ return NULL; }
   if(index_colonne >= 1)
   {
    domaine_colonne = get_nbre_domaines(argv,index_colonne); 	
	char **domaine_cx = malloc(dim*sizeof(char *)) ;
    	
    int k = index_colonne, h = 0, i = 0;
    while(k++ < domaine_colonne+index_colonne)
    {
     domaine_cx[h] = argv[k];
 	 h++;
    }
	
	//Initialisation du tableau + affectation
	int *tableau_colonne = malloc(dim*sizeof(int)), u = 0;
    for(u = 0; u < dim; u++) tableau_colonne[u] = 0;
    i = 0;

	//Boucle sur arguments et affectation du tableau de colonne 
	while(h) 
    {
      debut = fin = 0;
//	  printf("domaine_cx[i] = %s\n", domaine_cx[i]);
	  get_debut_fin_domaine(domaine_cx[i], dim, &debut, &fin);
      
	//  printf("debut = %d\nfin = %d\n",debut,fin);
	  
	  if((fin == 0) || (debut == fin)){ tableau_colonne[debut] = 1; return tableau_colonne; }
	  
      while(debut <= fin)
	  {
 	   tableau_colonne[debut++] = 1;
	   h--;
	   if(h < 0) h = 0;
 	  }
	}   
  
  // for(u = 0; u < dim; u++) printf("%d\n",tableau_colonne[u]);
   
    free(domaine_cx);
	return tableau_colonne;
	
   }
  }
  
  if(c == 'L')
 /* {
   int index_ligne = seek_option(argv, 'L');
   int domaine_ligne = 0, debut = 0, fin = 0;
   
   if(index_ligne == -1 || index_ligne == 0){ return NULL; }
   if(index_ligne >= 1)
   {
    domaine_ligne = get_nbre_domaines(argv,index_ligne);
    char **domaine_lx = malloc(domaine_ligne*sizeof(char*)); 
    int k = index_ligne, h = 0, i = 0;
    while(k++ < domaine_ligne+index_ligne+1)
    {
     domaine_lx[h] = malloc(sizeof(int));
     domaine_lx[h] = argv[k];
     h++;
    }
	
    int *tableau_ligne = malloc(dim*sizeof(int)), v = 0;
    for(v = 0; v < dim; v++) tableau_ligne[v] = 0;
	i = 0;
	while(domaine_lx[i]) 
    {
     debut = fin = 0;
     if(get_debut_fin_domaine(domaine_lx[i], dim, &debut, &fin))
	 {

	  if((fin == 0) || (debut == fin)) tableau_ligne[debut] = 1;
	  while(debut <= fin) tableau_ligne[debut++] = 1;
	 }
	 i++;
    }
     free(domaine_lx);
	 return tableau_ligne;
   }
  }*/
  {
   int index_ligne = seek_option(argv, 'L');
   int domaine_ligne = 0,debut = 0, fin = 0;
   
   if(index_ligne == -1 || index_ligne == 0){ return NULL; }
   if(index_ligne >= 1)
   {
    domaine_ligne = get_nbre_domaines(argv,index_ligne); 	
	char **domaine_lx = malloc(dim*sizeof(char *)) ;
    	
    int k = index_ligne, h = 0, i = 0;
    while(k++ < domaine_ligne+index_ligne)
    {
     domaine_lx[h] = argv[k];
 	 h++;
    }
	
	//Initialisation du tableau + affectation
	int *tableau_ligne = malloc(dim*sizeof(int)), u = 0;
    for(u = 0; u < dim; u++) tableau_ligne[u] = 0;
    i = 0;

	//Boucle sur arguments et affectation du tableau de colonne 
	while(h) 
    {
      debut = fin = 0;
	//  printf("domaine_lx[i] = %s\n", domaine_lx[i]);
	  get_debut_fin_domaine(domaine_lx[i], dim, &debut, &fin);
      
	 // printf("debut = %d\nfin = %d\n",debut,fin);
	  
	  if((fin == 0) || (debut == fin)){ tableau_ligne[debut] = 1; return tableau_ligne; }
	  
      while(debut <= fin)
	  {
 	   tableau_ligne[debut++] = 1;
	   h--;
	   if(h < 0) h = 0;
 	  }
	}   
  
  //  for(u = 0; u < dim; u++) printf("%d\n",tableau_ligne[u]);
   
    free(domaine_lx);
	return tableau_ligne;
	
   }
  }
  return NULL;
}