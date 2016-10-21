#include "f2_poly.h"
#include "arithm.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define PERMUTER(x,y) x ^= y, y ^= x, x ^= y
const int PREMIER64[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
const int EXP_MERSENNE_PIRME64[] = {2,3,5,7,13,17,19,31,61 }; // 2^m - 1 prime




// retourner l'index du "MSB" (most significant bit)
f2_deg_t f2_poly_deg(f2_poly_t pol)
{
  f2_deg_t b = 0;
  uint64_t n = pol;

  if (!n)
    return 0;

  #define step(x) if (n >= ((uint64_t)1) << x) b += x, n >>= x
  step(32); step(16); step(8); step(4); step(2); step(1);
  #undef step

  return b;

}

int f2_poly_print(f2_poly_t f, char c, FILE * fi){

  if ( f == 0 || f == 1 )
  {
    fprintf(fi, "%" PRIu64 "\n", f);
    return 0;
  }

  f2_deg_t deg = f2_poly_deg(f);
  fprintf(fi, "%c^%d ", c, deg);


  while (deg > 1) {
      deg--;
    if (f >> deg & 1)
      fprintf(fi, "+ %c^%d ", c, deg);

  }


  if(f%2==1)
    fprintf(fi, "+ 1");

  fprintf(fi,"\n");
  return 0;
}



int
f2_poly_div(f2_poly_t *quotient,f2_poly_t *reste,  \
                  f2_poly_t dividende, f2_poly_t diviseur){

  assert(diviseur != 0); /* division par 0 ... */

  if(diviseur == 1) { /* division par 1 ... */
    *quotient = dividende;
    *reste = 0;
    return 0;
  }
  if(diviseur > dividende){ /* si le diviseur est plus grand que le dividende ... */
    *quotient = 0;
    *reste = dividende;
    return 0;
  }

  f2_poly_t degDiviseur = f2_poly_deg(diviseur);
  *quotient = 0; // on initialise le quotient à 0

  int k = f2_poly_deg(dividende) - degDiviseur;

  while((k >= 0) && (dividende != 0)){
    *quotient |= ( 1ull << k );
    dividende ^= (diviseur << k);
    k = f2_poly_deg(dividende) - degDiviseur;
  }
  *reste = dividende;

  return 0;

}


// reste de arg1 par arg2
f2_poly_t
f2_poly_rem(f2_poly_t dividende, f2_poly_t diviseur ){

  assert(diviseur != 0);

  if( diviseur == 1 ) // division par 1 ...
    return 0;

  int degDiviseur = f2_poly_deg(diviseur);


  int k = f2_poly_deg(dividende) - degDiviseur;

  while( k >= 0 && (dividende != 0) ){
    dividende = dividende ^ (diviseur << k);
    k = f2_poly_deg(dividende) - degDiviseur;

  }


  return dividende;
}


f2_poly_t
f2_poly_gcd(f2_poly_t arg1, f2_poly_t arg2){

  f2_poly_t tmp;

  if( arg2 > arg1)
    PERMUTER(arg1,arg2);

  if(arg2 == 0)
    return arg1;

    tmp = 1;
    while( tmp != 0 ){

      tmp = f2_poly_rem(arg1,arg2);
      if( tmp == 0 ){
        return arg2;
      }
      arg1 = arg2;
      arg2 = tmp;
    }

return tmp;

}


// retourne X*arg1 mod (arg2)
f2_poly_t
f2_poly_xtimes(f2_poly_t arg1, f2_poly_t arg2){

  return f2_poly_rem(arg1 << 1,arg2);
}


// retourne arg1 * arg2 modulo  arg3
f2_poly_t
f2_poly_times(f2_poly_t arg1, f2_poly_t arg2, f2_poly_t arg3){

  f2_poly_t r = 0;

  f2_deg_t d1 = f2_poly_deg(arg1),
           d2 = f2_poly_deg(arg2),
           i = 0;

  // cette technique est plus rapide
  // mais demande que les 2 degs des polys < 32
  // car un shift left de 32 avec un poly de deg 32 = impossible
  // avec des uint64_t, au début j'avais opté pour des uint128
  // avant de trouver une seconde manière et de traiter les 2 cas
  if((d1 + d2) < 64)
  {
    for( i = 0; i <= d1; i++)
      if( arg1 & (1ull << i) )
        r ^= ( arg2 << i );
    return f2_poly_rem(r, arg3);
  }

  arg1 = f2_poly_rem(arg1, arg3);
  arg2 = f2_poly_rem(arg2, arg3);

  // on réduit progressivement la taille de arg2
  while(arg2 != 0)
  {
      if(( arg2 & 1 ) == 0){
        arg1 = f2_poly_xtimes(arg1, arg3); // x*arg1 mod arg3;
        arg2 = arg2 >> 1; // réduire arg2
      }
      else
      {
          r ^= arg1; // XOR avec arg1
          arg2 ^= 1; // dernier bit XORé pour le prochain loop
      }
  }

  return r;
}



// retourne X^2^d  modulo arg2
f2_poly_t
f2_poly_x2n(f2_deg_t n, f2_poly_t mod){


  if( n == 0 )
		return 1;

	int i;
	f2_poly_t ret = 0x2; //initialisation à X
	for( i = 0; i < n; i++)
		ret = f2_poly_times(ret, ret, mod);

	return ret;


}
//retourne le reste de la division par X+1 (xor des bits)
f2_poly_t
f2_poly_parity(f2_poly_t arg1){

  return f2_poly_rem(arg1, 0x3);

}


// retourne le polynôme réciproque considéré comme de degré le second argument
f2_poly_t
f2_poly_recip(f2_poly_t arg1){

  f2_deg_t deg = f2_poly_deg(arg1);

  arg1 = ((arg1 & 0x5555555555555555ULL) << 1)
  ^ ((arg1 & 0xaaaaaaaaaaaaaaaaULL) >> 1);
  arg1 = ((arg1 & 0x3333333333333333ULL) << 2)
  ^ ((arg1 & 0xccccccccccccccccULL) >> 2);
  arg1 = ((arg1 & 0x0f0f0f0f0f0f0f0fULL) << 4)
  ^ ((arg1 & 0xf0f0f0f0f0f0f0f0ULL) >> 4);
  arg1 = ((arg1 & 0x00ff00ff00ff00ffULL) << 8)
  ^ ((arg1 & 0xff00ff00ff00ff00ULL) >> 8);
  arg1 = ((arg1 & 0x0000ffff0000ffffULL) << 16)
  ^ ((arg1 & 0xffff0000ffff0000ULL) >> 16);
  arg1 = ((arg1 & 0x00000000ffffffffULL) << 32)
  ^ ((arg1 & 0xffffffff00000000ULL) >> 32);

  arg1 = arg1 >> (63 - deg); // shift

  return arg1;

}

// vérifie si le polynôme arg1 est irréductible
int
f2_poly_irred(f2_poly_t arg1){

	f2_deg_t n = f2_poly_deg(arg1);

  // 0,1 ne sont pas "irréductibles"
  if(arg1 == 0 || arg1 == 1)
    return 0;

  // X, X +1 sont irreductibles
	if( arg1 < 4 ){
	 return 1;
	}

  //on regarde si il y a qu'un seul bit set
  // X^n pour n > 1 n'est pas irred
  uint8_t c = arg1 && !(arg1 & (arg1-1)),
          i;

  if(c == 1)
    return 0;

   //il faut qu'il y ait un nombre impair de termes
  if(__builtin_popcountll(arg1) % 2 == 0)
      return 0;

  // si le polynome ne finit pas par + 1
  if((arg1 & 1) == 0)
    return 0;


  f2_poly_t x2n = f2_poly_x2n(n, arg1);



  if (x2n != 0x2) // congru à X ?
      return 0;


  for(i = 0; i < 18; ++i){
    if(PREMIER64[i] > n)
      break;

    if(n % PREMIER64[i] == 0)
    {
      // on cherche "fabriquer" X^2^(n/p) + X
      // et faire son pgcd avec arg1
      // 1ère étape on calcul d = X^2^(n/p) mod arg1
      // or on a besoin de X^2^(n/p) + X mod arg1 (d'ou le XOR avec 0x2)
      // enfin on calcul le PGCD
      x2n = f2_poly_x2n(n / PREMIER64[i], arg1);
      x2n = x2n ^ 0x2; // + X sur F2

      if(f2_poly_gcd( x2n, arg1) != 0x1 )
        return 0;
    }
  }
  return 1;


}



//retourne le nombre de polynomes irréducibles de degré n
uint64_t
f2_poly_irred_count(f2_deg_t n){


  if (n == 0)
    return 0;

  if(n == 1)
    return 2;


    int64_t result = 0,
            d = 1;

  while(d*d < (n+1))
  {
    if(n % d == 0)
        result += mobius(d)*MASK(n/d) + mobius(n/d)*MASK(d);

    ++d;
  }

  result = result / n + result % 2;

  return (uint64_t) result;

}



// retourne X^{arg1} modulo arg 2
f2_poly_t
f2_poly_xn(f2_poly_t arg1, f2_poly_t arg2){

  if(arg1 == 0) // deg 0 ...
    return 1;

  if(arg1 == 1)
    return f2_poly_rem(0x2, arg2);

  f2_poly_t ret = 1;
  uint64_t i;

  for( i = 0; i < arg1; i++)
  	 ret = f2_poly_rem(ret << 1,  arg2);


    return ret;
}



// retourne un polynôme tiré au hasard parmi les polynômes de degré < arg
f2_poly_t
f2_poly_random_inf(f2_deg_t arg1){

  FILE * f;
  uint64_t x_min = 2; // 0 or 1 n'a pas vraiment de sens.
  uint64_t x_max;
  int n = 0, nb_bits;
  uint64_t r,x;
  int readBytes;

  if ((f = fopen(RANDOMFILE,"r")) == NULL){
		fprintf(stderr, "Error opening %s for reading: Permission denied", RANDOMFILE);
		exit(1);
	}
    x_max = ULLONG_MAX >> -arg1; // 111..11 de la taille de arg1

    readBytes = fread(&r, sizeof(uint64_t), 1, f);
    nb_bits = r % arg1; // nb random de bits set

    while (n != nb_bits)
    {
        readBytes = fread(&r, sizeof(uint64_t), 1, f);
        x = r;
        if (arg1 > 31){
          readBytes = fread(&r, sizeof(uint64_t), 1, f);
          x ^= r << 31;
        }

        if (arg1 > 62){
          readBytes = fread(&r, sizeof(uint64_t), 1, f);
          x ^= r << 33;
        }

        x = x_min | (x & x_max);
        n = __builtin_popcountll(x); // compter le nombre de bits set

        if (n > nb_bits)
            x_max = x;
        else
            x_min = x;

    }
    fclose(f);
    return x_min;

}

f2_poly_t
f2_poly_random(f2_deg_t arg1){

  FILE * f;
  uint64_t x_min = (1ull << arg1);
  uint64_t x_max;
  int n = 0, nb_bits;
  uint64_t r, x = 0;
  int readBytes;

  if ((f = fopen(RANDOMFILE,"r")) == NULL){
    fprintf(stderr, "Error opening %s for reading: Permission denied", RANDOMFILE);
    exit(1);
  }
    x_max = ULLONG_MAX >> -arg1; // 111..11 avec la taille de arg1

    readBytes = fread(&r, sizeof(uint64_t), 1, f);
    nb_bits = r % arg1 + 1; // nb random de bits set

    while (n != nb_bits)
    {
        readBytes = fread(&r, sizeof(uint64_t), 1, f);
        x = r;
        if (arg1 > 31){
          readBytes = fread(&r, sizeof(uint64_t), 1, f);
          x ^= r << 31;
        }

        if (arg1 > 62){
          readBytes = fread(&r, sizeof(uint64_t), 1, f);
          x ^= r << 33;
        }

        x = x_min | (x & x_max);
        n = __builtin_popcountll(x); // compter le nombre de bits set

        if (n > nb_bits)
            x_max = x;
        else
            x_min = x;

    }
    fclose(f);
    return x;
}




// vérifie si le polynôme arg1 est primitif
int
f2_poly_primitive(f2_poly_t arg1){

  if( !f2_poly_irred(arg1))
    return 0;



  f2_deg_t d = f2_poly_deg(arg1),k;

  if( d == 1 || d == 2 ) // X,X+1,X^2+X+1 primitifs
    return 1;

  for(k = 0; k < 8; ++k)
    if(d == EXP_MERSENNE_PIRME64[k])
      return 1;

  Diviseurs diviseurs;
  diviseurs.liste = NULL;
  diviseurs.c = 0;

  uint64_t i = 2, // on skip 1 et 2^d - 1 comme diviseur
          n = f_exp(2,d) -1;

  get_all_divisors(n,&diviseurs);

  for(; i < diviseurs.c; ++i){
    if ( f2_poly_xn(diviseurs.liste[i], arg1) == 1 || f2_poly_xn(n/diviseurs.liste[i],arg1) == 1)
      return 0;
  }

  return 1;

}



// renvoie 0 si le polynôme polP n'est pas irréductible,
// l'ordre multiplicatif d'une racine, soit de  X modulo P sinon
// Si cet ordre égale 1 << f2_poly-deg(P), le polynôme est primitif.

uint64_t
f2_poly_irred_order(f2_poly_t polP){

  if( !f2_poly_irred(polP))
    return 0;

  f2_deg_t d = f2_poly_deg(polP);

  if( d == 1 || d == 2 ) // X,X+1,X^2+X+1 primitifs
    return 1;

  f2_poly_t i = 1,
          p = f_exp(2, f2_poly_deg(polP)) - 1;

for(i = 0; i < 8; ++i)
  if(d == EXP_MERSENNE_PIRME64[i])
    return p;

  for(i = 1; i < (p+1); ++i)
    if(p % i == 0)
      if (f2_poly_xn(i,polP) == 1 )
        return i;

  return p;


}



// retourne un polynôme tiré au hasard parmi les polynômes irréductibles
// de degré = arg2
f2_poly_t
f2_poly_irred_random(f2_deg_t arg1){

	f2_poly_t r = f2_poly_random(arg1);

	while(!f2_poly_irred(r)){
		r = f2_poly_random(arg1);
	}

	return r;

}


// retourne un polynôme tiré au hasard parmi les polynômes primitifs
// de degré = arg2
f2_poly_t
f2_poly_primitive_random(f2_deg_t arg1){
	f2_poly_t r = f2_poly_random(arg1);

	while(!f2_poly_primitive(r)){
		r = f2_poly_random(arg1);
	}

	return r;
}


//retourne le nombre de polynome primitifs de degré n
uint64_t
f2_poly_primitive_count(f2_deg_t n){

  // phi(Q^n - 1) / n

  uint64_t x = MASK(n), i;

  for(i = 0; i < 8; ++i)
    if(n == EXP_MERSENNE_PIRME64[i])
      return f2_poly_irred_count(n); // + rapide qu'euler



  return (uint64_t) euler(x)/ n;


}
