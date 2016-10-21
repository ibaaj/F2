#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "f2_poly.h"



int main(int argc, char** argv){

  uint8_t deg = 0;
  f2_poly_t pol;

  if(argc == 2)
    deg = atoi(argv[1]);
  else {
    printf("Entrez degré des polynômes aléatoires souhaités : ");
    scanf("%2" SCNu8, &deg);
    printf("\n");
  }

  while(1){

    pol = f2_poly_random(deg);
    f2_poly_print(pol, F2_VARN, stdout);
    printf("Est il irreductible ? %d \n", f2_poly_irred(pol));
    printf("Est il primitif ? %d\n", f2_poly_primitive(pol));
  }

  return 0;
}
