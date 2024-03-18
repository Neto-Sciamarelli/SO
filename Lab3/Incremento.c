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
#include <unistd.h>

#define FIBER_STACK 1024*64

struct shared_data {
    int value; // Variável compartilhada
};

// The child thread will execute this function
int threadFunction(void* argument) {
    struct shared_data *data = (struct shared_data*)argument;
    printf("Child thread executing\n");
    data->value = 0; // Altera o valor na área compartilhada
    printf("Child thread exiting with value %d\n", data->value);
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    struct shared_data *shared_data;

    shared_data = malloc(sizeof(struct shared_data));
    if (shared_data == NULL) {
        perror("malloc: could not allocate shared data");
        exit(1);
    }
    shared_data->value = 0; // Inicializa a variável compartilhada

    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("Creating child thread\n");
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, shared_data);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Wait for the child thread to exit
    pid = waitpid(pid, NULL, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    printf("Child thread returned and stack freed. Shared value: %d\n", shared_data->value);

    // Free the resources
    free(stack);
    free(shared_data);

    return 0;
}
