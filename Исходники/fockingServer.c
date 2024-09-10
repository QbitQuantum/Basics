int main()
{
int listen_sock, conn_sock;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

listen_sock = socket(AF_INET, SOCK_STREAM, 0);
if (listen_sock == -1)
 {
    printf("khong tao duoc socket\n");
    return 0;
 }
 printf("Tao socket thanh cong\n");

server_address.sin_family = AF_INET;
inet_aton("127.0.0.1",&server_address.sin_addr);
server_address.sin_port = htons(5500);
server_len = sizeof(server_address);

if(bind(listen_sock, (struct sockaddr *)&server_address,server_len)<0)
{
	printf("bind failed.\n");
    return 0;
}
printf("bind done\n");
int check = listen(listen_sock,10);
if (check == -1)
 {
 printf("error connect");
 return 0;
 }
printf("waiting connect ...\n");
while(1) {
		client_len = sizeof(client_address);
		conn_sock = accept(listen_sock,(struct sockaddr *)&client_address, &client_len);
		if(conn_sock==-1){
			printf("error connect\n");
			return 1;
		}else{
			printf("Accept new connection\n");
		}
		if(fork() == 0){
			close(listen_sock);

			int sentBytes,revedBytes,i;
			//char buff[1024];
			int chose;
			while(1){
					revedBytes = recv(conn_sock,buff,1024,0);
					if(revedBytes < 0) break;
					if(strcmp(buff,"S")==0) chose = 1;
					else if(strcmp(buff,"M")==0) chose =2;
					else if(strcmp(buff,"exit")==0) chose = 3;									
					switch(chose){
					case 1:
						printf("Menu1 \n");
						while(1){
						    	revedBytes = recv(conn_sock,buff,1024,0);
						        buff[revedBytes]='\0';
						        if(strcmp(buff,"Q")==0) break;
						        printf("string send by client : %s\n",buff);
						        for(i=0;buff[i]!=NULL;i++)
	   	 						m[i]=buff[i]; 
								n=p*q; 
            					t=(p-1)*(q-1); 
           						 ce();
           						 encrypt();
           							 //decrypt();
           						 for (i = 0; i < strlen(buff); i++)
          							{				
	 								buff[i]=en[i];
					       			}
					    			sentBytes=send(conn_sock,buff,1024,0);
						    		}
								printf("exit menu1 \n");
						break;
					case 2:
						printf("\n Menu2");
						while(1){
						    	revedBytes = recv(conn_sock,buff,1024,0);
						        buff[revedBytes]='\0';
						        if(strcmp(buff,"Q")==0) break;
						        printf("string send by client : %s\n",buff);
						        n=p*q; 
           			 			t=(p-1)*(q-1); 
            					for(i=0;buff[i]!=NULL;i++)
            						en[i]=buff[i] ;
            					ce();decrypt();
           				 		for (i = 0; m[i]!=-1; i++)
            					{
            						buff[i]=(char)m[i];
           			 			}
           			 			buff[i]='\0';
           			 			printf("%s\n",buff);
            					sentBytes=send(conn_sock,buff,1024,0);
						}
						printf("exit menu2 \n");
					break;
					case 3: 
					close(conn_sock);
					break;
					default:
					break;
				}
			}
			close(conn_sock);
			exit(1);
		}
		signal(SIGCHLD,sig_chld);
	}
return 1;
}