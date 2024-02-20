# Makefile
# Řešení IJC-DU1, příklad a) && b), 23/3/2021
# Autor: David Novák (xnovak2x), FIT
# Vytvořeno pro: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall  -Wextra

all: primes primes-i steg-decode

#sestaveni programu

primes: primes.o error.o eratosthenes.o bitset.o
	$(CC) $(CFLAGS) primes.o error.o eratosthenes.o bitset.o -o primes -lm

primes-i: error.o primes-i.o eratosthenes-i.o bitset-i.o
	$(CC) $(CFLAGS) error.o primes-i.o eratosthenes-i.o bitset-i.o -o primes-i -lm

steg-decode: error.o eratosthenes.o bitset.o steg-decode.o ppm.o
	$(CC) $(CFLAGS) error.o eratosthenes.o bitset.o steg-decode.o ppm.o -o steg-decode -lm

#vytvoreni .o souboru

primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

error.o: error.c
	$(CC) $(CFLAGS) -c error.c -o error.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

bitset.o: bitset.c
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

bitset-i.o: bitset.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

#dalsi veci

clear:
	rm *.o primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

zip: all
	zip xnovak2x.zip *.c *.h Makefile