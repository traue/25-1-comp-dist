#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforo;

void *thread_funcA(void *arg)
{
    printf("Thread A inicializando....\n");
    sleep(3); // em segundos -> Apenas a simulação de algo que pode precisar de sincronização
    printf("Thread A acordou... liberando o semáforo...\n");
    sem_post(&semaforo);
    pthread_exit(NULL);
}

void *thread_funcB(void *arg)
{
    printf("Thread B inicializando....\n");
    sem_wait(&semaforo);
    sleep(20); // em segundos -> Apenas a simulação de algo que pode precisar de sincronização
    printf("Thread B acordou... executando...\n");
 
    pthread_exit(NULL);
}

int main() {

    //Inicialização das threads
    pthread_t threadA, threadB;

    // Inicializa o semáforo
    sem_init(&semaforo, 0, 0);

    // Criação das Threads
    pthread_create(&threadA, NULL, thread_funcA, NULL);
    pthread_create(&threadB, NULL, thread_funcB, NULL);

    // Espera a finalização das Threads
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    sem_destroy(&semaforo);

    printf("Terminei.... \n");

    return 0;
}