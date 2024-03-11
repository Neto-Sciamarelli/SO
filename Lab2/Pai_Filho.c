//Nome: Henrique Árabe Neres de Farias
//RA: 10410152
//Nome: Antônio Carlos Sciamarelli Neto
//RA: 10409160

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

int main() {
    int pipe_pai_filho[2];
    int pipe_filho_pai[2];
    pid_t pid;

    // Cria os pipes
    if (pipe(pipe_pai_filho) == -1 || pipe(pipe_filho_pai) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Código do processo filho
        close(pipe_pai_filho[1]);  
        char msg_filho[60]; 
        read(pipe_pai_filho[0], msg_filho, sizeof(msg_filho)); 
        printf("Filho recebeu: %s\n", msg_filho);

        // Prepara e envia a resposta ao pai
        close(pipe_pai_filho[0]);  
        close(pipe_filho_pai[0]);  
        const char* resposta_filho = "Eae, pai. Estou bem e o senhor?";
        write(pipe_filho_pai[1], resposta_filho, strlen(resposta_filho) + 1); 
        close(pipe_filho_pai[1]);  
        
    } else { // Código do processo pai
        close(pipe_pai_filho[0]);  
        const char* msg_pai = "Olá, filho. Como você está?";
        write(pipe_pai_filho[1], msg_pai, strlen(msg_pai) + 1);
        close(pipe_pai_filho[1]);  

        // Espera pelo processo filho terminar
        wait(NULL);

        // Prepara-se para receber a resposta do filho
        close(pipe_filho_pai[1]); 
        char resposta_pai[60]; 
        read(pipe_filho_pai[0], resposta_pai, sizeof(resposta_pai)); 
        printf("Pai recebeu: %s\n", resposta_pai);
        close(pipe_filho_pai[0]);  
    }

    return 0;
}
