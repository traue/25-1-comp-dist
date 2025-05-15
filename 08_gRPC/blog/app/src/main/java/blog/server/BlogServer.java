package blog.server;

import java.io.IOException;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;

import io.grpc.Server;
import io.grpc.ServerBuilder;

public class BlogServer {
    
    public static void main(String[] args) throws InterruptedException, IOException {
        
        int port = 50051;

        MongoClient client = MongoClients.create("mongodb://root:root@localhost:20017");

        Server server = ServerBuilder.forPort(port)
                .addService(new BlogServiceImpl(client))
                .build();

        server.start();
        System.out.println("Servidor inicializado!");
        System.out.println("Escutando na porta " + port);

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
                System.out.println("Recebido uma requisição de shutdown");
                server.shutdown();
                client.close();
                System.out.println("Servidor parado!");
            }
        ));
        
        server.awaitTermination();
    }
}
