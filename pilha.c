#include <stdlib.h> 
#include "pilha.h"

int pilhaVazia (pilha * p){
  return (p->topo == 0); 
}

item topoPilha (pilha * p){
  if (!pilhaVazia(p))
    return (p->v[p->topo - 1]);
}

item desempilha (pilha * p){
  if (!pilhaVazia(p)){
    p->topo = p->topo - 1;
    return (p->v[p->topo]);
  }
}

pilha * cria (){
  pilha * p = malloc (sizeof(pilha)); 
  p->v = malloc (5 * sizeof(item));
  p->max = 5;
  p->topo = 0;
  return p;
}

void empilha (pilha * p, item x){
  if (p->topo == p->max)
    resize(p);
  p->v[p->topo] = x;
  p->topo = p->topo + 1;
}

void resize(pilha * p){
  int i; 
  item * w = malloc (2 * p->max * sizeof(item));
  for (i = 0; i < p->max; i++) 
    w[i] = p->v[i];
  p->max = 2 * p->max;
  free (p->v); 
  p->v = w;
}

void destroi (pilha * p){
  free (p->v);
  free (p);
}
