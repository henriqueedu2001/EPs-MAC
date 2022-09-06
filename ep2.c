#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.c"

#define MAX_LENGHT_STRING 200

void ler_dados();

void aloca_matriz(int ***matriz, int linhas, int colunas);

typedef struct instancia {int linhas; int colunas; int **matriz} instancia;

int main(){
    instancia *entradas;
    entradas = malloc(4*sizeof(instancia));
    ler_dados(entradas);
    return 0;
}

/* lê cada uma das instâncias e as registra no dicionário (entradas) */
void ler_dados(instancia *entradas){
    int i, j, k;
    int qtd_instancias;
    int qtd_palavras;
    int linhas, colunas; /* dimensões da matriz */
    int **matriz; /* posições proibidas */
    char **palavras;

    /* faz leitura de cada uma das n instâncias */
    printf("Digite a quantidade de instancias:\n");
    scanf("%d", &qtd_instancias);

    for(i = 0; i < qtd_instancias; i++){
        printf("Instancia %d:\n", i);
        scanf("%d%d", &linhas, &colunas);
        aloca_matriz(&matriz, linhas, colunas);

        /* lê a matriz base */
        for(j = 0; j < linhas; j++)
            for(k = 0; k < colunas; k++)
                scanf("%d", &matriz[j][k]);

        /* leitura do conjunto de palavras */
        printf("Quantidade de palavras:\n");
        scanf("%d", &qtd_palavras);
        palavras = malloc(qtd_palavras*sizeof(char*));

        /* registro de cada palavra */
        for(j = 0; j < qtd_palavras; j++){
            palavras[j] = malloc(MAX_LENGHT_STRING*sizeof(char));
            scanf("%s", palavras[j]);
        }
    }
}

/* aloca a matriz dinamicamente, com dimensões determinadas pelos parâmetros */
void aloca_matriz(int ***matriz, int linhas, int colunas){
    int i = 0;
    matriz[0] = malloc(linhas*sizeof(int*));
    for(i = 0; i < linhas; i++)
        matriz[0][i] = malloc(colunas*sizeof(int));
}