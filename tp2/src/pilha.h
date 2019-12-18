#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#include <stdlib.h>

typedef int TipoDireita, TipoEsquerda;

typedef struct {
    TipoDireita Dir;
    TipoEsquerda Esq;
} TipoItem;

typedef struct Celula_str *Apontador;

typedef struct Celula_str {
    TipoItem Item;
    Apontador Prox;
} Celula;

typedef struct {
    Apontador Fundo, Topo;
} TipoPilha;

void fazPilhaVazia(TipoPilha*);
int vazia(TipoPilha*);
void empilha(TipoItem, TipoPilha*);
int desempilha(TipoPilha*, TipoItem*);

#endif
