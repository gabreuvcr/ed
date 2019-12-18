#include "arendellelib.h"

int main(int argc, char *argv[]) {
    char variacao_quick[5], tipo_vetor[5];
    int numero_itens, exibe_vetor;
    exibe_vetor = 0;
    if(argc > 3 && argc < 6) { //verifica se há 4 ou 5 argumentos
        strcpy(variacao_quick, argv[1]);
        strcpy(tipo_vetor, argv[2]);
        numero_itens = atoi(argv[3]);
        if(argc == 5) {
            if(strcmp("-p", argv[4]) == 0) {
                exibe_vetor = 1;
            }
        }
        teste_argumentos(variacao_quick, tipo_vetor, numero_itens, exibe_vetor);
    }
    else {
        printf("Quantidade de entrada invalida.\n");
    }
    
    return 0;
}
