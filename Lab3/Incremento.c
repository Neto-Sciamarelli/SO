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
    *args->shared_var = 1;
    printf("Child thread depois de modificar: %d\n", *args->shared_var);
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    int shared_var = 0; // Esta variável será compartilhada e modificada pela thread filho.
    
    // Alocar a stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }
    
    thread_args_t args = { .shared_var = &shared_var };
    
    printf("Creating child thread\n");
    // Chamar a chamada de sistema clone para criar a thread filho
    pid = clone(&threadFunction, (char*) stack + FIBER_STACK,
    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &args);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }
    
    // Esperar pela thread filho sair
    pid = waitpid(pid, NULL, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }
    
    // Aqui a variável shared_var deve ter sido modificada pelo filho
    printf("Valor da variável no pai após a thread filho modificar: %d\n", shared_var);
    
    // Liberar a stack
    free(stack);
    printf("Child thread returned and stack freed.\n");
    return 0;
}
