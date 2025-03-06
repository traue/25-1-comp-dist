#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

    // Inicializa Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("Falha ao iniciar o Winsock\n");
        return 1;
    }

    // criando o socket:
    SOCKET network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(network_socket == INVALID_SOCKET) {
        printf("Erro ao criar socket\n");
        WSACleanup();
        return 1;
    }

    // especifica o endereço para o socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // verifica a conexão:
    if (connection_status == SOCKET_ERROR) {
        printf("Erro ao conectar ao socket remoto\n");
        closesocket(network_socket);
        WSACleanup();
        return 1;
    }

    char server_response[256];
    recv(network_socket, server_response, sizeof(server_response), 0);

    // Exibe os dados recebidos do servidor
    printf("O servidor enviou o seguinte: %s\n", server_response);

    // Fecha o socket
    closesocket(network_socket);

    // Finaliza Winsock
    WSACleanup();

    return 0;
}
