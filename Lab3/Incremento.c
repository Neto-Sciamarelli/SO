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
*args->shared_var);
    printf("Child thread exiting\n");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    int shared_var = 0; // Esta variável será compartilhada entre o processo pai e a thread (processo filho)
    thread_args_t args = { .shared_var = &shared_var };

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("Creating child thread\n");
    // Call the clone system call to create the child thread
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &args);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Wait for the child thread to exit
    pid = waitpid(pid, 0, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Check the value of shared_var after child thread has modified it
    printf("Shared variable after child thread: %d\n", shared_var);

    // Free the stack
    free(stack);
    printf("Child thread returned and stack freed.\n");
    return 0;
}
