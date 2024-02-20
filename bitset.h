// erastothenes.h
// Řešení IJC-DU1, příklad a), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Toto je rozhraní s makry/inline funkcemi pro tvorbu a práci s bitovými poli

#ifndef BITSET_H
#define BITSET_H

#include <limits.h>
#include "error.h"


typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(jmeno_pole, velikost)                                                   \
    _Static_assert((velikost)>0,"bitset_create: Nekladná velikost pole\n");                     \
    bitset_index_t (jmeno_pole)[/*if*/((velikost)%(CHAR_BIT*sizeof(bitset_index_t)))?         \
                                    (1+(velikost)/(CHAR_BIT*sizeof(bitset_index_t))+1)        \
                               :/*else*/                                                      \
                                    (1+(velikost)/(CHAR_BIT*sizeof(bitset_index_t)))] = {0};  \
    (jmeno_pole)[0]=(velikost);


#define bitset_alloc(jmeno_pole, velikost)                                                                  \
    assert((velikost)>0);                                                                                   \
    bitset_t (jmeno_pole) = calloc(/*if*/((velikost)%(CHAR_BIT*sizeof(bitset_index_t)))?                    \
                                       (1+(velikost)/(CHAR_BIT*sizeof(bitset_index_t))+1)                   \
                                  :/*else*/                                                                 \
                                       (1+(velikost)/(CHAR_BIT*sizeof(bitset_index_t)))                     \
                                  ,(CHAR_BIT*sizeof(bitset_index_t)));                                      \
    if((jmeno_pole) == NULL){                                                                               \
        error_exit("bitset_alloc: Chyba alokace paměti\n");                                                   \
    }                                                                                                       \
    (jmeno_pole)[0]=(velikost);

#define bitset_free(jmeno_pole) \
    free(jmeno_pole);

#ifndef USE_INLINE

#define bitset_size(jmeno_pole) \
    (jmeno_pole)[0]

#define bitset_setbit(jmeno_pole, index, vyraz)                                                                       \
if ((unsigned long)(index)>(jmeno_pole)[0]){                                                                          \
    error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)(jmeno_pole)[0]);  \
}                                                                                                                     \
(jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] = (                                                       \
    /*if*/(vyraz)?                                                                                                    \
        (jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] |                                                 \
        ((unsigned long)1 << (index) % (CHAR_BIT*sizeof(bitset_index_t)))                                             \
    :/*else*/                                                                                                         \
        (jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] &                                                 \
        (~((unsigned long)1 << (index) % (CHAR_BIT*sizeof(bitset_index_t))))                                          \
    );


#define bitset_getbit(jmeno_pole, index)                                     \
/*if*/(((index)>(jmeno_pole)[0])?                                            \
    (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",               \
    (unsigned long)index, (unsigned long)(jmeno_pole)[0]), 42)               \
:/*else*/(((jmeno_pole)[((index) / (CHAR_BIT*sizeof(bitset_index_t)))+1] >>  \
    (unsigned int)(index))%2))

#else
    inline unsigned long bitset_size(bitset_t jmeno_pole){
        return (jmeno_pole)[0];
    }

    inline unsigned int bitset_getbit(bitset_t jmeno_pole, unsigned long index){
        if((index)>(jmeno_pole)[0]){
            (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
            (unsigned long)index, (unsigned long)(jmeno_pole)[0]));
        }
        return (((jmeno_pole)[((index) / (CHAR_BIT*sizeof(bitset_index_t)))+1] >> (unsigned int)(index))%2);
    }

    inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, long vyraz){
        if ((unsigned long)(index)>(jmeno_pole)[0]){
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
                       (unsigned long)index, (unsigned long)(jmeno_pole)[0]);
        }
        (jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] = (
            /*if*/(vyraz)?
                (jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] |
                ((unsigned long)1 << (index) % (CHAR_BIT*sizeof(bitset_index_t)))
            :/*else*/
                (jmeno_pole)[((index)/(CHAR_BIT*sizeof(bitset_index_t)))+1] &
                (~((unsigned long)1 << (index) % (CHAR_BIT*sizeof(bitset_index_t))))
            );
    }
#endif

#endif //IJC_PROJEKT_1_PPM_H
