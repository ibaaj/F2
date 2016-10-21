#include "arithm.h"


uint64_t
pp_diviseur_premier(uint64_t n){

    if (n == 0 || n == 1)
      return n;

    if( n % 2 == 0)
      return 2;

    uint64_t d = 3;

    while(n % d != 0 && d*d < n)
      d+=2;

    if(d*d > n)
    d = n;

    return d;

}


int64_t f_exp(int64_t a, uint64_t b){
  int64_t r = 1;

  while (b) {
    if (b & 1){
      r *= a;
    }
    b >>=1 ;
    a *= a;
  }

  return r;
}

int8_t mobius(int d){

  if(d == 1)
         return 1;


  int a=d,
  i=2,
  c=0,
  f=0;

   while(a > 1)
   {
       c = 0;
       while(a%i == 0)
       {
           c++;
           if(c > 1)
              return 0;

           f++;
           a=a/i;
       }
           i++;
   }

   if(f == 0)
       return 0;
   else
       return f_exp(-1,f);

}

uint64_t euler(uint64_t n){
  uint64_t x = n,i;

  if(x == 1)
    return 1;

  for( i = 2; i*i <= x; ++i)
    if(x % i == 0){
      while(x % i == 0)
        x /= i;
      n -= n / i;
    }
    if(x > 1)
      n -= n / x;

  return n;
}


void divisors_memory_management( Diviseurs *d, uint64_t *suiteListe, unsigned int taille){

  unsigned int nouvelleTaille = d->c + taille, i, j;

  if(nouvelleTaille > taille)
    d->liste = realloc( d->liste, nouvelleTaille * sizeof(uint64_t));
  else
    d->liste = malloc( nouvelleTaille * sizeof (uint64_t));

  if(d->liste == NULL)
    exit(1);

  i = d->c;
  j = 0;
  while(i < nouvelleTaille){
    d->liste[i] = suiteListe[j];
    i++;
    j++;
  }
  d->c = nouvelleTaille;
}

Diviseurs* get_all_divisors( uint64_t n, Diviseurs *d)
{
    uint64_t diviseurs[1001];
    uint64_t compteur = 0,
            diviseur = 1;

    d->c = 0;
    d->liste = NULL;
    free(d->liste); // pour la réutulisation

    while(diviseur*diviseur < (n + 1) ){

      if(n % diviseur == 0)
      {
        if(compteur == 1000){ // compteur et id
          divisors_memory_management(d, diviseurs, compteur);
          compteur = 0;
        }
        diviseurs[compteur] = diviseur;
        compteur++;
        diviseurs[compteur] = n/diviseur;
        compteur++;
      }
      diviseur++;
    }
  if(compteur > 0)
    divisors_memory_management(d, diviseurs, compteur);

  return d;
}
