#define _GNU_SOURCE
#include <malloc.h>
#include <pthread.h> // Adicionado para utilizar mutex
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// 64kB stack
#define FIBER_STACK (1024 * 64)

struct conta {
  int saldo;
};
typedef struct conta conta;

conta from, to;
int valor;
pthread_mutex_t mutex; // Mutex para sincronização

// Função de transferência protegida por mutex
void *transferencia(void *arg) {
  pthread_mutex_lock(
      &mutex); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

  if (from.saldo == 0) {
    printf("Saldo insuficiente!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
  }

  if (from.saldo >= valor) {
    from.saldo -= valor;
    to.saldo += valor;
  }

  printf("Transferência concluída com sucesso!\n");
  printf("Saldo de c1: %d\n", from.saldo);
  printf("Saldo de c2: %d\n", to.saldo);

  pthread_mutex_unlock(
      &mutex); // Libera o mutex após o acesso às variáveis compartilhadas
  return NULL;
}

void *transferencia2(void *arg) {
  pthread_mutex_lock(
      &mutex); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

  if (to.saldo == 0) {
    printf("Saldo insuficiente!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
  }

  if (to.saldo >= valor) {
    to.saldo -= valor;
    from.saldo += valor;
  }

  printf("Transferência concluída com sucesso!\n");
  printf("Saldo de c1: %d\n", from.saldo);
  printf("Saldo de c2: %d\n", to.saldo);

  pthread_mutex_unlock(
      &mutex); // Libera o mutex após o acesso às variáveis compartilhadas
  return NULL;
}

int main() {
  void *stack;
  pthread_t
      thread_ids[100]; // Utilizar pthread_t para identificadores de thread
  pthread_t thread_ids2[100];
  int i;

  // Inicialização das contas
  from.saldo = 100;
  to.saldo = 100;
  valor = 10;

  pthread_mutex_init(&mutex, NULL); // Inicializa o mutex

  // Alocação da pilha
  stack = malloc(FIBER_STACK);
  if (stack == NULL) {
    perror("malloc: could not allocate stack");
    exit(1);
  }

  for (i = 0; i < 50; i++) {
    if (pthread_create(&thread_ids[i], NULL, transferencia, NULL) != 0) {
      perror("pthread_create");
      exit(2);
    }

    if (pthread_create(&thread_ids[i + 50], NULL, transferencia2, NULL) != 0) {
      perror("pthread_create");
      exit(2);
    }
  }

  for (i = 0; i < 100; i++) {
    pthread_join(thread_ids[i], NULL);
  }

  // Liberação da pilha e do mutex
  free(stack);
  pthread_mutex_destroy(&mutex);

  printf("Transferências concluídas e memória liberada.\n");
  return 0;
}
