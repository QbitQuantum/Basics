int
main(int argc, char **argv)
{
   int               listenfd, connfd;
   socklen_t      clilen, n;
   struct sockaddr_in   servaddr, cliaddr;
   char           buff[MAXLINE];
   time_t            ticks;
   FILE *fp;

   listenfd = Socket(AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family      = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port        = htons(13);  /* daytime server */

   Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

   Listen(listenfd, LISTENQ);

   if ((fp = fopen("np09s_hw1_serv.log", "a")) == NULL) {
      printf("log file open error!\n");
      exit(0);
   };

   for ( ; ; ) {
      clilen = sizeof(cliaddr);
      connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
      ticks = time(NULL);
      fprintf(fp, "===================\n");
      fprintf (fp, "%.24s: connected from %s, port %d\n",
            ctime(&ticks),
            Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof (buff)),
            ntohs(cliaddr.sin_port));
      srand((int) ticks);
      n = Read(connfd, buff, sizeof(buff));
      buff[n] = 0;
      fprintf(fp, "id = %s\n", buff);
      ticks = time(NULL);
      snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
      Write(connfd, buff, strlen(buff));
      fprintf (fp, "%.24s: disconnected from %s, port %d\n",
            ctime(&ticks),
            Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof (buff)),
            ntohs(cliaddr.sin_port));
      fflush(fp);

      Close(connfd);
   }
}