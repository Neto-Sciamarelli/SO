#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

// Estrutura para os parâmetros de cada pessoa
typedef struct {
    int id;
    int chegada;
    int direcao;
    int saida; // Tempo de saída da escada
} Pessoa;

// Variáveis globais
sem_t mutex;
sem_t esteira;
sem_t escada_vazia;
int direcao_escada = 0; // 0: parada, 1: direção 0, -1: direção 1
int num_pessoas;
int pessoas_na_escada = 0; // Quantidade de pessoas na escada

void *pessoa(void *arg) {
    Pessoa *p = (Pessoa *)arg;
    int id = p->id;
    int chegada = p->chegada;
    int direcao = p->direcao;

    sleep(chegada);

    sem_wait(&mutex);
    if ((direcao_escada == 0 || direcao_escada == direcao) && pessoas_na_escada == 0) {
        direcao_escada = direcao;
        pessoas_na_escada++;
        sem_post(&mutex);

        printf("Pessoa %d entra na escada\n", id);

        sleep(10); // Tempo na escada

        printf("Pessoa %d sai da escada\n", id);
        pessoas_na_escada--;
        sem_post(&escada_vazia); // Libera a escada

        if (pessoas_na_escada == 0) {
            direcao_escada = 0; // Reinicia a direção quando a escada esvazia
        }
        p->saida = chegada + 10; // Armazena o tempo de saída
    } else {
        sem_post(&mutex);
        printf("Pessoa %d aguarda na esteira\n", id);
        sem_wait(&esteira); // Aguarda a esteira estar livre
        sem_wait(&escada_vazia); // Aguarda a escada estar vazia
        sem_wait(&mutex);
        direcao_escada = direcao;
        pessoas_na_escada++;
        sem_post(&escada_vazia); // Libera a escada_vazia
        sem_post(&mutex);
        printf("Pessoa %d entra na escada\n", id);

        sleep(10); // Tempo na escada

        printf("Pessoa %d sai da escada\n", id);
        pessoas_na_escada--;
        sem_post(&escada_vazia); // Libera a escada
        if (pessoas_na_escada == 0) {
            direcao_escada = 0; // Reinicia a direção quando a escada esvazia
        }
        p->saida = chegada + 10; // Armazena o tempo de saída
    }

    pthread_exit(NULL);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int i;
    FILE *file;
    file = fopen("entrada.txt", "r"); // Abre o arquivo para leitura

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(file, "%d", &num_pessoas); // Lê o número de pessoas

    Pessoa pessoas[num_pessoas];

    sem_init(&mutex, 0, 1);
    sem_init(&esteira, 0, 1);
    sem_init(&escada_vazia, 0, 1);

    // Lê os dados de cada pessoa do arquivo
    for (i = 0; i < num_pessoas; ++i) {
        fscanf(file, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
        pessoas[i].id = i + 1;
    }

    fclose(file); // Fecha o arquivo após a leitura

    // Cria as threads para cada pessoa
    pthread_t threads[num_pessoas];
    for (i = 0; i < num_pessoas; ++i) {
        pthread_create(&threads[i], NULL, pessoa, (void *)&pessoas[i]);
    }

    // Aguarda o término de cada thread
    for (i = 0; i < num_pessoas; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Encontra o tempo de saída da última pessoa
    int tempo_saida_ultima_pessoa = 0;
    for (i = 0; i < num_pessoas; ++i) {
        if (pessoas[i].saida > tempo_saida_ultima_pessoa) {
            tempo_saida_ultima_pessoa = pessoas[i].saida;
        }
    }

    printf("Tempo em que a última pessoa saiu da escada: %d segundos\n", tempo_saida_ultima_pessoa);

    sem_destroy(&mutex);
    sem_destroy(&esteira);
    sem_destroy(&escada_vazia);

    return 0;
}

