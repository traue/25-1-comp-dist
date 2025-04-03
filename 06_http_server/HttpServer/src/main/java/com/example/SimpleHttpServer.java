package com.example;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class SimpleHttpServer {
    public static void main(String[] args) {
        int port = 8080;
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Servidor HTTP ouvindo na porta " + port);

            while (true) {
                try (Socket clientSocket = serverSocket.accept()) {
                    System.out.println("Cliente conectado: " + clientSocket.getInetAddress());

                    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    OutputStream out = clientSocket.getOutputStream();

                    String requestLine = in.readLine();
                    System.out.println("Requisição: " + requestLine);

                    String line;
                    while (!(line = in.readLine()).isEmpty()) {
                        System.out.println("Header: " + line);
                    }

                    String responseBody = "<html><body><h1>Olá, mundo!</h1></body></html>";
                    byte[] contentBytes = responseBody.getBytes(StandardCharsets.UTF_8);

                    String response = "HTTP/1.1 200 OK\r\n" +
                                      "Content-Type: text/html; charset=UTF-8\r\n" +
                                      "Content-Length: " + contentBytes.length + "\r\n" +
                                      "Connection: close\r\n" +
                                      "\r\n";

                    out.write(response.getBytes(StandardCharsets.UTF_8));
                    out.write(contentBytes);
                    out.flush();

                    System.out.println("Resposta enviada.");
                } catch (IOException e) {
                    System.err.println("Erro ao processar a requisição: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao iniciar o servidor: " + e.getMessage());
        }
    }
}
