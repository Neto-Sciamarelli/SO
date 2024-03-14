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

// Variável compartilhada entre o processo pai e o processo filho
int Value = 0;

// O processo filho executará esta função
int threadFunction(void* argument) {
    printf("Valor compartilhado no processo filho: %d\n", Value);
    Value++; // Incrementa o valor compartilhado
    printf("Child thread exiting\n");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;

    // Aloca a pilha
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: não foi possível alocar a pilha");
        exit(1);
    }

    printf("Creating child thread\n");
    // Chama a chamada de sistema clone para criar a thread filha
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
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

    // Mostra o valor compartilhado após o retorno da thread filha
    printf("Valor compartilhado após a execução do processo filho: %d\n", Value);

    // Libera a pilha
    free(stack);
    printf("Child thread returned and stack freed.\n");
    return 0;
}
