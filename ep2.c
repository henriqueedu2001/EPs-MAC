#include <stdio.h>
#include <stdlib.h>
#include "EstruturasDinamicas.c"

/* armazena uma única instância do problemas */
typedef struct Instancia {
    matriz_int caca_palavras;
    vetor_string palavras; } instancia;


/* armazena todas as instâncias do problema */
typedef struct Conjunto_Instancias {
    int quantidade;
    instancia* casos; } conjunto_instancias;

/* Posição espacial do vetor em relação a uma matriz
orientacao = 'v' para vertical e 'h' para horizontal
linha e coluna indicam coordenadas
 */
typedef struct Posicao {
    char orientacao; 
    int linha;
    int coluna; } posicao;

/* OPERAÇÕES DE ALTO NÍVEL */

void ler_dados();
void ResolverInstancia();

/* OPERAÇÕES DE BAIXO NÍVEL */
void escrever_string_matriz(string str, matriz_char *matriz, posicao pos);
void set_posicao(posicao *pos, char orientacao, int linha, int coluna);
int insercao_valida(string str, matriz_char matriz, posicao pos);
int indice(int linhas, int colunas, posicao pos);
posicao pos(int indice, int linhas, int colunas);

int main(){
    int n, m, i;
    scanf(" %d %d %d", &n, &m, &i);
    posicao p;
    p = pos(i, n, m);
    printf("%d %d %c", p.linha, p.coluna, p.orientacao);
    // ler_dados();
    return 0;
}

/* faz a leitura de todas as instâncias */
void ler_dados(){
    int indice_instancia = 0;
    matriz_int matriz;
    int linhas, colunas;
    vetor_string palavras;
    int qtd_palavras;
    conjunto_instancias conjunto;
    instancia inst;
    while(1){
        scanf(" %d %d", &linhas, &colunas);
        if(linhas == 0 && colunas == 0)
            break;
        else {
            /* leitura da matriz */
            alocar_matriz_int(&matriz, linhas, colunas);
            scanf_matriz_int(&matriz);
            /* leitura das palavras */
            scanf(" %d", &qtd_palavras);
            alocar_vetor_string(&palavras, qtd_palavras);
            scanf_vetor_string(&palavras);
        }
        inst.caca_palavras = matriz;
        inst.palavras = palavras;
        ResolverInstancia(inst);
        /*
        inst.caca_palavras = matriz;
        inst.palavras = palavras;
        indice_instancia++;
        printar_matriz_int(inst.caca_palavras);
        printar_vetor_string(inst.palavras);*/
        /* falta registrar isso no vetor de instâncias */
    }
}


void ResolverInstancia(instancia inst){
    printf("Resolvendo Instância:\n");
    printar_matriz_int(inst.caca_palavras);
    printar_vetor_string(inst.palavras);
    posicao pos;
    pos.linha = 1;
    pos.coluna = 2;
    pos.orientacao = 'v';
    printf("%d\n", indice(inst.caca_palavras.linhas, inst.caca_palavras.colunas, pos));
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
    return veredito;
}

/* configura a posição pos com os parâmetros: pos <- (orientação, linha, coluna) */
void set_posicao(posicao *pos, char orientacao, int linha, int coluna){
    pos->orientacao = orientacao;
    pos->linha = linha;
    pos->coluna = coluna;
}

/* retorna um índice que corresponde à pos = (x,y,o) para uma matriz n por m */
int indice(int linhas, int colunas, posicao pos){
    int x = pos.linha;
    int y = pos.coluna;
    int o;
    if(pos.orientacao == 'v')
        o = 1;
    else
        o = 0;
    return 1 + x + y*linhas + linhas*colunas*o;
}

/* retorna a posição pos = (x,y,o) correspondente ao índice na matriz n por m */
posicao pos(int indice, int linhas, int colunas){
    posicao p;
    
    if(indice <= linhas*colunas){
        int x = ((indice - 1) % linhas);
        int y = indice/colunas;
        set_posicao(&p, 'h', x, y);
    } else {
        int x = ((indice - 1) % linhas);
        int y = (indice - linhas*colunas)/colunas;
        set_posicao(&p, 'v', x, y);
    }
    return p;
}