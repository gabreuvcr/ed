#ifndef ARENDELLELIB_H
#define ARENDELLELIB_H
#include <string.h>
#include <time.h>
#include "quicksort.h"
#define num_teste 21

int verifica_vetor(int*, int **, char*, int, int, int);
int verifica_quick(char*, int*, int, struct timespec *start, struct timespec *end, long int*, long int*);
void imprime_vetores(int **, int);
void teste_argumentos(char*, char*, int, int);

#endif
