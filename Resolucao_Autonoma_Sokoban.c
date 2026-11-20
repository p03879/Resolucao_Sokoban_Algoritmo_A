#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "lista.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int nivel;
    int velocidadeMs = 400;

    system("cls");
    printf("\n-----------------------------------------------------------------------");
    printf("\n               RESOLUCAO AUTONOMA - SOKOBAN (RACHA-CUCA)               ");
    printf("\n-----------------------------------------------------------------------");
    printf("\nSokoban eh um jogo de logica no qual o jogador deve movimentar caixas \npor todo o mapa ate posiciona-las sobre seus objetivos.");
    printf("\nTendo isso em vista, eh necessario que o jogador planeje suas jogadas, \npois as caixas so podem ser empurradas e nao podem atravessar \nparedes.");
    printf("\n\nO programa utiliza o algoritmo de busca A-Estrela para encontrar solucao \npara --- fases do jogo, com diferentes niveis de dificuldade.");
    printf("\nCada fase possui um mapa com diferentes dimensoes e quantidade de caixas.");
    printf("\nO algoritmo analisa os movimentos possiveis para o personagem e situacoes \nque nao levam a nenhuma solucao, com isso, ira gerar \nnovas possibilidades de movimentos utilizando uma funcao heuristica \npara chegar a solucao.");
    printf("\nApos a resolucao de todas as fases do nivel escolhido o programa apresenta \numa tabela comparativa, analisando o desempenho do algoritmo durante \nsua execucao em -- cenarios diferentes.");
    printf("\n\nVamos comecar?\n");
    system("pause");


    do{
        do{
            system("cls");
            printf("\n-----------------------------------------------------------------------");
            printf("\n               RESOLUCAO AUTONOMA - SOKOBAN (RACHA-CUCA)               ");
            printf("\n-----------------------------------------------------------------------");
            printf("\n\nEscolha o nivel que deseja executar ");
            printf("\n 1 - Facil");
            printf("\n 2 - Medio");
            printf("\n 3 - Dificil");
            printf("\n 0 - Encerrar");
            printf("\nQual opcao deseja selecionar?: ");

            while(scanf("%d", &nivel) != 1){
                LimparBuffer();
                printf("\nERRO");
                printf("\nSomente numeros sao permitidos");
                printf("\nQual nivel deseja executar?: ");
            }

            LimparBuffer();

            if(nivel < 0 || nivel > 3){
                printf("\nOpcao invalida.\n");
                system("pause");

            }

        }while(nivel < 0 || nivel > 3);


        switch(nivel){
            case 1:
                ExecutarNivel(nivel, velocidadeMs);
                break;

            case 2:
                ExecutarNivel(nivel, velocidadeMs);
                break;

            case 3:
                ExecutarNivel(nivel, velocidadeMs);
                break;

            case 0:
                printf("\nPrograma encerrado.");
                break;
        }
    }while(nivel != 0);

    return 0;
}
