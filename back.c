#include <stdio.h>
#include <stdlib.h>
#include "EstruturasDinamicas.c"

#define DB printf("debug\n")

int ok(vetor_int v, pilha_int p);
void print_seq(vetor_int v, pilha_int p);
void backtracking();

int main(){
    backtracking();
    return 0;
}

void print_seq(vetor_int v, pilha_int p){
    int i;
    for(i = 0; i < p.tamanho; i++){
        printf("%d ", v.lista[p.lista[i]]);
    }
    printf("\n");
}

int ok(vetor_int v, pilha_int p){
    int i, j;
    for(i = 0; i < p.tamanho; i++){
        for(j = i + 1; j < p.tamanho; j++){
            if(v.lista[p.lista[i]] == v.lista[p.lista[j]])
                return 0;
        }
    }
    return 1;
}


void backtracking(){

    pilha_int p;
    alocar_pilha_int(&p);
    
    vetor_int v;
    alocar_vetor_int(&v, 4);
    v.lista[0] = 1;
    v.lista[1] = 1;
    v.lista[2] = 1;
    v.lista[3] = 1;
    int sol_count = 0;
    int tam_seq = 3;
    /*
    # último elemento extrapola => remover e incrementar o anterior
    # caso contrário:
      # pilha não ok => incrementar último
      # caso contrário (pilha ok)
        # pilha incompleta => add(0)
        # pilha completa => print e incrementar último
    */
    empilhar(&p, 0);
    while (1){
        /* último elemento extrapola => remover e incrementar o anterior */
        if(p.lista[p.topo] > v.tamanho - 1){
            desempilhar(&p);
            if(pilha_vazia(p) == 1)
                break;
            else
                p.lista[p.topo] += 1;
        } else {
            if(ok(v, p) == 0){
                /* pilha não ok => incrementar último */
                p.lista[p.topo] += 1;
            } else
                if(p.tamanho < tam_seq)
                    /* pilha incompleta */
                    empilhar(&p, 0);
                else{
                    /* solução encontrada */
                    sol_count++;
                    printf("sol: ");
                    print_seq(v, p);
                    p.lista[p.topo] += 1;
                }
                    
        }
    }
    if(sol_count == 0){
        printf("no solutions\n");
    } 
    printf("fim!\n");
}


