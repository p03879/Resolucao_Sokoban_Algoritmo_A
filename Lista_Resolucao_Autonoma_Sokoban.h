#ifndef LISTA_RESOLUCAO_SOKOBAN_H_INCLUDED
#define LISTA_RESOLUCAO_AUTONOMA_SOKOBAN_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


#define CIMA 0
#define BAIXO 1
#define ESQ 2
#define DIR 3
#define INF 10000
#define QTD_FASES 2


/*SUMARIO DAS FUNÇOES:
int CriarFase(Fase *f, int linhas, int colunas, int qtd_caixas)                                                                     RESERVA MEMÓRIA PARA O MAPA E OBJETIVOS
int CriarEstado(Estado *e, int qtd_caixas)                                                                                          RESERVAR A QUANTIDADE NECESSARIA DE POSICOES DAS CAIXAS DE UM ESTADO
void LiberarFase(Fase *f) 	                                                                                                        LIBERA MEMORIA ALOCADA PARA CRIACAO DA FASE, EVITANDO DESPERDICIO
void LiberarEstado(Estado *e) 	                                                                                                    LIBERA A MEMORIA ALOCADA PARA A QUANTIDADE DE CAIXAS DE CADA FASE
void CriarMapa(Fase *f, int mapa[f->linhas][f->colunas]) 	                                                                        COPIA OS VALORES DA MATRIZ RECEBIDA (FASE)
void PreencherPosicoes(Fase *f, Estado *e, Posicao objetivos[], Posicao caixas[], Posicao jogador) 	                                PREENCHE AS POSICOES INICIAIS DOS OBJETIVOS, CAIXAS E JOGADOR
void InicializarFase(Fase *f, Estado *e, int mapa[f->linhas][f->colunas], Posicao objetivos[], Posicao caixas[], Posicao jogador) 	INICIALIZA UMA FASE DO JOGO, CONFIGURANDO O MAPA E PREENCHENDO AS POSIÇOES DOS OBJETIVOS, CAIXAS E JOGADOR
int EncontrarCaixa(Fase *f, Estado *e, int linha, int coluna) 	                                                                    VERIFICAR SE EXISTE CAIXA EM DETERMINADA POSICAO DO MAPA
int VerificarMovimento(Fase *f, Estado *e, int direcao) 	                                                                        VALIDA SE UM  MOVIMENTO DO JOGADOR PODE SER REALIZADO, CONSIDERANDO OBSTACULOS, LIMITES DO MAPA E MOVIMENTAÇAO DE CAIXAS
int EstadoSucessor(Fase *f, Estado *atual, int direcao, Estado *novo) 	                                                            GERA O ESTADO SUCESSOR PARA UMA DIREÇÃO, SERÁ UTILIZADO PARA GUIAR O A*. AS POSSIBILIDADE DE ESTADOS PARA O ALGORITMO: CRIA UM NOVO ESTADO A PARTIR DO ATUAL
int CompararEstados(Fase *f, Estado *e1, Estado *e2) 	                                                                            VERIFICA SE DOIS ESTADOS GERADOS SAO IGUAIS
int CriaDistancia(Fase *f) 	                                                                                                        ALOCA DINAMICAMENTE A MATRIZ DE DISTANCIAS UTILIZADA PELA HEURISTICA, GARANTINDO O TRATAMENTO DE FALHAS DE MEMORIA
void Distancias(Fase *f) 	                                                                                                        INICIALIZA A MATRIZ DE DISTANCIA DA FASE, ATRIBUINDO O VALOR INF A TODAS AS POSIÇOES PARA INDICAR QUE AS DISTANCIAS DAS CAIXAS AINDA NAO FORAM CALCULADAS
void Deslocamento(int direcao, int *dl, int *dc) 	                                                                                RECEBE UMA DIRECAO E TRANSFORMA EM DESLOCAMENTO
int LimiteMapa(Fase *f, int linha, int coluna) 		                                                                                VERIFICA SE UMA POSICAO ESTA DENTRO DO LIMITE DO MAPA
Fila* CriarFila() 	                                                                                                                CRIA UMA FILA
int FilaVazia(Fila *fila) 	                                                                                                        VERIFICA SE A FILA ESTÁ VAZIA
int InserirFila(Fila *fila, Posicao p) 		                                                                                        INSERE NOVA POSICAO NA FILA
Posicao RetirarFila(Fila *fila) 	                                                                                                REMOVE POSICAO DA FILA
void LiberarFila(Fila *fila) 	                                                                                                    LIBERA TODA MEMORIA ALOCADA PARA FILA
int CalculoDistanciaObjetivos(Fase *f, int i, Fila *fila) 	                                                                        CALCULA, POR BUSCA EM LARGURA, O MENOR NUMERO DE EMPURROES PARA LEVAR UMA CAIXA DE CADA POSICAO ATE O OBJETIVO
int PercorrerDistanciaObjetivos(Fase *f)                                                                                            CALCULA A TABELA DE DISTANCIAS DE TODOS OS OBJETIVOS
int AssociarCaixasObjetivos(Fase *f, Estado *e, int caixa, int associados[]) 	                                                    TESTA TODAS AS COMBINAÇÕES E RETORNA A MENOR SOMA DE EMPURRÕES. ASSOCIADOS[] GUARDA OS OBJETIVOS JA OCUPADOS
int EstimarCusto(Fase *f, Estado *e) 	                                                                                            CALCULA A ESTIMATIVA DO CUSTO PARA UM DETERMINADO ESTADO
int CaixaNoObjetivo(Fase *f, int linha, int coluna) 	                                                                            VERIFICA A EXISTENCIA DE OBJETIVO NA POSICAO INFORMADA
int DistanciaJogador(Fase *f, Estado *e) 	                                                                                        CALCULA A MENOR DISTANCIA ENTRE O JOGADOR E UMA CAIXA FORA DO OBJETIVO. UTILIZA A DISTANCIA DE MANHATTAN
Lista* CriarLista() 	                                                                                                            CRIA A LISTA DINAMICAMENTE
int ListaVazia(Lista *l) 	                                                                                                        VERIFICA SE A LISTA ESTA VAZIA
int Prioridade(No *no1, No *no2)                                                                                                   	IRÁ COMPARAR DOIS NOS DO A* E VERIFICAR QUAL POSSUI PRIORIDADE COM BASE EM VARIAVEIS
void InserirListaOrdenada(Lista *l, No *novo) 	                                                                                    INSERE UM NO NA LISTA MANTENDO A ORDENAÇAO DEFINIDA PELO CRITERIO DE PRIORIDADE
No* RemoverInicio(Lista *l) 	                                                                                                    REMOVE E RETORNa O PRIMEIRO NO DA LISTA, ATUALIZANDO SEU INICIO
void LiberarLista(Lista *l)                                                                                                      	LIBERA A MEMORIA ALOCADA PARA TODOS OS NOS DA LISTA
int CopiarEstado(Fase *f, Estado *partida, Estado *chegada) 	                                                                    COPIA INFORMACOES DE UM ESTADO PARA OUTRO
void CalculoCustoH(Fase *f, No *no, No *ant) 	                                                                                    CALCULA OS CUSTOS G, H e F DO NO, ALEM DO CRITERIO DE DESEMPATE UTILIZADO NA BUSCA
No* CriarNo(Fase *f, Estado *e, No *ant) 	                                                                                        CRIA O NO UTILIZADO PELO A*
int EstadoNaLista(Fase *f, Lista *l, Estado *e)                                                                                 	VERIFICA SE O ESTADO DO JOGO JA FOI ARMAZENADO NA LISTA
int Sucesso(Fase *f, Estado *e) 	                                                                                                VERIFICA SE O ESTADO ATUAL REPRESENTA A SOLUÇAO
void NoSucessor(Fase *f, No *ant, int direcao, Lista *aberta, Lista *fechada) 	                                                    GERA O SUCESSOR DE UM NO EM UMA DIRECAO E O INSERE NA LISTA ABERTA, CASO NAO ESTEJA NA LISTA FECHADA E NAO SEJA DEADLOCK
void ExpandirNo(Fase *f, No *atual, Lista *aberta, Lista *fechada)                                                                 	EXPANDE UM NO TENTANDO GERAR POSSIVEIS ESTADOS
No* AEstrela(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos) 		                                        A PARTIR DO ESTADO INCIAL, EXPLORA OS ESTADOS DE ACORDO COM SUA PRIORIDADE
void ImprimirMapa(Fase *f, Estado *e)                                                                                               IMPRIME O MAPA UTILIZANDO SIMBOLOS UNICODE ESCOLHIDOS
No *ResolveFase(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos)                                       	ALOCA E CALCULA A TABELA DE DISTANCIAS USADA PELA HEURISTICA E EXECUTA O A*
void AnimarMapaSolucao(Fase *f, No *no, int nivel, int numeroFase, int velocidadeMs) 	                                            ANIMA A SOLUCAO, FAZ O BONECO SE MOVIMENTAR E MOVIMENTAR AS CAIXAS
void ImprimirTabelaResultados(ResultadoTabela r[], int qtdFases)                                                                	APRESENTA A TABELA COMPARATIVA DAS FASES DO NIVEL EXECUTADO, APOS SUA EXECUÇAO. R ARMAZENA OS RESULTADOS E QTDFFASES INFORMA QUANTAS POSICOES TERA O VETOR
int CarregarFaseFacil(int numeroFase, Fase *f, Estado *e) 	                                                                        PREPARA OS MAPAS DO NIVEL FACIL, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFaseMedio(int numeroFase, Fase *f, Estado *e) 	                                                                        PREPARA OS MAPAS DO NIVEL MEDIO, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFaseDificil(int numeroFase, Fase *f, Estado *e)                                                                      	PREPARA OS MAPAS DO NIVEL DIFICIL, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFase(int nivel, int numeroFase, Fase *f, Estado *e)                                                                 	RECEBE O NIVEL DE DIFICULDADE ESCOLHIDO PELO USUARIO NA MAIN, COM ISSO, EXECUTA O CASE
void LimparBuffer() 	                                                                                                            LIMPEZA DE BUFFER, CONFERE ENTRADA DE CARACTERES E FAZ LIMPEZA CASO O FINAL DO VALOR INSERIDO SEJA != 1 (FINAL 1 REPRESENTA NUMERO)
void ExecutarNivel(int nivel, int velocidadeMs) 	                                                                                PROCESSO DE RESOLUCAO DE CADA FASE DENTRO DO NIVEL DE DIFICULDADE
*/


typedef struct Posicao_mapa{
    int linha;
    int coluna;
}Posicao;


typedef struct Fase{
    int **mapa;
    int qtd_caixas;
    int linhas;
    int colunas;
    Posicao *objetivos;
    int ***distancias;
}Fase;


typedef struct Estado{
    Posicao jogador;
    Posicao *caixas;
}Estado;


typedef struct No{
    int g;
    int h;
    int f;
    int desempate;
    Estado estado;
    struct No *anterior;
    struct No *prox;
}No;


typedef struct NoFila{
    Posicao posicao;
    struct NoFila *prox;
}NoFila;


typedef struct Fila{
    NoFila *inicio;
    NoFila *fim;
}Fila;


typedef struct Lista{
    No *ini;
}Lista;


typedef struct ResultadoTabela{
    int dificuldade;
    int caixas;
    float tempoMs;
    int nos_expandidos;
    int profundidade;
    int custo;
    int faseConcluida;
}ResultadoTabela;



int CriarFase(Fase *f, int linhas, int colunas, int qtd_caixas){
    int i;

    f->mapa = NULL;
    f->objetivos = NULL;
    f->distancias = NULL;
    f->linhas = linhas;
    f->colunas = colunas;
    f->qtd_caixas = qtd_caixas;

    f->mapa = calloc(linhas, sizeof(int *));

    if(f->mapa == NULL){
        return 0;
    }

    for(i = 0; i < linhas; i++){
        f->mapa[i] = calloc(colunas, sizeof(int));

        if(f->mapa[i] == NULL){
            return 0;
        }
    }

    f->objetivos = malloc(qtd_caixas * sizeof(Posicao));

    if(f->objetivos == NULL){
        return 0;
    }

    return 1;
}


int CriarEstado(Estado *e, int qtd_caixas){
    e->caixas  = NULL;
    e->caixas = malloc(qtd_caixas * sizeof(Posicao));

    if(e->caixas == NULL){
        return 0;
    }

    return 1;
}


void LiberarFase(Fase *f){
    int i, j;

    if(f->mapa != NULL){
        for(i = 0; i < f->linhas; i++){
            free(f->mapa[i]);
        }

        free(f->mapa);
    }

    if(f->distancias != NULL){
       for(i = 0; i < f->qtd_caixas; i++){
            if(f->distancias[i] != NULL){
                for(j = 0; j < f->linhas; j++){
                    free(f->distancias[i][j]);
                }

                free(f->distancias[i]);
            }
        }

        free(f->distancias);
    }

    free(f->objetivos);
}


void LiberarEstado(Estado *e){
    free(e->caixas);
}


void CriarMapa(Fase *f, int mapa[f->linhas][f->colunas]){
    int i, j;

    for(i = 0; i < f-> linhas; i++){
        for(j = 0; j < f->colunas; j++){
            f->mapa[i][j] = mapa[i][j];
        }
    }
}

void PreencherPosicoes(Fase *f, Estado *e, Posicao objetivos[], Posicao caixas[], Posicao jogador){
    int i;

    for(i = 0; i < f->qtd_caixas; i++){
        f->objetivos[i] = objetivos[i];
        e->caixas[i] = caixas[i];
    }

    e->jogador = jogador;
}


void InicializarFase(Fase *f, Estado *e, int mapa[f->linhas][f->colunas], Posicao objetivos[], Posicao caixas[], Posicao jogador){
    CriarMapa(f, mapa);
    PreencherPosicoes(f, e, objetivos, caixas, jogador);
}


int EncontrarCaixa(Fase *f, Estado *e, int linha, int coluna){
    int i;

    for(i = 0; i < f->qtd_caixas; i++){
        if(e->caixas[i].linha == linha && e->caixas[i].coluna == coluna){
            return i;
        }
    }

    return -1;
}


int VerificarMovimento(Fase *f, Estado *e, int direcao){
    int novaL, novaC;
    int linhaCaixa, colunaCaixa;
    int caixaEncontrada;

    novaL = e->jogador.linha;
    novaC = e->jogador.coluna;

    switch(direcao){
        case CIMA:
            novaL--;
            break;

        case BAIXO:
            novaL++;
            break;

        case ESQ:
            novaC--;
            break;

        case DIR:
            novaC++;
            break;

        default:
            return 0;
    }

    if(novaL < 0 || novaL >= f->linhas || novaC < 0 || novaC >= f->colunas || f->mapa[novaL][novaC] == 1){
        return 0;
    }

    caixaEncontrada = EncontrarCaixa(f, e, novaL, novaC);

    if(caixaEncontrada == -1){
        return 1;
    }

    linhaCaixa = novaL + (novaL - e->jogador.linha);
    colunaCaixa = novaC + (novaC - e->jogador.coluna);


    if(linhaCaixa < 0 || linhaCaixa >= f->linhas ||colunaCaixa < 0 || colunaCaixa >= f->colunas || EncontrarCaixa(f, e, linhaCaixa, colunaCaixa) != -1 || f->mapa[linhaCaixa][colunaCaixa] == 1){
        return 0;
    }

    return 1;
}


int EstadoSucessor(Fase *f, Estado *atual, int direcao, Estado *novo){
    int i;
    int novaL, novaC;
    int linhaCaixa, colunaCaixa;
    int caixaEncontrada;

    novo->jogador = atual->jogador;
    novo->caixas = malloc(f->qtd_caixas *sizeof(Posicao));

    if(novo->caixas == NULL){
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++){
        novo->caixas[i] = atual->caixas[i];
    }

    novaL = atual->jogador.linha;
    novaC = atual->jogador.coluna;

    switch(direcao){
        case CIMA:
            novaL--;
            break;

        case BAIXO:
            novaL++;
            break;

        case ESQ:
            novaC--;
            break;

        case DIR:
            novaC++;
            break;

        default:
            free(novo->caixas);
            novo->caixas = NULL;
            return 0;
    }

    caixaEncontrada = EncontrarCaixa(f, atual, novaL, novaC);

    if(caixaEncontrada != -1){
        linhaCaixa = novaL;
        colunaCaixa = novaC;

        switch(direcao){
            case CIMA:
            linhaCaixa--;
            break;

        case BAIXO:
            linhaCaixa++;
            break;

        case ESQ:
            colunaCaixa--;
            break;

        case DIR:
            colunaCaixa++;
            break;
        }

        novo->caixas[caixaEncontrada].linha = linhaCaixa;
        novo->caixas[caixaEncontrada].coluna = colunaCaixa;
    }

    novo->jogador.linha = novaL;
    novo->jogador.coluna = novaC;

    return 1;
}

int CompararEstados(Fase *f, Estado *e1, Estado *e2){
    int i;

    if(e1->jogador.linha != e2->jogador.linha || e1->jogador.coluna != e2->jogador.coluna){
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++){
        if(EncontrarCaixa(f, e2, e1->caixas[i].linha, e1->caixas[i].coluna)== -1){
            return 0;
        }
    }

    return 1;
}



int CriaDistancia(Fase *f) {
    int i, j;

    f->distancias = calloc(f->qtd_caixas, sizeof(int **));

    if(f->distancias == NULL) {
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++) {
        f->distancias[i] = calloc(f->linhas, sizeof(int *));

        if(f->distancias[i] == NULL) {
            return 0;
        }

        for(j = 0; j < f->linhas; j++) {
            f->distancias[i][j] = malloc(f->colunas * sizeof(int));

            if(f->distancias[i][j] == NULL) {
                return 0;
            }
        }
    }

    return 1;
}


void Distancias(Fase *f) {
    int i, j, k;

    for(i = 0; i < f->qtd_caixas; i++) {
        for(j = 0; j < f->linhas; j++) {
            for(k = 0; k < f->colunas; k++) {
                f->distancias[i][j][k] = INF;
            }
        }
    }
}


void Deslocamento(int direcao, int *dl, int *dc) {
    *dl = 0;
    *dc = 0;

    switch(direcao) {
        case CIMA:
            *dl = -1;
            break;

        case BAIXO:
            *dl = 1;
            break;

        case ESQ:
            *dc = -1;
            break;

        case DIR:
            *dc = 1;
            break;
    }
}


int LimiteMapa(Fase *f, int linha, int coluna) {
    if(linha >= 0 && linha < f->linhas && coluna >= 0 && coluna < f->colunas) {
        return 1;
    }

    return 0;
}


Fila* CriarFila(){
    Fila *fila;
    fila = malloc(sizeof(Fila));

    if(fila == NULL){
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}


int FilaVazia(Fila *fila){
    if(fila->inicio == NULL){
        return 1;
    }

    return 0;
}


int InserirFila(Fila *fila, Posicao p){
    NoFila *novo;
    novo = malloc(sizeof(NoFila));

    if(novo == NULL){
        return 0;
    }

    novo->posicao = p;
    novo->prox = NULL;

    if(fila->fim == NULL){
        fila->inicio = novo;
    }
    else{
        fila->fim->prox = novo;
    }

    fila->fim = novo;

    return 1;
}


Posicao RetirarFila(Fila *fila){
    NoFila *aux;
    Posicao p;

    aux = fila->inicio;
    p = aux->posicao;
    fila->inicio = aux->prox;

    if(fila->inicio == NULL){
        fila->fim = NULL;
    }

    free(aux);

    return p;
}


void LiberarFila(Fila *fila){
    NoFila *aux;

    while(fila->inicio !=NULL){
        aux = fila->inicio;
        fila->inicio = aux->prox;
        free(aux);
    }

    free(fila);
}


int CalculoDistanciaObjetivos(Fase *f, int i, Fila *fila){
    int j, l, c;
    int dl, dc;
    int caixaL, caixaC;
    int jogadorL, jogadorC;
    int **dist;
    Posicao atual;

    dist = f->distancias[i];
    l = f->objetivos[i].linha;
    c = f->objetivos[i].coluna;

    if(!LimiteMapa(f, l, c) || f->mapa[l][c] == 1){
        return 0;
    }

    dist[l][c] = 0;

    atual.linha = l;
    atual.coluna = c;

    if(!InserirFila(fila, atual)){
        return 0;
    }

    while(!FilaVazia(fila)){
        atual = RetirarFila(fila);

        l = atual.linha;
        c = atual.coluna;

        for(j = 0; j < 4; j++){
            Deslocamento(j, &dl, &dc);
            caixaL = l - dl;
            caixaC = c - dc;
            jogadorL = caixaL - dl;
            jogadorC = caixaC - dc;

            if(LimiteMapa(f, caixaL, caixaC) && LimiteMapa(f, jogadorL, jogadorC) && f->mapa[caixaL][caixaC] != 1 && f->mapa[jogadorL][jogadorC] != 1 && dist[caixaL][caixaC] == INF){

                dist[caixaL][caixaC] = dist[l][c] + 1;

                atual.linha = caixaL;
                atual.coluna = caixaC;

                if(!InserirFila(fila, atual)){
                    return 0;
                   }
            }
        }
    }

    return 1;
}


int PercorrerDistanciaObjetivos(Fase *f){
    int i;
    Fila *fila;

    fila = CriarFila();

    if(fila == NULL){
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++){
        if(!CalculoDistanciaObjetivos(f, i, fila)){
            LiberarFila(fila);
            return 0;
        }
    }

    LiberarFila(fila);

    return 1;
}


int AssociarCaixasObjetivos(Fase *f, Estado *e, int caixa, int associados[]){
    int custo, menor_custo, obj_teste;

    if(caixa == f->qtd_caixas){
        return 0;
    }

    menor_custo = INF;

    for(obj_teste = 0; obj_teste < f->qtd_caixas; obj_teste++){
        if(associados[obj_teste] == 0){
            associados[obj_teste] = 1;

            custo = f->distancias[obj_teste][e->caixas[caixa].linha][e->caixas[caixa].coluna]+ AssociarCaixasObjetivos(f, e, caixa + 1, associados);
            associados[obj_teste] = 0;

            if(custo < menor_custo){
                menor_custo = custo;
            }
        }
    }

    return menor_custo;
}


int EstimarCusto(Fase *f, Estado *e){
    int i, estimativa;
    int associados[f->qtd_caixas];

    for(i= 0; i < f->qtd_caixas; i++){
        associados[i] = 0;
    }

    estimativa = AssociarCaixasObjetivos(f, e, 0, associados);
    return  estimativa;
}


int CaixaNoObjetivo(Fase *f, int linha, int coluna){
    int i;

    for(i = 0; i < f->qtd_caixas; i++){
        if(f->objetivos[i].linha == linha && f->objetivos[i].coluna == coluna){
            return 1;
        }
    }

    return 0;
}


int DistanciaJogador(Fase *f, Estado *e){
    int i, dist, menor;

    menor = INF;

    for(i = 0; i < f->qtd_caixas; i++){
        if(!CaixaNoObjetivo(f, e->caixas[i].linha, e->caixas[i].coluna)){
            dist = abs(e->caixas[i].linha - e->jogador.linha) + abs(e->caixas[i].coluna - e->jogador.coluna);

            if(dist < menor){
                menor = dist;
            }
        }
    }

    if(menor == INF){
        return 0;
    }

    return menor - 1;
}


Lista* CriarLista(){
    Lista *l;
    l = malloc(sizeof(Lista));

    if(l == NULL){
        return NULL;
    }

    l->ini = NULL;
    return l;
}


int ListaVazia(Lista *l){
    if(l->ini == NULL){
        return 1;
    }

    return 0;
}


int Prioridade(No *no1, No *no2){
    if (no1->f < no2->f) {
        return 1;
    }
    else {
        if (no1->f > no2->f) {
            return 0;
        }
        else {
            if (no1->h < no2->h) {
                return 1;
            }
            else {
                if (no1->h > no2->h) {
                    return 0;
                }
                else {
                    if (no1->desempate < no2->desempate) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
            }
        }
    }
}


void InserirListaOrdenada(Lista *l, No *novo){
    No *atual;

    if(l->ini == NULL || Prioridade(novo, l->ini)){
        novo->prox = l->ini;
        l->ini = novo;
    }

    else{
        atual = l->ini;

        while(atual->prox != NULL && !Prioridade(novo, atual->prox)){
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}


No* RemoverInicio(Lista *l){
    No *primeiro;

    if(l->ini == NULL){
        return NULL;
    }

    primeiro = l->ini;
    l->ini = primeiro->prox;
    primeiro->prox = NULL;

    return primeiro;
}


void LiberarLista(Lista *l){
    No *atual;

    while(l->ini != NULL){
        atual = l->ini;
        l->ini = atual->prox;

        free(atual->estado.caixas);
        free(atual);
    }
    free(l);
}


int CopiarEstado(Fase *f, Estado *partida, Estado *chegada){
    int i;
    chegada->caixas = malloc(f->qtd_caixas * sizeof(Posicao));

    if(chegada->caixas == NULL){
        return 0;
    }

    chegada->jogador = partida->jogador;

    for(i = 0; i < f->qtd_caixas; i++){
        chegada->caixas[i] = partida->caixas[i];
    }

    return 1;
}


void CalculoCustoH(Fase *f, No *no, No *ant){
    if(ant == NULL){
        no->g = 0;
    }

    else{
        no->g = ant->g + 1;
    }

    no->h = EstimarCusto(f, &no->estado);
    no->f = no->g + no->h;
    no->desempate = DistanciaJogador(f, &no->estado);
}


No* CriarNo(Fase *f, Estado *e, No *ant){
    No *novo;
    novo = malloc(sizeof(No));

    if(novo == NULL){
        return NULL;
    }

    if(!CopiarEstado(f, e, &novo->estado)){
        free(novo);
        return NULL;
    }

    novo->anterior = ant;
    novo->prox = NULL;

    CalculoCustoH(f, novo, ant);

    return novo;
}


int EstadoNaLista(Fase *f, Lista *l, Estado *e){
    No *atual;

    atual = l->ini;

    while(atual != NULL){
        if(CompararEstados(f, e, &atual->estado)){
            return 1;
        }

        atual = atual->prox;
    }

    return 0;
}


int Sucesso(Fase *f, Estado *e){
    int i;

    for(i = 0; i < f->qtd_caixas; i++){
        if(!CaixaNoObjetivo(f, e->caixas[i].linha, e->caixas[i].coluna)){
            return 0;
        }
    }

    return 1;
}


void NoSucessor(Fase *f, No *ant, int direcao, Lista *aberta, Lista *fechada){
    No *sucessor;
    Estado novoEstado;

    if(VerificarMovimento(f, &ant->estado, direcao)){
        if(EstadoSucessor(f, &ant->estado, direcao, &novoEstado)){
            if(!EstadoNaLista(f, fechada, &novoEstado)){
                sucessor = CriarNo(f, &novoEstado, ant);

                if(sucessor != NULL){
                    if(sucessor->h >= INF){
                        free(sucessor->estado.caixas);
                        free(sucessor);
                    }
                    else{
                        InserirListaOrdenada(aberta, sucessor);
                    }
                }
            }

            LiberarEstado(&novoEstado);
        }
    }
}


void ExpandirNo(Fase *f, No *atual, Lista *aberta, Lista *fechada){
    int i;

    for(i = 0; i < 4; i++){
        NoSucessor(f, atual, i, aberta, fechada);
    }
}


No* AEstrela(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos){
    No *atual, *ant;

    *expandidos = 0;

    ant = CriarNo(f, inicial, NULL);

    if(ant == NULL){
        return NULL;
    }

    if(ant->h >= INF){
        free(ant->estado.caixas);
        free(ant);
        return NULL;
    }

    InserirListaOrdenada(aberta, ant);

    while(!ListaVazia(aberta)){
        atual = RemoverInicio(aberta);

        if(EstadoNaLista(f, fechada, &atual->estado)){
            free(atual->estado.caixas);
            free(atual);
        }
        else{
            InserirListaOrdenada(fechada, atual);

            if(Sucesso(f, &atual->estado)){
                return atual;
            }

            (*expandidos)++;
            ExpandirNo(f, atual, aberta, fechada);
        }
    }

    return NULL;
}


void ImprimirMapa(Fase *f, Estado *e){
    int i, j, jogador, caixa, objetivo;

    for(i = 0; i < f->linhas; i++){
        for(j = 0; j < f->colunas; j++){
            jogador = (e->jogador.linha == i && e->jogador.coluna == j);
            caixa = (EncontrarCaixa(f, e, i, j) != -1);
            objetivo = CaixaNoObjetivo(f, i, j);

            if(jogador && objetivo){
                printf("\u263B ");
            }
            else{
                if(jogador){
                    printf("\u263A ");
                }
                else{
                    if(caixa && objetivo){
                        printf("\u2605 ");
                    }
                    else{
                        if(caixa){
                            printf("\u2612 ");
                        }
                        else{
                            if(f->mapa[i][j] == 1){
                                printf("# ");
                            }
                            else{
                                if(objetivo){
                                    printf("\u25CB ");
                                }
                                else{
                                    printf("  ");
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("\n");
    }

    printf("\n");
}


No *ResolveFase(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos){
    No *solucao;
    if(!CriaDistancia(f)){
        return NULL;
    }

    Distancias(f);

    if(!PercorrerDistanciaObjetivos(f)){
        return NULL;
    }

    solucao = AEstrela(f, inicial, aberta, fechada, expandidos);
    return solucao;
}


void AnimarMapaSolucao(Fase *f, No *no, int nivel, int numeroFase, int velocidadeMs){
    if(no != NULL){
        AnimarMapaSolucao(f, no->anterior, nivel, numeroFase, velocidadeMs);
        system("cls");
        printf("\nNIVEL %d - FASE %02d \n\n", nivel, numeroFase);
        ImprimirMapa(f, &no->estado);
        Sleep(velocidadeMs);

    }
}



void ImprimirTabelaResultados(ResultadoTabela r[], int qtdFases){
    int i;

    printf("\n------------------- TABELA COMPARATIVA: RESULTADOS ALGORITMO A* -------------------");
    printf("\n Fase | Dificuldade | Caixas | Tempo (ms) | Nos Expandidos | Profundidade | Custo |");
    printf("\n------+-------------+--------+------------+----------------+--------------+-------+");

    for(i = 0; i < qtdFases; i++){
        printf("\n %02d   |", i + 1);

        switch(r[i].dificuldade){
            case 1:
                printf(" Facil       |");
                break;

            case 2:
                printf(" Medio       |");
                break;

            case 3:
                printf(" Dificil     |");
                break;

            default:
                printf(" -           |");
                break;
        }

        printf(" %6d | %10.4f | %14d |", r[i].caixas, r[i].tempoMs, r[i].nos_expandidos);

        if(r[i].faseConcluida){
            printf(" %12d | %5d |", r[i].profundidade, r[i].custo);
        }

        else{
            printf(" Sem solucao  |     - |");
        }
    }

    printf("\n------+-------------+--------+------------+----------------+--------------+-------+\n");
}


int CarregarFaseFacil(int numeroFase, Fase *f, Estado *e){
    switch(numeroFase){
        case 1:{
           int mapa[6][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 1, 1},
                {1, 0, 0, 1, 1, 1},
                {1, 1, 0, 1, 1, 1},
                {1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[2] = {{1, 1}, {2, 3}};
            Posicao caixas[2] = {{2, 1}, {3, 2}};
            Posicao jogador = {4, 2};

            if(!CriarFase(f, 6, 6, 2) || !CriarEstado(e, 2)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        case 2:{
            int mapa[6][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 0, 1},
                {1, 1, 1, 0, 0, 1},
                {1, 1, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[2] = {{1, 2}, {3, 4}};
            Posicao caixas[2] = {{2, 3}, {3, 3}};
            Posicao jogador = {3, 2};

            if(!CriarFase(f, 6, 6, 2) || !CriarEstado(e, 2)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        default:
            return 0;
    }

    return 1;
}


int CarregarFaseMedio(int numeroFase, Fase *f, Estado *e){
    switch(numeroFase){
        case 1:{
            int mapa[7][7] = {
                {1, 1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 0, 1, 1},
                {1, 1, 0, 0, 0, 1, 1},
                {1, 1, 0, 0, 0, 0, 1},
                {1, 1, 1, 0, 0, 1, 1},
                {1, 0, 0, 0, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[2] = {{1, 2}, {3, 5}};
            Posicao caixas[2] = {{1, 3}, {4, 3}};
            Posicao jogador = {5, 1};

            if(!CriarFase(f, 7, 7, 2) || !CriarEstado(e, 2)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        case 2:{
            int mapa[9][9] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 1, 0, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[2] = {{1, 4}, {7, 7}};
            Posicao caixas[2] = {{3, 2}, {4, 6}};
            Posicao jogador = {6, 2};

            if(!CriarFase(f, 9, 9, 2) || !CriarEstado(e, 2)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        default:
            return 0;
    }

    return 1;
}


int CarregarFaseDificil(int numeroFase, Fase *f, Estado *e){
    switch(numeroFase){
        case 1:{
            int mapa[11][11] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
                {1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1},
                {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[3] = {{8, 1}, {5, 9}, {2, 8}};
            Posicao caixas[3] = {{4, 1}, {7, 6}, {2, 4}};
            Posicao jogador = {3, 1};

            if(!CriarFase(f, 11, 11, 3) || !CriarEstado(e, 3)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        case 2:{
            int mapa[12][12] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
                {1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                {1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1},
                {1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[3] = {{1, 9}, {5, 1}, {10, 7}};
            Posicao caixas[3] = {{4, 9}, {2, 2}, {7, 4}};
            Posicao jogador = {5, 7};

            if(!CriarFase(f, 12, 12, 3) || !CriarEstado(e, 3)){
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);
            break;
        }

        default:
            return 0;
    }

    return 1;
}


int CarregarFase(int nivel, int numeroFase, Fase *f, Estado *e){
    switch(nivel){
        case 1:
            return CarregarFaseFacil(numeroFase, f, e);

        case 2:
            return CarregarFaseMedio(numeroFase, f, e);

        case 3:
            return CarregarFaseDificil(numeroFase, f, e);

        default:
            return 0;
    }
}


void LimparBuffer(){
    int c;

    do{
        c = getchar();
    }while(c != '\n' && c != EOF);
}


void ExecutarNivel(int nivel, int velocidadeMs){
    int i;
    int numeroFase;
    int expandidos;
    Lista *aberta, *fechada;
    No *solucao;
    ResultadoTabela resultados[QTD_FASES] = {0};
    LARGE_INTEGER frequencia, inicio, fim;

    QueryPerformanceFrequency(&frequencia);

    for(i = 0; i < QTD_FASES; i++){
        Fase fase = {0};
        Estado inicial = {0};

        numeroFase = i + 1;
        resultados[i].dificuldade = nivel;

        aberta = CriarLista();
        fechada = CriarLista();

        if(aberta == NULL || fechada == NULL || !CarregarFase(nivel, numeroFase, &fase, &inicial)){
            resultados[i].faseConcluida = 0;
            printf("\nErro ao carregar a fase %02d", numeroFase);
        }

        else{
            system("cls");
            printf("\nNIVEL %d - FASE %02d \n\n", nivel, numeroFase);
            ImprimirMapa(&fase, &inicial);

            resultados[i].caixas = fase.qtd_caixas;

            expandidos = 0;
            QueryPerformanceCounter(&inicio);
            solucao = ResolveFase(&fase, &inicial, aberta, fechada, &expandidos);
            QueryPerformanceCounter(&fim);

            resultados[i].tempoMs = (float)((fim.QuadPart - inicio.QuadPart) * 1000.0) / (float)frequencia.QuadPart;
            resultados[i].nos_expandidos = expandidos;

            if(solucao == NULL){
                resultados[i].faseConcluida = 0;
                printf("\nNenhuma solucao encontrada pelo algoritmo A-Estrela na fase %02d", numeroFase);
            }

            else{
                resultados[i].faseConcluida = 1;
                resultados[i].profundidade = solucao->g;
                resultados[i].custo = solucao->g;
                AnimarMapaSolucao(&fase, solucao, nivel, numeroFase, velocidadeMs);
                printf("\nSolucao encontrada!");
                printf("\nMovimentos: %d | Nos expandidos: %d", solucao->g, expandidos);
            }
        }

        if(aberta != NULL){
            LiberarLista(aberta);
        }

        if(fechada != NULL){
            LiberarLista(fechada);
        }

        LiberarFase(&fase);
        LiberarEstado(&inicial);

        if(i < QTD_FASES - 1){
            printf("\n\nPressione uma tecla para resolver a proxima fase");
        }

        else{
            printf("\n\nFim da resolucao das fases do nivel!");
            printf("\nPressione uma tecla para visualizar a tabela de resultados");
        }

        getch();
    }

    system("cls");
    ImprimirTabelaResultados(resultados, QTD_FASES);
    printf("\nPressione uma tecla para voltar ao menu");
    getch();
}

#endif
