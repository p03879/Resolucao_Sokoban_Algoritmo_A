#ifndef LISTA_RESOLUCAO_SOKOBAN_H_INCLUDED
#define LISTA_RESOLUCAO_SOKOBAN_COMENTADA_H_INCLUDED


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
void LiberarFase(Fase *f) 	                                                                                                        LIBERA MEMORIA ALOCADA PARA CRIACAO DA FASE, EVITANDO DISPERDICIO
void LiberarEstado(Estado *e) 	                                                                                                    LIBERA A MEMORIA ALOCADA PARA A QUANTIDADE DE CAIXAS DE CADA FASE
void CriarMapa(Fase *f, int mapa[f->linhas][f->colunas]) 	                                                                        COPIA OS VALORES DA MATRIZ RECEBIDA (FASE)
void PreencherPosicoes(Fase *f, Estado *e, Posicao objetivos[], Posicao caixas[], Posicao jogador) 	                                PREENCHE AS POSICOES INICIAIS DOS OBJETIVOS, CAIXAS E JOGADOR
void InicializarFase(Fase *f, Estado *e, int mapa[f->linhas][f->colunas], Posicao objetivos[], Posicao caixas[], Posicao jogador) 	INICIALIZA UMA FASE DO JOGO, CONFIGURANDO O MAPA E PREENCHENDO AS POSIÇOES DOS OBJETIVOS, CAIXAS E JOGADOR
int EncontrarCaixa(Fase *f, Estado *e, int linha, int coluna) 	                                                                    VERIFICAR SE EXISTE CAIXA EM DETERMINADA POSICAO DO MAPA
int VerificarMovimento(Fase *f, Estado *e, int direcao) 	                                                                        VALIDA SE UM  MOVIMENTO DO JOGADOR PODE SER REALIZADO, CONSIDERANDO OBSTACULOS, LIMITES DO MAPA E MOVIMENTAÇAO DE CAIXAS
int EstadoSucessor(Fase *f, Estado *atual, int direcao, Estado *novo) 	                                                            GERA O ESTADO SUCESSOR PARA UMA DIREÇÃO, SERÁ UTILIZADO PARA GUIAR O A* .AS POSSIBILIDADE DE ESTADOS PARA O ALGORITMO: CRIA UM NOVO ESTADO A PARTIR DO ATUAL
int CompararEstados(Fase *f, Estado *e1, Estado *e2) 	                                                                            VERIFICA SE DOIS ESTADOS GERADOS SAO IGUAIS
int CriaDistancia(Fase *f) 	                                                                                                        ALOCA DINAMICAMENTE A MATRIZ DE DISTANCIAS UTILIZADA PELA HEURISTICA, GARANTINDO O TRATAMENTO DE FALHAS DE MEMORIA E A LIBERAÇAO DOS RECURSOS JA ALOCADOS QUANDO NECESSARIO
void Distancias(Fase *f) 	                                                                                                        INICIALIZA A MATRIZ DE DISTANCIA DA FASE, ATRIBUINDO O VALOR INF A TODAS AS POSIÇOES PARA INDICAR QUE AS DISTANCIAS DAS CAIXASA AINDA NAO FORAM CALCULADAS
void Deslocamento(int direcao, int *dl, int *dc) 	                                                                                RECEBE UMA DIRECAO E TRANSFORMA EM DESLOCAMENTO
int LimiteMapa(Fase *f, int linha, int coluna) 		                                                                                VERIFICA SE UMA POSICAO ESTA DENTRO DO LIMITE DO MAPA
Fila* CriarFila() 	                                                                                                                CRIA UMA FILA
int FilaVazia(Fila *fila) 	                                                                                                        VERIFICA SE A FILA ESTÁ VAZIA
int InserirFila(Fila *fila, Posicao p) 		                                                                                        INSERE NOVA POSICAO NA FILA
Posicao RetirarFila(Fila *fila) 	                                                                                                REMOVE POSICAO DA FILA
void LiberarFila(Fila *fila) 	                                                                                                    LIBERA TODA MEMORIA ALOCADA PARA FILA
int CalculoDistanciaObjetivos(Fase *f, int i, Fila *fila) 	                                                                        CALCULA A DISTANCIA A PARTIR DE OBJETIVO ESPECIFICO, CONSIDERANDO MOVIMENTOS PARA CAIXA CHEGAR ATE LA E INDICA QUAL OBJETIVO ESTA SENDO UTILIZADO COMO REFERENCIA PARA O CALCULO
int PercorrerDistanciaObjetivos(Fase *f)                                                                                            CALCULA A TABELA DE DISTANCIAS DE TODOS OS OBJETIVOS
int AssociarCaixasObjetivos(Fase *f, Estado *e, int caixa, int associados[]) 	                                                    TESTA TODAS AS COMBINAÇÕES E RETORNA A MENOR SOMA DE EMPURRÕES. ASSOCIADOS[] GUARDA OS OBJETIVOS JA OCUPADOS
int EstimarCusto(Fase *f, Estado *e) 	                                                                                            CALCULA A ESTIMATIVA DO CUSTO PARA UM DETERMINADO ESTADO
int CaixaNoObjetivo(Fase *f, int linha, int coluna) 	                                                                            VERIFICA A EXISTENCIA DE OBJETIVO NA POSICAO INFORMADA
int DistanciaJogador(Fase *f, Estado *e) 	                                                                                        CALCULA A MENOR DISTANCIA ENTRE O JOGADOR E UMA CAIXA FORA DO OBJETIVO. UTILIZA A DISTANCIA DE MANHATTAN
Lista* CriarLista() 	                                                                                                            CRIA A LISTA DINAMICAMENTE
int ListaVazia(Lista *l) 	                                                                                                        VERIFICA SE A LISTA ESTA VAZIA
int Prioridade(No *no1, No *no2)                                                                                                   	IRÁ COMPARAR DOIS NOS DO A* E VERIFICAR QUAL POSSUI PRIORIDADE COM BASE EM VARIAVEIS
void InserirListaOrdenada(Lista *l, No *novo) 	                                                                                    INSERE UM NO NA LISTA MANTENDO A ORDENAÇAO DEFINIDA PELO CRITERIO DE PRIORIDADE
No* RemoverInicio(Lista *l) 	                                                                                                    REMOVE E RETORNa O PRIMEIRO NO DA LISTA, ATULAIZANDO SEU INICIO
void LiberarLista(Lista *l)                                                                                                      	LIBERA A MEMORIA ALOCADA PARA TODOS OS NOS DA LISTA
int CopiarEstado(Fase *f, Estado *partida, Estado *chegada) 	                                                                    COPIA INFORMACOES DE UM ESTADO PARA OUTRO
void CalculoCustoH(Fase *f, No *no, No *ant) 	                                                                                    CALCULA OS CUSTOS G, H e F DO NO, ALEM DO CRITERIO DE DESEMPATE UTILIZADO NA BUSCA
No* CriarNo(Fase *f, Estado *e, No *ant) 	                                                                                        CRIA O NO UTILIZADO PELO A*
int EstadoNaLista(Fase *f, Lista *l, Estado *e)                                                                                 	VERIFICA SE O ESTADO DO JOGO JA FOI ARMAZENADO NA LISTA
int Sucesso(Fase *f, Estado *e) 	                                                                                                VERIFICA SE O ESTADO ATUAL REPRESENTA A SOLUÇAO
void NoSucessor(Fase *f, No *ant, int direcao, Lista *aberta, Lista *fechada) 	                                                    CRIA E ADICIONA À LISTA ABERTA OS NOS SUCESSORES VALIDOS GERADOS A PARTIR DE UM ESTADO
void ExpandirNo(Fase *f, No *atual, Lista *aberta, Lista *fechada)                                                                 	EXPANDE UM NO TENTANDO GERA POSSIVEIS ESTADOS
No* AEstrela(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos) 		                                        A PARTIR DO ESTADO INCIAL, ESPLORA OS ESTADOS DE ACORDO COM SUA PRIORIDADE
void ImprimirMapa(Fase *f, Estado *e)                                                                                               IMPRIME O MAPA UTILIZANDO SIMBOLOS UNICODE ESCOLHIDOS
No *ResolveFase(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos)                                       	RESOLVE A FASE EM ETAPAS, DE ACORDO COM OS NOS EXPANDIDOS, PARA FAZER A CONFIGURAÇAO DO MAPA ATUALIZADO
void AnimarMapaSolucao(Fase *f, No *no, int nivel, int numeroFase, int velocidadeMs) 	                                            ANIMA A SOLUCAO, FAZ O BONECO SE MOVIMENTAR E MOVIMENTAR AS CAIXAS
void ImprimirTabelaResultados(ResultadoTabela r[], int qtdFases)                                                                	APRESENTA A TABELA COMPARATIVA DAS FASES DO NIVEL EXECUTADO, APOS SUA EXECUÇAO. R ARMAZENA OS RESULTADOS E QTFFASES INFORMA QUANTAS POSICOES TERA O VETOR
int CarregarFaseFacil(int numeroFase, Fase *f, Estado *e) 	                                                                        PREPARA OS MAPAS DO NIVEL FACIL, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFaseMedio(int numeroFase, Fase *f, Estado *e) 	                                                                        PREPARA OS MAPAS DO NIVEL MEDIO, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFaseDificil(int numeroFase, Fase *f, Estado *e)                                                                      	PREPARA OS MAPAS DO NIVEL FACIL, CAIXAS, OBJETIVOS E JOGADOR
int CarregarFase(int nivel, int numeroFase, Fase *f, Estado *e)                                                                 	RECEBE O NIVEL DE DIFICULDADE ESCOLHIDO PELO USUARIO NA MAIN, COM ISSO, EXECUTA O CASE
void LimparBuffer() 	                                                                                                            LIMPEZA DE BUFFER, CONFERE ENTRADA DE CARACTERES E FAZ LIMPEZA CASO O FINAL DO VALOR INSERIDO SEJA != 1 (FINAL 1 REPRESENTA NUMERO)
void ExecutarNivel(int nivel, int velocidadeMs) 	                                                                                PROCESSO DE RESOLUCAO DE CADA FASE DENTRO DO NIVEL DE DIFICULDADE
*/


//ESTRUTURAS DO PROGRAMA
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



//FUNÇÕES
int CriarFase(Fase *f, int linhas, int colunas, int qtd_caixas){  //RESERVA MEMORIA PARA O MAPA E OBJETIVOS
    int i;

    f->mapa = NULL;  //INICIALIZA O PONTEIRO COM VALOR NULO
    f->objetivos = NULL;
    f->distancias = NULL;
    f->linhas = linhas;  //ARMAZENA DENTRO DA ESTRUTURA FASE OS VALORES RECEBIDOS POR PARAMETRO
    f->colunas = colunas;
    f->qtd_caixas = qtd_caixas;

    f->mapa = calloc(linhas, sizeof(int *));  //ALOCACAO DAS LINHAS MAPA. CALLOC IRA INICIALIZAR TODOS OS BYTES RESERVADOS COM ZERO

    if(f->mapa == NULL){
        return 0;  //QUANDO A ALOCAÇÃO NAO FOI CONCLUIDA
    }

    for(i = 0; i < linhas; i++){
        f->mapa[i] = calloc(colunas, sizeof(int));  //ALOCACAO DAS COLUNAS DO MAPA

        if(f->mapa[i] == NULL){
            return 0;  //QUANDO A ALOCAÇÃO NAO FOI CONCLUIDA
        }
    }

    f->objetivos = malloc(qtd_caixas * sizeof(Posicao));  //ALOCAÇAO DOS OBJETIVOS, EM CADA FASE HAVERA UMA QUANTIDADE DE OBJETIVOS A SER ALOCADA

    if(f->objetivos == NULL){
        return 0;  //QUANDO A ALOCAÇÃO NAO FOI CONCLUIDA
    }

    return 1;  //QUANDO A ALOCAÇÃO FOI CONCLUIDA
}


int CriarEstado(Estado *e, int qtd_caixas){  //RESERVAR A QUANTIDADE NECESSARIA DE POSICOES DAS CAIXAS DE UM ESTADO
    e->caixas  = NULL;  //INICIALIZA O PONTEIRO COM VALOR NULO
    e->caixas = malloc(qtd_caixas * sizeof(Posicao));  //CADA CAIXA POSSUI UMA POSICAO, ESSA LINHA FAZ ISSO, RESERVA UM LUGAR NA MEMORIA PARA CADA POSICAO DE CAIXA

    if(e->caixas == NULL){
        return 0;  //QUANDO A ALOCAÇÃO NAO FOI CONCLUIDA
    }

    return 1;  //QUANDO A ALOCAÇÃO FOI CONCLUIDA
}


void LiberarFase(Fase *f){  //LIBERA MEMORIA ALOCADA PARA CRIACAO DA FASE, EVITANDO DESPERDICIO
    int i, j;

    if(f->mapa != NULL){  //PERCORRE TODAS AS LINHAS DO MAPA, ENQUANTO NAO FOR NULO, E LIBERA CADA UMA
        for(i = 0; i < f->linhas; i++){
            free(f->mapa[i]);
        }

        free(f->mapa);
    }

    if(f->distancias != NULL){  //DISTANCIAS USADAS PELO A*, SAO ESTIMATIVAS DE DESLOCAMENTO DA CAIXA AO OBJETIVO
       for(i = 0; i < f->qtd_caixas; i++){  //PARA CADA CAMADA (OBJETIVO)
            if(f->distancias[i] != NULL){  //PODE SER NULO SE A ALOCACAO FALHOU NO MEIO
                for(j = 0; j < f->linhas; j++){
                    free(f->distancias[i][j]);  //LIBERA AS COLUNAS
                }

                free(f->distancias[i]);  //LIBERA AS LINHAS
            }
        }

        free(f->distancias);  //LIBERA AS CAMADAS
    }

    free(f->objetivos);  //LIBERA A MEMORIA RESERVADA PARA ARMAZENAR AS POSICOES DE CADA OBJETIVO
}


void LiberarEstado(Estado *e){  //LIBERA A MEMORIA ALOCADA PARA A QUANTIDADE DE CAIXAS DE CADA FASE
    free(e->caixas);
}


void CriarMapa(Fase *f, int mapa[f->linhas][f->colunas]){  //COPIA OS VALORES DA MATRIZ RECEBIDA (FASE)
    int i, j;

    for(i = 0; i < f-> linhas; i++){  //COPIA O VALOR DA POSICAO CORRESPONDENTE DA MATRIZ PASSADA POR PARAMETRO PARA A MATRIZ ALOCADA
        for(j = 0; j < f->colunas; j++){
            f->mapa[i][j] = mapa[i][j];
        }
    }
}

void PreencherPosicoes(Fase *f, Estado *e, Posicao objetivos[], Posicao caixas[], Posicao jogador){  //PREENCHE AS POSICOES INICIAIS DOS OBJETIVOS, CAIXAS E JOGADOR
    int i;

    for(i = 0; i < f->qtd_caixas; i++){  //PARA CADA CAIXA
        f->objetivos[i] = objetivos[i];  //ATRIBUI A POSICAO DO OBJETIVO
        e->caixas[i] = caixas[i];  //ATRIBUI A POSICAO DA CAIXA
    }

    e->jogador = jogador;  //ATRIBUI A POSICAO INICIAL DO JOGADOR NAQUELA FASE
}


void InicializarFase(Fase *f, Estado *e, int mapa[f->linhas][f->colunas], Posicao objetivos[], Posicao caixas[], Posicao jogador){
    CriarMapa(f, mapa);  //CHAMA A FUNCAO CRIARMAPA PARA COPIAR OS VALORES DA MATRIZ RECEBIDA NO MAPA ALOCADO
    PreencherPosicoes(f, e, objetivos, caixas, jogador);  //CHAMA PREENCHERPOSICOES PARA PREENCHER AS POSICOES DO MAPA PASSADO POR PARAMETRO
}


int EncontrarCaixa(Fase *f, Estado *e, int linha, int coluna){  //VERIFICAR SE EXISTE CAIXA EM DETERMINADA POSICAO DO MAPA
    int i;

    for(i = 0; i < f->qtd_caixas; i++){
        if(e->caixas[i].linha == linha && e->caixas[i].coluna == coluna){  //SE A LINHA E COLUNA DA CAIXA FOR IGUAL A LINHA E COLUNA PELA QUAL ESTAMOS PROCURANDO, O INDICE DA CAIXA QUE SATISFAZ TAL CONDICAO É RETORNADO
            return i;
        }
    }

    return -1;  //COMO O INDICE COMEÇA EM 0, NAO PODEMOS RETORNA-LO CASO NAO HAJA UMA CAIXA EM DETERMINADA POSICAO. LOGO, RETORNAMOS -1 CASO NAO HAJA CAIXA NA POSICAO PROCURADA
}


int VerificarMovimento(Fase *f, Estado *e, int direcao){  //VALIDACAO DE MOVIMENTO: VERIFICA SE O JOGADOR PODE REALIZAR MOVIMENTO, CONSIDERANDO OS LIMITES DO MAPA E A POSSIBILIDADE DE EMPURRAR CAIXA. RECEBE O ESTADO ATUAL DO JOGO COMO PARAMETRO
    int novaL, novaC;  //LINHA E COLUNA PARA AS QUAIS O JOGADOR PRETENDE SE MOVIMENTAR
    int linhaCaixa, colunaCaixa;  //LINHA E COLUNA PARA AS QUAIS A CAIXA SERA EMPURRADA (CASO HAJA CAIXA PARA EMPURRAR)
    int caixaEncontrada;  //ARMAZENA O INDICE DA CAIXA ENCONTRADA

    novaL = e->jogador.linha;  //POSICAO ATUAL DO JOGADOR
    novaC = e->jogador.coluna;

    switch(direcao){  //VERIFICA QUAL DIRECAO FOI RECEBIDA PELA FUNCAO
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

    if(novaL < 0 || novaL >= f->linhas || novaC < 0 || novaC >= f->colunas || f->mapa[novaL][novaC] == 1){  //VERIFICA SE A POSICAO PARA ANDAR É VALIDA
        return 0;
    }

    caixaEncontrada = EncontrarCaixa(f, e, novaL, novaC);  //VERIFICA A EXISTENCIA DE CAIXA NA POSICAO QUE O JOGADOR PRETENDE SE MOVIMENTAR

    if(caixaEncontrada == -1){
        return 1;  //CONCLUI QUE NAO EXISTE CAIXA E PERMITE A MOVIMENTACAO DO JOGADOR
    }

    //SE HOUVER CAIXA
    linhaCaixa = novaL + (novaL - e->jogador.linha);  //CALCULO DA NOVA POSICAO DA CAIXA
    colunaCaixa = novaC + (novaC - e->jogador.coluna);


    if(linhaCaixa < 0 || linhaCaixa >= f->linhas ||colunaCaixa < 0 || colunaCaixa >= f->colunas || EncontrarCaixa(f, e, linhaCaixa, colunaCaixa) != -1 || f->mapa[linhaCaixa][colunaCaixa] == 1){  //VERIFICA SE A POSICAO PARA ONDE A CAIXA SERA EMPURRADA É VALIDA
        return 0;  //CASO ALGUMA CONDICAO NAO PERMITA QUE A POSICAO SEJA VALIDA
    }

    return 1;  //TUDO CERTO NA VERIFICACAO
}


int EstadoSucessor(Fase *f, Estado *atual, int direcao, Estado *novo){  //GERA AS POSSIBILIDADES DE ESTADOS PARA O ALGORITMO A*: CRIA UM NOVO ESTADO A PARTIR DO ATUAL
    int i;
    int novaL, novaC;  //LINHA E COLUNA PARA A NOVA POSICAO DO JOGADOR
    int linhaCaixa, colunaCaixa;  //NOVA POSICAO DE UMA CAIXA, CASO SEJA EMPURRADA
    int caixaEncontrada;  //ARMAZENA O INDICE DA CAIXA

    novo->jogador = atual->jogador;  //COPIA A POSICAO ATUAL DO JOGADOR NO NOVO ESTADO
    novo->caixas = malloc(f->qtd_caixas *sizeof(Posicao));  //ALOCA ESPAÇO PARA QUANTIDADE DE CAIXAS DA FASE NO NOVO ESTADO

    if(novo->caixas == NULL){
        return 0;  //VERIFICA SE ALOCACAO FOI REALIZADA
    }

    for(i = 0; i < f->qtd_caixas; i++){
        novo->caixas[i] = atual->caixas[i];  //COPIA A POSICAO DE CADA CAIXA DO ESTADO ATUAL PARA O NOVO
    }

    novaL = atual->jogador.linha;  //POSICAO ATUAL DO JOGADOR
    novaC = atual->jogador.coluna;

    switch(direcao){  //CALCULA A NOVA POSICAO, ATUALIZANDO LINHA OU COLUNA
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

    caixaEncontrada = EncontrarCaixa(f, atual, novaL, novaC);  //VERIFICA SE HA CAIXA NA POSICAO PARA QUAL O JOGADOR QUER SE MOVIMENTAR

    if(caixaEncontrada != -1){  //IRA ATUALIZAR A POSICAO DA CAIXA ENCONTRADA
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

        novo->caixas[caixaEncontrada].linha = linhaCaixa;  //ATUALIZA POSICAO DA CAIXA NO ESTADO NOVO
        novo->caixas[caixaEncontrada].coluna = colunaCaixa;
    }

    novo->jogador.linha = novaL;  //ATUALIZA POSICAO DO JOGADOR
    novo->jogador.coluna = novaC;

    return 1;
}

int CompararEstados(Fase *f, Estado *e1, Estado *e2){  //VERIFICA SE DOIS ESTADOS GERADOS SAO IGUAIS
    int i;

    if(e1->jogador.linha != e2->jogador.linha || e1->jogador.coluna != e2->jogador.coluna){  //VERIFICA POSICAO DO JOGADOR, SE A LINHA OU COLUNA FOR DIFERENTE RETORNA 0
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++){  //CASO AS LINHAS E COLUNAS DO JOGADOR SEJAM IGUAIS, COMPARAMOS A POSICAO DA CAIXA
        if(EncontrarCaixa(f, e2, e1->caixas[i].linha, e1->caixas[i].coluna)== -1){  //VERIFICA SE EXISTE UMA CAIXA DO ESTADO 1 NO ESTADO 2
            return 0;  //NAO HA CAIXA NA MESMA POSICAO. ESTADOS DIFERENTES
        }
    }

    return 1;  //CASO ESTADOS FOREM IGUAIS, OU SEJA, CAIXAS E JOGADORES ESTAO NAS MESMAS POSICOES
}



//FUNÇÕES RELACIONADAS AO ALGORITMO A* E HEURÍSTICA
int CriaDistancia(Fase *f) {
    int i, j;

    f->distancias = calloc(f->qtd_caixas, sizeof(int **));  //ALOCA UMA CAMADA PARA CADA OBJETIVO.

    if(f->distancias == NULL) {
        return 0;  //ALOCACAO DEU ERRADO
    }

    for(i = 0; i < f->qtd_caixas; i++) {
        f->distancias[i] = calloc(f->linhas, sizeof(int *));  //ALOCA AS LINHAS DA CAMADA DO OBJETIVO I

        if(f->distancias[i] == NULL) {
            return 0;  //O QUE JA FOI ALOCADO SERA LIBERADO PELA LIBERARFASE
        }

        for(j = 0; j < f->linhas; j++) {
            f->distancias[i][j] = malloc(f->colunas * sizeof(int));  //ALOCA AS COLUNAS

            if(f->distancias[i][j] == NULL) {
                return 0;  //O QUE JA FOI ALOCADO SERA LIBERADO PELA LIBERARFASE
            }
        }
    }

    return 1;
}


void Distancias(Fase *f) {
    int i, j, k;

    for(i = 0; i < f->qtd_caixas; i++) {  //PARA CADA OBJETIVO
        for(j = 0; j < f->linhas; j++) {
            for(k = 0; k < f->colunas; k++) {
                f->distancias[i][j][k] = INF;  //DISTANCIA AINDA NAO CALCULADA, ATRIBUIMOS DISTANCIA DESCONHECIDA. SE CONTINUAR INF APOS A BFS, A CAIXA NAO CHEGA AO OBJETIVO A PARTIR DESSA CASA
            }
        }
    }
}


void Deslocamento(int direcao, int *dl, int *dc) {  //RECEBE UMA DIRECAO E TRANSFORMA EM DESLOCAMENTO
    *dl = 0; //INICIALIZA EM 0
    *dc = 0;

    switch(direcao) {  //DETERMINA MOVIMENTACAO FEITA DE ACORDO COM A DIRECAO
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


int LimiteMapa(Fase *f, int linha, int coluna) {  //VERIFICA SE UMA POSICAO ESTA DENTRO DO LIMITE DO MAPA
    if(linha >= 0 && linha < f->linhas && coluna >= 0 && coluna < f->colunas) {
        return 1;  //CASO A POSICAO ESTEJA DENTRO DOS LIMITES
    }

    return 0;
}


Fila* CriarFila(){  //ALOCA A FILA DINAMICAMENTE. ESSA FILA SERA UTILIZADA PARA REALIZAÇAO DE UMA BFS ANTES DO ALGORITMO A* SER EXECUTADO. ELA IRA AJUDAR A CALCULAR QUAL O NUMERO MINIMO DE EMPURROES UMA CAIXA PRECISA PARA CHEGAR NO OBJETIVO, PARTINDO DO PROPRIO OBJETIVO
    Fila *fila;
    fila = malloc(sizeof(Fila));

    if(fila == NULL){
        return NULL;
    }

    fila->inicio = NULL;  //INICIALIZA OS PONTEIROS COM VALORES NULOS
    fila->fim = NULL;

    return fila;
}


int FilaVazia(Fila *fila){
    if(fila->inicio == NULL){
        return 1;  //NAO EXISTEM ELEMENTOS NA FILA
    }

    return 0;  //EXISTEM ELEMENTOS NA FILA
}


int InserirFila(Fila *fila, Posicao p){  //INSERE NOVA POSICAO NA FILA
    NoFila *novo;
    novo = malloc(sizeof(NoFila));  //ALOCA NOVO NO

    if(novo == NULL){
        return 0;
    }

    novo->posicao = p;  //ARMAZENA POSICAO RECEBIDA
    novo->prox = NULL;  //PROXIMO ELEMENTO SERA O ULTIMO DA FILA, PORTANTO DEVE SER NULO

    if(fila->fim == NULL){  //VERIFICA SE A FILA ESTA VAZIA
        fila->inicio = novo;  //INSERE NO INICIO DA FILA
    }
    else{  //SE A FILA NAO ESTIVER VAZIA
        fila->fim->prox = novo;  //INSERE NO FINAL
    }

    fila->fim = novo;  //ATUALIZA PONTEIRO PARA APONTAR PARA ULTIMO NO

    return 1;  //FUNCAO REALIZADA
}


Posicao RetirarFila(Fila *fila){  //REMOVE POSICAO DA FILA
    NoFila *aux;
    Posicao p;

    aux = fila->inicio;  //ARMAZENA ENDEREÇO DO PRIMEIRO NO NA VARIAVEL AUXILIAR
    p = aux->posicao;  //COPIA A POSICAO ARMAZENADA
    fila->inicio = aux->prox;  //ATUALIZA INICIO DA FILA

    if(fila->inicio == NULL){  //VERIFICA SE APOS A REMOCAO A FILA FICOU VAZIA
        fila->fim = NULL;  //FIM TAMBEM DEVE APONTAR PARA NULO CASO ESTEJA VAZIA
    }

    free(aux);  //LIBERA AUX

    return p;  //RETORNA POSICAO
}


void LiberarFila(Fila *fila){  //LIBERA TODA MEMORIA ALOCADA PARA FILA
    NoFila *aux;

    while(fila->inicio !=NULL){  //PERCORRE A FILA ENQUANTO AINDA HOUVEREM ELEMENTOS
        aux = fila->inicio;  //GUARDA PRIMEIRO NO
        fila->inicio = aux->prox;  //AVANÇA PARA PROXIMO NO
        free(aux);  //LIBERA AUX
    }

    free(fila);  //LIBERA MEMORIA ALOCADA
}


int CalculoDistanciaObjetivos(Fase *f, int i, Fila *fila){  //CALCULA AS DISTANCIAS A PARTIR DE UM OBJETIVO ESPECIFICO, CONSIDERANDO OS EMPURROES PARA A CAIXA CHEGAR ATE LA. I INDICA QUAL OBJETIVO ESTA SENDO UTILIZADO COMO REFERENCIA PARA O CALCULO
    int j, l, c;  //J CONDIZ COM AS DIRECOES DE MOVIMENTACAO. L E C SAO LINHA E COLUNA
    int dl, dc;  //DESLOCAMENTO NA LINHA E NA COLUNA
    int caixaL, caixaC;
    int jogadorL, jogadorC;
    int **dist;  //PONTEIRO PARA ACESSAR A MATRIZ DE DISTANCIAS QUE CORRESPONDE AO OBJETIVO ATUAL
    Posicao atual;

    dist = f->distancias[i]; //PEGA A CAMADA DE OBJETIVOS DA MATRIZ 3D
    l = f->objetivos[i].linha;  //LINHA DO OBJETIVO
    c = f->objetivos[i].coluna;  //COLUNA DO OBJETIVO

    if(!LimiteMapa(f, l, c) || f->mapa[l][c] == 1){  //VERIFICA SE A POSICAO DO OBJETIVO É VALIDA
        return 0;
    }

    dist[l][c] = 0;  //BUSCA COMEÇA NO OBJETIVO E VAI EM DIRECAO AS CAIXAS, PORTANTO, A DISTANCIA DO OBJETIVO ATE ELE MESMO É 0

    atual.linha = l;  //INICIO DA BUSCA
    atual.coluna = c;

    if(!InserirFila(fila, atual)){  //INSERE A POSICAO DO OBJETIVO NA FILA, E SE FALHAR, RETORNA 0
        return 0;
    }

    while(!FilaVazia(fila)){  //ENQUANTO HOUVEREM POSICOES NA FILA
        atual = RetirarFila(fila);  //ARMAZENA POSICAO RETIRADA DA FILA EM ATUAL

        l = atual.linha;  //ATUALIZA LINHA DA POSICAO
        c = atual.coluna;

        for(j = 0; j < 4; j++){  //PERCORRENDO AS 4 DIRECOES, IRA VERIFICAR QUAIS POSICOES PODEM SER ACESSADAS A PARTIR DA POSICAO RETIRADA DA FILA
            Deslocamento(j, &dl, &dc);  //ALTERA O VALOR DE LINHA OU COLUNA
            caixaL = l - dl;  //LINHA DA NOVA POSICAO DE BUSCA - O DESLOCAMENTO PQ É NECESSARIO DESCOBRIR DE ONDE A CAIXA VEM EM BUSCA DO OBJETIVO
            caixaC = c - dc;
            jogadorL = caixaL - dl;  //POSICAO ATRAS DA CAIXA NA QUAL O JOGADOR DEVERIA ESTAR PARA EMPURRA-LA
            jogadorC = caixaC - dc;

            if(LimiteMapa(f, caixaL, caixaC) && LimiteMapa(f, jogadorL, jogadorC) && f->mapa[caixaL][caixaC] != 1 && f->mapa[jogadorL][jogadorC] != 1 && dist[caixaL][caixaC] == INF){  //VERIFICA SE TODAS AS POSICOES SAO VALIDAS E SE A DISTANCIA AINDA NAO FOI DESCOBERTA ((X == INF) EVITA A MESMA POSICAO VARIAS VEZES)

                dist[caixaL][caixaC] = dist[l][c] + 1; //EM DIST, NA LINHA E COLUNA DA CAIXA ELE IRA ATRIBUIR A DISTANCIA DO OBJETIVO + 1. ISSO GERA UM ACUMULADO, QUE DEMONSTRA O QUAO LONGE A CAIXA ESTA DO OBJETIVO

                atual.linha = caixaL;
                atual.coluna = caixaC;

                if(!InserirFila(fila, atual)){  //INSERE NOVA POSICAO NA FILA PARA CONTINUAR EXPLORANDO
                    return 0;
                   }
            }
        }
    }

    return 1;  //CALCULO EXECUTADO, FILA VAZIA
}


int PercorrerDistanciaObjetivos(Fase *f){  //CALCULA A TABELA DE DISTANCIAS DE TODOS OS OBJETIVOS
    int i;
    Fila *fila;

    fila = CriarFila();  //CRIA A FILA VAZIA

    if(fila == NULL){
        return 0;
    }

    for(i = 0; i < f->qtd_caixas; i++){  //UMA BFS PARA CADA OBJETIVO
        if(!CalculoDistanciaObjetivos(f, i, fila)){  //CALCULA AS DISTANCIAS DE CADA OBJETIVO
            LiberarFila(fila);  //NECESSARIO LIBERAR MEMORIA CASO O CALCULO DE ERRADO
            return 0;
        }
    }

    LiberarFila(fila);

    return 1;
}


int AssociarCaixasObjetivos(Fase *f, Estado *e, int caixa, int associados[]){  //ASSOCIA CADA CAIXA A TODOS OS OBJETIVOS PARA DEPOIS VERIFICAR QUAL COMBINACAO TEM A MENOR SOMA DE EMPURROES. ASSOCIADOS[] GUARDA OS OBJETIVOS JA UTILIZADOS NA COMBINACAO COM A CAIXA
    int custo, menor_custo, obj_teste;

    if(caixa == f->qtd_caixas){  //CONDICAO DE PARADA DA FUNCAO RECURSIVA
        return 0;
    }

    menor_custo = INF;  //INICIA COM VALOR DESCONHECIDO

    for(obj_teste = 0; obj_teste < f->qtd_caixas; obj_teste++){ //PERCORRE TODOS OS OBJETIVOS DA FASE
        if(associados[obj_teste] == 0){  //VERIFICA SE O OBJETIVO JA FOI ASSOCIADO, CASO NAO
            associados[obj_teste] = 1; //ASSOCIA A CAIXA AO OBJETIVO

            custo = f->distancias[obj_teste][e->caixas[caixa].linha][e->caixas[caixa].coluna]+ AssociarCaixasObjetivos(f, e, caixa + 1, associados);  //ANTES DA RECURSAO: ACESSA A MATRIZ DE DISTANCIAS E OBTEM O CUSTO P LEVAR A CAIXA AO OBJETIVO, REPRESENTANDO O MINIMO DE MOVIMENTOS. APOS RECURSAO: ANALISA A PROXIMA CAIXA E SOMA O CUSTO
            //MELHOR COMBINACAO DAS CAIXAS
            associados[obj_teste] = 0;  //NECESSARIO LIBERAR OBJETIVO PARA ANALISE DA PROXIMA CAIXA. BACKTRACKING. EXPERIMENTA UMA POSSIBILIDADE, LIBERA E TESTA OUTRA

            if(custo < menor_custo){  //ATUALIZA MENOR CUSTO COM O MENOR VALOR
                menor_custo = custo;
            }
        }
    }

    return menor_custo;
}


int EstimarCusto(Fase *f, Estado *e){  //CALCULA A ESTIMATIVA DO CUSTO PARA UM DETERMINADO ESTADO
    int i, estimativa;
    int associados[f->qtd_caixas];  //CADA POSICAO REPRESENTA UM OBJETIVO DA FASE. O VETOR VAI INDICAR QUAIS OBJETIVOS JA FORAM ASSOCIADOS A UMA CAIXA

    for(i= 0; i < f->qtd_caixas; i++){
        associados[i] = 0;  //INDICA QUE O OBJETIVO AINDA NAO FOI ASSOCIADO
    }

    estimativa = AssociarCaixasObjetivos(f, e, 0, associados);  //RETORNA O CALCULO DA ESTIMATIVA APOS ASSOCIAR CAIXA A OBJETIVOS
    return  estimativa;
}


int CaixaNoObjetivo(Fase *f, int linha, int coluna){  //VERIFICA A EXISTENCIA DE OBJETIVO NA POSICAO INFORMADA
    int i;

    for(i = 0; i < f->qtd_caixas; i++){  //VERIFICA TODOS OS OBJETIVOS DA FASE
        if(f->objetivos[i].linha == linha && f->objetivos[i].coluna == coluna){  //VERIFICA SE A POSICAO DO OBJETIVO CORRESPONDE AO PARAMETRO RECEBIDO
            return 1;  //CASO ENCONTRE UM OBJETIVO NA POSICAO PROCURADA
        }
    }

    return 0;
}


int DistanciaJogador(Fase *f, Estado *e){  //CALCULA A MENOR DISTANCIA ENTRE O JOGADOR E UMA CAIXA FORA DO OBJETIVO. UTILIZA A DISTANCIA DE MANHATTAN
    int i, dist, menor;  //DIST ARMAZENA A DISTANCIA ENTRE O JOGADOR E A CAIXA E MENOR ARMAZENA A MENOR DISTANCIA

    menor = INF;

    for(i = 0; i < f->qtd_caixas; i++){  //VERIFICA TODAS AS CAIXAS
        if(!CaixaNoObjetivo(f, e->caixas[i].linha, e->caixas[i].coluna)){  //VERIFICA SE A CAIXA JA NAO SE ENCONTRA NO OBJETIVO
            dist = abs(e->caixas[i].linha - e->jogador.linha) + abs(e->caixas[i].coluna - e->jogador.coluna);  //ABS TORNA OS VALORES POSITIVOS PARA EVITAR DISTANCIAS NEGATIVAS. CALCULAMOS A DIFERENÇA ENTRE A POSICAO DA CAIXA E DO JOGADOR

            if(dist < menor){
                menor = dist;  //ATRIBUI MENOR DISTANCIA ENCONTRADA
            }
        }
    }

    if(menor == INF){  //SIGNIFICA QUE NENHUMA CAIXA FOI CONSIDERADA, PORTANTO, TODAS JA ESTAO SOBRE SEUS OBJETIVOS
        return 0;
    }

    return menor - 1;  //SUBTRAI 1 PORQUE O JOGADOR SO PRECISA CHEGAR NA CASA AO LADO DA CAIXA PARA EMPURRA-LA, E NAO NA CASA DA PROPRIA CAIXA
}


Lista* CriarLista(){  //CRIA A LISTA DINAMICAMENTE
    Lista *l;
    l = malloc(sizeof(Lista));

    if(l == NULL){  //CASO A ALOCAÇAO FALHE
        return NULL;
    }

    l->ini = NULL;  //INICIALIZA O PONTEIRO COM NULO LOGO APOS A CRIACAO DA LISTA
    return l;  //RETORNA O PONTEIRO LISTA
}


int ListaVazia(Lista *l){
    if(l->ini == NULL){  //VERIFICA SE LISTA NAO ESTÁ APONTANDO PARA NENHUM NO
        return 1;  //RETORNA CASO A LISTA ESTEJA VAZIA
    }

    return 0;  //RETORNA CASO A LISTA NAO ESTEJA VAZIA
}


int Prioridade(No *no1, No *no2){  //IRÁ COMPARAR DOIS NOS DO A* E VERIFICAR QUAL POSSUI PRIORIDADE COM BASE EM VARIAVEIS
    if (no1->f < no2->f) {  //COMPARA A ESTIMATIVA DO CUSTO TOTAL
        return 1;  //SEMPRE RETORNARÁ 1 SE A VARIAVEL DO NO 1 CORRESPONDER A UM VALOR MENOR
    }
    else {
        if (no1->f > no2->f) {
            return 0;  //SEMPRE RETORNARA 0 CASO A ESTIMATIVA DO NO 2 CORRESPONDER A UM VALOR MENOR
        }
        else {
            if (no1->h < no2->h) {  //COMPARA A ESTIMATIVA DO CUSTO RESTANTE ATÉ O OBJETIVO
                return 1;
            }
            else {
                if (no1->h > no2->h) {
                    return 0;
                }
                else {  //SE F E H FOREM IGUAIS NOS DOIS NÓS, UTILIZA A VARIAVEL DESEMPATE: CONDIZ NA DISTANCIA ENTRE O JOGADOR E A CAIXA. A MENOR DISTANCIA TEM PRIORIDADE
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
    No *atual;  //PONTEIRO AUXILIAR PARA PERCORRER A LISTA

    if(l->ini == NULL || Prioridade(novo, l->ini)){
        novo->prox = l->ini;  //NOVO NO APONTARA PARA O PRIMEIRO ELEMENTO DA LISTA OU NULO
        l->ini = novo;  //INICIO DA LISTA DEVERA APONTAR PARA NOVO, O MENOR VALOR ATE O MOMENTO
    }

    else{
        atual = l->ini;  //PONTEIRO AUXILIAR IRA RECEBER O ENDEREÇO DO PRIMEIRO DA LISTA

        while(atual->prox != NULL && !Prioridade(novo, atual->prox)){
            atual = atual->prox;  //IRA AVANÇAR PARA O PROXIMO NO DA LISTA, ENQUANTO HOUVER NÓS E ENQUANTO O PROXIMO NÓ TIVER PRIORIDADE MAIOR OU IGUAL A DAQUELE QUE SERA INSERIDO
        }
        novo->prox = atual->prox;  //NOVO APONTA PARA O ELEMENTO QUE VEM DEPOIS DE ATUAL, OU SEJA, SEU SUCESSOR
        atual->prox = novo;  //ATUAL APONTA PARA NOVO, ATUAL É ANTECESSOR DE NOVO PQ POSSUI PRIORIDADE MAIOR OU IGUAL
    }
}


No* RemoverInicio(Lista *l){
    No *primeiro;  //PONTEIRO PARA ARMAZENAR O PRIMEIRO VALOR DA LISTA

    if(l->ini == NULL){  //VERIFICA SE A LISTA ESTA VAZIA
        return NULL;
    }

    primeiro = l->ini;  //ARMAZENA O ENDEREÇO DO PRIMEIRO VALOR DA LISTA
    l->ini = primeiro->prox;  //ATUALIZA O PRIMEIRO VALOR DA LISTA
    primeiro->prox = NULL;  //DESVINCULA O NO DO RESTANTE DA LISTA

    return primeiro;  //RETORNA O ENDEREÇO DO NO REMOVIDO
}


void LiberarLista(Lista *l){  //LIBERA A MEMORIA ALOCADA PARA TODOS OS NOS DA LISTA
    No *atual;

    while(l->ini != NULL){
        atual = l->ini;  //ARMAZENA O ENDEREÇO DO PRIMEIRO NO
        l->ini = atual->prox;  //ATUALIZA O INICIO DA LISTA

        free(atual->estado.caixas);  //LIBERA A MEMORIA ALOCADA PARA ARMAZENAR AS POSICOES DAS CAIXAS
        free(atual);  //LIBERA A MEMORIA ALOCADA PARA O NO
    }
    free(l);  //LIBERA A ESTRUTURA DA LISTA
}


int CopiarEstado(Fase *f, Estado *partida, Estado *chegada){  //COPIA INFORMACOES DE UM ESTADO PARA OUTRO
    int i;
    chegada->caixas = malloc(f->qtd_caixas * sizeof(Posicao));  //ALOCA MEMORIA PARA ARMAZENAR AS POSICOES DA CAIXA NO ESTADO CHEGADA

    if(chegada->caixas == NULL){  //VERIFICA SE A ALOCAÇAO FALHOU
        return 0;
    }

    chegada->jogador = partida->jogador;  //COPIA A POSICAO DO JOGADOR NO ESTADO DE PARTIDA PARA O ESTADO SEGUINTE, CHEGADA

    for(i = 0; i < f->qtd_caixas; i++){  //VISITA TODAS AS CAIXAS
        chegada->caixas[i] = partida->caixas[i];  //COPIA A POSICAO DAS CAIXAS NO VETOR DE CHEGADA
    }

    return 1;
}


void CalculoCustoH(Fase *f, No *no, No *ant){
    if(ant == NULL){  //VERIFICA SE NO ANTERIOR CORRESPONDE A UM ESTADO INICIAL
        no->g = 0;  //CUSTO ACUMULADO DEFINIDO COM 0 POIS AINDA NAO FORAM REALIZADOS MOVIMENTOS
    }

    else{
        no->g = ant->g + 1;  //SOMA 1 AO CUSTO ACUMULADO DO NO ANTERIOR, POIS UM MOVIMENTO REALIZADO PARA CHEGAR AO NOVO ESTADO CUSTA 1
    }

    no->h = EstimarCusto(f, &no->estado);  //CALCULA A ESTIMATIVA DE CUSTO RESTANTE PARA RESOLVER A FASE
    no->f = no->g + no->h;  //CALCULA O CUSTO TOTAL SOMANDO O CUSTO ACUMULADO COM A ESTIMATIVA RESTANTE
    no->desempate = DistanciaJogador(f, &no->estado);  //CALCULO DA MENOR DISTANCIA ENTRE O JOGADOR E UMA CAIXA QUE AINDA NAO ESTA NO OBJETIVO
}


No* CriarNo(Fase *f, Estado *e, No *ant){  //CRIA O NO UTILIZADO PELO A*
    No *novo;
    novo = malloc(sizeof(No));  //ALOCA MEMORIA PARA ARMAZENAR ESTRUTURA DO TIPO NO

    if(novo == NULL){  //VERIFICA SE A ALOCAÇAO FALHOU
        return NULL;
    }

    if(!CopiarEstado(f, e, &novo->estado)){  //CASO NAO SEJA POSSIVEL COPIAR O ESTADO
        free(novo);  //LIBERA MEMORIA ALOCADA PARA NO
        return NULL;
    }

    novo->anterior = ant;  //ARMAZENA ENDEREÇO DO NO ANTERIOR (PERMITE RECONSTRUIR O CAMINHO DE BUSCA)
    novo->prox = NULL;  //NOVO APONTA PARA NULO

    CalculoCustoH(f, novo, ant);  //CALCULA OS VALORES DE G, H, F, DESEMPATE PARA SER UTILIZADO NO NOVO NÓ

    return novo;  //RETORNA NÓ CRIADO
}


int EstadoNaLista(Fase *f, Lista *l, Estado *e){  //VERIFICA SE O ESTADO DO JOGO JA FOI ARMAZENADO NA LISTA
    No *atual;

    atual = l->ini;  //PONTEIRO AUXILIAR INICIALIZA COM O ENDEREÇO DO PRIMEIRO VALOR DA LISTA

    while(atual != NULL){  //PERCORRE A LISTA ENQUANTO HOUVEREM NÓS
        if(CompararEstados(f, e, &atual->estado)){  //VERIFICA SE O ESTADO RECEBIDO É IGUAL AO ESTADO ARMAZENADO NO NÓ ATUAL
            return 1;  //INDICA QUE O ESTADO FOI ENCONTRADO E NAO É NECESSARIO PERCORRER MAIS NÓS
        }

        atual = atual->prox;  //AVANÇA PARA O PROXIMO VALOR PARA VERIFICAR O PROXIMO ESTADO, CASO NAO TENHA ENTRADO NO IF
    }

    return 0;  //CASO NAO ENCONTRE ESTADO NA LISTA
}


int Sucesso(Fase *f, Estado *e){  //VERIFICA SE O ESTADO ATUAL REPRESENTA A SOLUÇAO
    int i;

    for(i = 0; i < f->qtd_caixas; i++){  //PERCORRE AS CAIXAS DA FASE
        if(!CaixaNoObjetivo(f, e->caixas[i].linha, e->caixas[i].coluna)){  //CASO A CAIXA NAO ESTEJA SOBRE O OBJETIVO
            return 0;  //SIGNIFICA QUE HÁ PELO MENOS UMA CAIXA QUE NAO ESTA NO OBJETIVO
        }
    }

    return 1;  //CASO TODAS AS CAIXAS ESTEJAM SOBRE OBJETIVOS
}


void NoSucessor(Fase *f, No *ant, int direcao, Lista *aberta, Lista *fechada){
    No *sucessor;
    Estado novoEstado;

    if(VerificarMovimento(f, &ant->estado, direcao)){  //SO CONTINUA SE O MOVIMENTO FOR VALIDO
        if(EstadoSucessor(f, &ant->estado, direcao, &novoEstado)){  //SO CONTINUA SE O NOVO ESTADO FOI CRIADO
            if(!EstadoNaLista(f, fechada, &novoEstado)){  //SO CONTINUA SE O ESTADO AINDA NAO FOI EXPANDIDO
                sucessor = CriarNo(f, &novoEstado, ant);

                if(sucessor != NULL){
                    if(sucessor->h >= INF){  //DEADLOCK: ALGUMA CAIXA NAO CHEGA EM NENHUM OBJETIVO, DESCARTA O NO
                        free(sucessor->estado.caixas);
                        free(sucessor);
                    }
                    else{
                        InserirListaOrdenada(aberta, sucessor);  //NO VALIDO, ENTRA NA LISTA ABERTA ORDENADO POR F
                    }
                }
            }

            LiberarEstado(&novoEstado);  //LIBERA O ESTADO EM TODOS OS CASOS (A CRIARNO JA FEZ UMA COPIA)
        }
    }
}


void ExpandirNo(Fase *f, No *atual, Lista *aberta, Lista *fechada){  //EXPANDE UM NO TENTANDO GERA POSSIVEIS ESTADOS
    int i;

    for(i = 0; i < 4; i++){  //CADA ITERAÇAO REPRESENTA UMA DIREÇAO
        NoSucessor(f, atual, i, aberta, fechada);  //GERA UM NOVO ESTADO A PARTIR DO ATUAL
    }
}


No* AEstrela(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos){  //A PARTIR DO ESTADO INICIAL, EXPLORA OS ESTADOS DE ACORDO COM SUA PRIORIDADE
    No *atual, *ant;  //ATUAL ESTA SENDO EXPLORADO, ANT ARMAZENA O NO DO ESTADO INICIAL

    *expandidos = 0;  //CONTADOR DE NOS EXPANDIDOS INICIA EM 0

    ant = CriarNo(f, inicial, NULL);  //CRIA O PRIMEIRO NO UTILIZANDO O ESTADO INICIAL

    if(ant == NULL){  //VERIFICA SE A CRIAÇAO DEU ERRADO
        return NULL;
    }

    if(ant->h >= INF){  //VERIFICA SE A ESTIMATIVA DA HEURISTICA É INVIAVEL
        free(ant->estado.caixas);  //LIBERA ALOCAÇAO DO VETOR DE CAIXAS
        free(ant);  //LIBERA NO INICIAL
        return NULL;  //ENCERRA A BUSCA PQ ANT NAO PODE SER EXPLORADO
    }

    InserirListaOrdenada(aberta, ant);  //INSERE NO NA LISTA ABERTA, ORGANIZADA POR PRIORIDADE DE CUSTO

    while(!ListaVazia(aberta)){  //CONTINUA ENQUANTO A LISTA ABERTA NAO ESTIVER VAZIA
        atual = RemoverInicio(aberta);  //REMOVE PRIMEIRO NO DA LISTA ABERTA, ARMAZENANDO-O EM ATUAL

        if(EstadoNaLista(f, fechada, &atual->estado)){  //VERIFICA SE O ESTADO DO NO JÁ ESTA NA LISTA FECHADA
            free(atual->estado.caixas);
            free(atual);
        }
        else{
            InserirListaOrdenada(fechada, atual);  //CASO O ESTADO NAO ESTEJA NA LISTA, INSERE NO ATUAL NA LISTA FECHADA. O ESTADO PASSA A SER REGISTRADO COMO EXPLORADO

            if(Sucesso(f, &atual->estado)){  //VERIFICA SE O ESTADO REPRESENTA SOLUÇAO
                return atual;  //RETORNA NO QUE REPRESENTA SOLUÇAO
            }

            (*expandidos)++;  //AUMENTA A QUANTIDADE DE NOS EXPANDIDOS
            ExpandirNo(f, atual, aberta, fechada);  //NECESSARIO GERAR POSSIVEIS SUCESSORES CASO A SOLUÇAO AINDA NAO TENHA SIDO ENCONTRADA
        }
    }

    return NULL;  //CASO A LISTA FIQUE VAZIA, INDICA QUE A* NAO ENCONTROU CAMINHO PARA RESOLUÇAO DA FASE
}


void ImprimirMapa(Fase *f, Estado *e){  //IMPRIME O MAPA UTILIZANDO SIMBOLOS UNICODE ESCOLHIDOS
    int i, j, jogador, caixa, objetivo;  //JOGADOR, CAIXA E OBJETIVOS FICAM ARMAZENADOS EM VETORES SEPARADOS DO MAPA, PORTANTO É IMPORTANTE VERIFICAR POSICOES

    for(i = 0; i < f->linhas; i++){
        for(j = 0; j < f->colunas; j++){
            jogador = (e->jogador.linha == i && e->jogador.coluna == j);  //VERIFICA SE O JOGADOR ESTA NA POSICAO ATUAL DA MATRIZ
            caixa = (EncontrarCaixa(f, e, i, j) != -1);  //VERIFICA A EXISTENCIA DE CAIXA NA POSICAO ATUAL
            objetivo = CaixaNoObjetivo(f, i, j);  //VERIFICA SE A POSICAO CORRESPONDE A UM OBJETIVO

            if(jogador && objetivo){
                printf("\u263B ");  //JOGADOR SOBRE O OBJETIVO
            }
            else{
                if(jogador){
                    printf("\u263A ");  //JOGADOR
                }
                else{
                    if(caixa && objetivo){
                        printf("\u2605 ");  //CAIXA SOBRE O OBJETIVO
                    }
                    else{
                        if(caixa){
                            printf("\u2612 ");  //CAIXA
                        }
                        else{
                            if(f->mapa[i][j] == 1){
                                printf("# ");  //PAREDE
                            }
                            else{
                                if(objetivo){
                                    printf("\u25CB ");  //OBJETIVO VAZIO
                                }
                                else{
                                    printf("  ");  //CHAO VAZIO
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("\n");  //FIM DE UMA LINHA DO MAPA
    }

    printf("\n");
}


No *ResolveFase(Fase *f, Estado *inicial, Lista *aberta, Lista *fechada, int *expandidos){  //RESOLVE A FASE EM ETAPAS: ALOCA E CALCULA A TABELA DE DISTANCIAS USADA PELA HEURISTICA E DEPOIS EXECUTA O A*
    No *solucao;  //ARMAZENA O RESULTADO RETORNADO PELO A*
    if(!CriaDistancia(f)){  //VERIFICA SE FOI POSSIVEL OU NAO REALIZAR AS AÇOES DA FUNCAO, CASO NAO, RETORNA NULO
        return NULL;
    }

    Distancias(f);  //INICIALIZA TODAS AS DISTANCIAS DA FASE COM INF (AINDA NAO CALCULADAS)

    if(!PercorrerDistanciaObjetivos(f)){  //CALCULA AS DISTANCIAS DE EMPURROES A PARTIR DE CADA OBJETIVO (BFS REVERSA). SE FALHAR, RETORNA NULO
        return NULL;
    }

    solucao = AEstrela(f, inicial, aberta, fechada, expandidos);  //O RESULTADO DO A* É ARMAZENADO EM SOLUCAO, SE ENCONTRAR UMA SOLUCAO, O PONTEIRO APONTA PARA O NO FINAL (ESTADO SOLUCAO); CASO CONTRARIO, RECEBE NULO
    return solucao;
}


void AnimarMapaSolucao(Fase *f, No *no, int nivel, int numeroFase, int velocidadeMs){  //ANIMA A SOLUCAO, FAZ O BONECO SE MOVIMENTAR E MOVIMENTAR AS CAIXAS
    //USO DE RECURSAO PARA PERCORRER NOS ANTERIORES A SOLUÇAO E ANIMAR O MAPA. O CAMINHO É RECONSTRUIDO VISUALMENTE
    if(no != NULL){  //SE O PONTEIRO NAO FOR NULO, ELA ANIMA. CONDICAO DE PARADA DA RECURSIVIDADE.
        AnimarMapaSolucao(f, no->anterior, nivel, numeroFase, velocidadeMs);  //PERCORRE OS NOS DE TRAS PARA FRENTE, OU SEJA, DA SOLUCAO AO ESTADO INICIAL E PARA QUANDO CHEGA NO ESTADO INICIAL
        system("cls");  //FAZ O PRINT DE UM ESTADO DE CADA VEZ, DANDO EFEITO DE MOVIMENTAÇAO
        printf("\nNIVEL %d - FASE %02d \n\n", nivel, numeroFase);  //MOSTRA QUAL NIVEL E FASE ESTAO SENDO EXECUTADOS
        ImprimirMapa(f, &no->estado);  //EXIBE O ESTADO ATUAL, AGORA PARTINDO DO INICIO EM DIRECAO A SOLUÇAO
        Sleep(velocidadeMs);  //TEMPO EM QUE CADA ESTADO APARECE NA TELA (EM MILIS)

    }
}



//FUNCOES RELACIONADAS A MAIN E RESULTADO FINAL
void ImprimirTabelaResultados(ResultadoTabela r[], int qtdFases){  //APRESENTA A TABELA COMPARATIVA DAS FASES DO NIVEL EXECUTADO, APOS SUA EXECUÇAO. R ARMAZENA OS RESULTADOS E QTDFASES INFORMA QUANTAS POSICOES TERA O VETOR
    int i;

    printf("\n------------------- TABELA COMPARATIVA: RESULTADOS ALGORITMO A* -------------------");  //IMPRESSAO DO CABECALHO DA TABELA
    printf("\n Fase | Dificuldade | Caixas | Tempo (ms) | Nos Expandidos | Profundidade | Custo |");
    printf("\n------+-------------+--------+------------+----------------+--------------+-------+");

    for(i = 0; i < qtdFases; i++){  //PERCORRE AS POSICOES DO VETOR DE ACORDO COM A QUANTIDADE DE FASES DO NIVEL
        printf("\n %02d   |", i + 1);

        switch(r[i].dificuldade){  //VERIFICA O VALOR ARMAZENADO EM DIFICULDADE
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

        if(r[i].faseConcluida){  //SE A FASE FOR CONCLUIDA COM SUCESSO, EXIBE AS INFORMAÇOES
            printf(" %12d | %5d |", r[i].profundidade, r[i].custo);
        }

        else{
            printf(" Sem solucao  |     - |");
        }
    }

    printf("\n------+-------------+--------+------------+----------------+--------------+-------+\n");
}


int CarregarFaseFacil(int numeroFase, Fase *f, Estado *e){  //PREPARA OS MAPAS DO NIVEL FACIL, CAIXAS, OBJETIVOS E JOGADOR
    switch(numeroFase){  //EXECUTA CADA CASE CONFORME O VALOR DA VARIAVEL NUMEROFASE
        case 1:{
           int mapa[6][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 1, 1},
                {1, 0, 0, 1, 1, 1},
                {1, 1, 0, 1, 1, 1},
                {1, 1, 1, 1, 1, 1}
            };

            Posicao objetivos[2] = {{1, 1}, {2, 3}};  //VETOR DE POSICAO DOS OBJETIVOS
            Posicao caixas[2] = {{2, 1}, {3, 2}};  //VETOR DE POSICAO DAS CAIXAS
            Posicao jogador = {4, 2};  //POSICAO DO JOGADOR

            if(!CriarFase(f, 6, 6, 2) || !CriarEstado(e, 2)){  //VERIFICA SE A CRIACAO DEU ERRADO, CASO UMA DAS OPERACOES FALHE, RETORNA 0
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);  //INICIALIZA A FASE PREENCHENDO OS VALORES NO MAPA
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

            Posicao objetivos[2] = {{1, 2}, {3, 4}};  //VETOR DE POSICAO DOS OBJETIVOS
            Posicao caixas[2] = {{2, 3}, {3, 3}};  //VETOR DE POSICAO DAS CAIXAS
            Posicao jogador = {3, 2};  //POSICAO DO JOGADOR

            if(!CriarFase(f, 6, 6, 2) || !CriarEstado(e, 2)){  //VERIFICA SE A CRIACAO DEU ERRADO, CASO UMA DAS OPERACOES FALHE, RETORNA 0
                return 0;
            }

            InicializarFase(f, e, mapa, objetivos, caixas, jogador);  //INICIALIZA A FASE PREENCHENDO OS VALORES NO MAPA
            break;
        }

        default:
            return 0;  //FASE INEXISTENTE
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


int CarregarFase(int nivel, int numeroFase, Fase *f, Estado *e){  //RECEBE O NIVEL DE DIFICULDADE ESCOLHIDO PELO USUARIO NA MAIN, COM ISSO, EXECUTA O CASE
    switch(nivel){
        case 1:
            return CarregarFaseFacil(numeroFase, f, e);  //CARREGA AS FASES DO NIVEL DE DIFICULDADE ESCOLHIDO

        case 2:
            return CarregarFaseMedio(numeroFase, f, e);

        case 3:
            return CarregarFaseDificil(numeroFase, f, e);

        default:
            return 0;
    }
}


void LimparBuffer(){  //LIMPEZA DE BUFFER: DESCARTA OS CARACTERES QUE SOBRARAM NA ENTRADA ATE O ENTER OU O FIM DA ENTRADA (EOF). USADA APOS O SCANF, PRINCIPALMENTE QUANDO O USUARIO DIGITA LETRAS EM VEZ DE NUMEROS
    int c;

    do{
        c = getchar();
    }while(c != '\n' && c != EOF);
}


void ExecutarNivel(int nivel, int velocidadeMs){  //PROCESSO DE RESOLUCAO DE CADA FASE DENTRO DO NIVEL DE DIFICULDADE
    int i;  //CONTROLA O LACO PARA PERCORRER AS FASES
    int numeroFase;  //NUMERO DA FASE EXECUTADA
    int expandidos;  //NOS EXPANDIDOS PELO ALGORITMO
    Lista *aberta, *fechada;  //LISTAS QUE ARMAZENAM OS NOS
    No *solucao;  //ARMAZENA O RESULTADO QUE SERA RETORNADO PELA FUNCAO RESOLVERFASE
    ResultadoTabela resultados[QTD_FASES] = {0};  //CADA POSICAO DO VETOR ARMAZENA O RESULTADO DE UMA FASE
    LARGE_INTEGER frequencia, inicio, fim;  //CONTADORES DE ALTA PRECISAO DO WINDOWS (LARGE_INTEGER) PARA DETERMINAR O TEMPO DE EXECUCAO DO ALGORITMO

    QueryPerformanceFrequency(&frequencia);

    for(i = 0; i < QTD_FASES; i++){  //PERCORRE TODAS AS FASES
        Fase fase = {0};
        Estado inicial = {0};  //ARMAZENA O ESTADO INICIAL DO JOGO

        numeroFase = i + 1;  //CASE NAO INICIA EM 0, NECESSARIO SOMAR 1 PARA EXECUTAR CADA FASE
        resultados[i].dificuldade = nivel;  //PREENCHE O NIVEL DE DIFICULDADE

        aberta = CriarLista();
        fechada = CriarLista();

        if(aberta == NULL || fechada == NULL || !CarregarFase(nivel, numeroFase, &fase, &inicial)){  //VERIFICAÇAO DE ERROS DURANTE A PREPARACAO DA FASE
            resultados[i].faseConcluida = 0;
            printf("\nErro ao carregar a fase %02d", numeroFase);
        }

        else{  //BLOCO EXECUTADO QUANDO A CRIAÇAO DE LISTAS E PREPARACAO OCORREM BEM
            system("cls");
            printf("\nNIVEL %d - FASE %02d \n\n", nivel, numeroFase);  //EXIBE O NIVEL E FASE QUE ESTAMOS EXECUTANDO
            ImprimirMapa(&fase, &inicial);  //APRESENTA O ESTADO INICIAL NA TELA

            resultados[i].caixas = fase.qtd_caixas;  //ARMAZENA A QUANTIDADE DE CAIXAS NA FASE

            expandidos = 0;  //INICIA O CONTADOR DE NOS
            QueryPerformanceCounter(&inicio);  //INICIO DA CONTAGEM DE MILIS DE RESOLUCAO
            solucao = ResolveFase(&fase, &inicial, aberta, fechada, &expandidos); //RESOLVE A FASE
            QueryPerformanceCounter(&fim);  //FIM DA CONTAGEM

            resultados[i].tempoMs = (float)((fim.QuadPart - inicio.QuadPart) * 1000.0) / (float)frequencia.QuadPart;  //CALCULO DO TEMPO DE EXECUCAO EM MS (DIFERENCA DE CONTAGENS DIVIDIDA PELA FREQUENCIA = SEGUNDOS; 1000 = CONVERSAO PARA MILISSEGUNDOS)
            resultados[i].nos_expandidos = expandidos;  //ARMAZENA A QUANTIDADE DE NOS EXPANDIDOS

            if(solucao == NULL){  //VERIFICA SE O ALGORITMO ENCONTROU SOLUCAO
                resultados[i].faseConcluida = 0;
                printf("\nNenhuma solucao encontrada pelo algoritmo A-Estrela na fase %02d", numeroFase);
            }

            else{
                resultados[i].faseConcluida = 1;  //FASE CONCLUIDA
                resultados[i].profundidade = solucao->g;  //PROFUNDIDADE DA SOLUCAO (G = CUSTO ACUMULADO)
                resultados[i].custo = solucao->g;
                AnimarMapaSolucao(&fase, solucao, nivel, numeroFase, velocidadeMs);  //ANIMA ANTES DE LIBERAR AS LISTAS, POIS A SOLUCAO ESTA NA FECHADA
                printf("\nSolucao encontrada! A fase foi resolvida!");
                printf("\nMovimentos: %d | Nos expandidos: %d", solucao->g, expandidos);
            }
        }

        if(aberta != NULL){  //SO LIBERA O QUE FOI CRIADO
            LiberarLista(aberta);
        }

        if(fechada != NULL){
            LiberarLista(fechada);
        }

        LiberarFase(&fase);  //A FASE E LIBERADA ANTES DE CARREGAR A PROXIMA: SO UMA FASE NA MEMORIA POR VEZ
        LiberarEstado(&inicial);  //LIBERA O ESTADO INICIAL, INCLUINDO OS VETORES DE POSICAO, ANTES DA EXECUCAO DA PROXIMA FASE

        if(i < QTD_FASES - 1){
            printf("\n\nPressione uma tecla para resolver a proxima fase");
        }

        else{
            printf("\n\nFim da resolucao das fases do nivel!");
            printf("\nPressione uma tecla para visualizar a tabela de resultados");
        }

        getch();  //AGUARDA O USUARIO PRESSIONAR UMA TECLA PARA EXIBIR A PROXIMA RESOLUCAO
    }

    system("cls");
    ImprimirTabelaResultados(resultados, QTD_FASES);  //EXIBICAO DA TABELA DE RESULTADOS APOS A EXECUCAO DE TODAS AS FASES
    printf("\nPressione uma tecla para voltar ao menu");
    getch();
}

#endif // LISTA_RESOLUCAO_SOKOBAN_COMENTADA_H_INCLUDED
