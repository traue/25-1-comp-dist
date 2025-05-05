#include <stdio.h>
#include <mpi.h>

#define MESSAGE_SIZE 8  // Número de elementos a serem enviados/recebidos

int main(int argc, char* argv[]) {
    int rank;

    MPI_Init(&argc, &argv);  // Inicializa o ambiente MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Descobre o rank (ID) do processo

    if (rank == 0) {
        MPI_Request send_request;  // Requisição para o envio não bloqueante

        // Inicializa o vetor de inteiros
        int message[MESSAGE_SIZE];
        for (int i = 0; i < MESSAGE_SIZE; ++i) {
            message[i] = i;
        }

        // Envia o vetor para o processo 1 usando envio não bloqueante
        MPI_Isend(message, MESSAGE_SIZE, MPI_INT, 1, 0,
                  MPI_COMM_WORLD, &send_request);

        // Enquanto o envio ocorre em segundo plano, o processo 0 pode continuar computando
        int sum = 0;
        for (int i = 0; i < MESSAGE_SIZE; ++i) {
            sum += message[i];
        }

        printf("Processo 0 calculou a soma: %d\n", sum);

        // Aguarda a finalização da operação de envio
        MPI_Wait(&send_request, MPI_STATUS_IGNORE);
        printf("Processo 0 enviou a mensagem para o processo 1\n");

    } else if (rank == 1) {
        int received_message[MESSAGE_SIZE];  // Buffer para armazenar a mensagem recebida
        MPI_Request recv_request;            // Requisição de recepção

        // Recepção não bloqueante da mensagem do processo 0
        MPI_Irecv(received_message, MESSAGE_SIZE, MPI_INT,
                  0, 0, MPI_COMM_WORLD, &recv_request);

        // Espera até que a recepção esteja concluída
        MPI_Wait(&recv_request, MPI_STATUS_IGNORE);
        printf("Processo 1 recebeu uma mensagem do processo 0\n");

        // Calcula a soma dos elementos recebidos
        int sum = 0;
        for (int i = 0; i < MESSAGE_SIZE; ++i) {
            sum += received_message[i];
        }
        printf("Processo 1 calculou a soma: %d\n", sum);
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}

// compilar: mpicc -o nonblocking nonblocking.c
// executar: mpirun -np 2 ./nonblocking