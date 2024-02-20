// bitset.c
// Řešení IJC-DU1, příklad a), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento soubor obsahuje extern deklarace funkci

#include "bitset.h"

#ifdef USE_INLINE
extern inline unsigned long bitset_size(bitset_t jmeno_pole);
extern inline unsigned int bitset_getbit(bitset_t jmeno_pole, unsigned long index);
extern inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, long vyraz);

#endif
