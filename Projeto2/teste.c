#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIBER_STACK (1024 * 64)

struct conta {
  int saldo;
};
typedef struct conta conta;

conta from, to;
int valor, contagem;
pthread_mutex_t mutex;

void *transferencia(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    if (from.saldo >= valor) {
      from.saldo -= valor;
      to.saldo += valor;
      contagem++;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
  }
}

void *transferencia2(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    if (to.saldo >= valor) {
      to.saldo -= valor;
      from.saldo += valor;
      contagem++;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
  }
}

int main() {
  void *stack;
  pthread_t thread_ids[100];
  int i;

  from.saldo = 100;
  to.saldo = 100;

  printf("Transferindo 10 para a conta c2\n");
  valor = 10;

  pthread_mutex_init(&mutex, NULL);

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

    if (pthread_create(&thread_ids[i+50], NULL, transferencia2, NULL) != 0) {
      perror("pthread_create");
      exit(2);
    }
  }

  for (i = 0; i < 100; i++) {
    pthread_join(thread_ids[i], NULL);
  }

  free(stack);
  pthread_mutex_destroy(&mutex);

  printf("Transferências concluídas e memória liberada.\n");
  printf("%d\n", contagem);

  return 0;
}
