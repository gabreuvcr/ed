#include "arvore.h"

int main(int argc, char *argv[]) {
    int i;
    char letra, aux;
    FILE *arq_morse;
    Registro registro;
    size_t len;
    arq_morse = fopen("morse.txt", "r");
    No *trie = cria_no_vazio(); //cria a raiz da Trie
    while(1) {
        registro.letra = (char)fgetc(arq_morse); //pega a letra
        (char)fgetc(arq_morse); //pegando o espaço entre a letra e o codigo
        fgets(registro.morse, 7, arq_morse); //pega o codigo morse
        if(feof(arq_morse)){
            break;
        } 
        len = strlen(registro.morse);
        if(registro.morse[len - 1] == '\n') registro.morse[len - 1] = 0; //retirando o \n pego do fgets
        insere(trie, &registro); //insere o novo registro na trie
    }
    strcpy(registro.morse, " "); //limpando a variavel
    while(!feof(stdin)) { 
        scanf("%s", registro.morse); //pega o caracter morse ou '/'
        aux = (char)fgetc(stdin); //auxiliar para detectar as quebras de linhas '\n'
        if(strcmp(registro.morse, "/") == 0) { //se for '/' é dado um espaço
            printf(" ");
            continue; //acaba a iteração atual e vai para a proxima
        }
        letra = procura(trie, registro.morse); //pesquisa na Trie o morse, retornando a letra correspondente
        printf("%c", letra); //imprime a letra
        strcpy(registro.morse, " "); //limpanado a variavel para proxima iteracao
         if(aux == '\n') { //caso for quebra de linha, é dado "\n"
            printf("\n");
        }
    }
    printf("\n");
    if(argc > 1 && strcmp(argv[1], "-a") == 0){ //se o parametro opcinal "-a" foi utilizado
        printf("\n");
        imprime_preordem(trie); //imprime a pre ordem da arvore
    }
    
    return 0;
}
