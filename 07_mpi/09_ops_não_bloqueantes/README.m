
# 🚀 Comunicação Não Bloqueante com MPI (MPI_Isend & MPI_Irecv)

## 📝 Descrição

Este programa em MPI exemplifica o uso de **operações de envio e recepção não bloqueantes**, que permitem que os processos executem outras tarefas **enquanto a comunicação ainda está em andamento**. Ele envolve dois processos:

- **Processo 0**: envia um vetor de inteiros para o processo 1.
- **Processo 1**: recebe esse vetor e calcula a soma dos valores.

Ambos os processos utilizam `MPI_Isend` e `MPI_Irecv` para comunicação assíncrona, e `MPI_Wait` para garantir que a operação foi concluída.

---

## 🧠 Conceitos Fundamentais

### 🔹 Comunicação Bloqueante (para comparação)
Em MPI, funções como `MPI_Send` e `MPI_Recv` **bloqueiam o processo** até que a operação de envio ou recepção seja completada.

### 🔸 Comunicação Não Bloqueante
Funções como `MPI_Isend` e `MPI_Irecv` **iniciam** uma operação de comunicação, mas **não aguardam sua conclusão**. Isso permite:

- **Overlap entre comunicação e computação**: o processo pode continuar executando cálculos enquanto os dados são enviados/recebidos.
- **Melhor performance em programas de alto desempenho.**

Para garantir que a operação foi concluída, deve-se utilizar:
- `MPI_Wait`: bloqueia até a finalização.
- `MPI_Test`: consulta se a operação foi concluída, sem bloquear.

---

## ✅ Etapas do Programa

### Processo 0:
1. Inicializa um vetor com valores de 0 a 7.
2. Envia o vetor para o processo 1 com `MPI_Isend`.
3. Calcula a soma dos valores localmente.
4. Espera a finalização do envio com `MPI_Wait`.

### Processo 1:
1. Inicia recepção não bloqueante com `MPI_Irecv`.
2. Espera a finalização da recepção com `MPI_Wait`.
3. Calcula a soma dos valores recebidos.

---

## 📤 Execução

### Compilação:
```bash
mpicc -o nonblocking nonblocking.c
```

### Execução com 2 processos:
```bash
mpirun -np 2 ./nonblocking
```

---

## 💡 Vantagens da Comunicação Não Bloqueante

- **Melhor uso da CPU**: processos continuam computando enquanto aguardam comunicação.
- **Evita deadlocks**: especialmente quando múltiplos processos tentam se comunicar simultaneamente.
- **Mais flexível para padrões de comunicação complexos.**

---

## 📌 Considerações

- Sempre finalize operações com `MPI_Wait` ou `MPI_Test`.
- Nunca acesse buffers usados em `MPI_Isend` ou `MPI_Irecv` antes da confirmação de finalização.

---

## 🧪 Exemplo de saída:

```
Processo 0 calculou a soma: 28
Processo 0 enviou a mensagem para o processo 1
Processo 1 recebeu uma mensagem do processo 0
Processo 1 calculou a soma: 28
```

Ambos os processos realizaram a mesma computação com os dados compartilhados entre eles, de forma eficiente e não bloqueante.
