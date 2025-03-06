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

    char server_message[256] = "Você alcançou o servidor! Congrats";

    // Criação do socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == INVALID_SOCKET) {
        printf("Erro ao criar socket\n");
        WSACleanup();
        return 1;
    }

    // Define o endereço do servidor
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind do socket
    if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Erro ao fazer bind\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    listen(server_socket, 5);
    printf("Servidor aguardando conexões...\n");

    SOCKET client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == INVALID_SOCKET) {
        printf("Erro ao aceitar conexão\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Envia a mensagem
    send(client_socket, server_message, sizeof(server_message), 0);

    // Fecha sockets
    closesocket(client_socket);
    closesocket(server_socket);

    // Finaliza Winsock
    WSACleanup();

    return 0;
}