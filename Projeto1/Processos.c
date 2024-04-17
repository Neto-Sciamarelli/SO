#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Estrutura para os parâmetros de cada pessoa
typedef struct {
  int chegada;
  int direcao;
} Pessoa;

// Função para calcular o tempo final da escada rolante
int pessoa(Pessoa *pessoas, int num_pessoas) {
  int direcao = -1;
  int tempoFinal = 0;
  int espera = 0;

  for (int i = 0; i < num_pessoas; ++i) {
    if (direcao == -1 || pessoas[i].direcao == direcao) {
      if (pessoas[i].chegada > tempoFinal && espera > 0) {
        espera = 0;
        direcao = pessoas[i].direcao * (-1);
        tempoFinal += 10;
        espera++;
      } else {
        direcao = pessoas[i].direcao;
        tempoFinal = pessoas[i].chegada + 10;
      }
    } else {
      if (pessoas[i].chegada > tempoFinal) {
        if (espera > 0) {
          espera = 0;
          tempoFinal += 10;
          espera++;
        } else {
          tempoFinal = pessoas[i].chegada + 10;
        }
      } else {
        espera++;
      }
    }
  }

  if (espera > 0) {
    tempoFinal += 10;
  }

  return tempoFinal;
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  int num_pessoas;
  FILE *file;
  file = fopen("entrada.txt", "r"); // Abre o arquivo para leitura

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fscanf(file, "%d", &num_pessoas); // Lê o número de pessoas

  Pessoa pessoas[num_pessoas];

  // Lê os dados de cada pessoa do arquivo
  for (int i = 0; i < num_pessoas; ++i) {
    fscanf(file, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
  }

  fclose(file); // Fecha o arquivo após a leitura

  int fd[2]; // Pipe para comunicação entre pai e filho
  if (pipe(fd) == -1) {
    perror("Erro ao criar pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("Erro ao criar processo");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // Processo filho fecha a extremidade de leitura do pipe e escreve o
    // resultado
    close(fd[0]);
    int tempoFinal = pessoa(pessoas, num_pessoas);
    write(fd[1], &tempoFinal, sizeof(int));
    close(fd[1]);
    exit(EXIT_SUCCESS);
  } else {
    // Processo pai espera pelo processo filho e lê o resultado do pipe
    close(fd[1]);
    int resultado;
    wait(NULL);
    read(fd[0], &resultado, sizeof(int));
    close(fd[0]);
    printf("O momento final de parada da escada rolante é %d\n", resultado);
  }

  return 0;
}
