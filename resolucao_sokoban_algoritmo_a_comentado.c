#include <stdio.h>  //ENTRADA E SAIDA DE DADOS (PRINTF E SCANF)
#include <stdlib.h>  //FUNCAO SYSTEM, UTILIZADA PARA LIMPAR A TELA E PAUSAR O PROGRAMA
#include <windows.h>  //CONFIGURACAO DO CONSOLE EM UTF-8, SLEEP E CONTADORES DE TEMPO
#include <conio.h>  //FUNCAO GETCH, QUE AGUARDA O USUARIO PRESSIONAR UMA TECLA
#include "lista_resolucao_sokoban_comentada.h"  //BIBLIOTECA DO PROJETO: ESTRUTURAS, FASES, HEURISTICA E ALGORITMO A*

int main(){
    SetConsoleOutputCP(CP_UTF8);  //CONFIGURA A SAIDA DO CONSOLE EM UTF-8 PARA EXIBIR OS SIMBOLOS UNICODE DO MAPA
    SetConsoleCP(CP_UTF8);  //CONFIGURA A ENTRADA DO CONSOLE EM UTF-8

    int nivel;  //NIVEL DE DIFICULDADE ESCOLHIDO PELO USUARIO (1 FACIL, 2 MEDIO, 3 DIFICIL, 0 ENCERRA)
    int velocidadeMs = 400;  //TEMPO, EM MILISSEGUNDOS, QUE CADA PASSO DA ANIMACAO DA SOLUCAO PERMANECE NA TELA

    system("cls");  //LIMPA A TELA ANTES DE EXIBIR A APRESENTACAO
    printf("\n-----------------------------------------------------------------------");  //CABECALHO DO PROGRAMA
    printf("\n               RESOLUCAO AUTONOMA - SOKOBAN (RACHA-CUCA)               ");
    printf("\n-----------------------------------------------------------------------");
    printf("\nSokoban eh um jogo de logica no qual o jogador deve movimentar caixas \npor todo o mapa ate posiciona-las sobre seus objetivos.");  //APRESENTACAO DO JOGO E DE SUAS REGRAS
    printf("\nTendo isso em vista, eh necessario que o jogador planeje suas jogadas, \npois as caixas so podem ser empurradas e nao podem atravessar \nparedes.");
    printf("\n\nO programa utiliza o algoritmo de busca A-Estrela para encontrar solucao \npara --- fases do jogo, com diferentes niveis de dificuldade.");  //APRESENTACAO DO FUNCIONAMENTO DO PROGRAMA
    printf("\nCada fase possui um mapa com diferentes dimensoes e quantidade de caixas.");
    printf("\nO algoritmo analisa os movimentos possiveis para o personagem e situacoes \nque nao levam a nenhuma solucao, com isso, ira gerar \nnovas possibilidades de movimentos utilizando uma funcao heuristica \npara chegar a solucao.");
    printf("\nApos a resolucao de todas as fases do nivel escolhido o programa apresenta \numa tabela comparativa, analisando o desempenho do algoritmo durante \nsua execucao em -- cenarios diferentes.");
    printf("\n\nVamos comecar?\n");
    system("pause");  //AGUARDA O USUARIO PRESSIONAR UMA TECLA PARA ABRIR O MENU


    do{  //REPETE O MENU ATE O USUARIO ESCOLHER A OPCAO 0 (ENCERRAR)
        do{  //REPETE A EXIBICAO DO MENU ENQUANTO A OPCAO DIGITADA FOR INVALIDA
            system("cls");  //LIMPA A TELA ANTES DE EXIBIR O MENU
            printf("\n-----------------------------------------------------------------------");
            printf("\n               RESOLUCAO AUTONOMA - SOKOBAN (RACHA-CUCA)               ");
            printf("\n-----------------------------------------------------------------------");
            printf("\n\nEscolha o nivel que deseja executar ");  //OPCOES DO MENU
            printf("\n 1 - Facil");
            printf("\n 2 - Medio");
            printf("\n 3 - Dificil");
            printf("\n 0 - Encerrar");
            printf("\nQual opcao deseja selecionar?: ");

            while(scanf("%d", &nivel) != 1){  //SCANF RETORNA 1 QUANDO CONSEGUE LER UM NUMERO. SE O USUARIO DIGITAR LETRAS, A LEITURA FALHA E O NUMERO E PEDIDO NOVAMENTE
                LimparBuffer();  //DESCARTA OS CARACTERES INVALIDOS QUE FICARAM NA ENTRADA, EVITANDO LACO INFINITO
                printf("\nERRO");
                printf("\nSomente numeros sao permitidos");
                printf("\nQual nivel deseja executar?: ");
            }

            LimparBuffer();  //DESCARTA O ENTER E QUALQUER CARACTERE QUE SOBROU APOS O NUMERO LIDO

            if(nivel < 0 || nivel > 3){  //VERIFICA SE O NUMERO DIGITADO ESTA FORA DAS OPCOES DO MENU
                printf("\nOpcao invalida.\n");
                system("pause");  //AGUARDA O USUARIO PRESSIONAR UMA TECLA ANTES DE EXIBIR O MENU NOVAMENTE

            }

        }while(nivel < 0 || nivel > 3);  //SO SAI DO LACO QUANDO A OPCAO FOR VALIDA


        switch(nivel){  //EXECUTA A OPCAO ESCOLHIDA PELO USUARIO
            case 1:
                ExecutarNivel(nivel, velocidadeMs);  //CARREGA, RESOLVE E ANIMA AS FASES DO NIVEL FACIL E EXIBE A TABELA DE RESULTADOS
                break;

            case 2:
                ExecutarNivel(nivel, velocidadeMs);  //CARREGA, RESOLVE E ANIMA AS FASES DO NIVEL MEDIO E EXIBE A TABELA DE RESULTADOS
                break;

            case 3:
                ExecutarNivel(nivel, velocidadeMs);  //CARREGA, RESOLVE E ANIMA AS FASES DO NIVEL DIFICIL E EXIBE A TABELA DE RESULTADOS
                break;

            case 0:
                printf("\nPrograma encerrado.");  //MENSAGEM DE ENCERRAMENTO
                break;
        }
    }while(nivel != 0);  //APOS CADA NIVEL, VOLTA AO MENU ATE O USUARIO DIGITAR 0

    return 0;  //FIM DO PROGRAMA
}
