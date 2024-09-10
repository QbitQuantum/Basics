/*
   Cliente
   Aplicacao simples de cliente tcp que se conecta num
   IP e PORTA passados por parametro, envia um comando ao 
   servidor e escreve na saida padrao o retorno
*/
int main(int argc, char **argv) {
   // Declaracao de variaveis
   int sockfd;
   char buf[MAXDATASIZE + 1], error[MAXDATASIZE + 1];
   char server[MAXDATASIZE + 1], server_reply[MAXDATASIZE + 1];
   struct sockaddr_in servaddr;

   // Checa a presenca do parametro de IP e Porta
   // caso ausente, fecha o programa
   if (argc != 3) {
      strcpy(error,"uso: ");
      strcat(error,argv[0]);
      strcat(error," <IPaddress> <Port>");
      perror(error);
      exit(1);
   }

   // Cria um socket
   sockfd = Socket(AF_INET, SOCK_STREAM, 0);

   // Limpa o que estiver no ponteiro do socket que representa o servidor
   // Seta o socket do servidor como IPv4 e seta a porta de conexao para a porta da aplicacao.
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port   = htons(atoi(argv[2]));
   
   // Converte o IP recebido na entrada para a forma binária da struct
   InetPton(AF_INET, argv[1], servaddr);
   
   // Conecta o socket local com o socket servidor
   Connect(sockfd, servaddr);
   
  	// Escrever IP e porta do servidor na saida padrao
   printf("Server: IP %s - Port %d\n", argv[1], atoi(argv[2]));
   
   // Coletar informacoes sobre o socket com o servidor
   servaddr = Getsockname(sockfd, servaddr);

   // Converter informacao do IP de binario para string
   // armazenar o resultado no buffer
   InetNtop(AF_INET, server, servaddr);
  	
  	// Escrever IP e porta do cliente no socket na saida padrao
  	printf("Client: IP %s - Port %d\n", server, ntohs(servaddr.sin_port));
  	
   // lê uma cadeia de caracteres do teclado
   printf("Digite um comando:\n");
   fgets(buf, MAXDATASIZE, stdin);
   
   // Imprime a linha de comando digitada pelo usuario
   printf("Linha de comando digitada: %s", buf);
   
   // envia os dados lidos ao servidor
   Write(sockfd , buf);

   // le os dados enviados pelo servidor
   Read(sockfd, server_reply);
   
   // Imprime a linha de comando devolvida pelo servidor
   printf("Linha de comando recebida: %s\n", server_reply);
   
   exit(0);
}