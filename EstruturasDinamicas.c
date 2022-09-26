#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Este arquivo apresenta uma série de estruturas dinâmicas que permitem 
operações mais alto nível de modo simplificado.
Das estruturas, temos:
    1 - Vetores de inteiros
    2 - Strings
    3 - Matrizes de Inteiros
    4 - Matrizes de Caracteres
    5 - Pilha de Inteiros
    6 - Vetor de strings
Para cada uma delas, temos métodos especiais:
    1 - Alocação Dinâmica (todas)
    2 - Leitura de Entradas (matrizes e vetores)
    3 - Exibição de Conteúdo (todas)
    4 - Operações empilhar e desempilhar (pilhas)
    5 - Adição de elementos (vetores)
    6 - Escrita de vetor em matriz
*/

/* vetor de elementos inteiros */
typedef struct Vetor_int {
    int *lista; 
    int tamanho; } 
    vetor_int;

/* vetor de caracteres (string) */
typedef struct String {
    char *conteudo; 
    int tamanho; } 
    string;

/* matriz de inteiros */
typedef struct Matriz_int {
    int **lista; 
    int linhas; 
    int colunas; } matriz_int;

/* matriz de caracteres */
typedef struct Matriz_char {
    char **lista; 
    int linhas; 
    int colunas; } matriz_char;

/* pilha de inteiros */
typedef struct Pilha_int {
    int *lista; 
    int tamanho; 
    int topo; } pilha_int;

/* vetor de strings */
typedef struct Vetor_string {
    char **lista; 
    int tamanho; } vetor_string;

#define MAX_STR_SIZE 200

/* funções de alocação dinâmica*/

void alocar_vetor_int(vetor_int *vetor, int tamanho);
void alocar_matriz_int(matriz_int *matriz, int linhas, int colunas);
void alocar_matriz_char(matriz_char *matriz, int linhas, int colunas);
void alocar_pilha_int(pilha_int *pilha);
void alocar_string(string *str);
void alocar_vetor_string(vetor_string *vetor, int tamanho);

/* funções de exibição das estruturas */

void printar_vetor_int(vetor_int vetor);
void printar_string(string str);
void printar_matriz_int(matriz_int matriz);
void printar_matriz_char(matriz_char matriz);
void printar_pilha_int(pilha_int pilha);
void printar_vetor_string(vetor_string vetor);

/* funções de leitura para registro nas estruturas */

void scanf_vetor_int(vetor_int *vetor);
void scanf_string(string *str);
void scanf_matriz_int(matriz_int *matriz);
void scanf_matriz_char(matriz_char *matriz);
void scanf_vetor_string(vetor_string *vetor);

/* métodos específicos de cada estrutura */

void adicionar_vetor_int(vetor_int *vetor, int item);
int pilha_vazia(pilha_int p);
void empilhar(pilha_int *p, int item);
void desempilhar(pilha_int *p);

/* BLOCO DAS FUNÇÕES DE ALOCAÇÃO DINÂMICA */

/* aloca um vetor do tipo inteiro de tamanho definido pelo parâmetro*/
void alocar_vetor_int(vetor_int *vetor, int tamanho){
    vetor->tamanho = tamanho;
    vetor->lista = malloc(tamanho*sizeof(int));
}

/* aloca uma matriz de inteiros com tamanho determinado pelos parâmetros*/
void alocar_matriz_int(matriz_int *matriz, int linhas, int colunas){
    int i;
    matriz->lista = malloc(linhas*sizeof(int));
    for(i = 0; i < linhas; i++)
        matriz->lista[i] = malloc(colunas*sizeof(int));
    matriz->linhas = linhas;
    matriz->colunas = colunas;
}

/* aloca uma matriz de caracteres com tamanho determinado pelos parâmetros */
void alocar_matriz_char(matriz_char *matriz, int linhas, int colunas){
    int i;
    matriz->lista = malloc(linhas*sizeof(char));
    for(i = 0; i < linhas; i++)
        matriz->lista[i] = malloc(colunas*sizeof(char));
    matriz->linhas = linhas;
    matriz->colunas = colunas;
}

/* aloca uma pilha vazia */
void alocar_pilha_int(pilha_int *pilha){
    pilha->tamanho = 0;
    pilha->topo = -1;
}

/* aloca uma string de tamanho definido */
void alocar_string(string *str){
    str->conteudo = malloc(MAX_STR_SIZE*sizeof(char));
    str->tamanho = MAX_STR_SIZE;
}

/* aloca um vetor de strings */
void alocar_vetor_string(vetor_string *vetor, int tamanho){
    vetor->lista = malloc(tamanho*sizeof(char*));
    vetor->tamanho = tamanho;
}

/* BLOCO DAS FUNÇÕES DE EXIBIÇÃO DAS ESTRUTURAS */

/* exibe todos os valores do vetor */
void printar_vetor_int(vetor_int vetor){
    int i = 0;
    for(i = 0; i < vetor.tamanho; i++)
        printf("%d ", vetor.lista[i]);
    printf("\n");
}

/* imprime a string */
void printar_string(string str){
    printf("%s\n", str.conteudo);
}

/* exibe todos os valores da matriz de inteiros */
void printar_matriz_int(matriz_int matriz){
    int i, j;
    for(i = 0; i < matriz.linhas; i++){
        for(j = 0; j < matriz.colunas; j++){
            printf("%d ", matriz.lista[i][j]);
        }
        printf("\n");
    }
}

/* exibe todos os valores da matriz de caracteres*/
void printar_matriz_char(matriz_char matriz){
    int i, j;
    for(i = 0; i < matriz.linhas; i++){
        for(j = 0; j < matriz.colunas; j++){
            printf("%c ", matriz.lista[i][j]);
        }
        printf("\n");
    }
}
/* exibe todas os valores da pilha */
void printar_pilha_int(pilha_int pilha){
    int i;
    if(pilha_vazia(pilha) == 1)
        printf("pilha vazia\n");
    else {
        for(i = 0; i < pilha.tamanho; i++)
            printf("%d ", pilha.lista[i]);
        printf("\n");
    }
}

/* exibe todas as strings do vetor */
void printar_vetor_string(vetor_string vetor){
    int i = 0;
    for(i = 0; i < vetor.tamanho; i++)
        printf("%s\n", vetor.lista[i]);
}

/* BLOCO DAS FUNÇÕES DE LEITURA PARA REGISTRO NAS ESTRUTURAS */

/* faz a leitura das entradas e as registra no vetor*/
void scanf_vetor_int(vetor_int *vetor){
    int i = 0;
    for(i = 0; i < (*vetor).tamanho; i++)
        scanf(" %d", &(*vetor).lista[i]);
}

/* faz leitura da string e a registra na estrutura */
void scanf_string(string *str){
    char temp[] = "";
    scanf(" %s", temp);
    str->conteudo = temp;
    str->tamanho = strlen(temp);
}

/* faz leitura da string */
void scanf_matriz_int(matriz_int *matriz){
    int i, j;
    for(i = 0; i < matriz->linhas; i++)
        for(j = 0; j < matriz->colunas; j++)
            scanf(" %d", &matriz->lista[i][j]);
}

/* faz leitura de uma matriz de caracteres, com dimensões já definidas */
void scanf_matriz_char(matriz_char *matriz){
    int i, j;
    for(i = 0; i < matriz->linhas; i++)
        for(j = 0; j < matriz->colunas; j++)
            scanf(" %c", &matriz->lista[i][j]);
}

/* faz a leitura das entradas e as registra no vetor */
void scanf_vetor_string(vetor_string *vetor){
    int i = 0;
    char **aux;
    aux = malloc(vetor->tamanho*sizeof(char*));

    for(i = 0; i < vetor->tamanho; i++){
        aux[i] = malloc(MAX_STR_SIZE*sizeof(char));
        scanf(" %s", aux[i]);
        vetor->lista[i] = aux[i];
    }
}

/* BLOCO DOS MÉTODOS ESPECÍFICOS DE CADA ESTRUTURA */

/* aloca mais uma posição no vetor de inteiros e insere o novo item nela */
void adicionar_vetor_int(vetor_int *vetor, int item){
    vetor->tamanho += 1;
    vetor->lista = realloc(vetor->lista, vetor->tamanho*sizeof(int));
    vetor->lista[vetor->tamanho - 1] = item;
}

/* retorna 1 caso a pilha esteja vazia e 0 caso contrário */
int pilha_vazia(pilha_int p){
    if(p.tamanho != 0)
        return 0;
    return 1;
}

/* aloca mais uma posição na pilha (no topo) e insere o item nela */
void empilhar(pilha_int *pilha, int item){
    /*
    pilha->lista = realloc(pilha->lista, (pilha->tamanho + 1)*sizeof(int));
    pilha->tamanho += 1;
    pilha->topo += 1;
    printf("%d %d\n", pilha->tamanho, pilha->topo);
    printf("%d\n", pilha->lista[0]);
    pilha->lista[pilha->topo] = item;
    printf("%d\n", 5);
    */
    int novo_tamanho = 1 + pilha->tamanho;
    int *nova_lista = malloc(novo_tamanho*sizeof(int));
    int i;
    for(i = 0; i < novo_tamanho - 1; i++){
        nova_lista[i] = pilha->lista[i];
    }
    nova_lista[novo_tamanho - 1] = item;
    pilha->lista = nova_lista;
    pilha->tamanho += 1;
    pilha->topo += 1;

}

/* remove o item do topo da lista e libera o espaço da memória, caso não vazia */
void desempilhar(pilha_int *p){
    if(pilha_vazia(*p) != 1){
        free(&p->lista[p->topo]);
        p->topo -= 1;
        p->tamanho -= 1;
    }
}