// erastothenes.c
// Řešení IJC-DU1, příklad a), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento modul implementuje algoritmus Erastothenova síta nad bitovým polem

#include "bitset.h"
#include "error.h"
#include <math.h>
#include <limits.h>

void Eratosthenes(bitset_t pole){

    //nastaveni prvnich bitu pro 0 a 1
    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    for(unsigned long x = 2; (double)x < sqrt(bitset_size(pole));x++){
        //neni prvocislo, muzu preskocit
        if(!bitset_getbit(pole, x)) {
            //projde pole a nastavi nasobky prvocisla na 1
            for (unsigned long i = x + x; i < bitset_size(pole); i += x) {
                bitset_setbit(pole, i, 1);
            }
        }
    }
}
