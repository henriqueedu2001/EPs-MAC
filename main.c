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

int posicoes_validas(pilha_int p, instancia inst);
posicao pos(int indice, int linhas, int colunas);
int eh_solucao(pilha_int p, instancia inst);
void montar_solucao(pilha_int p, instancia inst);

pilha_int backtrack(instancia inst);

int criterio(pilha_int p){
    int i, j;
    for(i = 0; i < p.qtd; i++){
        for(j = i + 1; j < p.qtd; j++){
            if(p.lista[i] <= p.lista[j])
                return 0;
        }
    }
    return 1;
}

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

int solucao_nula(pilha_int p){
    int i;
    for(i = 0; i < p.qtd; i++){
        if(p.lista[i] != 0)
            return 0;
    }
    return 1;
}

pilha_int backtrack(instancia inst){
    pilha_int p = nova_pilha_int();
    int tam_seq = inst.palavras.tamanho;
    int limite = 2*inst.caca_palavras.linhas*inst.caca_palavras.colunas;
    empilhar_pilha_int(&p, 0);
    while(1){
        /* começar verificando limite de tamanho do último item */
        print_pilha_int(p);
        if(p.lista[p.topo] > limite){
            /* último elemento extrapola => remover e incrementar o anterior, se p != vazia */
            desempilhar_pilha_int(&p);
            if(vazia_pilha_int(p) == 1)
                break;
            else
                p.lista[p.topo] += 1;
        } else {
            if(posicoes_validas(p, inst) == 0){
                /* pilha não ok => incrementar último */
                p.lista[p.topo] += 1;
            } else {
                if(p.qtd < tam_seq)
                    /* pilha incompleta */
                    empilhar_pilha_int(&p, 0);
                else{
                    /* solução encontrada */
                    if(solucao_nula(p) == 0){
                        return p;
                    }
                    p.lista[p.topo] += 1;
                }
            }
        }
    }
    return p;
}

/* */
void resolver_instancia(instancia *inst){

    printf("Resolvendo Instancia\n");

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
    print_matriz_char(inst->solucao);
    pilha_int p = nova_pilha_int();
    posicoes_validas(p, *inst);
    printf("FAZENDO BACKTRACKING\n");
    p = backtrack(*inst);
    printf("BACKTRACKING CONCLUIDO\n");
    montar_solucao(p, *inst);

    print_matriz_char(inst->solucao);
}

/* */
void mostrar_solucoes(conjunto_instancias conj){
    int i;
    for(i = 0; i < conj.quantidade; i++){
        printf("Instancia %d\n\n", i);
        if(conj.casos->ha_solucao == 0)
            printf("nao ha solucao\n\n");
        else
            print_matriz_char(conj.casos[i].solucao);
    }
}

/* */
int posicoes_validas(pilha_int p, instancia inst){
    if(vazia_pilha_int(p) == 1){
        return 1;
    } else if(p.qtd == inst.palavras.tamanho){
        if(eh_solucao(p, inst) == 1){
            return 1;
        } else {
            return 0;
        }
    }
    int veredito = 1;
    int i;
    int linhas = inst.solucao.linhas;
    int colunas = inst.solucao.colunas;
    matriz_char rascunho = inst.solucao;

    /* para cada posicao, verificar se a inserção é possível */
    for(i = 0; i < p.qtd && p.lista[i] != 0; i++){
        posicao pos_strings = pos(p.lista[i], linhas, colunas);
        print_matriz_char(rascunho);
        if(insercao_valida(rascunho, inst.palavras.strings[i], pos_strings) == 1)
            escrever_str_matriz(&rascunho, inst.palavras.strings[i], pos_strings);
        else
            return 0;
    }
    return veredito;
}

/* */
void montar_solucao(pilha_int p, instancia inst){
    print_pilha_int(p);
    int i;
    int linhas = inst.solucao.linhas;
    int colunas = inst.solucao.colunas;

    /* para cada posicao, verificar se a inserção é possível */
    for(i = 0; i < p.qtd && p.lista[i] != 0; i++){
        posicao pos_strings = pos(p.lista[i], linhas, colunas);
        escrever_str_matriz(&inst.solucao, inst.palavras.strings[i], pos_strings);
    }
}

int eh_solucao(pilha_int p, instancia inst){

    int i, j;
    int linhas = inst.solucao.linhas;
    int colunas = inst.solucao.colunas;
    matriz_char rascunho = inst.solucao;

    /* para cada posicao, verificar se a inserção é possível */
    for(i = 0; i < p.qtd && p.lista[i] != 0; i++){
        posicao pos_strings = pos(p.lista[i], linhas, colunas);
        escrever_str_matriz(&rascunho, inst.palavras.strings[i], pos_strings);
    }
    //printf("verificando se a matriz abaixo eh solucao\n");
    //print_matriz_char(rascunho);
    for(i = 0; i < rascunho.linhas; i++){
        for(j = 0; j < rascunho.colunas; j++){
            if(rascunho.lista[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

/* retorna a posição pos = (linha,coluna,o) correspondente ao índice na matriz n por m */
posicao pos(int indice, int linhas, int colunas){
    posicao p;
    int x, y, o;
    if(indice <= linhas*colunas){
        x = ((indice - 1) % linhas);
        y = (indice - 1)/colunas;
        o = 0;
    } else {
        x = ((indice - 1) % linhas);
        y = (indice - (linhas*colunas) - 1)/colunas;
        o = 1;
    }
    p.linha = y;
    p.coluna = x;
    p.orientacao = o;
    return p;
}