#include <stdio.h>
#include "ED.c"

#define DB(A) printf("%d\n", A)
int r = 0;

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

int posicoes_validas(pilha_int p, instancia inst);
posicao pos(int indice, int linhas, int colunas);
int eh_solucao(pilha_int p, instancia inst);
void montar_solucao(pilha_int p, instancia inst);

pilha_int backtrack(instancia inst);

int criterio(pilha_int p, instancia inst);

void inicializar(matriz_char *m, instancia inst);

void solve(){
    conjunto_instancias conj;
    conj.casos = malloc(10*sizeof(instancia));
    ler_instancias(&conj);
    resolver_instancias(&conj);
}

void teste(){
    instancia inst;
    scanf(" %d %d", &inst.caca_palavras.linhas, &inst.caca_palavras.colunas);
    inst.caca_palavras = nova_matriz_int(inst.caca_palavras.linhas, inst.caca_palavras.colunas);
    scan_matriz_int(&inst.caca_palavras);
    scanf(" %d", &inst.palavras.tamanho);
    inst.palavras = novo_vetor_string(inst.palavras.tamanho);
    scan_vetor_string(&inst.palavras);
    print_matriz_int(inst.caca_palavras);
    print_vetor_string(inst.palavras);

    int i, j, k, l;
    pilha_int p = nova_pilha_int();
    for(i = 0; i < inst.palavras.tamanho; i++){
        int x;
        scanf(" %d", &x);
        empilhar_pilha_int(&p, x);
    }
    for(i = 0; i < 32; i++){
        for(j = 0; j < 32; j++){
            for(k = 0; k < 32; k++){
                p.lista[0] = i;
                p.lista[1] = j;
                p.lista[2] = k;
                if(criterio(p, inst)){
                    print_pilha_int(p);
                }
            }
        }
    }
    printf("Finalizado com sucesso\n");
}

int main(){
    
    solve();
    
    

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
        i++;
    }
    conj->quantidade = i;
}

/* */
void resolver_instancias(conjunto_instancias *conj){
    int i;
    for(i = 0; i < conj->quantidade; i++){
        printf("Instancia %d\n", i + 1);
        resolver_instancia(&(conj->casos[i]));
        printf("\n");
    }
        
}

/* */
void resolver_instancia(instancia *inst){
    pilha_int p = backtrack(*inst);
}

pilha_int backtrack(instancia inst){
    pilha_int p = nova_pilha_int();
    int tam_seq = inst.palavras.tamanho;
    int limite = 2*inst.caca_palavras.linhas*inst.caca_palavras.colunas;
    empilhar_pilha_int(&p, 0);
    while(1){
        /* começar verificando limite de tamanho do último item */
        if(p.lista[p.topo] > limite){
            /* último elemento extrapola => remover e incrementar o anterior, se p != vazia */
            desempilhar_pilha_int(&p);
            if(vazia_pilha_int(p) == 1){
                printf("Sem solucao\n");
                break;
            } else
                p.lista[p.topo] += 1;
        } else {
            if(criterio(p, inst) == 0){
                /* pilha não ok => incrementar último */
                p.lista[p.topo] += 1;
            } else {
                if(p.qtd < tam_seq)
                    /* pilha incompleta */
                    empilhar_pilha_int(&p, 0);
                else{
                    /* solução encontrada */
                    return p;
                    p.lista[p.topo] += 1;
                }
            }
        }
    }
    return p;
}

int criterio(pilha_int p, instancia inst){
    int i, j;
    
    
    /* verificar se é possível escrever palavras no rascunho */
    int linhas = inst.caca_palavras.linhas;
    int colunas = inst.caca_palavras.colunas;
    matriz_char rascunho = nova_matriz_char(linhas, colunas);
    inicializar(&rascunho, inst);
    
    for(i = 0; i < p.qtd; i++){
        r++;
        
        if(p.lista[i] != 0){
            DB(r);
            string palavra = inst.palavras.strings[i];
            posicao pos_palavra = pos(p.lista[i], linhas, colunas);
            if(insercao_valida(rascunho, palavra, pos_palavra)){
                escrever_str_matriz(&rascunho, palavra, pos_palavra);
            } else{
                destruir_matriz_char(&rascunho);
                return 0;
            }
        }
    }

    /* eliminação das soluções triviais da forma 0 0 0 0 .. 0 0 */
    int eh_nula = 1;
    for(i = 0; i < p.qtd && p.qtd == inst.palavras.tamanho; i++){
        if(p.lista[i] != 0){
            eh_nula = 0;
            break;
        }
    }
    if(eh_nula && p.qtd == inst.palavras.tamanho){
        destruir_matriz_char(&rascunho);
        return 0;
    }
    
    /* eliminando soluções com espaços em branco ' ' */
    if(p.qtd == inst.palavras.tamanho){
        for(i = 0; i < linhas; i++){
            for(j = 0; j < colunas; j++){
                if(rascunho.lista[i][j] == ' '){
                    destruir_matriz_char(&rascunho);
                    return 0;
                    break;
                }
            }
        }
        print_matriz_char(rascunho);
    }
    
    destruir_matriz_char(&rascunho);
    return 1;
}

void inicializar(matriz_char *m, instancia inst){
    int i, j;
    for(i = 0; i < m->linhas; i++){
        for(j = 0; j < m->colunas; j++){
            if(inst.caca_palavras.lista[i][j] == -1){
                m->lista[i][j] = '*';
            } else {
                m->lista[i][j] = ' ';
            }
        }
    }
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