#include "quicksort.h"

void QuickClas(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaCentral(0, n-1, A, n_comp, n_mov);
}

void QuickM3(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaM3(0, n-1, A, n_comp, n_mov);
}

void QuickPE(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaPE(0, n-1, A, n_comp, n_mov);
}

void QuickI1(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaI(0, n-1, n, A, n_comp, n_mov, 0.01);
}

void QuickI5(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaI(0, n-1, n, A, n_comp, n_mov, 0.05);
}

void QuickI10(int *A, int n, long int *n_comp, long int *n_mov) {
    OrdenaI(0, n-1, n, A, n_comp, n_mov, 0.1);
}

void QuickNR(int *A, int n, long int *n_comp, long int *n_mov) {
    TipoPilha pilha;
    TipoItem item;
    int esq, dir, i, j;
    fazPilhaVazia(&pilha);
    esq = 0; 
    dir = n - 1;
    item.Dir = dir;
    item.Esq = esq;
    empilha(item, &pilha);
    do {
        if(dir > esq) {
            ParticaoCentral(esq, dir, &i, &j, A, n_comp, n_mov);
            if((j - esq) > (dir - i)) {
                item.Dir = j;
                item.Esq = esq;
                empilha(item, &pilha);
                esq = i;
            }
            else {
                item.Esq = i;
                item.Dir = dir;
                empilha(item, &pilha);
                dir = j;
            }
        }
        else {
            desempilha(&pilha, &item);
            dir = item.Dir;
            esq = item.Esq;
        }
    } while(vazia(&pilha) == 0);
}
