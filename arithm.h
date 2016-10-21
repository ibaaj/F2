#ifndef ARITHM_H
#define ARITHM_H

#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    uint64_t *liste;
    uint8_t c;
} Diviseurs;

uint64_t
pp_diviseur_premier(uint64_t);

int64_t
f_exp(int64_t a, uint64_t b);

int8_t
mobius(int d);

uint64_t
euler(uint64_t n);

void
divisors_memory_management( Diviseurs *d, uint64_t *suiteListe, unsigned int taille);

Diviseurs*
get_all_divisors( uint64_t n, Diviseurs *d);


#endif /* ARITHM_H */
