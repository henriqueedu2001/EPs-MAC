#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha {int *lista; int tamanho; int topo; } pilha;

void aloca_pilha(pilha *p);
int pilha_vazia(pilha p);
void empilha(pilha *p, int item);
void desempilha(pilha *p);
void print_pilha(pilha p);

/* aloca uma pilha vazia */
void aloca_pilha(pilha *p){
    p->lista = malloc(0*sizeof(int));
    p->tamanho = 0;
    p->topo = -1;
}

/* retorna 1 se a pilha é vazia e 0 caso contrário */
int pilha_vazia(pilha p){
    if(p.tamanho != 0)
        return 0;
    return 1;
}

/* empilha o elemento "item" na pilha "p" */
void empilha(pilha *p, int item){
    p->lista = realloc(p->lista, sizeof(int));
    p->tamanho += 1;
    p->topo += 1;
    p->lista[p->topo] = item;
}

/* remove o último elemento da pilha "p" */
void desempilha(pilha *p){
    free(&p->lista[p->topo]);
    p->topo -= 1;
    p->tamanho -= 1;
}

/** imprime todos os elementos da pilha ou "pilha vazia", caso vazia **/
void print_pilha(pilha p){
    int i;
    if(pilha_vazia(p) == 1)
        printf("pilha vazia\n");
    else {
        for(i = 0; i < p.tamanho; i++)
            printf("%d ", p.lista[i]);
        printf("\n");
    }
}