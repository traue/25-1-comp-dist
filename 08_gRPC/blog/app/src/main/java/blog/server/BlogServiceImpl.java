package blog.server;

import org.bson.Document;

import com.google.common.annotations.VisibleForTesting;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

import br.mack.blog.BlogServiceGrpc;
import io.grpc.Status;


public final class BlogServiceImpl extends BlogServiceGrpc.BlogServiceImplBase {

    @VisibleForTesting
    static final String BLOG_COULDNT_BE_CREATED = "O blog não pode ser criado!";

    @VisibleForTesting
    static final String BLOG_COULDNT_BE_DELETED = "O blog não pode ser deletado!";

    @VisibleForTesting
    static final String BLOG_NOT_FOUND = "Blog não encontrado!";

    @VisibleForTesting
    static final String BLOG_CANNOT_BE_EMPTY = "O blog não pode ser vazio!";

    private final MongoCollection<Document> mongoCollection;

    public BlogServiceImpl(MongoClient client) {
        MongoDatabase db = client.getDatabase("blogdb");
        mongoCollection = db.getCollection("blog");
    }

    private io.grpc.StatusRuntimeException error(Status status, String message, String augmentMessage) {
        return status.withDescription(message)
            .augmentDescription(augmentMessage)
            .asRuntimeException();
    }
    

}