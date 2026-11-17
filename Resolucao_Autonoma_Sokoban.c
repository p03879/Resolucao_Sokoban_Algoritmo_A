#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lista.h"

#define FASES 5

int main(){
    setlocale(LC_ALL, "portuguese");

    int i;
    int alocacaoConcluida = 1;

    Fase fases[FASES] = {0};
    Estado estadosIniciais[FASES] = {0};

    int l[FASES] = {6, 7, 9, 11, 12};
    int c[FASES] = {6, 7, 9, 11, 12};
    int quantidadeCaixas[FASES] = {2, 2, 2, 3, 3};

    for(i = 0; i < FASES && alocacaoConcluida; i++){
        if(!CriarFase(&fases[i], l[i], c[i], quantidadeCaixas[i])){
            printf("\nErro na alocação de memória da fase %02d" , i+1);
            alocacaoConcluida = 0;
        }

        else{
            if(!CriarEstado(&estadosIniciais[i], quantidadeCaixas[i])){
                printf("\nErro na alocação de memória do estado %02d" , i+1);
                alocacaoConcluida = 0;
            }
        }
    }

    if(alocacaoConcluida){
        printf("\nMemória alocada com sucesso");


        int mapa1[6][6] = {
            {1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 0, 1},
            {1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1}
        };

        Posicao objetivos1[2] = {{1, 2}, {3, 4}};
        Posicao caixas1[2] = {{2, 3}, {3, 3}};
        Posicao jogador1 = {3, 2};

        InicializarFase(&fases[0], &estadosIniciais[0], mapa1, objetivos1, caixas1, jogador1);


        int mapa2[7][7] = {
            {1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 0, 1, 1},
            {1, 1, 0, 0, 0, 1, 1},
            {1, 1, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1}
        };

        Posicao objetivos2[2] = {{1 ,2}, {3,5}};
        Posicao caixas2[2] = {{1, 3}, {4, 3}};
        Posicao jogador2 = {5 , 1};

        InicializarFase(&fases[1], &estadosIniciais[1], mapa2, objetivos2, caixas2, jogador2);


        int mapa3[9][9] = {
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

        Posicao objetivos3[2] = {{1,4}, {7,7}};
        Posicao caixas3[2] = {{3, 2}, {4, 6}};
        Posicao jogador3= {6, 2};

        InicializarFase(&fases[2], &estadosIniciais[2], mapa3, objetivos3, caixas3, jogador3);


        int mapa4[11][11] = {
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

        Posicao objetivos4[3] = {{8, 1}, {5, 9}, {2, 8}};
        Posicao caixas4[3] = {{4, 1}, {7,6}, {2, 4}};
        Posicao jogador4 = {3, 1};

        InicializarFase(&fases[3], &estadosIniciais[3], mapa4, objetivos4, caixas4, jogador4);


        int mapa5[12][12] = {

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
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        Posicao objetivos5[3] = {{1, 9}, {5, 1}, {10, 7}};
        Posicao caixas5[3] = {{4, 9}, {2, 2}, {7, 4}};
        Posicao jogador5 = {5, 7};

        InicializarFase(&fases[4], &estadosIniciais[4], mapa5, objetivos5, caixas5, jogador5);
    }

    for(i = 0; i < FASES; i++){
        LiberarFase(&fases[i]);
        LiberarEstado(&estadosIniciais[i]);
    }

    return 0;
}
