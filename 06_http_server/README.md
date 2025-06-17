# Roteiro de Aula Prática

## Servidor HTTP Básico com Socket


### Revisão teórica

- **Modelo Cliente-Servidor e Sockets:** Um socket é um ponto de conexão de rede que permite troca de dados entre processos em máquinas diferentes. Sockets TCP fornecem um canal de bytes confiável (conexão orientada), pelo qual protocolos de nível superior podem ser implementados (por exemplo, HTTP usa sockets TCP por baixo).

<br>

- **Protocolo HTTP (HyperText Transfer Protocol):** É um protocolo de aplicação do tipo requisição-resposta no modelo cliente-servidor. Um cliente (por exemplo, um navegador web) abre uma conexão TCP com o servidor e envia uma mensagem de requisição HTTP; o servidor então processa e devolve uma mensagem de resposta HTTP correspondente. O HTTP é um protocolo stateless (sem estado) – cada requisição é independente e o servidor não mantém contexto de requisições anteriores. Isso simplifica a lógica do servidor: ele trata cada conexão/requisição separadamente (não precisa lembrar do cliente após responder).


<br>

- **Formato de Mensagens HTTP:** Estrutura básica de uma requisição e resposta HTTP:
    <br>
    - **Requisição:** uma linha de início com método, caminho e versão (ex: GET /index.html HTTP/1.1), seguida de cabeçalhos (um por linha, ex: Host: localhost:8080), uma linha em branco e possivelmente um corpo (em métodos como POST). Para nosso exercício, focaremos em requisições GET simples, possivelmente sem corpo.
    <br>
    - **Resposta:** uma linha de status com versão e código (ex: HTTP/1.1 200 OK), cabeçalhos de resposta (ex: Content-Type: text/html; charset=UTF-8 e Content-Length indicando tamanho do corpo), linha em branco e então o corpo (HTML ou texto) da resposta. Para saber mais sobre os códigos de status, [leia este material](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status)
    <br>
        - Tanto requisições quanto respostas HTTP são texto com quebras de linha \r\n. O fim dos cabeçalhos é indicado por uma linha vazia (dupla quebra de linha). O servidor precisará identificar esse fim ao ler a requisição.
    <br>
    - **Portas e Acesso:** Lembre-se que o HTTP por padrão utiliza a porta 80 (ou 443 para HTTPS), mas que em nosso laboratório usaremos uma porta alta (e.g. 8080) para evitar necessidade de privilégios de administrador ao abrir o socket do servidor. Os grupos poderão testar localmente via localhost:8080 ou usar uma instância na AWS (ajustada para aceitar conexões na porta escolhida) ou Codespaces com porta publicada, se desejarem acesso externo. O importante é todos usarem portas diferentes ou localhost para não haver conflito no laboratório.
    <br>

### Descrição do Problema e Objetivos do Exercício

**Implementação Manual vs. Frameworks:** Objetivo educacional: não serão usados frameworks web prontos (como Flask, Django, Spring) nesta prática. Em vez disso, vocês construirão a lógica HTTP manualmente sobre sockets para consolidar os fundamentos de comunicação e entender o que acontece por baixo dos panos em servidores web. Em aplicações reais normalmente se usa servidores e bibliotecas robustas, mas este exercício pedagógico ilustra o funcionamento interno de um servidor web básico.

**Problema:** Construir um servidor web básico capaz de aceitar conexões HTTP e responder a requisições do tipo GET, servindo uma página simples. Cada grupo deve implementar seu próprio servidor usando sockets TCP, na linguagem de sua escolha (Java ou Python), do zero. O servidor será mínimo, mas funcional o suficiente para comunicar-se com um navegador ou cliente HTTP simples.

#### Objetivos
- Entender os conceitos de comunicação em rede (cliente-servidor, troca de mensagens) no contexto de sistemas distribuídos.
- Entender a dinâmica do protocolo HTTP ao implementá-lo manualmente: como uma requisição é recebida e interpretada e como formar uma resposta válida.
- Consolidar o uso de sockets TCP em Java/Python para construir protocolos de aplicação.
- Exercitar trabalho em equipe na construção de um sistema distribuído simples, dividindo tarefas de design, implementação, teste e integração.
- Ao final da aula, cada grupo terá um servidor HTTP básico rodando, capaz de responder “Hello World” (ou conteúdo definido) via HTTP para um browser. Isso exemplifica como serviços web funcionam e prepara terreno para discutir servidores web reais e frameworks em aulas futuras.

#### Escopo

O servidor implementado não terá todas as funcionalidades HTTP (por enquanto!), apenas o essencial para responder a requisições GET simples. Não haverá suporte a HTTPS, autenticação, métodos além de GET (a não ser em desafios extras), ou gestão de múltiplas conexões simultâneas (inicialmente). Cada grupo deve documentar brevemente seu código (comentários) para fixar ideias.

#### Preparação do Ambiente de Desenvolvimento

Antes de partir para a implementação:

- Escolha da Linguagem: Cada grupo decide entre Java ou Python, conforme preferência ou para equilibrar desafios (Java pode exigir mais código cerimonial; Python, atenção a detalhes de bytes/strings).
- Setup no Laboratório: Como as máquinas não permitem instalar software sem admin, assegure-se de que já há JDK (Java Development Kit) e Python instalados. Se uma versão específica for necessária (Java 8+ ou Python 3+), verifique antecipadamente.
- GitHub Codespaces/AWS: Opcionalmente, vocês podem usar o GitHub Codespaces (ambiente de desenvolvimento no navegador, já configurado com sudo e ferramentas) ou uma instância EC2 na AWS. Isso pode contornar limitações da máquina local e permite acesso remoto para testes. Garanta que todos sabem abrir uma Codespace ou conectar na VM AWS. Caso usem AWS, lembrar de configurar o Security Group para liberar a porta (8080, por exemplo) e de obter o IP público para testes externos.
- Sem Root/Admin: escolher portas acima de 1024 (por exemplo, 8080 ou 5000) para o servidor. Isso evita a necessidade de permissões elevadas, já que portas <1024 são privilegiadas em muitos sistemas ￼.
- Projeto/Arquivo Inicial: Cada grupo deve criar um novo projeto ou arquivo:
    - Java: um projeto simples (pode ser pelo VSCode, Codespaces ou IDE online) com uma classe principal Main ou SimpleHttpServer. Não há dependências externas – apenas usar java.net e java.io. Se estiverem em Codespaces, podem usar Maven ou Gradle se quiserem, mas não é obrigatório.
    - Python: um script .py novo (por ex. servidor_http.py). Garantir que usarão Python 3. No Codespaces, Python já deve estar disponível. Recomende adicionar #!/usr/bin/env python3 no topo se forem executar diretamente.
- Controle de Versão: Recomenda-se usarem Git para versionar o código, especialmente se estiverem no Codespaces ou GitHub. Isso ajuda na colaboração entre membros. Podem criar um repositório próprio para o projeto de aula (público ou privado conforme orientação do curso).
- Verificações Iniciais: Certifiquem-se de que os grupos conseguem executar um “Hello World” simples em seu ambiente (ex: imprimir algo no console) para garantir que está tudo configurado corretamente antes de mergulhar no código do servidor.


### Implementação Passo a Passo do Servidor HTTP

1.	Criar o Socket do Servidor (Socket de Escuta): Inicialmente, escrever o código para abrir um socket TCP do lado servidor:
    - Java: Usar a classe ServerSocket. Exemplo: ServerSocket serverSocket = new ServerSocket(8080); – isso abre a porta 8080 em modo escuta ￼. Trate possíveis exceções (por exemplo, usar throws IOException ou try-catch). Imprima no console algo como “Servidor ouvindo na porta 8080…” para indicar que o socket foi criado com sucesso.
    - Python: Utilizar o módulo socket. Exemplo:


```python
import socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', 8080))
server_socket.listen(5)
print("Servidor ouvindo na porta 8080...")
```

Isso cria um socket TCP IPv4, associa à porta 8080 em todas interfaces locais, e começa a escutar com fila de até 5 conexões pendentes.

Nota: Escolhemos 8080 como porta de teste (pode ser outra alta se 8080 estiver ocupada). Lembrar que se a porta estiver em uso, o bind dará erro – mudar para outra ou finalizar processo ocupando-a.
Dica: Em Python, pode ser útil configurar server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) antes do bind para reusar a porta imediatamente após encerrar o programa (evita erro de “Address already in use” em reexecuções rápidas). Em Java, o ServerSocket costuma lidar bem com isso automaticamente.

---

2.	Aguardar e Aceitar uma Conexão de Cliente: Depois de iniciar o servidor, precisamos esperar que um cliente (ex: navegador) conecte, escreva um laço para aceitar conexões. Exemplo em Java:

```java
while (true) {
    Socket clientSocket = serverSocket.accept();
    // ... processa requisição ...
    // fecha clientSocket no final
}
```

Em Python, similar:

```python
while True:
    client_conn, client_addr = server_socket.accept()
    print(f"Conexão recebida de {client_addr}")
    # ... processa requisição ...
    # fecha client_conn no final
}
```


O método accept() bloqueia até chegar uma conexão. Quando um cliente conecta, ele retorna um novo socket para comunicação com aquele cliente (clientSocket em Java, client_conn em Python) e também informa o endereço do cliente.

Exiba uma mensagem ao aceitar, para log: “Cliente conectado: [IP]:[porta]”.

Observação: Este loop infinito implementa um servidor que roda até ser interrompido manualmente. Cada iteração tratará uma conexão por vez, atendendo um cliente de cada vez. Isso é suficiente por ora (no desafio extra veremos como lidar com múltiplos simultâneos). Conforme mencionado, este servidor básico atende um cliente por vez, pois HTTP é sem estado e não precisa guardar informações de conexões anteriores ￼. Importante: Depois de terminar de responder a um cliente, deve-se fechar o socket daquela conexão e voltar ao loop para aceitar o próximo; assim, o servidor fica disponível para novas conexões enquanto rodar ￼.

---
    
3.	Ler a Requisição HTTP do Cliente: Agora vem a parte crucial – ao aceitar a conexão, o servidor deve ler os dados enviados pelo cliente (a mensagem HTTP). Instruções:

Em Java: obter o InputStream do clientSocket (por ex. InputStream input = clientSocket.getInputStream();). Encapsule em um InputStreamReader e BufferedReader para facilitar leitura textual linha a linha:

```java
BufferedReader reader = new BufferedReader(new InputStreamReader(input));
String line = reader.readLine();
```

Leia repetidamente até encontrar uma linha vazia:

```java
while (line != null && !line.isEmpty()) {
    System.out.println(line);
    // (poderia fazer parsing aqui)
    line = reader.readLine();
}
```

Isso lerá a linha de requisição (ex: "GET / HTTP/1.1") e todos os cabeçalhos, terminando quando readLine() retornar uma string vazia (indicando a linha em branco final). Usar readLine() é conveniente pois ele já separa por \r\n.

Em Python: usar client_conn.recv(1024) para obter bytes. Como o HTTP request pode ter mais que 1024 bytes (vários cabeçalhos), pode ser necessário chamar recv em loop até obter toda a requisição. Uma alternativa simples é usar client_conn.makefile('r') para tratar o socket como arquivo e então usar .readline(). Por exemplo:

```python
import sys
client_socket_file = client_conn.makefile('rwb')  # modo leitura/escrita binária
request_line = client_socket_file.readline().decode('utf-8')
print(request_line.strip())
headers = ""
# ler cabeçalhos até linha em branco
while True:
    line = client_socket_file.readline().decode('utf-8')
    if line == "\r\n" or line == "":
        break
    headers += line
print(headers)
```

(Também é possível usar recv repetidamente e procurar por \r\n\r\n dentro dos dados recebidos para separar cabeçalhos).

Dicas de Parsing: Para simplificar, pode-se ignorar todos os cabeçalhos na implementação básica e só usar a primeira linha. Entretanto, por boa prática, imprimir todos eles no console ajuda a depurar e entender o que o cliente mandou. Você pode armazenar a primeira linha em alguma variável, para extrair dela o método (deve ser “GET”) e o caminho solicitado.

Ex: ao conectar com um navegador em localhost:8080, a saída no console do servidor deve mostrar algo como:

```
GET / HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0...
Accept: text/html,...
(demais cabeçalhos)
```

Isso confirma que a requisição foi recebida corretamente. (Neste momento, o navegador ficará esperando uma resposta, provavelmente mostrando uma página em branco ou carregando.)

---

4.	Processar a Requisição (identificar o recurso solicitado): Para nosso servidor básico, o processamento será mínimo:

Extraia o método HTTP e o caminho da primeira linha da requisição. Ela deve ter o formato "GET /algum/recurso HTTP/1.1". Em Java/Python, você pode fazer um split() dessa linha por espaços. Por exemplo:


```java
String[] parts = requestLine.split(" ");
String method = parts[0];
String path = parts[1];
```

Em Python:

```python
parts = request_line.strip().split()
method = parts[0]
path = parts[1]
```

Verifique se o method é “GET”. (Neste exercício esperamos apenas GET, mas poderia haver outros. Se não for GET, poderíamos ignorar ou responder com erro, mas não é obrigatório implementar isso agora.)

O path representa o recurso pedido. Exemplos: “/” (raiz), “/index.html”, “/sobre”. Para simplicidade, podemos definir que qualquer caminho requisitado retornará a mesma resposta estática (por exemplo, uma página HTML simples ou mensagem). Alternativamente, se quisermos um comportamento mínimo de 404, podemos decidir que se o caminho não for “/” retornaremos um texto de “Não encontrado” com status 404 (ver desafio extra).

Decidir Conteúdo de Resposta: Sugestão: uma página HTML bem simples, ou uma mensagem de texto "Hello, World from my server!". Pode ser uma resposta fixa suficiente para reconhecimento. Guarde essa string de conteúdo em uma variável (por ex. responseContent).

---

5.	Preparar a Resposta HTTP: Com base na requisição, monte a mensagem de resposta adequada. Lembre-se do formato de resposta HTTP:

Primeiro, a linha de status. Usaremos "HTTP/1.1 200 OK" para indicar sucesso (ou "HTTP/1.1 404 Not Found" se forem implementar resposta a recurso desconhecido). Adicione \r\n ao final dessa linha.

Em seguida, os cabeçalhos necessários seguidos de \r\n. Pelo menos dois cabeçalhos importantes:

Content-Type: indicar o tipo de conteúdo retornado. Ex: "Content-Type: text/html; charset=UTF-8" se for HTML, ou "Content-Type: text/plain; charset=UTF-8" se for texto puro. Dica: especificar charset para acentos ficarem corretos.

Content-Length: o tamanho em bytes do corpo da resposta. Isso não é estritamente obrigatório se fecharmos a conexão após enviar (o cliente saberá que acabou quando a conexão fechar), mas é uma boa prática incluir para conformidade com HTTP/1.1 ￼. Calcule o tamanho da string de conteúdo em bytes UTF-8. Em Java, content.getBytes("UTF-8").length; em Python, len(response_body.encode('utf-8')).

- Connection: close para deixar explícito que vamos fechar a conexão após responder (como não estamos implementando keep-alive/persistência, informar isso evita o browser ficar esperando mais dados).
- Depois dos cabeçalhos, adicione uma linha em branco (\r\n) para terminar a seção de cabeçalhos.
- Por fim, concatene o corpo (conteúdo HTML ou texto).
- Monte tudo em uma única string (ou sequência de bytes). Por exemplo, em Python:

```
response = "HTTP/1.1 200 OK\r\n"
response += "Content-Type: text/html; charset=UTF-8\r\n"
response += f"Content-Length: {len(response_body.encode('utf-8'))}\r\n"
response += "Connection: close\r\n"
response += "\r\n"
response += response_body
```

Em Java, pode-se construir com StringBuilder ou string multi-linha:

```
String response = "HTTP/1.1 200 OK\r\n"
                 + "Content-Type: text/html; charset=UTF-8\r\n"
                 + "Content-Length: " + contentBytes.length + "\r\n"
                 + "Connection: close\r\n"
                 + "\r\n"
                 + responseBody;
```


Nota: Se o grupo optou por sempre fechar a conexão após responder, a ausência de Content-Length não impede o funcionamento, pois o cliente recebe EOF. Porém, alguns clientes podem acusar “Invalid HTTP response” se algo estiver fora do esperado. Usar HTTP/1.1 sem Content-Length e sem fechar conexão levará o cliente a esperar indefinidamente, então garanta ou Content-Length ou fechamento explícito. Para simplificar, estamos incluindo Content-Length e fechando a conexão em todos os casos.


---

6.	Enviar a Resposta ao Cliente: Agora escreva a resposta montada de volta através do socket do cliente:

Em Java: obter o OutputStream do clientSocket. Ex: OutputStream out = clientSocket.getOutputStream();. Então enviar os dados:

```java
out.write(response.getBytes(StandardCharsets.UTF_8));
out.flush();
```
(Pode usar PrintWriter também, mas cuidado para enviar corretamente os \r\n).

- Em Python: você pode usar client_conn.sendall(response.encode('utf-8')). sendall garante enviar até o fim do buffer. Certifique-se de codificar a string para bytes.
- Após enviar, registre no console que a resposta foi enviada, e idealmente o que foi enviado (pelo menos o status ou algo).
- Encerrar a Conexão: Feche o socket do cliente após enviar a resposta, já que não implementaremos persistenza. Em Java: clientSocket.close();. Em Python: client_conn.close().
- O loop então retorna ao início para aceitar outro cliente, se houver. (Se quiser, pode colocar uma condição de sair do loop após uma certa quantidade de conexões, mas não é necessário – pode interromper o programa manualmente quando terminar os testes).


---


7.	Testar o Servidor (ver próxima seção): Assim que um grupo terminar os passos acima, ele deve ter um servidor funcional. Instrua-os a testar (detalhado abaixo). Muitas vezes serão necessários alguns ajustes se a resposta não estiver nos conformes (por exemplo, esquecimento de um \r\n ou um header mal formatado). Debugar comparando a saída do servidor com exemplos conhecidos pode ajudar.
	
---

8.	Iterar e Refinar: Conforme os testes, os alunos podem precisar voltar a algum passo para corrigir parsing ou formatação. Incentive-os a usar prints no console para verificar valores (por exemplo, imprimir o conteúdo da resposta completa antes de enviar, para conferir os \r\n). Uma vez tudo funcionando para uma requisição simples, o objetivo principal está alcançado!


## Atividzade (entregar via moodle)

Crie um servidor Web em Java que escute a porta 8082 e mapeia uma pasta chama "www" (dentro do projeto) usando o protocolo HTTP.

Em grupos (o mesmo já configurado aqui no Moodle)
