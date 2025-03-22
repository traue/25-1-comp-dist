import socket
 
HOST = "localhost"
PORT = 8080
 
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

sock.sendall(str.encode("meu nome é Computação Distribuída ;-)\n"))
data = sock.recv(1024)
print(data)


