#include "arendellelib.h"

int verifica_vetor(int *vetor, int **todos_vetores, char *tipo_vetor, int numero_itens, int exibe_vetor, int k) {
    int i, j;
    /*os 3 if's a seguir testam qual o tipo do vetor desejado e dentro do for é verificado se
    o parametro -p foi utilizado, caso for verdadeiro, é colocado na matriz uma copia do 
    valor do vetor definido anteriormente*/
    if(strcmp(tipo_vetor, "OrdC") == 0) {
        for(i = 0; i < numero_itens; i++) {
            vetor[i] = i;
            if(exibe_vetor == 1) {
                todos_vetores[k][i] = vetor[i];
            }
        }
    }
    else if(strcmp(tipo_vetor, "OrdD") == 0) {
        j = 0;
        for(i = numero_itens - 1; i >= 0; i--) {
            vetor[j] = i;
            if(exibe_vetor == 1) {
                todos_vetores[k][j] = vetor[j];
            }
            j++;
        }
    }
    else if(strcmp(tipo_vetor, "Ale") == 0) {
        for(i = 0; i < numero_itens; i++) {
            vetor[i] = rand() % numero_itens;
            if(exibe_vetor == 1) {
                todos_vetores[k][i] = vetor[i];
            }
        }
    }
    else {
        printf("Tipo de vetor invalido.\n");
        return 0;
    }
    return 1;
}

int verifica_quick(char *variacao_quick, int* vetor, int numero_itens, struct timespec *start, struct timespec *end,
                    long int *n_comp, long int *n_mov) {
    /*os 7 if's a seguir testam qual variação de quicksort deve ser executada
    e entre cada função é pego o tempo de inicio e logo após acabar a execução
    é pego o tempo final*/
    if(strcmp(variacao_quick, "QC") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickClas(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QM3") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickM3(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QPE") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickPE(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QI1") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickI1(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QI5") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickI5(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QI10") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickI10(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else if(strcmp(variacao_quick, "QNR") == 0) {
        clock_gettime(CLOCK_REALTIME, start);
        QuickNR(vetor, numero_itens, n_comp, n_mov);
        clock_gettime(CLOCK_REALTIME, end);
    }
    else {
        printf("Variacao de Quicksort invalida.\n");
        return 0;
    }
    return 1;
}

void imprime_vetores(int **todos_vetores, int numero_itens) {
    int i, j;
    for(i = 0; i < num_teste; i++) {
        for(j = 0; j < numero_itens; j++) {
            printf("%d ", todos_vetores[i][j]);
        }   
        printf("\n");
    }
}

void teste_argumentos(char *variacao_quick, char *tipo_vetor, int numero_itens, int exibe_vetor) {
    struct timespec start, end;
    long int n_comp, n_mov, aux;
    int tempos_vetor[num_teste], med_tempo, i, j, k;
    srand(time(NULL));
    int *vetor = malloc(numero_itens * sizeof(int)); //alocando memoria para o veto 
    int **todos_vetores = malloc(num_teste * sizeof(int*)); //alocando memoria para matriz (armazena os vetores caso utilizar -p)
    for(i = 0; i < num_teste; i++) {
        todos_vetores[i] = malloc(numero_itens * sizeof(int));
    }
    n_comp = 0;
    n_mov = 0;
    for(k = 0; k < num_teste; k++) {  //laço para executar a quantidade de testes definida no #define num_teste(21) 
        /*verificar se o tipo de vetor é valido e entao o cria,
        se retornar 0, o argumento foi invalido*/
        if(verifica_vetor(vetor, todos_vetores, tipo_vetor, numero_itens, exibe_vetor, k) == 0) {
            return;
        }
        /*verificar se a variacao do quicksort é valida e entao ordena o vetor criado anteriormente,
        se retornar 0, o argumento foi invalido*/
        if(verifica_quick(variacao_quick, vetor, numero_itens, &start, &end, &n_comp, &n_mov) == 0) {
            return;
        }
        //o vetor tempos_vetor guarda todos os tempos dos num_teste(21) testes
        tempos_vetor[k] = 1.e+6 * (double)(end.tv_sec - start.tv_sec) + 1.e-3 * (double)(end.tv_nsec - start.tv_nsec);
    }
    n_comp /=  num_teste; //media do numero de comparacoes
    n_mov /= num_teste; //media do numero de movimentacoes
    QuickM3(tempos_vetor, num_teste, &aux, &aux); //ordenando o vetor de tempo
    med_tempo = tempos_vetor[num_teste/2]; //pegando a mediana do vetor de tempo

    //imprimindo a saida principal
    printf("%s %s %d %ld %ld %d\n", variacao_quick, tipo_vetor, numero_itens, n_comp, n_mov, med_tempo);
    /*imprime todos vetores utilizados, que foi armazenado na matriz todos_vetores 
    caso o parametro -p foi utilizado*/
    if(exibe_vetor == 1) {
        imprime_vetores(todos_vetores, numero_itens);
    }
    //desalocando a memoria do vetor e da matriz
    free(vetor);
    for(i = 0; i < num_teste; i++) {
        free(todos_vetores[i]);
    }
    free(todos_vetores);
}
