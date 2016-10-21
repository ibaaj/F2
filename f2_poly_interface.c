#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "f2_poly.h"



int main(int argc, char **argv){

  f2_poly_t pol = 0;

  if(argc == 2)
    pol = atoi(argv[1]);
  else
  {
    printf("Entrez le polynôme que vous souhaitez étudier : ");
    scanf("%2" SCNu64, &pol);
    printf("\n");
  }

    f2_poly_print(pol, F2_VARN, stdout);
    printf("Degré : %" PRIu8 " \n", f2_poly_deg(pol));
    printf("Est il irreductible ? %d \n", f2_poly_irred(pol));
    printf("Est il primitif ? %d\n", f2_poly_primitive(pol));
    printf("Ordre multiplicatif d'une racine ? %" PRIu64 "\n", f2_poly_irred_order(pol));


  return 0;
}
