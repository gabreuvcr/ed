#include "arvore.h"

No *cria_no_vazio() { //cria um no vazio
    No *no = malloc(sizeof(No*));
    strcpy(no->regis.morse, " ");
    no->regis.letra = ' ';
    no->ponto = NULL;
    no->traco = NULL;
    return no;
}

void insere_rec(No *trie, Registro *reg, long int len, int nivel) {
    if(nivel == len) { //quando estiver na posicao correta (tamanho do morse)
        //insere as informacoes letra e morse
        trie->regis.letra = reg->letra;
        strcpy(trie->regis.morse, reg->morse);
        return;
    }
    if(reg->morse[nivel] == '.') { //se o simbolo atual for um ponto
        if(trie->ponto == NULL) {
            /*se o no apontado for null
            é criado um no vazio nesse lugar */
            trie->ponto = cria_no_vazio();
        }
        /*caminha pela arvore recursivamente
        enviando o no apontado pelo apontador ponto 
        com o nivel incrementado de 1*/
        insere_rec(trie->ponto, reg, len, nivel + 1);
    }
    else if(reg->morse[nivel] == '-') { //se o simbolo atual for um traco
        if(trie->traco == NULL) {
            /*se o no apontado for null
            é criado um no vazio nesse lugar */
            trie->traco = cria_no_vazio();
        }
        /*caminha pela arvore recursivamente
        enviando o no apontado pelo apontador traco
        com o nivel incrementado de 1 */
        insere_rec(trie->traco, reg, len, nivel + 1);
    }
    
}

void insere(No *trie, Registro *reg) { //insere o registro na Trie
    size_t len;
    //pega o tamanho do morse para controlar o nivel
    len = strlen(reg->morse);
    /*envia a trie para funcao que irá caminhar de forma recursiva
    enviando o nivel inicial como 0*/
    insere_rec(trie, reg, len, 0);
}

char procura_rec(No *trie, char *morse, long int len, int nivel) {
    if(nivel == len) { //quando estiver na posicao correta (tamanho do morse)
        return trie->regis.letra; //retorna a letra do no
    }
    if(morse[nivel] == '.') { //se o simbolo atual for um ponto
        if(trie->ponto == NULL) {
            /*caso apontar para um valor null, 
            retorna um char vazio ' ' */
            return ' ';
        }
        /*caminha recursivamente enviando o no apontado
        pelo apontador ponto e com nivel incrementado de 1 */
        procura_rec(trie->ponto, morse, len, nivel + 1);
    }
    else if(morse[nivel] == '-') { //se o simbolo atual for um traco
        if(trie->traco == NULL) {
            /*caso apontar para um valor null, 
            retorna um char vazio ' ' */
            return ' ';
        }
        /*caminha recursivamente enviando o no apontado
        pelo apontador traco e com nivel incrementado de 1 */
        procura_rec(trie->traco, morse, len, nivel + 1);
    }
}

char procura(No *trie, char *morse) {
    size_t len;
    //pega o tamanho do morse enviado para pesquisa
    len = strlen(morse);
    /*envia a trie para funcao que ira pesquisar caminhando
    de forma recursiva, enviando o nivel inicial como 0 */
    return procura_rec(trie, morse, len, 0);
}

void imprime_preordem(No *trie) {
    if(trie != NULL) {
        if(trie->regis.letra != ' '){
            //caso o no nao for vazio, imprime as informacoes
            printf("%c ", trie->regis.letra);
            printf("%s\n", trie->regis.morse);
        }
        imprime_preordem(trie->ponto);
        imprime_preordem(trie->traco);
    }
}
