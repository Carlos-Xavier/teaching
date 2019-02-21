#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void ucp() // Função que inicia um looping infinito com uso intenso de processamento.
{   
    for (;;) // Cria um laço infinito.
    {} 
}

void ucp_mem() // Função que inicia um looping infinito com uso intenso de processamento e memória.
{  
    for(;;)  // Cria um laço infinito
    { 
        usleep(1); // Atrasa a execução do programa em milionésimos de segundo.
        malloc(sizeof(1000000)); // Aloca espaço para um bloco de bytes consecutivos na memória.
    }
}

void inspecionar_ucp(int pid, int n) { // Função que observa o comportamento da Unidade Central de Processamento.
    char bash_cmd[256]; // Cria o vetor de caracteres - bash_cmd;
	char buffer[1000];  // Cria o vetor de caracteres de char - buffer;
    sprintf(bash_cmd, "ps u %d | awk '{print $3}' | grep -v CPU", pid); // sprintf - retorna a string formatada.
                                                                          // ps u - seleciona os processos cujo ID efetivo está na lista de usuários.
                                                                          // awk - é usando para processamento de informações em textos, nesse caso serve como separador de campos.
                                                                          // grep v - Exibe as linhas que não contém o padrão.
	FILE *pipe; // É um ponteiro para um arquivo. Pipe é uma variável.
	pipe = popen(bash_cmd, "r"); // O comando popen abre um processo criando um pipe, bifurcando e invocando o shell. 
                                 // Nesse caso o argumento utilizado foi de leitura.

	if (NULL == pipe) // Se o pipe não tiver um valor definido, o erro é informado e o programa fecha.
    {
		perror("pipe");
		exit(1);
	} 
	
	char* uso_ucp = fgets(buffer, sizeof(buffer), pipe); 
	pclose(pipe); // Fecha o ponteiro de arquivo.
    if (n == 0) { // Se n == 0, imprime o pid e o monitoramento da ucp.
        printf("  %i %s", pid, uso_ucp);
    }
    else
    { // Se n != 0, imprime apenas o uso da ucp.
         printf("  %s", uso_ucp);
    } // Imprime o comportamento da ucp.
}

void inspecionar_mem(int pid) { // Função que observa o comportamento da memória.
    char bash_cmd[256];
    char buffer[1000];
    sprintf(bash_cmd, "ps u %d | awk '{print $5}' | grep -v VSZ", pid);
	FILE *pipe;
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) // Se o pipe não tiver um valor definido, o erro é informado e o programa fecha.
    {
		perror("pipe");
		exit(1);
	} 
	
	char* uso_mem = fgets(buffer, sizeof(buffer), pipe);
	pclose(pipe);

	printf(" MEM  :  %s", uso_mem); // Imprime o comportamento da memória, enquanto o filho atua.
}

void matar_filho(int pid) { // Função que mata o processo filho.
    char matar[256] = "kill - TERM 0"; // Cria o vetor de caracteres - matar. Também faz a atribuição do comando kill.
    sprintf(matar, "kill -TERM %d", pid); // sprintf - retorna a string formatada, com o pid do filho.
	FILE *pipe; // É um ponteiro para um arquivo. Pipe é uma variável.
	pipe = popen(matar, "r");

	if (NULL == pipe) // Se o pipe não tiver um valor definido, o erro é informado e o programa fecha.
    {
		perror("pipe");
		exit(1);
	} 

	pclose(pipe);
}

void ucp_loop(int i, int pid) { // Função recursiva que chama o inspecionar_ucp.

    if (i > 9) { // Condição de pausa.
        return;
    }
    else {
        printf(" PID / UCP%% :");
        inspecionar_ucp(pid, 0); // Monitora o comportamento da Unidade Central de Processamento
        sleep(1);
    }
    ucp_loop(i + 1, pid);
}

void ucp_mem_loop(int i, int pid) { // Função recursiva que chama o inspecionar_ucp.
 
    if (i > 9) { // Condição de pausa.
        return;
    }
    else {
        printf(" UCP%% :");
        inspecionar_ucp(pid, 1); // Monitora o comportamento da ucp
        inspecionar_mem(pid); // Monitora o comportamento da memória.
        sleep(1);
    }
    ucp_mem_loop(i + 1, pid);
}

int main (int argc, char **argv) {

    pid_t pid; // Declarando o filho.

    pid = fork(); // Criando o processo filho.

    if (argc < 2 || argc > 2) // Caso o usuário tente digitar menos ou mais de 2 parâmetros.
    {
        printf("Digite 'ucp' ou 'ucp-mem', por favor.\n");
    }   else 
        {
            if (pid < 0) // Se o processo filho for menor que zero, o programa encerra.
            {
                perror("Error: ");
                exit (-1); 
            } 

            if (pid == 0) { // Código filho.
                if (strcmp(argv[1], "ucp") == 0)
                {
                    ucp(); // Chamada de função. 
                } 
                else if (strcmp(argv[1], "ucp-mem") == 0)
                {
                    ucp_mem(); // Chamada de função.
                }
            } 
            else 
            { // Código pai
                if (strcmp(argv[1], "ucp") == 0)
                {   
                    ucp_loop(0, pid); // Chamada de função recursiva.
                }
                else if (strcmp(argv[1], "ucp-mem") == 0) 
                {
                    ucp_mem_loop(0, pid); // Chamada de função recursiva.
                }
                else {
                    printf("Digite 'ucp' ou 'ucp-mem', por favor.\n"); // Caso o usuário digite algo deferente de 'ucp' ou 'ucp-mem'.
                }
                matar_filho(pid); // Chamada de função.
            }
        }
    
    
    exit(0) ; // Fim do programa.
    return 0;
}
