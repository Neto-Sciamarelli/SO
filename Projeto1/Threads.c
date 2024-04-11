#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <locale.h>

// Estrutura para os parâmetros de cada pessoa
typedef struct {
    int chegada;
    int direcao;
} Pessoa;

// Variáveis globais
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int direcao = -1;
int tempoFinal = 0;

void *pessoa(void *arg) {
    Pessoa *p = (Pessoa *)arg;
    
    sleep(p->chegada);
    pthread_mutex_lock(&mutex);
    
    if(direcao == -1 || p->direcao == direcao) {
    	direcao = p->direcao;
    	tempoFinal = p->chegada+10;
	}else {
		pthread_mutex_unlock(&mutex);
		sleep(tempoFinal-p->chegada);
		pthread_mutex_lock(&mutex);
		
		direcao = p->direcao;
		tempoFinal+=10;
	}
	
	pthread_mutex_unlock(&mutex);
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

    // Cria as threads para cada pessoa
    pthread_t threads[num_pessoas];
    for (i = 0; i < num_pessoas; ++i) {
        pthread_create(&threads[i], NULL, pessoa, (void *)&pessoas[i]);
    }

    // Aguarda o término de cada thread
    for (i = 0; i < num_pessoas; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("O momento final de parada da escada rolante é %d\n", tempoFinal);

    return 0;
}