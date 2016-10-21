#include "arithm.h"


int main(){
  uint64_t i,j;
  Diviseurs f;
  f.liste = NULL;
  f.c = 0;

  printf("Arithmetique : \n");
  printf("Plus petit diviseur premier : \n");
  for(i = 1; i < 50; i++)
    printf("Plus petit diviseur premier de %" PRIu64 " : %" PRIu64 " \n", i, pp_diviseur_premier(i));

  printf("Exponentiation rapide : \n");
  for(i = 1; i < 15; i++)
    printf("2^%" PRIu64 " : %" PRIu64 " \n", i, f_exp(2,i));

  printf("Mobius : \n");
  for(i = 1; i < 50; i++)
    printf("%" PRIu64 " : %d \n", i, mobius(i));

  printf("Euler : \n");
  for(i = 1; i < 50; ++i)
    printf("%" PRIu64 " :  %" PRIu64 " \n", i, euler(i));

  printf("Diviseurs : \n");
  for(i = 10; i < 15; ++i ){
    printf("Diviseurs de 2^%" PRIu64 " - 1: \n", i);
    get_all_divisors(f_exp(2,i) -1, &f);
    for(j = 0; j < f.c; j++)
      printf("%" PRIu64 ", ", f.liste[j]);
    printf("\n");


  }

  return 0;
}
