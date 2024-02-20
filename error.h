// error.h
// Řešení IJC-DU1, příklad b), 23/3/2021
// Autor: David Novák (xnovak2x), FIT
// Přeloženo: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Toto je hlavičkový soubor modulu error.c

#ifndef ERROR_H
#define ERROR_H

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif //IJC_PROJEKT_1_ERROR_H
