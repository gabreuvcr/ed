#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char NomeCurso, NomeAluno;
typedef int NumVagas, Opcao1, Opcao2, NumEspera;
typedef float NotaAluno, NotaCorte;

typedef struct {
    NomeCurso Curso[100];
    NumVagas Vagas;
} TipoCurso;

typedef struct {
    NomeAluno Nome[100];
    NotaAluno Nota;
    Opcao1 Op1;
    Opcao2 Op2;
} TipoAluno;

typedef struct {
    NomeAluno NomesClassificacao[100];
    NotaAluno NotasClassificacao;
} TipoClassificao;

typedef struct Celula_str *Apontador;

typedef struct Celula_str {
    TipoCurso ItemCurso;
    TipoAluno ItemAluno;
    TipoClassificao ItemClassificacao;
    Apontador Prox;
} Celula;

typedef struct {
    Apontador Primeiro, Ultimo;
} TipoLista;

void faz_lista_vazia(TipoLista*);
int verifica_lista_vazia(TipoLista*);
void insere_curso(TipoLista*, NomeCurso*, NumVagas);
void insere_aluno(TipoLista*, NomeAluno*, NotaAluno, Opcao1, Opcao2);
void retira_aluno(TipoLista*, Apontador);
void desempate_classificado(TipoLista*, Apontador, Apontador);
void insere_decrescente(TipoLista*, TipoLista*);
void faz_classificados(TipoLista*, TipoLista*, int);
void imprime_classificacao(TipoLista*, TipoLista*, int, int*, float*, int*);

#endif
