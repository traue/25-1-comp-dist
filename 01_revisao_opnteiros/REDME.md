# Revisão de Ponteiros

## 1. Introdução

Nesta aula, vamos revisar:

- **Ponteiros:** O que são, como declarar, inicializar e manipular.
- **Operações com ponteiros:** Aritmética de ponteiros e uso com arrays.
- **Passagem de ponteiros em funções:** Como utilizar ponteiros para modificar variáveis e trabalhar com estruturas de dados.
- **Exemplos práticos:** Códigos comentados para fixação dos conceitos.

O foco é desenvolver uma compreensão sólida sobre como e por que utilizar ponteiros, mostrando aplicações práticas e exemplos que facilitam o entendimento.

---

## 2. Conceitos Básicos de Ponteiros

### 2.1 O que é um ponteiro?
Um ponteiro é uma variável que armazena o endereço de memória de outra variável. Em C, isso permite manipular diretamente a memória e criar estruturas de dados dinâmicas.

### 2.2 Declaração e Inicialização
Para declarar um ponteiro, usamos o operador `*`. Por exemplo:

```c
int *p;  // p é um ponteiro para inteiro
```

Para inicializá-lo, podemos atribuir o endereço de uma variável usando o operador de endereço `&`:

```c
int x = 10;
int *p = &x;  // p armazena o endereço de x
```

### 2.3 Acessando o Valor Apontado
Para acessar ou modificar o valor armazenado no endereço para o qual o ponteiro aponta, usamos o operador de desreferenciação `*`:

```c
printf("Valor de x: %d\n", *p);  // Imprime 10
*p = 20;  // Modifica x para 20
```

---

## 3. Operações com Ponteiros

### 3.1 Aritmética de Ponteiros
A aritmética de ponteiros permite navegar por arrays. Se `p` é um ponteiro para `int`, então `p+1` aponta para o próximo inteiro na memória:

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;  // Equivalente a p = &arr[0]
printf("Primeiro elemento: %d\n", *p);        // 10
printf("Segundo elemento: %d\n", *(p+1));       // 20
```

### 3.2 Diferença entre Ponteiros e Arrays
Embora em muitas situações um array seja tratado como um ponteiro para seu primeiro elemento, eles não são a mesma coisa. Um array tem tamanho fixo e sua memória é contínua, enquanto um ponteiro pode apontar para qualquer local de memória, inclusive para memória alocada dinamicamente.

---

## 4. Funções e Passagem de Ponteiros

### 4.1 Por que usar ponteiros em funções?
Usar ponteiros em funções permite:
- **Modificar variáveis** definidas fora da função (passagem por referência);
- **Economizar memória** ao passar grandes estruturas (ao invés de passar cópias);
- **Retornar múltiplos valores** indiretamente.

### 4.2 Passagem de Ponteiros para Modificar Variáveis

Exemplo: função que troca os valores de duas variáveis.

```c
#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    printf("Antes: x = %d, y = %d\n", x, y);
    trocar(&x, &y);
    printf("Depois: x = %d, y = %d\n", x, y);
    return 0;
}
```

**Explicação:**  
- A função `trocar` recebe os endereços de `x` e `y`.
- Ao desreferenciar (`*a` e `*b`), podemos acessar e modificar os valores originais.
- A troca efetiva dos valores é feita sem retornar nenhum valor, demonstrando a passagem por referência.

### 4.3 Passagem de Arrays para Funções

Arrays são passados como ponteiros para funções. Exemplo: função que imprime os elementos de um array.

```c
#include <stdio.h>

void imprimirArray(int *arr, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: %d\n", i, arr[i]);
    }
}

int main() {
    int numeros[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    imprimirArray(numeros, tamanho);
    return 0;
}
```

**Explicação:**  
- O array `numeros` é passado como um ponteiro para a função `imprimirArray`.
- A função itera sobre o array usando o tamanho informado.

### 4.4 Ponteiros para Ponteiros

Ponteiros podem apontar para outros ponteiros. Isso é útil, por exemplo, quando precisamos modificar o ponteiro original dentro de uma função.

```c
#include <stdio.h>
#include <stdlib.h>

void alocarMemoria(int **p) {
    *p = (int *)malloc(sizeof(int));
    if (*p != NULL) {
        **p = 100;  // atribui 100 ao espaço alocado
    }
}

int main() {
    int *ptr = NULL;
    alocarMemoria(&ptr);
    if (ptr != NULL) {
        printf("Valor alocado: %d\n", *ptr);
        free(ptr);
    }
    return 0;
}
```

**Explicação:**  
- A função `alocarMemoria` recebe um ponteiro para ponteiro `int **p`.
- Usamos `*p` para modificar o ponteiro original, alocando memória dinamicamente.
- É importante liberar a memória com `free` após o uso para evitar vazamentos de memória.

---

## 5. Exemplos Práticos e Exercícios

### 5.1 Exemplo Prático: Soma de Elementos de um Array

Crie uma função que receba um array e seu tamanho, e retorne a soma dos elementos usando ponteiros.

```c
#include <stdio.h>

int somaArray(int *arr, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += *(arr + i);  // ou arr[i]
    }
    return soma;
}

int main() {
    int valores[] = {2, 4, 6, 8, 10};
    int tamanho = sizeof(valores) / sizeof(valores[0]);
    printf("Soma: %d\n", somaArray(valores, tamanho));
    return 0;
}
```

**Atividade:**  
- Modifique a função para calcular a média dos elementos.

### 5.2 Exemplo Prático: Manipulação de Strings

Manipule strings usando ponteiros. Lembre-se que strings em C são arrays de caracteres terminados em `'\0'`.

```c
#include <stdio.h>

void imprimirString(char *str) {
    while (*str != '\0') {
        printf("%c", *str);
        str++;  // move para o próximo caractere
    }
    printf("\n");
}

int main() {
    char mensagem[] = "Olá, ponteiros!";
    imprimirString(mensagem);
    return 0;
}
```

**Atividade:**  
- Escreva uma função que inverta uma string utilizando ponteiros.

### 5.3 Exemplo Prático: Passagem de Estruturas por Ponteiro

Utilize ponteiros para modificar os membros de uma estrutura dentro de uma função.

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

void atualizarPessoa(Pessoa *p, const char *novoNome, int novaIdade) {
    strcpy(p->nome, novoNome);  // acesso através do operador "->"
    p->idade = novaIdade;
}

int main() {
    Pessoa pessoa = {"João", 30};
    printf("Antes: %s, %d anos\n", pessoa.nome, pessoa.idade);
    atualizarPessoa(&pessoa, "Maria", 25);
    printf("Depois: %s, %d anos\n", pessoa.nome, pessoa.idade);
    return 0;
}
```

**Atividade:**  
- Adicione uma nova função que imprima os dados da estrutura, utilizando passagem por ponteiro.

---

## 6. Dicas e Boas Práticas

- **Inicialize sempre seus ponteiros:** Sempre que declarar um ponteiro, tente inicializá-lo com `NULL` ou com o endereço de uma variável válida para evitar acessos indevidos à memória.
- **Cuidado com a alocação dinâmica:** Ao usar `malloc`, `calloc` ou `realloc`, verifique se o retorno não é `NULL` e sempre libere a memória com `free` quando não for mais necessária.
- **Cuidado com a aritmética de ponteiros:** Certifique-se de que os ponteiros apontem para a memória correta, especialmente ao trabalhar com arrays, para evitar erros de segmentação (segmentation fault).

---

## 7. Conclusão

Nesta aula, revisamos os conceitos essenciais dos ponteiros em C, incluindo:
- Como declarar, inicializar e acessar ponteiros;
- Aritmética de ponteiros e sua aplicação com arrays;
- Passagem de ponteiros em funções para modificar variáveis e estruturas;
- Exemplos práticos que demonstram a aplicação desses conceitos.

Com esta revisão, espera-se que você se sinta mais confortável em utilizar ponteiros em seus programas em C, entendendo melhor as vantagens e os cuidados ao trabalhar com memória e passagem de dados por referência.

**Exercício Final:**  
Crie um programa que:
- Aloca dinamicamente um array de inteiros;
- Preenche o array com valores lidos do usuário;
- Calcula e exibe a soma e a média dos valores;
- Libera a memória alocada.

Esta prática consolidará os conceitos revisados e permitirá a aplicação dos conhecimentos em um cenário real.

---

Boa revisão e bons códigos!