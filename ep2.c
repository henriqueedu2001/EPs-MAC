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

/* escreve a string str na matriz de caracteres na posição pos = (x,y,orientação) */
void escrever_string_matriz(string str, matriz_char *matriz, posicao pos){
    int i;
    char novo_elemento;
    for(i = 0; i < str.tamanho; i++){
        novo_elemento = str.conteudo[i];
        if(pos.orientacao == 'v')
            matriz->lista[pos.coluna + i][pos.linha] = novo_elemento;
        else
            matriz->lista[pos.coluna][pos.linha + i] = novo_elemento;
    }
}

/* configura a posição pos com os parâmetros: pos <- (orientação, linha, coluna) */
void set_posicao(posicao *pos, char orientacao, int linha, int coluna){
    pos->orientacao = orientacao;
    pos->linha = linha;
    pos->coluna = coluna;
}

int main(){
    matriz_char m;
    string str;
    posicao pos;
    alocar_matriz_char(&m, 4, 4);
    scanf_matriz_char(&m);
    scanf_string(&str);
    set_posicao(&pos, 'v', 1, 1);
    printf("%d %d %c\n", pos.linha, pos.coluna, pos.orientacao);
    escrever_string_matriz(str, &m, pos);
    printar_matriz_char(m);
    return 0;
}