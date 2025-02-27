# Brincando com Threads em C


## 1. Conceitos Básicos

**Threads vs. Processos**, resumidamente:

- **Processos:** São instâncias de programas em execução, com seu próprio espaço de memória. A comunicação entre processos (IPC) geralmente é mais custosa.  
- **Threads:** São "sub-processos" que rodam dentro de um mesmo processo, compartilhando o mesmo espaço de memória. Isso permite comunicação mais rápida entre elas, mas exige cuidado com o acesso concorrente a recursos compartilhados.

**Por que usar threads?**  
- Melhor aproveitamento de processadores multinúcleo.  
- Permite dividir tarefas em partes menores que podem ser executadas simultaneamente.  
- Útil para aplicações que precisam responder a múltiplas solicitações ao mesmo tempo (por exemplo, servidores, interfaces gráficas, etc.).

---

## 2. Exemplo 1: Criação e Execução Simples de Threads

Neste exemplo, criaremos três threads que executam uma função que imprime uma mensagem identificando a thread. Cada thread recebe um identificador para facilitar a visualização de que elas estão sendo executadas de forma separada.

```c
#include <stdio.h>
#include <pthread.h>

// Função que será executada por cada thread
void* thread_func(void* arg) {
    int id = *(int*) arg; // Converte o argumento para inteiro
    printf("Olá, eu sou a thread %d\n", id);
    pthread_exit(NULL); // Encerra a thread
}

int main() {
    pthread_t threads[3];  // Vetor para armazenar os identificadores das threads
    int thread_ids[3] = {1, 2, 3}; // Identificadores para cada thread
    
    // Criação das threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*) &thread_ids[i])) {
            fprintf(stderr, "Erro ao criar a thread %d\n", i + 1);
            return 1;
        }
    }
    
    // Aguardar a finalização de cada thread
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Todas as threads foram finalizadas.\n");
    return 0;
}
```

### O que esse código faz?

- **Inclusão de Bibliotecas:**  
  - `stdio.h`: Para funções de entrada e saída
  - `pthread.h`: Para as funções de manipulação de threads (nativas do C)

- **Função `thread_func`:**  
  Cada thread executa essa função. Ela recebe um ponteiro para um inteiro (identificador da thread), imprime uma mensagem e, em seguida, encerra a thread com `pthread_exit`.

- **Função `main`:**  
  - Cria um array de identificadores (`pthread_t`) e um array de inteiros para os IDs.
  - Um loop cria 3 threads usando `pthread_create`, passando o endereço do ID correspondente como argumento.
  - Outro loop usa `pthread_join` para esperar que todas as threads terminem sua execução.
  
> **Para compilar:**  
> Usar o comando: `gcc -pthread <nome_do_seu_arquivo>.c -o <nome_do_seu_arquivo>`

---

## 3. Exemplo 2: Sincronização com Semáforos

Agora, vamos incrementar nosso exemplo usando semáforos para sincronizar a execução de duas threads. Neste exemplo, a **Thread A** executa uma tarefa e, ao final, libera um semáforo. A **Thread B** aguarda esse sinal para então executar sua parte, demonstrando como controlar a ordem de execução.

### Código de Exemplo com Semáforos

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declaração do semáforo
sem_t sem;

// Função executada pela Thread A
void* funcao_thread_A(void* arg) {
    printf("Thread A: Iniciando...\n");
    sleep(1); // Simula algum processamento
    printf("Thread A: Finalizando e liberando o semáforo.\n");
    sem_post(&sem); // Libera o semáforo, sinalizando que terminou
    pthread_exit(NULL);
}

// Função executada pela Thread B
void* funcao_thread_B(void* arg) {
    printf("Thread B: Aguardando sinal da Thread A...\n");
    sem_wait(&sem); // Espera até que o semáforo seja liberado
    printf("Thread B: Sinal recebido, executando...\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t threadA, threadB;
    
    // Inicializa o semáforo com valor 0 (bloqueado)
    sem_init(&sem, 0, 0);
    
    // Cria as threads
    pthread_create(&threadA, NULL, funcao_thread_A, NULL);
    pthread_create(&threadB, NULL, funcao_thread_B, NULL);
    
    // Aguarda a finalização das threads
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    
    // Destroi o semáforo
    sem_destroy(&sem);
    
    printf("Execução completa.\n");
    return 0;
}
```

### O que esse código faz?

- **Bibliotecas utilizadas:**  
  - `semaphore.h`: Necessária para manipulação dos semáforos (nativa do C)
  - `unistd.h`: Para usar a função `sleep`, que **simula** um atraso no processamento (nativa do C)

- **Semáforo (`sem`):**  
  Declarado globalmente e inicializado no `main` com valor 0, o que significa que ele começa “bloqueado”.

- **Função `funcao_thread_A`:**  
  Simula uma tarefa com `sleep(1)` e, ao terminar, chama `sem_post(&sem)`. Esse comando incrementa o contador do semáforo e libera a Thread B que estava aguardando.

- **Função `funcao_thread_B`:**  
  Inicia imprimindo uma mensagem e, em seguida, chama `sem_wait(&sem)`, que bloqueia a execução da thread até que o semáforo seja liberado pela Thread A. Após o desbloqueio, a thread imprime uma mensagem de continuação.

- **Função `main`:**  
  - Inicializa o semáforo.
  - Cria as duas threads (A e B).
  - Usa `pthread_join` para esperar a finalização de ambas.
  - Destroi o semáforo após o uso.


---



## 4. Conclusão

Esses conceitos são fundamentais para o desenvolvimento de aplicações distribuídas, onde a execução concorrente e a sincronização de processos são aspectos essenciais. Conforme avançarem nos estudos, vocês poderão explorar outros mecanismos de sincronização (como mutexes e barreiras) e casos mais complexos de comunicação entre threads.


---

### Exercício: Corrida de Threads com Sincronização

**Objetivo:**  
Simular uma corrida entre corredores utilizando threads. Cada thread representará um corredor e deverá "correr" por um tempo aleatório. Ao final da corrida, o programa deverá registrar e exibir a ordem de chegada dos corredores, garantindo que o acesso à variável que registra essa ordem seja feito de forma segura através de semáforos.

**Descrição do Exercício:**  
1. **Criação das Threads:**  
   - Crie 5 threads, cada uma representando um corredor.  
   - Cada thread deverá executar uma função que simula a corrida.

2. **Simulação da Corrida:**  
   - Dentro da função executada por cada thread, utilize a função `sleep()` com um tempo aleatório (por exemplo, entre 1 e 5 segundos) para simular a duração da corrida de cada corredor.
   - Para gerar números aleatórios, utilize `rand()` e inicialize o gerador com `srand(time(NULL))` na função `main()`.

3. **Registro da Ordem de Chegada:**  
   - Crie uma variável global que indique a posição de chegada (por exemplo, um contador que inicia em 1).
   - Ao terminar a "corrida" (após o `sleep`), cada thread deverá acessar essa variável para registrar sua posição de chegada e imprimir uma mensagem no formato:  
     `"Corredor X terminou em Yº lugar!"`
   - Como essa variável é compartilhada entre as threads, utilize semáforos para garantir que apenas uma thread por vez a modifique (evitando condições de corrida).

4. **Sincronização com Semáforos:**  
   - Inicialize um semáforo (com valor inicial 1) para proteger a seção crítica onde a ordem de chegada é atualizada.
   - Use `sem_wait()` antes de acessar e atualizar a variável e `sem_post()` logo em seguida.

5. **Finalização do Programa:**  
   - No `main()`, crie as threads e, em seguida, utilize `pthread_join()` para aguardar que todas terminem a execução.
   - Ao final, imprima uma mensagem geral indicando que a corrida terminou e exiba a ordem completa de chegada se desejar.

---

**Dicas:**

- **Bibliotecas Necessárias:**  
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
  #include <semaphore.h>
  #include <unistd.h>
  #include <time.h>
  ```

- **Estrutura Básica da Função da Thread:**  
  ```c
  void* corredor(void* arg) {
      int id = *(int*)arg;
      // Simula o tempo de corrida com sleep aleatório
      int tempo = (rand() % 5) + 1;
      sleep(tempo);

      // Acesso à seção crítica para atualizar a posição de chegada
      sem_wait(&sem);
      // Atualize a variável global de posição e imprima a mensagem
      // Exemplo: printf("Corredor %d terminou em %dº lugar!\n", id, posicao++);
      sem_post(&sem);

      pthread_exit(NULL);
  }
  ```

- **Considerações:**  
  - Certifique-se de inicializar o semáforo corretamente (valor inicial 1) e destruí-lo ao final do programa.  
  - Lembre-se de passar os argumentos corretos para cada thread (por exemplo, o ID do corredor).

---

**Tarefa:**  
Implementar o programa completo em C conforme as especificações acima. Teste a execução várias vezes para observar que, devido ao tempo aleatório de cada thread, a ordem de chegada varia a cada execução, mas é sempre registrada de forma correta e sem problemas de concorrência.

Boa programação e aproveite o desafio!

---

### Possível solução do exercício


Em breve ;)
