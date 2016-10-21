#include <stdio.h>
#include <stdlib.h>
#include "f2_poly.h"


int main(int argc, char** argv){

  if(argc != 2){
    printf("Ce programme énumère les polynomes irreductibles sur F2 du degré donné en argument du programme\n");
    printf("./enumerate_irreductible degree \n");
    exit(0);
  }

  uint8_t n = atoi(argv[1]);

  f2_poly_t start =  1ull << n;
  f2_poly_t end =  1ull << (n+1);


  while(start < end){
    if(f2_poly_irred(start) == 1)
        f2_poly_print(start, F2_VARN, stdout);


    start++;
  }



  return 0;
}
