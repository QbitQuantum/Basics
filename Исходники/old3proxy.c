/* 
 * main - Main routine for the proxy program runs the proxy server
 */
int main(int argc, char **argv)
{
  int listenfd, connfd, clientlen, ID=0;
  struct sockaddr_in clientaddr;
  struct sockaddr_in * passClientaddr=&clientaddr;
  struct hostent *hp;
  char *haddrp;
  pthread_t tid[MAXTREAD];

 
  /* Check arguments */
  if(argc != 2){
    fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
    exit(0);
  }
  signal(SIGPIPE, SIG_IGN);
  listenfd=Open_listenfd(atoi(argv[1]));
  
  while(1){
    
    clientlen =sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr,(unsigned int *)&clientlen);
    
    //Determine the domain name and IP address of the client then send print statement
    hp=Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    haddrp =inet_ntoa(clientaddr.sin_addr);
    printf("Thread %d: Receieved request from %s (%s):\n",ID,hp->h_name,haddrp);

    //make and set known data to thread
    struct treadInfo thread;
    thread.clientfd=connfd;
    rio_readinitb(&thread.rioWithClient,thread.clientfd);
    thread.ID=ID;
    thread.sockaddr=*passClientaddr;
 
    //create new thread
    Pthread_create(&tid[ID], NULL,doit,&(void *)thread); 

    //add one to ID count
    ID++;
  }    
  exit(0);
}