// primes.c
// Řešení IJC-DU1, příklad a), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento program najde prvnočísla v intervalu <0;HLEDANI_MAX) a posledních POSLEDNICH_PRV vzestupně vypíše na stdout

#include "error.h"
#include "eratosthenes.h"
#include "bitset.h"
#include <stdio.h>
#include <time.h>

#define POSLEDNICH_PRV 10 //pocet poslednich prvocisel ktere se vytisknou
#define HLEDANI_MAX 200000000 //v intervalu <0;HLEDANI_MAX) - cislo HLEDANI_MAX už neni soucasti intervalu

int main(){
    time_t start = clock();
bitset_create(pole, HLEDANI_MAX)

    Eratosthenes(pole);

    unsigned long na_tisk[POSLEDNICH_PRV] = {0};
    int j = 0;//pocitadlo zapsanych prvocisel na tisk

    for(unsigned long i = bitset_size(pole)-1; i>0; i--){//prochazi bit. pole prvocisel odzadu
        if(!bitset_getbit(pole, i)){
            na_tisk[j] = i;
            j++;
        }
        if(j==POSLEDNICH_PRV){
            break;
        }
    }

    //tisk prvocisel opacne (vzestupne)
    for(int i = POSLEDNICH_PRV-1; i>=0; i--){
        if(na_tisk[i] != 0){
            printf("%lu\n", na_tisk[i]);
        }
    }

    //tisk casu
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
