#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_CORREDORES 5

sem_t semaforo;
int posicao = 1;

void* corredor(void* arg) {
    int id = *(int*)arg;
    int tempo = (rand() % 5) + 1;
    printf("Corredor %d iniciou sua corrida e vai levar %d segundos!\n", id, tempo);
    sleep(tempo);
    sem_wait(&semaforo);
    int posicaoChegada = posicao;
    posicao++;
    printf("Corredor %d terminou em %dº lugar!\n", id, posicao++);
    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_CORREDORES];
    // e agora ?? terminar e postar no moodle até a próxima aula
    return 0;
}