#include "ordena.h"

void OrdenaCentral(int Esq, int Dir, int *A, long int *n_comp, long int *n_mov) {
    int i, j;
    ParticaoCentral(Esq, Dir, &i, &j, A, n_comp, n_mov);
    if(Esq < j) {
        OrdenaCentral(Esq, j, A, n_comp, n_mov);
    }
    if(Dir > i) {
        OrdenaCentral(i, Dir, A, n_comp, n_mov);
    }
}

void OrdenaM3(int Esq, int Dir, int *A, long int *n_comp, long int *n_mov) {
    int i, j;
    ParticaoM3(Esq, Dir, &i, &j, A, n_comp, n_mov);
    if(Esq < j) {
        OrdenaM3(Esq, j, A, n_comp, n_mov);
    }
    if(Dir > i) {
        OrdenaM3(i, Dir, A, n_comp, n_mov);
    }
}

void OrdenaPE(int Esq, int Dir, int *A, long int *n_comp, long int *n_mov) {
    int i, j;
    ParticaoPE(Esq, Dir, &i, &j, A, n_comp, n_mov);
    if(Esq < j) {
        OrdenaPE(Esq, j, A, n_comp, n_mov);
    }
    if(Dir > i) {
        OrdenaPE(i, Dir, A, n_comp, n_mov);
    }
}

void Insercao(int *A, int Dir, int Esq, long int *n_comp, long int *n_mov) {
    int i, j, aux;
    for(i = Esq+1; i <= Dir; i++) {
        aux = A[i];
        (*n_mov)++;
        j = i - 1;
        while((j >= 0) && (aux < A[j])) {
            (*n_comp)++;
            A[j + 1] = A[j];
            (*n_mov)++;
            j--;
        }
        A[j + 1] = aux;
        (*n_mov)++;
    }
}

void OrdenaI(int Esq, int Dir, int elementos_totais, int *A, long int *n_comp, long int *n_mov, float porcentagem) {
    int i, j, num_elementos;
    num_elementos = Dir - Esq + 1;
    if(num_elementos < (elementos_totais * porcentagem) && (num_elementos > 0)) {
        Insercao(A, Dir, Esq, n_comp, n_mov);
        return;
    }
    ParticaoM3(Esq, Dir, &i, &j, A, n_comp, n_mov);
    if(Esq < j) {
        OrdenaI(Esq, j, elementos_totais, A, n_comp, n_mov, porcentagem);
    }
    if(Dir > i) {
        OrdenaI(i, Dir, elementos_totais, A, n_comp, n_mov, porcentagem);
    }
}
