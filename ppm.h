// ppm.h
// Řešení IJC-DU1, příklad b), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Toto je hlavičkový soubor modulu ppm.c

#ifndef PPM_H
#define PPM_H

#define LIMIT_ROZMER 5

struct ppm * ppm_read(const char *filename);

void ppm_free(struct ppm *p);

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; //RGB bajty, velikost 3*xsize*ysize
};

#endif //IJC_PROJEKT_1_PPM_H
