#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <locale.h>

// Estrutura para os parâmetros de cada pessoa
typedef struct {
    int chegada;
    int direcao;
} Pessoa;

// Função que representa o comportamento de uma pessoa
void pessoa(Pessoa *p, int fd[]) {
    close(fd[0]); // Fecha a extremidade de leitura do pipe
    sleep(p->chegada);
    
    write(fd[1], p, sizeof(Pessoa)); // Escreve os dados da pessoa no pipe
    close(fd[1]); // Fecha a extremidade de escrita do pipe
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int i, num_pessoas;
    FILE *file;
    file = fopen("entrada.txt", "r"); // Abre o arquivo para leitura

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(file, "%d", &num_pessoas); // Lê o número de pessoas

    Pessoa pessoas[num_pessoas];

    // Lê os dados de cada pessoa do arquivo
    for (i = 0; i < num_pessoas; ++i) {
        fscanf(file, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
    }

    fclose(file); // Fecha o arquivo após a leitura

    int tempoFinal = 0;
    int direcao = -1;

    // Cria um pipe para comunicação entre processos
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Cria processos para cada pessoa
    for (i = 0; i < num_pessoas; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Processo filho
            pessoa(&pessoas[i], fd);
            exit(EXIT_SUCCESS);
        }
    }

    // Fecha a extremidade de escrita do pipe no processo pai
    close(fd[1]);

    // Lê os dados do pipe e determina o tempo final da escada rolante
    Pessoa p;
    while (read(fd[0], &p, sizeof(Pessoa)) > 0) {
        if (direcao == -1 || p.direcao == direcao) {
            direcao = p.direcao;
            tempoFinal = p.chegada + 10;
        } else {
            sleep(tempoFinal - p.chegada);
            direcao = p.direcao;
            tempoFinal += 10;
        }
    }

    // Aguarda o término de todos os processos filhos
    for (i = 0; i < num_pessoas; ++i) {
        wait(NULL);
    }

    printf("O momento final de parada da escada rolante é %d\n", tempoFinal);

    return 0;
}

