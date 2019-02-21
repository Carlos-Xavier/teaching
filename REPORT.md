# identificação

- Página do repositório  do trabalho ([link GitHub](https://github.com/Carlos-Xavier/Ufal.AB2))
- Discente 1
  - Nome : Carlos Eduardo Xavier Bezerra
  - Matrícula : 	18211739
  - Distribuição de nota (%): 33,3
- Discente 2
  - Nome : Marconde José da Silva Lima
  - Matrícula : 18211786
  - Distribuição de nota (%): 33,3
- Discente 3
  - Nome : Elygledson José da Silva Bezerra
  - Matrícula : 18211742
  - Distribuição de nota (%): 33,3

# Resultados

## Utilização intensa da UCP

*  *UCP*:

![gráfico](https://i.imgur.com/vEs0Lxm.png)

Não foi esperado, no começo manteve-se estável pelo programa está usando o processador ao máximo, mas um tempo depois teve uma queda abaixo do esperado. Apesar de que tenha voltado a crescer gradativamente, ainda assim não manteve as expectativas. As espectativas eram para um gráfico crescente ou um pico estável.

## Utilização intensa da UCP e memória

*  *Memória e UCP*:

O lado esquerdo representa o uso em porcentagem da UCP, enquanto o lado direito sendo representado também por porcentagem, é baseado no valor de 10 gigabytes como valor total. 

![gráfico](https://i.imgur.com/fOdk8BB.png)

Em relação aos resultados do nosso programa , em sua maioria, eles cumpriram com nossas expetativas. Os testes realizados na Unidade Central de Processamento através do comando ./bin ucp, atingiram altos níveis de consumo fazendo, os dispositivos utilizados nos testes,  apresentarem lerdeza ao executar determinados processos. Por outro lado, os testes realizados na memória, cumpriram em parte com nossas expectativas, utilizamos primeiramente uma função chamada usleep(), cuja função é atrasar a execução do programa em milionésimos de segundo, para limitar o uso do malloc(),  função essa que possibilita uma alocação dinâmica na memória RAM, e ao fazer isso tanto o uso da UCP, quanto da memória não atingiram altos níveis, portanto, durante o tempo de execução do programa, foi possível realizar tarefas sem nenhum problema. Em contrapartida, ao retirar a função usleep(), tanto o consumo de UCP, quanto de memória atingiram altíssimos níveis de consumo, causando extrema lentidão e até travamento dos dispositivos. Com base nisso, durante a execução do programa, notamos alguns pontos importantes a respeito da função usleep(), a qual independente do valor acrescentado na função malloc(), pois com ela ativada tanto o consumo de memória como o de UCP são baixos. 

Um dos computadores utilizados no processo de testes possuía um processador core i5, com 8GB de memória. Nesse dispositivo,  um caso interessante aconteceu enquanto testávamos  o programa sem a função usleep(). Durante a execução, tanto o consumo de UCP quanto o consumo da memória abaixaram rapidamente até chegar a zero, faltando poucos segundos para o programa terminar sua execução.

![gráfico](https://i.imgur.com/MrjXais.png)

Após outros testes, o mesmo caso se repetiu, no entanto, dessa vez apenas o consumo de UCP que abaixou bruscamente, enquanto o nível de consumo da memória se manteve até o final da execução.

![gráfico](https://i.imgur.com/bglHKpX.png)


# Discussão

O objetivo do código é aproveitar a funcionalidade do processo Pai e Filho que realizam tarefas diferentes e simultâneas. Desta maneira, é atribuído a ambos funções que buscam tanto o monitoramento do computador em decorrência do uso intenso de memória e processamento, como o a criação deles. Sendo assim, o processo Filho quando chamado será encarregado pelo consumo excessivo de memória e processamento até a parada da execução, quando será morto. Enquanto que ao mesmo tempo, o processo Pai monitora o processo Filho e retorna com o valor de consumo da memória e do processador. Logo após a função kill é usada para matar o processo filho evitando um loop infinito. Para utilizar a função fork(), é preciso adicionar as bibliotecas sys/types.h e unistd.h. O número que a função fork() retorna é chamado PID (process identification). Quanto ao monitoramento dos dados, funciona da seguinte forma,  dois vetores de caracteres são definidos, um deles é usado como parâmetro para receber o comando de monitoramento com a função sprintf(), e logo após passado para um ponteiro de arquivo, no qual pela função popen() recebe novamente outro processo. Após isso, um ponteiro de caracter vai receber os dois vetores criados, juntamente com o ponteiro de arquivo, e através da função fgets(), vai imprimir os dados, tanto da unidade central de processamento quanto da memória.
