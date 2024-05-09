#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h> // Adicionado para utilizar mutex

// 64kB stack
#define FIBER_STACK (1024*64)

struct conta {
    int saldo;
};
typedef struct conta conta;

conta from, to;
int valor;
pthread_mutex_t mutex; // Mutex para sincronização

// Função de transferência protegida por mutex
void* transferencia(void *arg) {
    pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar as variáveis compartilhadas
    
    if (from.saldo >= valor) {
        from.saldo -= valor;
        to.saldo += valor;
    }

    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);

    pthread_mutex_unlock(&mutex); // Libera o mutex após o acesso às variáveis compartilhadas
    return NULL;
}

int main() {
    void* stack;
    pthread_t thread_ids[10]; // Utilizar pthread_t para identificadores de thread
    int i;

    // Inicialização das contas
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 para a conta c2\n");
    valor = 10;

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex

    // Alocação da pilha
    stack = malloc(FIBER_STACK);
    if (stack == NULL) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Criação das threads
    for (i = 0; i < 10; i++) {
        if (pthread_create(&thread_ids[i], NULL, transferencia, NULL) != 0) {
            perror("pthread_create");
            exit(2);
        }
    }

    // Aguarda as threads terminarem
    for (i = 0; i < 10; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // Liberação da pilha e do mutex
    free(stack);
    pthread_mutex_destroy(&mutex);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
