#ifndef ARVORE_H
#define ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro {
    char morse[7];
    char letra;
} Registro;

typedef struct No_str *Apontador;

typedef struct No_str {
    Registro regis;
    //ponto = lado esquerdo
    //traco = lado direito
    Apontador ponto, traco;
} No;

No *cria_no_vazio();
void insere(No*, Registro*);
void insere_rec(No*, Registro*, long int, int);
char procura(No*, char*);
char procura_rec(No*, char*, long int, int);
void imprime_preordem(No*);

#endif
