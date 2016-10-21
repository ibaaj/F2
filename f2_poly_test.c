#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "f2_poly.h"



int main(){

  uint64_t i;

  f2_poly_t polAES = 0x11b;     //X^8+X^4+X^3+X+1, irréductible non primitif
  f2_poly_t polA51a = 0xe4001;  //X^19+X^18+X^17+X^14+1, irréductible primitif
  f2_poly_t polA51b = 0x600001; //X^22+X^21+1, irréductible primitif
  f2_poly_t polA51c = 0xe00101; //X^23+X^22+X^21+X^8+1, irréductible primitif
  f2_poly_t *arg1 = malloc(sizeof(f2_poly_t));
  f2_poly_t *arg2 = malloc(sizeof(f2_poly_t));
  f2_poly_t *arg3 = malloc(sizeof(f2_poly_t));
  f2_poly_t *arg4 = malloc(sizeof(f2_poly_t));


  printf("Programme de calcul sur F2\n");

  printf("-----------------------------------------\n");
  printf("-----------------------------------------\n");

  printf("Afficher le polynôme de l'AES : \n");
  f2_poly_print(polAES, F2_VARN, stdout);
  printf("Son degré est : %d \n", f2_poly_deg(polAES));

  printf("Afficher le polynôme de l'A5/1 a : \n");
  f2_poly_print(polA51a, F2_VARN, stdout);
  printf("Son degré est : %d \n", f2_poly_deg(polA51a));

  printf("Afficher le polynôme de l'A5/1 b : \n");
  f2_poly_print(polA51b, F2_VARN, stdout);
  printf("Son degré est : %d \n", f2_poly_deg(polA51b));

  printf("Afficher le polynôme de l'A5/1 c : \n");
  f2_poly_print(polA51c, F2_VARN, stdout);
  printf("Son degré est : %d \n", f2_poly_deg(polA51c));

  printf("-----------------------------------------\n");

  printf("Divisions : \n");

  printf("Division du polynôme de l'AES (X^8+X^4+X^3+X+1) ");
  printf("par le polynôme A5/1 a (X^19+X^18+X^17+X^14+1) : \n");

  *arg1 = polAES;
  *arg2 = polA51a;
  f2_poly_div(arg3, arg4, *arg1, *arg2);

  printf("quotient : \n");
  f2_poly_print(*arg3, F2_VARN, stdout);
  printf("reste : \n");
  f2_poly_print(*arg4, F2_VARN, stdout);
  printf("\n");

  printf("Division du polynôme de A5/1 c (X^23+X^22+X^21+X^8+1) ");
  printf("par le polynôme A5/1 b (X^22+X^21+1) : \n");

  *arg1 = polA51c;
  *arg2 = polA51b;
  f2_poly_div(arg3, arg4, *arg1, *arg2);

  printf("quotient : \n");
  f2_poly_print(*arg3, F2_VARN, stdout);
  printf("reste : \n");
  f2_poly_print(*arg4, F2_VARN, stdout);
  printf("\n");

  printf("Division du polynôme de A5/1 c (X^23+X^22+X^21+X^8+1) ");
  printf("par le polynôme AES (X^8+X^4+X^3+X+1) : \n");

  *arg1 = polA51c;
  *arg2 = polAES;
  f2_poly_div(arg3, arg4, *arg1, *arg2);

  printf("quotient : \n");
  f2_poly_print(*arg3, F2_VARN, stdout);
  printf("reste : \n");
  f2_poly_print(*arg4, F2_VARN, stdout);
  printf("\n");

  printf("-----------------------------------------\n");

  printf("Tester GCD,REM, Xtimes, time, x2n .... : Irréductibilité \n");

  printf("Le polynôme de l'AES est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(polAES));
  printf("Le polynôme de l'A5/1 a est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(polA51a));
  printf("Le polynôme de l'A5/1 b est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(polA51b));
  printf("Le polynôme de l'A5/1 c est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(polA51c));
  printf("Le polynôme X^2 + 1  est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(5));
  printf("Le polynôme X^4 + X^2 + 1 est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(0x15));
  printf("Le polynôme X^6 + X^4 + X^2 est il irreductible : %d ( 1 = oui, 0 = non)\n", f2_poly_irred(0x54));

  printf("-----------------------------------------\n");

  printf("Polynômes primitifs ?  \n");
  printf("Le polynôme de l'AES est il primitif : %d ( 1 = oui, 0 = non)\n", f2_poly_primitive(polAES));
  printf("Le polynôme de l'A5/1 a est il primitif : %d ( 1 = oui, 0 = non)\n",  f2_poly_primitive(polA51a));
  printf("Le polynôme de l'A5/1 b est il primitif : %d ( 1 = oui, 0 = non)\n",  f2_poly_primitive(polA51b));
  printf("Le polynôme de l'A5/1 c est il primitif : %d ( 1 = oui, 0 = non)\n",  f2_poly_primitive(polA51c));

  printf("L'ordre multiplicatif d'une racine du polynome de l'AES est : %" PRIu64 " \n", f2_poly_irred_order(polAES) );
  printf("L'ordre multiplicatif d'une racine du polynome de l'A5/1 a est : %" PRIu64 " \n", f2_poly_irred_order(polA51a) );
  printf("L'ordre multiplicatif d'une racine du polynome de l'A5/1 b est : %" PRIu64 " \n", f2_poly_irred_order(polA51b) );
  printf("L'ordre multiplicatif d'une racine du polynome de l'A5/1 c est : %" PRIu64 " \n", f2_poly_irred_order(polA51c) );

  printf("Quel est le polynôme réciproque de l'A5/1 a (X^19+X^18+X^17+X^14+1)? : \n");
  f2_poly_print(f2_poly_recip(polA51a), F2_VARN, stdout);
  printf("Est il primitif : %d \n", f2_poly_primitive(f2_poly_recip(polA51a)));
  printf("Quel est le polynôme réciproque de l'A5/1 b (X^22+X^21+1) ? : \n");
  f2_poly_print(f2_poly_recip(polA51b), F2_VARN, stdout);
  printf("Est il primitif : %d \n", f2_poly_primitive(f2_poly_recip(polA51b)));
  printf("Quel est le polynôme réciproque de l'A5/1 c (X^23+X^22+X^21+X^8+1) ? : \n");
  f2_poly_print(f2_poly_recip(polA51c), F2_VARN, stdout);
  printf("Est il primitif : %d \n", f2_poly_primitive(f2_poly_recip(polA51c)));

  printf("-----------------------------------------\n");

  printf("Aleatoire : \n");
  printf("Afficher 4 polynomes aléatoires de degré inférieur à 9  :\n");
  for(i = 0; i < 4; ++i)
    f2_poly_print(f2_poly_random_inf(9), F2_VARN, stdout);
  printf("Afficher 4 polynomes aléatoires de degré égal à 12 : \n");
  for(i = 0; i < 4; ++i)
    f2_poly_print(f2_poly_random(12), F2_VARN, stdout);
  printf("Afficher 4 polynomes aléatoires irreductibles de degré égal à 12 :\n");
  for(i = 0; i < 4; ++i)
    f2_poly_print(f2_poly_irred_random(12), F2_VARN, stdout);

  printf("Afficher 4 polynomes aléatoires irreductibles primitifs de degré égal à 12 :\n");
  for(i = 0; i < 4; ++i)
    f2_poly_print(f2_poly_primitive_random(12), F2_VARN, stdout);


  for(i = 1; i < 64; ++i)
    printf(" il y a %" PRIu64 " polynomes irreductibles de degrés %" PRIu64 " \n", f2_poly_irred_count(i),i);

  for(i = 1; i < 64; ++i)
    printf(" il y a %" PRIu64 " polynomes irreductibles primitifs de degrés %" PRIu64 " \n", f2_poly_primitive_count(i),i);


  return 0;
}
