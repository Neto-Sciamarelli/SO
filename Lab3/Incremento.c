//Nome: Henrique Árabe Neres de Farias
//RA: 10410152
//Nome: Antônio Carlos Sciamarelli Neto
//RA: 10409160

#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// 64kB stack
#define FIBER_STACK 1024*64

typedef struct {
    int *shared_var;
} thread_args_t;

// The child thread will execute this function
int threadFunction(void* argument) {
    thread_args_t *args = (thread_args_t *)argument;
    printf("Child thread antes de modificar: %d\n", *args->shared_var);
    // Modificar o valor da variável compartilhada
    *args->shared_var = 123;
    printf("Child thread depois de modificar: %d\n", *
}

int main() {
    void* stack;
    pid_t pid;
    struct shared_data *shared_data;

    // Aloca memória para a pilha e para os dados compartilhados
    stack = malloc(FIBER_STACK);
    shared_data = malloc(sizeof(struct shared_data));
    if (stack == 0 || shared_data == 0) {
        perror("Error allocating memory");
        exit(1);
    }

    shared_data->value = 0; // Inicializa a variável compartilhada

    printf("Creating child thread\n");

    // Cria a thread filha passando 'shared_data' como argumento
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, shared_data);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Espera a thread filha terminar
    pid = waitpid(pid, 0, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Verifica o valor modificado pela thread filha
    printf("Child thread modified the value to: %d\n", shared_data->value);

    // Libera a memória alocada
    free(stack);
    free(shared_data);
    printf("Child thread returned and memory freed.\n");
    return 0;
}
