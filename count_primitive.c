#include <stdio.h>
#include <stdlib.h>
#include "f2_poly.h"


int main(int argc, char** argv){


  uint8_t n = 1;
  unsigned int c;
  f2_poly_t start,end;

  for( ; n < 64; ++n){
    start =  1ull << n;
    end =  1ull << (n+1);
    c = 0;

    while(start < end){
      if(f2_poly_primitive(start) == 1)
        ++c;
      start++;
    }
    printf("Il y a %d polynômes primitifs de degrée %d.\n", c, n);
  }

  return 0;
}
