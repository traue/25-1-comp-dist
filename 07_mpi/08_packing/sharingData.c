#include <stdio.h>
#include "mpi.h"  // Inclusão da biblioteca MPI

int main(int argc, char* argv[]) {

    int rank;              // ID do processo
    int a;                 // Variável inteira a ser compartilhada
    double b;              // Variável double a ser compartilhada
    char packbuff[100];    // Buffer para empacotar os dados
    int packedsize;        // Tamanho atual dos dados empacotados
    int retrieve_pos;      // Posição para desempacotar os dados

    MPI_Init(&argc, &argv);  // Inicializa o ambiente MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtém o ID (rank) do processo atual

    do {
        packedsize = 0;  // Reinicializa o tamanho empacotado a cada iteração

        if (rank == 0) {
            // O processo 0 lê os dados do usuário
            scanf("%d %lf", &a, &b);

            // Empacota a variável 'a' (int) no buffer
            MPI_Pack(&a, 1, MPI_INT, packbuff, 100, &packedsize, MPI_COMM_WORLD);

            // Empacota a variável 'b' (double) no mesmo buffer
            MPI_Pack(&b, 1, MPI_DOUBLE, packbuff, 100, &packedsize, MPI_COMM_WORLD);
        }

        // Transmite o tamanho dos dados empacotados para todos os processos
        MPI_Bcast(&packedsize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // Transmite o buffer empacotado para todos os processos
        MPI_Bcast(packbuff, packedsize, MPI_PACKED, 0, MPI_COMM_WORLD);

        if (rank != 0) {
            retrieve_pos = 0;  // Começa a desempacotar do início do buffer

            // Desempacota a variável 'a'
            MPI_Unpack(packbuff, packedsize, &retrieve_pos, &a, 1, MPI_INT, MPI_COMM_WORLD);

            // Desempacota a variável 'b'
            MPI_Unpack(packbuff, packedsize, &retrieve_pos, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        }

        // Todos os processos imprimem os valores recebidos
        printf("Processo %d recebeu %d e %lf\n", rank, a, b);

    } while (a >= 0 && b >= 0);  // Continua até que um dos valores seja negativo

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}


// compilar: mpicc -o sharingData sharingData.c
// executar: mpirun -np 4 ./sharingData