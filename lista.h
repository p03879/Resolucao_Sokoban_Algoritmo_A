#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define CIMA 0
#define BAIXO 1
#define ESQ 2
#define DIR 3
#define INF 10000



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
    int **distancias;
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




//FUNÇÕES RELACIONADAS A CONFIGURAÇÃO DO MAPA, CONFERENCIAS...
int CriarFase(Fase *f, int linhas, int colunas, int qtd_caixas){  //RESERVA MEMORIA PARA O MAPA, OBJETIVOS E DISTANCIAS
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


void LiberarFase(Fase *f){  //LIBERA MEMORIA ALOCADA PARA CRIACAO DA FASE, EVITANDO DISPERDICIO
    int i;

    if(f->mapa != NULL){  //PERCORRE TODAS AS LINHAS DO MAPA, ENQUANTO NAO FOR NULO, E LIBERA CADA UMA
        for(i = 0; i < f->linhas; i++){
            free(f->mapa[i]);
        }

        free(f->mapa);
    }

    if(f->distancias != NULL){  //DISTANCIAS USADAS PELO A*, SAO ESTIMATIVAS DE DESLOCAMENTO DA CAIXA AO OBJETIVO
        for(i = 0; i < f->qtd_caixas * f->linhas; i++){  //LIBERA ESTIMATIVAS DE DISTANCIA
            free(f->distancias[i]);
        }

        free(f->distancias);
    }

    free(f->objetivos);  //LIBERA A MEMORIA RESERVADA PARA ARMAZENAR AS POSICOES DE CADA OBJETIVO
}


void LiberarEstado(Estado *e){  //LIBERA A MEMORIA ALOCADA PARA A QUANTIDADE DE CAIXAS DE CADA FASE
    free(e->caixas);
}


void CriarMapa(Fase *f, int mapa[f->linhas][f->colunas]){  //COPIA OS VALORES DA MATRIZ RECEBIDA (FASE) E FAZ A ALOCACAO
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
            return 0;  //RETORNA 0 CASO A FUNCAO RECEBA UMA DIRECAO QUE NAO EXISTE ////////////////////////////////////////////////////////////////////////////////////////
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


    if(linhaCaixa < 0 || linhaCaixa >= f->linhas ||colunaCaixa < 0 || colunaCaixa >= f->colunas || EncontrarCaixa(f, e, linhaCaixa, colunaCaixa) != -1 || f->mapa[linhaCaixa][colunaCaixa] == 1){  //VERIFICA SE A POSICAO PARA ANDAR É VALIDA
        return 0;  //CASO ALGUMA CONDICAO NAO PERMITA QUE A POSICAO SEJA VALIDA
    }

    return 1;  //TUDO CERTO NA VERIFICACAO
}


int EstadoSucessor(Fase *f, Estado *atual, int direcao, Estado *novo){  //GERA AS POSSIBILIDADE DE ESTADOS PARA O ALGORITMO A*: CRIA UM NOVO ESTADO A PARTIR DO ATUAL
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
            free(novo->caixas)_; /////////////////////////////////////////////////////////////////////////////////////////
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
    int i;

    f->distancias = calloc(f->qtd_caixas * f->linhas,sizeof(int *));  //ALOCA AS LINHAS DA MATRIZ DE DISTANCIAS QUE SERA UTILIZADA PELA HEURISTICA. ELA IRA ARMAZENAR INFORMAÇOES SOBRE A DISTANCIA DAS CAIXAS

    if(f->distancias == NULL) {
        return 0;  //ALOCACAO DEU ERRADO
    }

    for(i = 0; i < f->qtd_caixas * f->linhas; i++) {
        f->distancias[i] = malloc(f->colunas * sizeof(int));  //ALOCA AS COLUNAS

        if(f->distancias[i] == NULL) {  //LIBERA TODAS AS LINHAS CASO A ALOCAÇÃO FALHE

            while(i > 0) {
                i--;
                free(f->distancias[i]);
            }

            free(f->distancias);
            f->distancias = NULL;

            return 0;
        }
    }

    return 1;
}


void Distancias(Fase *f) {
    int i, j;

    for(i = 0; i < f->qtd_caixas * f->linhas; i++) {
        for(j = 0; j < f->colunas; j++) {
            f->distancias[i][j] = INF;  //ATRIBUIMOS UMA DISTANCIA DESCONHECIDA, POIS AS POSICOES DAS CAIXAS AINDA NAO TIVERAM SUAS DISTANCIAS CALCULADAS.
        }
    }
}


void Deslocamento(int direcao, int *dl, int *dc) {  //RECEBE UMA DIRECAO E TRANSFORMA EM DESOLCAMENTO
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


Fila* CriarFila(){  //ALOCA A FILA DINAMICAMENTE. ESSA FILA SERA UTILIZADA PARA REALIZAÇAO DE UMA BFS ANTES DO ALGORITMO SER IMPLEMENTADO. ELA IRA AJUDAR A CALCULAR QUAL O NUMERO MINIMO DE EMPURROES UMA CAIXA PRECISA PARA CHEGAR NO OBJETIVO, PARTINDO DO PROPRIO OBJETIVO
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
        exit(1);
    }

    novo->posicao = p;  //ARMAZENA POSICAO RECEBIDA
    novo->prox = NULL;  //PROXIMO ELEMENTO SERA O ULTIMO DA FILA, PORTANTO DEVE SER NULO

    if(fila->fim == NULL){  //VERIFICA SE A FILA ESTA VAZIA
        fila->inicio = novo;  //INSERE NO INICIO DA FILA
    }
    else{  //SE A FILA ESTIVER CHEIA
        fila->fim->prox = novo;  //INSERE NO FINAL
    }

    fila->fim = novo;  //ATUALLIZA PONTEIRO PARA APONTAR PARA ULTIMO NO

    return 1;  //FUNCAO REALIZADA
}


Posicao RetirarFila(Fila *fila){  //REMOVE POSICAO DA FILA
    NoFila *aux;
    Posicao p;

    aux = fila->inicio;  //ARMAZENA ENDEREÇO DO PRIMEIRO NO NA VAIRAVEL AUXILIAR
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


int CalculoDistanciaObjetivos(Fase *f, int i, Fila *fila){  //CALCULA AS DISTANCIA A PARITR DE OBJETIVO ESPECIFICO, CONSIDERAND MOVIMENTOS PARA CAIXA CHEGAR ATE LA. I INDICA QUAL OBJETIVO ESTA SENDO UTILIZADO COMO REFERNCIA PARA O CALCULO
    int j, l, c;  //J CONDIZ COM AS DIRECOES DE MOVIMENTACAO. L E C SAO LINHA E COLUNA
    int dl, dc;  //DESLOCAMENTO NA LINHA E NA COLUNA
    int caixaL, caixaC;
    int jogadorL, jogadorC;
    int **dist;  //PONTEIRO PARA ACESSAR A MATRIZ DE DISTANCIAS QUE CORRESPONDE AO OBJETIVO ATUAL
    Posicao atual;

    dist = &f->distancias[i * f->linhas];  //IRA CALCULAR O INDICE DA PRIMEIRA LINHA NA MATRIZ DE DISTANCIAS QUE CORRESPONDE AO OBJETIVO I, OU SEJA, A PARTIR DE QUAL LINHA NA MATRIZ DE DISTANCIAS ENCONTRAMOS O OBJETIVO I

    l = f->objetivos[i].linha;  //LINHA DO OBJETIVO
    c = f->objetivos[i].coluna;  //COLUNA DO OBJETIVO

    if(!LimiteMapa(f, l, c) || f->mapa[l][c] == 1){  //VERIFICA SE A POSICAO DO OBJETIVO É VALIDA
        return 0;
    }

    dist[l][c] = 0;  //BUSCA COMEÇA NO OBJETIVO E VAI EM DIRECAO AS CAIXAS, PORTANTO, A DISTANCIA DO OBJETIVO ATE ELE MESMO É 0

    atual.linha = l;  //INICIO DA BUSCA
    atual.coluna = c;

    InserirFila(fila, atual);  //INSERE A POSICAO DO OBJETIVO NA FILA

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

                InserirFila(fila, atual);  //INSERE NOVA POSICAO NA FILA PARA CONTINUAR EXPLORANDO
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


int AssociarCaixasObjetivos(Fase *f, Estado *e, int caixa, int associados[]){  //ASSOCIA CADA CAIXA A TODOS OS OBJETIVOS PARA DEPOIIS VERIFICAR QUAL O MAIS PROXIMO. ASSOCIADOS[] GUARDA OS OBJETIVOS JA UTILIZADOS NA COMBINACAO COM A CAIXA
    int custo, menor_custo, obj_teste;
    int linha;

    if(caixa == f->qtd_caixas){  //CONDICAO DE PARADA DA FUNCAO RECURSIVA
        return 0;
    }

    menor_custo = INF;  //INICIA COM VALOR DESCONHECIDO

    for(obj_teste = 0; obj_teste < f->qtd_caixas; obj_teste++){ //PERCORRE TODOS OS OBJETIVOS DA FASE
        if(associados[obj_teste] == 0){  //VERIFICA SE O OBJETIVO JA FOI ASSOCIADO, CASO NAO
            associados[obj_teste] = 1; //ASSOCIA A CAIXA AO OBJETIVO

            linha = (obj_teste * f->linhas) + e->caixas[caixa].linha;  //CALCULA A LINHA NA MATRIZ DE DISTANCIAS. OBJ_TESTE * F->LINHAS CORRESPONDE AO OBJETIVO ANALISADO, OU SEJA, A LINHA DELE NA MATRIZ DE DISTANCIAS. EM SEGUIDA, IREMOS OBTER A LINHA DA CAIXA. O RESULTADO SERA A LINHA ACESSADA NA MATRIZ DE DISTANCIAS
            custo = f->distancias[linha][e->caixas[caixa].coluna]+ AssociarCaixasObjetivos(f, e, caixa + 1, associados);  //ANTES DA RECURSAO: ACESSA A MATRIZ DE DISTANCIAS E OBTEM O CUSTO P LEVAR A CAIXA AO OBJETIVO, REPRESENTANDO O MINIMO DE MOVIMENTOS. APOS RECURSAO: ANALISA A PROXIMA CAIXA E SOMA O CUSTO

            associados[obj_teste] = 0;  //NECESSARIO LIBERAR OBJETIVO PARA ANALISE DA PROXIMA CAIXA. BACKTRACKING. EXPERIMENTA UMA POSSIBILIDADE, LIBERA E TESTA OUTRA

            if(custo < menor_custo){  //ATUALIZA MENOR CUSTO COM O MENOR VALOR
                menor_custo = custo;
            }
        }
    }

    return menor_custo;
}
#endif // LISTA_H_INCLUDED
