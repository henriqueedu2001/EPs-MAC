#include <stdio.h>
#include <stdlib.h>
#include "EstruturasDinamicas.c"

/* Posição espacial do vetor em relação a uma matriz
orientacao = 'v' para vertical e 'h' para horizontal
linha e coluna indicam coordenadas
 */
typedef struct Posicao {
    char orientacao; 
    int linha;
    int coluna; } posicao;

/* OPERAÇÕES DE ALTO NÍVEL */

void LerDados();
void ResolverInstancia();

/* OPERAÇÕES DE BAIXO NÍVEL */
void escrever_string_matriz(string str, matriz_char *matriz, posicao pos);
void set_posicao(posicao *pos, char orientacao, int linha, int coluna);
int insercao_valida(string str, matriz_char matriz, posicao pos);

int main(){
    matriz_char m;
    string str;
    posicao pos;
    alocar_matriz_char(&m, 4, 4);
    scanf_matriz_char(&m);
    scanf_string(&str);
    set_posicao(&pos, 'h', 3, 2);
    if(insercao_valida(str, m, pos) == 1){
        escrever_string_matriz(str, &m, pos);
        printar_matriz_char(m);
    } else {
        printf("insercao invalida\n");
    }
    /* escrever_string_matriz(str, &m, pos);*/
    printar_matriz_char(m);
    return 0;
}

/* escreve a string str na matriz de caracteres na posição pos = (x,y,orientação) */
void escrever_string_matriz(string str, matriz_char *matriz, posicao pos){
    int i;
    char novo_elemento;
    for(i = 0; i < str.tamanho; i++){
        novo_elemento = str.conteudo[i];
        if(pos.orientacao == 'v')
            matriz->lista[pos.linha + i][pos.coluna] = novo_elemento;
        else
            matriz->lista[pos.linha][pos.coluna + i] = novo_elemento;
    }
}

/* verifica se a inserção da string na matriz é possível; retorna 1 se válida e 0 caso contrário */
int insercao_valida(string str, matriz_char matriz, posicao pos){
    int veredito = 1;
    /* verificação de tamanho */
    if(pos.orientacao == 'v'){
        if(pos.coluna > matriz.colunas - 1 || str.tamanho > matriz.linhas - pos.linha)
            return 0;
    } else if(pos.orientacao == 'h'){
        if(pos.linha > matriz.linhas - 1 || str.tamanho > matriz.colunas - pos.coluna)
            return 0;
    }
    /* verificação de compatibilidade de letras */
    int i;
    char novo_elemento;
    for(i = 0; i < str.tamanho; i++){
        novo_elemento = str.conteudo[i];
        if(pos.orientacao = 'v'){
            
        } else if(pos.orientacao = 'h'){

        }
        if(matriz.lista[pos.linha + i][pos.coluna] != novo_elemento){

        }
    }
    return veredito;
}

/* configura a posição pos com os parâmetros: pos <- (orientação, linha, coluna) */
void set_posicao(posicao *pos, char orientacao, int linha, int coluna){
    pos->orientacao = orientacao;
    pos->linha = linha;
    pos->coluna = coluna;
}