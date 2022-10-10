/* 
Este arquivo contém uma série de estruturas de dados e operações de alto nível,
que tornam a construção do código mais simples e direta. Aqui, temos as seguin-
tes estruturas:
    1 - Pilhas
    2 - Matrizes de Inteiros
    3 - Matrizes de Caracteres
    4 - Strings
    5 - Vetores de Strings
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* tamanho inicial das pilhas */
#define tam_padrao_pilha 10
/* tamanho padrão da string */
#define tam_padrao_string 255

/* LISTA DE ESTRUTURAS E SUAS DEFINIÇÕES */

/* pilha com elementos inteiros */
typedef struct Pilha_Int {
    int *lista; 
    int qtd; 
    int topo; 
    int max_mem;
} pilha_int;

/* matriz de elementos inteiros */
typedef struct Matriz_int {
    int **lista; 
    int linhas; 
    int colunas; 
} matriz_int;

/* matriz de caracteres */
typedef struct Matriz_char {
    char **lista; 
    int linhas; 
    int colunas; 
} matriz_char;

/* string — lista de caracteres */
typedef struct String {
    char *conteudo; 
    int tamanho;
} string;

/* vetor de strings */
typedef struct Vetor_String {
    string *strings; 
    int tamanho;
} vetor_string;

/* MÉTODOS TIPO PILHA INT */

pilha_int nova_pilha_int();
void empilhar_pilha_int(pilha_int *p, int item);
void desempilhar_pilha_int(pilha_int *p);
void resize_pilha_int(pilha_int *p);
int vazia_pilha_int(pilha_int p);
void print_pilha_int(pilha_int p);

/* MÉTODOS TIPO MATRIZ INT */

matriz_int nova_matriz_int(int linhas, int colunas);
void scan_matriz_int(matriz_int *m);
void print_matriz_int(matriz_int m);
void preencher_matriz_int(matriz_int *m, int valor);

/* MÉTODOS TIPO MATRIZ CHAR */

matriz_char nova_matriz_char(int linhas, int colunas);
void scan_matriz_char(matriz_char *m);
void print_matriz_char(matriz_char m);
void preencher_matriz_char(matriz_char *m, char valor);

/* MÉTODOS TIPO STRING */

string nova_string();
void scan_string(string *s);
void print_string(string s);

/* MÉTODOS VETOR DE STRINGS */

vetor_string novo_vetor_string(int qtd);
void scan_vetor_string(vetor_string *s);
void print_vetor_string(vetor_string s);

/* PILHA INT
Estrutura:
    1 - *lista: contém os elementos
    2 - qtd: quantidade de elementos da pilha
    3 - topo: posição do último elemento
    4 - max: máxima quantidade de posições utilizáveis da pilha
Métodos:
    1 - nova_pilha_int: cria nova pilha vazia
    2 - empilhar_pilha_int: insere um elemento na última posição
    3 - desempilhar_pilha_int: remove o último elemento
    4 - resize_pilha_int: dobra a quantidade de memória — posições utilizáveis
    5 - vazia_pilha_int: diz se a pilha está vazia ou não
    6 - print_pilha_int: imprime todos os elementos da pilha
*/

/* cria uma nova pilha nova com n = tam_padrao posições vazias */
pilha_int nova_pilha_int(){
    pilha_int p;
    p.lista = malloc(tam_padrao_pilha*sizeof(int));
    p.qtd = 0;
    p.topo = -1;
    p.max_mem = tam_padrao_pilha;
    return p;
}

/* empilha o item na pilha p */
void empilhar_pilha_int(pilha_int *p, int item){
    if(p->qtd >= p->max_mem)
        resize_pilha_int(p);
    p->topo += 1;
    p->qtd += 1;
    p->lista[p->topo] = item;
}

/* desempilhar o último item da pilha p */
void desempilhar_pilha_int(pilha_int *p){
    if(!vazia_pilha_int(*p)){
        p->qtd -= 1;
        p->topo -= 1;
    }
}

/* dobra a quantidade de memória da pilha — posições utilizáveis */
void resize_pilha_int(pilha_int *p){
    int *nova_lista = malloc(2*p->max_mem*sizeof(int));
    int i;
    for(i = 0; i < p->max_mem; i++)
        nova_lista[i] = p->lista[i];
    p->max_mem *= 2;
}

/* retorna 1 se a pilha estiver vazia e 0 caso contrário */
int vazia_pilha_int(pilha_int p){
    if(p.qtd == 0)
        return 1;
    return 0;
}

/* imprime todos os elementos da pilha */
void print_pilha_int(pilha_int p){
    if(!vazia_pilha_int(p)){
        int i = 0;
        for(i = 0; i < p.qtd; i++)
            printf("%d ", p.lista[i]);
    } else
        printf("pilha vazia");
    printf("\n");
}

/* MATRIZ INT
Estrutura:
    1 - **lista: contém os elementos da matriz
    2 - linhas: quantidade de linhas da matriz
    3 - colunas: quantidade de colunas da matriz
Métodos:
    1 - nova_matriz_int: cria nova matriz_int vazia
    2 - scan_matriz_int: faz a leitura de elementos e os insere na matriz
    3 - print_matriz_int: exibe todos os elementos da matriz
    4 - preencher_matriz_int: preenche todas as posições da matriz com um certo item
*/

/* cria uma nova matriz de dimensões n = linhas e m = colunas */
matriz_int nova_matriz_int(int linhas, int colunas){
    matriz_int m;
    m.lista = malloc(linhas*sizeof(int));
    int i;
    for(i = 0; i < linhas; i++)
        m.lista[i] = malloc(colunas*sizeof(int));
    m.linhas = linhas;
    m.colunas = colunas;
    return m;
}

/* faz leitura das entradas e as insere na matriz m */
void scan_matriz_int(matriz_int *m){
    int i, j;
    for(i = 0; i < m->linhas; i++)
        for(j = 0; j < m->colunas; j++)
            scanf(" %d", &m->lista[i][j]);
}

/* exibe todos os valores da matriz inteira */
void print_matriz_int(matriz_int m){
    int i, j;
    for(i = 0; i < m.linhas; i++){
        for(j = 0; j < m.colunas; j++)
            printf("%d ", m.lista[i][j]);
        printf("\n");
    }
}

/* preenche todos os elementos da matriz com o valor indicado pelo argumento */
void preencher_matriz_int(matriz_int *m, int valor){
    int i, j;
    for(i = 0; i < m->linhas; i++)
        for(j = 0; j < m->colunas; j++)
            m->lista[i][j] = valor;
}

/* MATRIZ CHAR
Estrutura:
    1 - **lista: contém os elementos da matriz
    2 - linhas: quantidade de linhas da matriz
    3 - colunas: quantidade de colunas da matriz
Métodos:
    1 - nova_matriz_char: cria nova matriz_int vazia
    2 - scan_matriz_char: faz a leitura de elementos e os insere na matriz
    3 - print_matriz_char: exibe todos os elementos da matriz
    4 - preencher_matriz_char: preenche todas as posições da matriz com um certo item
    5 - escrever_matriz_char: escreve uma string na matriz
*/

/* cria uma nova matriz de dimensões n = linhas e m = colunas */
matriz_char nova_matriz_char(int linhas, int colunas){
    matriz_char m;
    m.lista = malloc(linhas*sizeof(char));
    int i;
    for(i = 0; i < linhas; i++)
        m.lista[i] = malloc(colunas*sizeof(char));
    m.linhas = linhas;
    m.colunas = colunas;
    return m;
}

/* faz leitura das entradas e as insere na matriz m */
void scan_matriz_char(matriz_char *m){
    int i, j;
    for(i = 0; i < m->linhas; i++)
        for(j = 0; j < m->colunas; j++)
            scanf(" %c", &m->lista[i][j]);
}

/* exibe todos os valores da matriz inteira */
void print_matriz_char(matriz_char m){
    int i, j;
    for(i = 0; i < m.linhas; i++){
        for(j = 0; j < m.colunas; j++)
            printf("%c ", m.lista[i][j]);
        printf("\n");
    }
}

/* preenche todos os elementos da matriz com o valor indicado pelo argumento */
void preencher_matriz_char(matriz_char *m, char valor){
    int i, j;
    for(i = 0; i < m->linhas; i++)
        for(j = 0; j < m->colunas; j++)
            m->lista[i][j] = valor;
}

/* indica uma posicao em relação a uma matriz e uma orientação */
typedef struct Posicao {
    int linha;
    int coluna;
    int orientacao;
} posicao;

/* escreve a string s */
void escrever_str_matriz(matriz_char *m, string s, posicao pos){
    int i = 0;
    for(i = 0; i < s.tamanho; i++){
        if(pos.orientacao == 0){
            m->lista[pos.linha][pos.coluna + i] = s.conteudo[i];
        } else if(pos.orientacao == 1){
            m->lista[pos.linha + i][pos.coluna] = s.conteudo[i];
        }
    }
}

/* verifica se é possível inserir a string  */
int insercao_valida(matriz_char m, string s, posicao pos){
    //printf("tentando inserir %s na posicao %d %d %d\n", s.conteudo, pos.linha, pos.coluna, pos.orientacao);
    //print_matriz_char(m);
    /* critério de borda */
    if(pos.linha + s.tamanho > m.linhas && pos.orientacao == 1)
        return 0;
    else if(pos.coluna + s.tamanho > m.colunas && pos.orientacao == 0)
        return 0;
    /* criterio de sobreposição */
    int i;
    for(i = 0; i < s.tamanho; i++){
        if(pos.orientacao == 0){
            if(m.lista[pos.linha][pos.coluna + i] != s.conteudo[i] && m.lista[pos.linha][pos.coluna + i] != ' ')
                return 0;
        } else if(pos.orientacao == 1){
            if(m.lista[pos.linha + i][pos.coluna] != s.conteudo[i] && m.lista[pos.linha + i][pos.coluna] != ' ')
                return 0;
        }
    }
    return 1;
}

/* STRING
Estrutura:
    1 - *palavra: contém os caracteres da string
    2 - tamanho: quantidade de caracteres
Métodos:
    1 - scan_string: faz leitura de uma string e a escreve
    2 - print_string: exibe a string
*/

/* cria uma string vazia */
string nova_string(){
    string s;
    s.conteudo = malloc(tam_padrao_string*sizeof(char));
    s.tamanho = 0;
    return s;
}

/* faz a leitura de uma string e a escreve na string s */
void scan_string(string *s){
    char *temp = malloc(tam_padrao_string*sizeof(char));
    scanf(" %s", temp);
    s->conteudo = temp;
    s->tamanho = strlen(temp);
}

/* print da string */
void print_string(string s){
    int i;
    for(i = 0; i < s.tamanho; i++)
        printf("%c", s.conteudo[i]);
}

/* VETOR DE STRINGS
Estrutura:
    1 - *strings: contém as strings
    2 - tamanho: quantidade de strings armazenadas
Métodos:
    1 - scan_vetor_string: faz leitura das strings e as escreve no vetor
    2 - print_vetor_string: exibe as strings do vetor
*/

/* cria um vetor de string vazio */
vetor_string novo_vetor_string(int qtd){
    vetor_string v;
    v.strings = malloc(qtd*sizeof(string));
    v.tamanho = qtd;
    return v;
}

/* faz leitura de n = qtd de strings e as registra no vetor de strings */
void scan_vetor_string(vetor_string *s){
    int i;
    for(i = 0; i < s->tamanho; i++)
        scan_string(&s->strings[i]);
}

/* imprime todas as strings do vetor */
void print_vetor_string(vetor_string s){
    int i;
    for(i = 0; i < s.tamanho; i++){
        print_string(s.strings[i]);
        printf("\n");
    }
}