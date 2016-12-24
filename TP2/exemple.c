#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "affichage.h"

// Ce fichier est un exemple pour vous montrer
// comment remplir struct tab2D  
// et comment utiliser affiche_Tab2D

int main (int argc, char *const argv[])
{

  struct tab2D mat2 = {2,4,NULL};
  char **p = malloc(8 * sizeof(char*));
  mat2.ptr = p;
  p[0] = strcpy(malloc(sizeof("abc")),"abc");
  p[1] = strcpy(malloc(sizeof("1F0")),"1F0");
  p[2] = strcpy(malloc(sizeof("4")),"4");
  p[3] = strcpy(malloc(sizeof("-2.TG")),"-2.TG");
  p[4] = strcpy(malloc(sizeof("ok")),"ok");
  p[5] = strcpy(malloc(sizeof("pere")),"pere");
  p[6] = strcpy(malloc(sizeof("")),"");
  p[7] = strcpy(malloc(sizeof("inf3135")),"inf3135");
  free(p);
  affiche_Tab2D(mat2);

  for(int i=0; i < 8 ; i++)
    free(mat2.ptr[i]);
  free(mat2.ptr);

  return 0;
}