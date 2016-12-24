/*
 *
 * @author : Maxime Girard 
 * @CodePermanent : GIRM30058500
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "affichage.h"


void
signaler_erreur(int err)
{
    switch (err)
    {
        case OUVERTURE_FICHIER_ERREUR :
            fprintf(stderr,"Erreur d'ouverture du fichier.\n");
        break;
        case SYNTAX_DOMAIN_ERREUR :
            fprintf(stderr,"Erreur de syntaxe dans un domaine.\n");
            break;
        case OPTION_ERREUR :
                fprintf(stderr,"Erreur dans une option.\n");
                break;
        case FICHIER_SANS_DONNEE_ERREUR : 
            fprintf(stderr,"Le fichier ne comporte aucune donnee.\n");
            break;
        case TABLEAU2D_VIDE_ERREUR :
            fprintf(stderr,"Tableau vide!\n");
            break;
        default : 
            break;
    }
    
}

void
affiche_Tab2D(struct tab2D mat)
{
if (mat.lignes>0 && mat.colonnes>0 && mat.ptr !=NULL)
{
    char * (*lignePtr)[mat.colonnes];

    lignePtr = (char * (*)[mat.colonnes]) mat.ptr;

    for (int i = 0 ; i < mat.lignes ; i++)
    {
        printf("[");
        for (int j = 0 ; j < mat.colonnes ; j++) 
        {
            printf("%-10s ",lignePtr[i][j]);
        }
        printf("]\n");
    }    
}
else
{
    signaler_erreur(TABLEAU2D_VIDE_ERREUR);
}
}