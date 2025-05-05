
# 📦 Compartilhando Dados com MPI_Pack e MPI_Unpack

## 📝 Descrição do Código

Este programa em MPI demonstra como compartilhar múltiplos dados de **tipos diferentes** entre processos MPI utilizando as funções `MPI_Pack` e `MPI_Unpack`.

Ele permite que o **processo 0** leia dois valores (`int a` e `double b`) a partir da entrada padrão, empacote esses dados em um único buffer, transmita esse buffer para todos os outros processos via `MPI_Bcast`, e, em seguida, **todos os processos (inclusive o 0)** imprimem os dados recebidos.

---

## 🔄 Funcionamento do Programa

1. **Inicialização MPI**
   - `MPI_Init` inicializa o ambiente MPI.
   - Cada processo descobre seu `rank` com `MPI_Comm_rank`.

2. **Entrada e Empacotamento**
   - O processo 0 lê dois valores: um inteiro `a` e um double `b`.
   - Ele empacota esses dois valores no buffer `packbuff` usando `MPI_Pack`.
   - O tamanho total do buffer empacotado (`packedsize`) é mantido para referência posterior.

3. **Transmissão dos dados**
   - Primeiro, o processo 0 envia `packedsize` para os demais usando `MPI_Bcast`.
   - Em seguida, transmite o buffer `packbuff` (com os dados empacotados) também via `MPI_Bcast`.

4. **Desempacotamento**
   - Todos os processos que não são o processo 0 recebem o buffer e o desempacotam com `MPI_Unpack`.
   - A ordem do desempacotamento deve ser a mesma do empacotamento.

5. **Impressão**
   - Todos os processos imprimem os valores de `a` e `b` que receberam.

6. **Encerramento**
   - O programa continua em loop até que **`a < 0` ou `b < 0`**, o que encerra o `do-while`.
   - `MPI_Finalize` finaliza o ambiente MPI.

---

## 📌 Conceitos-chave

### 🔹 `MPI_Pack`
Permite empacotar dados de diferentes tipos em um buffer contínuo de bytes, ideal para transmissão única.

### 🔹 `MPI_Unpack`
Extrai os dados empacotados de volta às variáveis originais, respeitando a mesma ordem usada no empacotamento.

### 🔹 `MPI_Bcast`
Transmite dados de um processo (raiz) para todos os outros processos no comunicador.

---

## ✅ Vantagens do Empacotamento

- Facilita o envio de **estruturas complexas** ou **múltiplos tipos de dados** de forma eficiente.
- Reduz o número de chamadas de envio (`MPI_Send`/`MPI_Bcast`).
- Evita problemas de alinhamento de memória entre tipos diferentes.

---

## 🧪 Exemplo de Execução

Ao rodar com 4 processos:

```bash
mpicc -o sharingData sharingData.c
mpirun -np 4 ./sharingData
```

Entrada:
```
10 3.5
```

Saída:
```
Processo 0 recebeu 10 e 3.500000
Processo 1 recebeu 10 e 3.500000
Processo 2 recebeu 10 e 3.500000
Processo 3 recebeu 10 e 3.500000
```

---

## 🚧 Observação

O código assume que `packbuff` tem espaço suficiente (100 bytes). Para dados mais complexos ou grandes, é recomendável **calcular previamente o tamanho necessário com `MPI_Pack_size`**.

