typedef char item;

typedef struct{
  item * v;
  int topo; 
  int max; 
} pilha; 

void empilha (pilha * p, item x); 
item desempilha (pilha * p); 
int pilhaVazia (pilha * p); 
item topoPilha (pilha *p); 
pilha * cria(); 
void destroi (pilha * p);
void resize (pilha * p); 
