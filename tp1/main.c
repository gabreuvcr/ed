#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    TipoLista Cursos, Alunos, AlunoCrescente;
    int numcursos, numalunos, i, vagas, op1, op2;
    float nota;
    char nomecurso[100], nomealuno[100];
    //cria as listas vazias
    faz_lista_vazia(&Cursos);
    faz_lista_vazia(&Alunos);
    faz_lista_vazia(&AlunoCrescente);
    //leitura do numero de cursos e numero de alunos
    scanf("%d", &numcursos);
    scanf("%d", &numalunos);
    //leitura dos cursos
    for(i = 0; i < numcursos; i++) {
        fgets(nomecurso, 100, stdin); //pegando o \n da string
        fgets(nomecurso, 100, stdin); //pegando o nome do curso
        size_t len;
        len = strlen(nomecurso);
        if(nomecurso[len - 1] == '\n') nomecurso[len - 1] = 0;
        scanf("%d", &vagas);
        insere_curso(&Cursos, nomecurso, vagas);
    }
    //leitura dos alunos
    for(i = 0; i < numalunos; i++) {
        fgets(nomealuno, 100, stdin); //pegando o \n da string
        fgets(nomealuno, 100, stdin); //pegando o nome do aluno
        size_t len;
        len = strlen(nomealuno);
        if(nomealuno[len - 1] == '\n') nomealuno[len - 1] = 0;
        scanf("%f", &nota);
        scanf("%d", &op1);
        scanf("%d", &op2);
        insere_aluno(&Alunos, nomealuno, nota, op1, op2);
    }
    //ordena a lista Alunos de forma decrescente em uma nova lista
    insere_decrescente(&Alunos, &AlunoCrescente);
    //classifica os alunos e imprime o resultado final
    faz_classificados(&AlunoCrescente, &Cursos, numcursos);
    
    return 0;
}
