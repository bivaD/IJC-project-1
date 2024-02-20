// ppm.c
// Řešení IJC-DU1, příklad b), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento modul obahuje funkce pro dynamické načtení obrázku .ppm ve formátu P6

#include "bitset.h"
#include "ppm.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct  ppm * ppm_read(const char *filename){

    struct ppm *obrazek = malloc(sizeof(struct ppm));
    if (obrazek == NULL){
        warning_msg("Nepodařilo se alokovat pamět\n");
        return NULL;
    }

    //otevreni a overeni spravnosti otevreni souboru
    FILE *p_obrazek;
    p_obrazek = fopen(filename, "rb");
    if(p_obrazek == NULL)
    {
        warning_msg("Nepodařilo se otevřít soubor\n");
        return NULL;
    }

    int c;
    char format[3];
    //nacte prvni dva znaky, ktere musi byt format obrazku P6
    format[0] = (char)fgetc(p_obrazek);
    format[1] = (char)fgetc(p_obrazek);
    format[2] = '\0';
    //kontrola formatu
    if(strcmp(format, "P6") != 0){
        free(obrazek);
        fclose(p_obrazek);
        warning_msg("Špatný formát obrázku, je vyžadován formát P6\n");
        return NULL;
    }

    //dale nactu rozmery
    //implementacni limit si zvolim ctyrciferne cislo, tzn. max. 9999
    char sirka_obrazku[LIMIT_ROZMER];
    char vyska_obrazku[LIMIT_ROZMER];

    //odstrani konec radku, popr. vic
    do{c=fgetc(p_obrazek);} while(c == '\n');

    //nacte sirku
    for(int i = 0; i<LIMIT_ROZMER; i++){
        if(i == LIMIT_ROZMER) {
            fclose(p_obrazek);
            free(obrazek);
            warning_msg("Obrázek je širší než 9999 pixelů\n");
            return NULL;
        } else if (c >= '0' && c <= '9') {
            sirka_obrazku[i] = (char)c;
        } else if (c == ' '){
            sirka_obrazku[i] = '\0';
            c=fgetc(p_obrazek);
            break;
        } else {
            fclose(p_obrazek);
            free(obrazek);
            warning_msg("Nepodařilo se načíst šířku obrázku\n");
            return NULL;
        }
        c=fgetc(p_obrazek);
    }
    //nacte sirku
    char *endptr;
    obrazek->xsize = strtoul(sirka_obrazku, &endptr, 10);
    if (*endptr != '\0') {
        fclose(p_obrazek);
        free(obrazek);
        warning_msg("Nepodařila se konveze šířky na číslo\n");
        return NULL;
    }

    //nacte vysku
    for(int i = 0; i<LIMIT_ROZMER; i++){
        if(i == LIMIT_ROZMER) {
            fclose(p_obrazek);
            free(obrazek);
            warning_msg("Obrázek je vyšší než 9999 pixelů\n");
            return NULL;
        } else if (c >= '0' && c <= '9') {
            vyska_obrazku[i] = (char) c;
        } else if (c == '\n'){
            vyska_obrazku[i] = '\0';
            break;
        } else {
            fclose(p_obrazek);
            free(obrazek);
            warning_msg("Nepodařilo se načíst výšku obrázku\n");
            return NULL;
        }
        c=fgetc(p_obrazek);
    }
    //zapise vysku
    obrazek->ysize = strtoul(vyska_obrazku, &endptr, 10);
    if (*endptr != '\0') {
        fclose(p_obrazek);
        free(obrazek);
        warning_msg("Nepodařila se konveze šířky na číslo\n");
        return NULL;
    }

    char rozsah[5]; //prostor pro tri cifry + konec radku + implicitni '\0' od fgets
    fgets(rozsah, 5, p_obrazek);
    if(rozsah[3] == '\n') {
        rozsah[3] = '\0';
    } else {
        fclose(p_obrazek);
        free(obrazek);
        warning_msg("Barvy v obrázku musí mít max. rozsah 255\n");
        return NULL;
    }
    if (strcmp(rozsah, "255") != 0){
        fclose(p_obrazek);
        free(obrazek);
        warning_msg("Barvy v obrázku musí mít max. rozsah 255\n");
        return NULL;
    }

    //nacteni dat obrazku
    unsigned long velikost_dat = (obrazek->xsize * obrazek->ysize* 3);
    struct ppm *p = realloc(obrazek, (velikost_dat*CHAR_BIT) + sizeof(struct ppm));
    if (obrazek == NULL){
        fclose(p_obrazek);
        free(obrazek);
        warning_msg("Alokace paměti\n");
        return NULL;
    }
    obrazek = p;
    if(fread(obrazek->data, 1, velikost_dat, p_obrazek)!= velikost_dat) {
        warning_msg("Nepodařilo se načíst data obrázku\n");
        free(obrazek);
        fclose(p_obrazek);
        return NULL;
    }
    fclose(p_obrazek);
    return obrazek;
}

void ppm_free(struct ppm * p){
    free(p);
}
