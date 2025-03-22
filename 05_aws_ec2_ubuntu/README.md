# AWS EC2

Nessa aula subimos uma um ubuntu server em um serviço EC2 da AWS.

Se precisar executar novamente o script, coloque-o em "user data":

```sh
#!/bin/bash

# Atualiza sistema
apt update -y && apt upgrade -y

# Instala Python 3.12
apt install -y software-properties-common
add-apt-repository ppa:deadsnakes/ppa -y
apt update -y
apt install -y python3.12 python3.12-venv python3-pip
python3.12 -m pip install --upgrade pip

# Instala Java (OpenJDK 21 LTS)
apt install -y openjdk-21-jdk openjdk-21-jre

# Instala ferramentas de desenvolvimento em C
apt install -y build-essential gcc g++ gdb make valgrind

# Instala VSCode Server (web IDE)
curl -fsSL https://code-server.dev/install.sh | sh

# Instala o zip e o wget se não houve
apt install -y zip && wget

# Opcional daqui para baixo
# Inicia VSCode Server como serviço systemd
cat <<EOF > /lib/systemd/system/code-server.service
[Unit]
Description=VSCode Server
After=network.target

[Service]
Type=simple
User=ubuntu
ExecStart=/usr/bin/code-server --bind-addr 0.0.0.0:8080 --auth none
Restart=always

[Install]
WantedBy=multi-user.target
EOF

# Ativa e inicia o serviço VSCode Server
systemctl daemon-reload
systemctl enable code-server
systemctl start code-server
```


## Configurações da instância

O EC2 foi configurado da seguinte forma

- Ubuntu server 24
- t2.micro
- 8gb 
- Acesso via chave SSH (.pem)
- Security gruoup: compdist-sg (manter, por enquanto, apenas a ports 22 liberada)


QUaisquer dúvidas, consultar o vídeo disponibilizado pelo professor ou entrar em contato
