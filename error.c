// error.c
// Řešení IJC-DU1, příklad b), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Tento modul obsahuje funkce pro zpracovani chyb

#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...) {
  va_list argumenty;
  va_start(argumenty, fmt);

  fprintf(stderr, "CHYBA: ");
  vfprintf(stderr, fmt, argumenty);

  va_end(argumenty);
}

void error_exit(const char *fmt, ...) {
    va_list argumenty;
    va_start(argumenty, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argumenty);

    va_end(argumenty);
    exit(1);
}