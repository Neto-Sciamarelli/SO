//Nome: Henrique Árabe Neres de Farias
//RA: 10410152
//Nome: Antônio Carlos Sciamarelli Neto
//RA: 10409160

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

int m = 2; // Tamanho da matriz (linhas)
int n = 2; // Tamanho da matriz (colunas)
int thread_count = 4; // Número de threads
double A[MAX_SIZE][MAX_SIZE]; // Matriz A
double x[MAX_SIZE]; // Vetor x
double y[MAX_SIZE]; // Vetor resultado

void *Pth_mat_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1 == thread_count) ? m : my_first_row + local_m;

    for (i = my_first_row; i < my_last_row; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    }

    return NULL;
}

int main() {
    pthread_t *thread_handles;
    long thread;

    // Aloca memória para os identificadores de thread
    thread_handles = (pthread_t *) malloc(thread_count * sizeof(pthread_t));

    // Solicita e insere os valores da matriz A
    printf("Insira os valores da matriz A(%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Solicita e insere os valores do vetor x
    printf("Insira os valores do vetor x(%d):\n", n);
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
    }

    // Cria as threads
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    // Aguarda as threads terminarem
    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // Libera memória dos identificadores de thread
    free(thread_handles);

    // Imprime o vetor resultado y
    printf("Vetor resultado y:\n");
    for (int i = 0; i < m; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");

    return 0;
}

