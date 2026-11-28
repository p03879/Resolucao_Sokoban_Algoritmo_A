# Resolucao_Sokoban_Algoritmo_A

DESCRIÇÃO

Sistema desenvolvido em linguagem C  que resolve fases do jogo Sokoban de maneira autônoma, usando o algoritmo de busca A*. O jogador precisa empurrar todas as caixas até os objetivos. Ele só pode empurrar e não consegue mover duas caixas de uma vez. Se uma caixa ficar presa em um canto (deadlock), a fase deixa de ter solução.


OBJETIVOS 

- Resolver automaticamente 6 fases divididas em três níveis de dificuldade 
- Aplicar o A* utilizando uma fila de prioridades ordenada por f(n) = g(n) + h(n)
- Detectar e descartar estados em deadlock
- Medir o desempenho: tempo (ms), nós expandidos, profundidade e custo da solução


COMO FUNCIONA

- Estado: posição do jogador + posições das caixas. Paredes e objetivos ficam fixos no mapa.
- Custo: cada movimento custa 1, então o custo da solução é igual à profundidade.
- Heurística: uma busca em largura (BFS) a partir de cada objetivo calcula o mínimo de empurrões até ele. h(n) é a menor soma dessas distâncias entre as caixas e os objetivos. Ela é admissível e consistente, então a solução encontrada é ótima.
- Deadlocks: casas que a BFS não alcança 


FUNCIONALIDADES

- Menu para escolher o nível de dificuldade
- Animação da solução passo a passo no console
- Tabela de resultados ao fim de cada nível
