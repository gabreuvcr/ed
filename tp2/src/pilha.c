#include "pilha.h"

void fazPilhaVazia(TipoPilha *Pilha) {
    Pilha->Topo = (Apontador) malloc(sizeof(Celula));
    Pilha->Fundo = Pilha->Topo;
    Pilha->Topo->Prox = NULL;
}

int vazia(TipoPilha *Pilha) {
    return(Pilha->Topo == Pilha->Fundo);
}

void empilha(TipoItem item, TipoPilha *Pilha) {
    Apontador Aux;
    Aux = (Apontador) malloc(sizeof(Celula));
    Pilha->Topo->Item = item;
    Aux->Prox = Pilha->Topo;
    Pilha->Topo = Aux;
}

int desempilha(TipoPilha *Pilha, TipoItem *item) {
    Apontador Aux;
    if(vazia(Pilha)) {
        printf("ERRO: Pilha está vazia");
        return 0;
    }
    Aux = Pilha->Topo;
    Pilha->Topo = Aux->Prox;
    free(Aux);
    *item = Pilha->Topo->Item;
    return 1;
}
