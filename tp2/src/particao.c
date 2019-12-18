#include "particao.h"

int Mediana3(int Esq, int Dir, int *A, long int *n_comp) {
    int primeiro, meio, ultimo, aux;
    primeiro = A[Esq];
    ultimo = A[Dir];
    meio = A[(Esq + Dir)/2];
    //usando xor
    if((primeiro > meio) != (primeiro > ultimo)) {
        //2 comparacoes caso entrar no if
        (*n_comp) += 2;
        return primeiro;
    }
    else if((meio > primeiro) != (meio > ultimo)) {
        //4 comparacoes (2 do if acima e 2 do else if)
        (*n_comp) += 4;
        return meio;
    }
    else {
        //caso não entrar em nenhum, fazendo 4 comparações
        (*n_comp) += 4;
        return ultimo;
    }
}

void ParticaoM3(int Esq, int Dir, int *i, int *j, int *A, long int *n_comp, long int *n_mov) {
    int pivo, aux;
    *i = Esq;
    *j = Dir;
    //pivo mediana de três
    pivo = Mediana3(Esq, Dir, A, n_comp);
    do {
        (*n_comp)++;
        while(pivo > A[*i]) {
            (*n_comp)++;
            (*i)++;
        }
        (*n_comp)++;
        while(pivo < A[*j]) {
            (*n_comp)++;
            (*j)--;
        }
        if(*i <= *j) {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*n_mov) += 3;
            (*i)++;
            (*j)--;
        }
    } while(*i <= *j);

}

void ParticaoCentral(int Esq, int Dir, int *i, int *j, int *A, long int *n_comp, long int *n_mov) {
    int pivo, aux;
    *i = Esq;
    *j = Dir;
    //pivo central
    pivo = A[(*i + *j)/2];
    do {
        (*n_comp)++;
        while(pivo > A[*i]) {
            (*n_comp)++;
            (*i)++;
        }
        (*n_comp)++;
        while(pivo < A[*j]) {
            (*n_comp)++;
            (*j)--;
        }
        if(*i <= *j) {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*n_mov) += 3;
            (*i)++;
            (*j)--;
        }
    } while(*i <= *j);

}

void ParticaoPE(int Esq, int Dir, int *i, int *j, int *A, long int *n_comp, long int *n_mov) {
    int pivo, aux;
    *i = Esq;
    *j = Dir;
    //primeiro elemento como pivo
    pivo = A[Esq];
    do {
        (*n_comp)++;
        while(pivo > A[*i]) {
            (*n_comp)++;
            (*i)++;
        }
        (*n_comp)++;
        while(pivo < A[*j]) {
            (*n_comp)++;
            (*j)--;
        }
        if(*i <= *j) {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*n_mov) += 3;
            (*i)++;
            (*j)--;
        }
    } while(*i <= *j);
}
