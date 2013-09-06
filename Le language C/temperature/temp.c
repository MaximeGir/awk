#include <stdio.h>
#include <stdlib.h>

int main()
{
  float fahr, celcius;
  int  mini, maxi, intervalle;
  
  mini = 0;
  maxi = 300;
  intervalle = 20;
  celcius = mini;
  printf("========================\n");
  printf("*Conversions des degrés*\n");
  printf("========================\n");  
  while(celcius <= maxi){
    fahr = 9.0/5.0 * celcius + 32 ;
    printf("%3.f %6.f\n", celcius, fahr);
    celcius += intervalle;
  }
  return EXIT_SUCCESS;
}
