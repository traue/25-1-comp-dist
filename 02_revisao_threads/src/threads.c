#include <stdio.h>
#include <pthread.h> // Pacote nativo do C que permite manipulação de Threads

void *thread_func(void *arg)
{
    int id = *(int *)arg;
    printf("Oi. Sou a thread %d\n", id);
    pthread_exit(NULL);
}

int main()
{
    printf("Brincando com Threads...\n");

    int N_THREADS = 200;

    pthread_t threads[N_THREADS];
    int thread_ids[N_THREADS]; // = {1, 2, 3, ...}

    // Inicialização do vetor identificador das threads
    for (int i = 0; i < N_THREADS; i++)
    {
        thread_ids[i] = i + 1;
    }

    // Criação das Threads
    for (int i = 0; i < N_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, thread_func, (void *)&thread_ids[i]))
        {
            fprintf(stderr, "Erro ao criar a thread %d\n", i + i);
            return 1;
        }
    }

    // Esperar a execução de cada thread 
    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nTodas as threads terminaram! Uhu!\n");

    return 0;
}