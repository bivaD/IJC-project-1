// steg-decode.c
// Řešení IJC-DU1, příklad b), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento program dekoduje zprávu podle zadání projektu

#include "eratosthenes.h"
#include <stdlib.h>
#include "bitset.h"
#include <stdio.h>
#include "ppm.h"
#include "error.h"
#include <assert.h>

int main(int argc, char *argv[]){

    //nacteni obrazku
    struct ppm * obrazek;
    if (argc != 2) {
        error_exit("Program musí mít jeden argument, a to jméno obrázku .ppm\n");
    }
    obrazek = ppm_read(argv[1]);
    if(obrazek == NULL){
            error_exit("Nepodařilo se načíst obrázek\n");
    }

    //alokace bitoveho pole a aplikace eratosthenova sita
    bitset_alloc(bitove_pole, (obrazek->xsize * obrazek->ysize * 3))
    Eratosthenes(bitove_pole);

    //desifrovani & tisk zpravy
    unsigned pomocny_znak;
    unsigned znak_na_tisk = 0;
    unsigned pocitadlo = 0; //pocita pozici bitu v charu
    unsigned long i = 23;
    for(; i<bitset_size(bitove_pole); i++){
        if(!bitset_getbit(bitove_pole, i)){ //pokud je dany index prvocislo
            pomocny_znak = (unsigned)obrazek->data[i]%2; //ziska lsb znaku (0 nebo 1)
            pomocny_znak <<= pocitadlo; //posune bit na spravne misto
            znak_na_tisk |= pomocny_znak; //vlozi bit do znaku pro tisk
            pocitadlo++;
            if(pocitadlo != CHAR_BIT){
                continue;
            }
            pocitadlo = 0;
            if(znak_na_tisk == '\0'){
                break;
            }
            putc((char)znak_na_tisk, stdout);
            znak_na_tisk ^= znak_na_tisk;
        }
    }
    putc('\n', stdout);
    if(i == bitset_size(bitove_pole)){
        error_exit("Tajná zpráva není korektně ukončena znakem '\\0'\n");
    }



    bitset_free(bitove_pole)
    ppm_free(obrazek);
}
