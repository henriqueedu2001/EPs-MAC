#include <stdio.h>
#include "ED.c"

#define DB(A) printf("%d\n", A)

/* 
Para este EP, foram criados algumas estruturas úteis:
    1 - instancia: armazena o caça-palavras, lista de palavras, a matriz solução e se há ou não solução
    2 - conjunto_instancias: armazena uma série de instancias
    3 - posicao: indica a linha, a coluna e a orientação de uma palavra em relação à matriz
Em seguida, algumas funções de alto nível que simplificam as operações:
    1 - ler_conj_instancias: faz a leitura de todas as instâncias e as armazena em conjunto_instancias
    2 - mostrar_solucao: mostra a matriz solucao de uma única instancia
    3 - mostrar_solucoes: mostra todas as solucoes de cada uma das instancias
    4 - resolver_instancia: encontra solucoes, caso existam, e as registra em cada instancia
    5 - resolver_instancias: encontra todas as solucoes, caso existam, e as registra em suas respectivas instancias
*/

/* armazena uma única instância do problemas */
typedef struct Instancia {
    matriz_int caca_palavras;
    vetor_string palavras;
    matriz_char solucao;
    int ha_solucao;
} instancia;

/* armazena todas as instâncias do problema */
typedef struct Conjunto_Instancias {
    int quantidade;
    instancia* casos;
} conjunto_instancias;

/* FUNÇÕES DE ALTO NÍVEL */

void ler_instancias(conjunto_instancias *conj);
void resolver_instancias(conjunto_instancias *conj);
void resolver_instancia(instancia *inst);
void mostrar_solucoes(conjunto_instancias conj);


int main(){
    conjunto_instancias conj;
    conj.casos = malloc(10*sizeof(instancia));
    ler_instancias(&conj);
    resolver_instancias(&conj);
    mostrar_solucoes(conj);
    return 0;
}

/* OPERAÇÕES COM INSTÂNCIAS */

/* faz a leitura das instancias e as registra no conjunto de instancias*/
void ler_instancias(conjunto_instancias *conj){
    printf("Insira suas instancias:\n");
    int linhas, colunas;
    int i = 0;

    /* faz leitura das instancias até que linhas = 0 ou colunas = 0*/
    while(1){
        scanf(" %d %d", &linhas, &colunas);
        if(linhas == 0 || colunas == 0)
            break;
        
        /* leitura da matriz */
        instancia inst;
        inst.caca_palavras = nova_matriz_int(linhas, colunas);
        inst.solucao = nova_matriz_char(linhas, colunas);
        inst.ha_solucao = 1;
        scan_matriz_int(&inst.caca_palavras);

        /* leitura das palavras */
        int qtd_palavras;
        scanf(" %d", &qtd_palavras);
        inst.palavras = novo_vetor_string(qtd_palavras);
        scan_vetor_string(&inst.palavras);

        /* registro no conjunto de instancias */
        conj->casos[i] = inst;
        printf("%d %d\n", conj->casos[i].caca_palavras.linhas, conj->casos[i].caca_palavras.colunas);
        i++;
    }
    conj->quantidade = i;
}

/* */
void resolver_instancias(conjunto_instancias *conj){
    int i;
    for(i = 0; i < conj->quantidade; i++)
        resolver_instancia(&(conj->casos[i]));
}

/* */
void resolver_instancia(instancia *inst){

    printf("Resolvendo Instancia\n");
    print_matriz_int(inst->caca_palavras);
    print_vetor_string(inst->palavras);
    

    int linhas = inst->caca_palavras.linhas;
    int colunas = inst->caca_palavras.colunas;

    /* inicializa a matriz com '*' e ' ' */
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            if(inst->caca_palavras.lista[i][j] == -1)
                inst->solucao.lista[i][j] = '*';
            else if(inst->caca_palavras.lista[i][j] == 0)
                inst->solucao.lista[i][j] = ' ';
        }
    }
    
}

/* */
void mostrar_solucoes(conjunto_instancias conj){
    int i;
    for(i = 0; i < conj.quantidade; i++){
        printf("Instancia %d\n", i);
        if(conj.casos->ha_solucao == 0)
            printf("nao ha solucao\n\n");
        else
            print_matriz_char(conj.casos[i].solucao);
    }
}