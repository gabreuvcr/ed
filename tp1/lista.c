#include "lista.h"

void faz_lista_vazia(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int verifica_lista_vazia(TipoLista *Lista) {
    return(Lista->Primeiro == Lista->Ultimo);
}

void insere_curso(TipoLista *Lista, NomeCurso *nome, NumVagas vagas) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    strcpy(Lista->Ultimo->ItemCurso.Curso, nome);
    Lista->Ultimo->ItemCurso.Vagas = vagas;
    Lista->Ultimo->Prox = NULL;
}

void insere_aluno(TipoLista *Lista, NomeAluno *nome, NotaAluno nota,
                  Opcao1 op1, Opcao2 op2) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    strcpy(Lista->Ultimo->ItemAluno.Nome, nome);
    Lista->Ultimo->ItemAluno.Nota = nota;
    Lista->Ultimo->ItemAluno.Op1 = op1;
    Lista->Ultimo->ItemAluno.Op2 = op2;
    Lista->Ultimo->Prox = NULL;
}

void insere_classificado(TipoLista *Lista, NomeAluno *nome, NotaAluno nota) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    strcpy(Lista->Ultimo->ItemClassificacao.NomesClassificacao, nome); 
    Lista->Ultimo->ItemClassificacao.NotasClassificacao = nota;
    Lista->Ultimo->Prox = NULL;
}

void desempate_classificado(TipoLista *Lista, Apontador Anterior, Apontador Alu) {
    Apontador Novo;
    Novo = (Apontador) malloc(sizeof(Celula));
    strcpy(Novo->ItemClassificacao.NomesClassificacao, Alu->ItemAluno.Nome);
    Novo->ItemClassificacao.NotasClassificacao = Alu->ItemAluno.Nota;
    Novo->Prox = Anterior->Prox;
    Anterior->Prox = Novo;
}

void retira_aluno(TipoLista *Lista, Apontador Anterior) {
    Apontador Elemento;
    if(verifica_lista_vazia(Lista) || Anterior == NULL || Anterior->Prox == NULL) {
        printf("Erro! Lista vazia ou posicao invalida");
        return;
    }
    Elemento = Anterior->Prox;
    Anterior->Prox = Elemento->Prox;
    if(Anterior->Prox == NULL) {
        Lista->Ultimo == Anterior;
    }
    free(Elemento);
}

void insere_decrescente(TipoLista *Lista, TipoLista *Nova) {
    float maior;
    Apontador E, Anterior;
    E = Lista->Primeiro->Prox;
    Anterior = Lista->Primeiro;
    while(E != NULL) {
        maior = E->ItemAluno.Nota;
        while (E->Prox != NULL) {
            if(E->Prox->ItemAluno.Nota > maior) {
                maior = E->Prox->ItemAluno.Nota; 
                Anterior = E; 
            }
            E = E->Prox;
        }
        insere_aluno(Nova, Anterior->Prox->ItemAluno.Nome, Anterior->Prox->ItemAluno.Nota,
        Anterior->Prox->ItemAluno.Op1, Anterior->Prox->ItemAluno.Op2);
        retira_aluno(Lista, Anterior);
        E = Lista->Primeiro->Prox;
        Anterior = Lista->Primeiro;
    }
    free(E);
    free(Anterior);
}

void faz_classificados(TipoLista *Alunos, TipoLista *Cursos, int numcursos) {
    int i, alunos_espera[numcursos], vagascopia[numcursos], vagas[numcursos];
    float cortes[numcursos];
    TipoLista Classificados[numcursos];
    for(i = 0; i < numcursos; i++) {
        faz_lista_vazia(&Classificados[i]);
    }
    Apontador Cur, Alu, AluAnterior, ClasAnterior[numcursos];
    Cur = Cursos->Primeiro->Prox;
    Alu = Alunos->Primeiro->Prox;
    AluAnterior = Alunos->Primeiro;
    for(i = 0; i < numcursos; i++) {
        vagas[i] = Cur->ItemCurso.Vagas;
        vagascopia[i] = Cur->ItemCurso.Vagas;
        alunos_espera[i] = 0;
        cortes[i] = 0;
        Cur = Cur->Prox;
    }
    while(Alu != NULL) { //percorre todos alunos
        if(vagas[Alu->ItemAluno.Op1] > 0) { //verifica se há vaga na opção 1
            //classifica na op1
            insere_classificado(&Classificados[Alu->ItemAluno.Op1], Alu->ItemAluno.Nome, Alu->ItemAluno.Nota);
            if(vagas[Alu->ItemAluno.Op1] == vagascopia[Alu->ItemAluno.Op1]) { //caso for o primeiro colocado
                ClasAnterior[Alu->ItemAluno.Op1] = Classificados[Alu->ItemAluno.Op1].Primeiro; //inicia o apontador do classifico anteriormente
            }
            else { //nas vezes posteriores
                ClasAnterior[Alu->ItemAluno.Op1] = ClasAnterior[Alu->ItemAluno.Op1]->Prox; //apontador recebe o prox
            }
            vagas[Alu->ItemAluno.Op1]--; //retira uma vaga do curso do aluno classificado
            if(vagas[Alu->ItemAluno.Op1] == 0) { //se não há mais vaga, a ultima nota inserida é corte
                cortes[Alu->ItemAluno.Op1] = Alu->ItemAluno.Nota;
            }
        }
        else if(vagas[Alu->ItemAluno.Op2] > 0) { //verifica se há vaga na opção 2
            //classifica na op2
            insere_classificado(&Classificados[Alu->ItemAluno.Op2], Alu->ItemAluno.Nome, Alu->ItemAluno.Nota);
            ClasAnterior[Alu->ItemAluno.Op2] = ClasAnterior[Alu->ItemAluno.Op2]->Prox;
            vagas[Alu->ItemAluno.Op2]--; //retira uma vaga do curso do aluno classificado
            //lista de espera da op1
            insere_classificado(&Classificados[Alu->ItemAluno.Op1], Alu->ItemAluno.Nome, Alu->ItemAluno.Nota);
            ClasAnterior[Alu->ItemAluno.Op1] = ClasAnterior[Alu->ItemAluno.Op1]->Prox;
            alunos_espera[Alu->ItemAluno.Op1]++; //incrementa +1 na quantidade de alunos na lista de espera do curso op1
            if(vagas[Alu->ItemAluno.Op2] == 0) { //se não há mais vaga, a ultima nota inserida é corte
                cortes[Alu->ItemAluno.Op2] = Alu->ItemAluno.Nota;
            }
        }
        else {  //caso não haja vaga em nenhum, então irá colocar na lista de espera das 2 opcoes*/

            //mas se o aluno anterior possuir a mesma nota, mas foi inserido em sua op2 e é a op1 do atual (prioridade)
            if((AluAnterior->ItemAluno.Nota == Alu->ItemAluno.Nota) && (AluAnterior->ItemAluno.Op2 == Alu->ItemAluno.Op1)) {
                desempate_classificado(&Classificados[Alu->ItemAluno.Op1], ClasAnterior[Alu->ItemAluno.Op1], Alu);
            }
            else {
            insere_classificado(&Classificados[Alu->ItemAluno.Op1], Alu->ItemAluno.Nome, Alu->ItemAluno.Nota);
            ClasAnterior[Alu->ItemAluno.Op1] = ClasAnterior[Alu->ItemAluno.Op1]->Prox;
            }
            alunos_espera[Alu->ItemAluno.Op1]++; //incrementa +1 na quantidade de alunos na lista de espera do curso op1
            
            insere_classificado(&Classificados[Alu->ItemAluno.Op2], Alu->ItemAluno.Nome, Alu->ItemAluno.Nota);
            ClasAnterior[Alu->ItemAluno.Op2] = ClasAnterior[Alu->ItemAluno.Op2]->Prox;
            alunos_espera[Alu->ItemAluno.Op2]++; //incrementa +1 na quantidade de alunos na lista de espera do curso op2
        }
        AluAnterior = AluAnterior->Prox;
        Alu = Alu->Prox;
    }
    imprime_classificacao(Cursos, Classificados, numcursos, vagascopia, cortes, alunos_espera);
    free(Cur);
    free(Alu);
    free(AluAnterior);
    for(i = numcursos-1; i <= 0; i--) {
        free(ClasAnterior[i]);
    }
}

void imprime_classificacao(TipoLista *Cursos, TipoLista *Classificados, int numcursos, int *vagas, float *cortes, int *alunos_espera) {
    int i, j;
    Apontador Cla, Cur;
    Cur = Cursos->Primeiro->Prox;
    for(i = 0; i < numcursos; i++) {
        Cla = Classificados[i].Primeiro;
        printf("%s %.2f\n", Cur->ItemCurso.Curso, cortes[i]);
        printf("Classificados\n");
        for(j = 0; (j < vagas[i] && Cla->Prox != NULL); j++) {
            Cla = Cla->Prox;
            printf("%s %.2f\n", Cla->ItemClassificacao.NomesClassificacao, Cla->ItemClassificacao.NotasClassificacao);
        }
        printf("Lista de espera\n");
        for(j = 0; j < alunos_espera[i]; j++) {
            Cla = Cla->Prox;
            printf("%s %.2f\n", Cla->ItemClassificacao.NomesClassificacao, Cla->ItemClassificacao.NotasClassificacao);
        }
        printf("\n");
        Cur = Cur->Prox;
    }
    free(Cla);
    free(Cur);
}
