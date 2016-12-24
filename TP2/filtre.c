/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fonctions.h"
#include "affichage.h"
#include "argument.h"

#define MAX_FICHIER_INPUT 100

/*
 * Fonction principale
 */

int main(int argc, char * argv[])
{	
	//Validation option H & V
	if(!validation_ligne_commande(argc, argv)) 
	{
		signaler_erreur(OUVERTURE_FICHIER_ERREUR);	 
		return EXIT_FAILURE;
	}

	//opt_fichier soit H ou V
	char opt_fichier;
	int nb_fichier = get_nombre_fichier(argc, argv, &opt_fichier);	 
	char **liste_fichier = get_noms_des_fichiers(argv, argc, nb_fichier);

	//Validation fichier de liste_fichier(size nb_fichier) sont tous present.
	if(!valider_liste_fichier(liste_fichier, nb_fichier)) 
	{
		signaler_erreur(OUVERTURE_FICHIER_ERREUR);
		return EXIT_FAILURE;
	}
	/*
	 * DEBUT peupler le tableau de structure tableau_de_vecteur
	 */

	int nombre_de_ligne; 

	struct tableau tableau_de_vecteur[nb_fichier];

	for(int i = 0; i < nb_fichier; i++) 
	{ 
		FILE * fichier_ouvert = fopen(liste_fichier[i],"r");
		assert(fichier_ouvert != NULL || printf("Fichier NULL, arret du programme."));

		nombre_de_ligne = nbre_lignes_fichier(fichier_ouvert);
		int vrai_ligne = 0;

		int * vecteur = malloc(nombre_de_ligne*sizeof(int));
		vecteur = get_vecteur(fichier_ouvert, nombre_de_ligne);

		for(int line = 0; line < nombre_de_ligne; line++) 
		{
			if(vecteur[line] != 0) vrai_ligne++; 
		}
		//structure contenant tout les vecteurs

		tableau_de_vecteur[i] = (struct tableau) { nombre_de_ligne, 0, 0, NULL };
		tableau_de_vecteur[i].vecteur = malloc(nombre_de_ligne * sizeof(int));

		for(int j = 0; j < nombre_de_ligne; j++)	  
			tableau_de_vecteur[i].vecteur[j] = *(vecteur+j);

		tableau_de_vecteur[i].taille = nombre_de_ligne;

		//Fermeture du fichier
		fclose(fichier_ouvert);

		//Liberation de la mémoire alloué à vecteur
		free(vecteur);
	}
	/*
	 * FIN peupler le tableau de structure tableau_de_vecteur
	 */

	//fonction trouver maximum_colonne parmis tout les vecteurs
	int index_max_colonne;
	int maximum_colonne = trouver_nombre_colonne_maximale(nb_fichier, tableau_de_vecteur, &index_max_colonne);

	//fonction trouver max_ligne parmis tout les vecteurs
	int index_max_ligne;
	int maximum_ligne = trouver_nombre_ligne_maximale(nb_fichier, tableau_de_vecteur, &index_max_ligne);

	//Affectation du champ significatif des structures concernees	 
	tableau_de_vecteur[index_max_ligne].est_max_ligne = 1;
	tableau_de_vecteur[index_max_colonne].est_max_colonne = 1;

	/*
	 * DEBUT peupler le tableau de structure matrice
	 */ 

	struct tab2D * tableau_de_matrice[nb_fichier];

	for(int i = 0; i < nb_fichier; i++)
	{    
		FILE * fichier_courrant = fopen(liste_fichier[i],"r");	

		/*
		 * DEBUT Set variables pour allocation
		 */ 

		int x_colonne = maximum_colonne;
		int x_ligne = maximum_ligne;

		int ligne_use = 0;
		int colonne_use = 0;

		if(opt_fichier == 'H')
		{
			ligne_use = x_ligne;
			colonne_use = get_max_nb_colonne(tableau_de_vecteur[i].vecteur, tableau_de_vecteur[i].taille);
		}        
		if(opt_fichier == 'V')
		{
			ligne_use = nbre_lignes_fichier(fichier_courrant);
			colonne_use = x_colonne; 
		} 

		/*
		 * FIN Set variable pour allocation
		 */ 

		tableau_de_matrice[i] = malloc(sizeof(struct tab2D*));
		*tableau_de_matrice[i] = (struct tab2D){ligne_use, colonne_use, NULL};
		tableau_de_matrice[i]->ptr = malloc(colonne_use*ligne_use*sizeof(char*));

		char ** copie = malloc((colonne_use*ligne_use)*sizeof(char*));	 
		copie = charger(fichier_courrant, maximum_ligne, colonne_use, tableau_de_matrice[i]->ptr, opt_fichier, nombre_de_ligne);

		for(int j = 0; j < colonne_use*ligne_use; j++)
		{
			tableau_de_matrice[i]->ptr[j] = strcpy(malloc(sizeof(copie[j])),copie[j]);
		} 

		tableau_de_matrice[i]->lignes = ligne_use;
		tableau_de_matrice[i]->colonnes = colonne_use;

		fclose(fichier_courrant);
		free(copie);
	}

	/*
	 * FIN peupler le tableau de structure matrice
	 */

	struct tab2D* mega_matrice = malloc(sizeof(struct tab2D*));
	mega_matrice = fusionner_les_matrices(nb_fichier, tableau_de_matrice, opt_fichier);
	if(mega_matrice == NULL) { signaler_erreur(OPTION_ERREUR); return EXIT_FAILURE; }

	/*
	 * DEBUT Validation / Vérification des options + controle
	 */	

	int nb_colonne = mega_matrice->colonnes;
	int vrai_ligne = mega_matrice->lignes;

	int *tableau_colonne = malloc(nb_colonne*sizeof(int));
	int *tableau_ligne = malloc(vrai_ligne*sizeof(int));

	//Initialisation des tableaux indicateurs
	tableau_colonne = control(argv,nb_colonne,'C');
	tableau_ligne = control(argv,vrai_ligne, 'L');

	/*
	 * FIN Validation / Vérification des options + controle
	 */	

	struct tab2D *matrice_reduite = malloc(sizeof(struct tab2D*));
	matrice_reduite = filter(mega_matrice, tableau_ligne, tableau_colonne, vrai_ligne, nb_colonne);
	affiche_Tab2D(*matrice_reduite);

	return EXIT_SUCCESS;
}
