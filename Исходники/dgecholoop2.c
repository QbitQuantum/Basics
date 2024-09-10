void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
  int n;
  socklen_t len;
  char mesg[MAXLINE];

  Signal(SIGINT, recvfrom_int);

  len = sizeof(n);
  Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, &len);
  if(len == sizeof(n))
    printf("initial SO_RCVBUF size: %d\n", n);
  else
    printf("Error getting SO_RCVBUF size.\n");
  
  n = 220 * 1024;
  /* Set the socket recvbuf size. By default*/
  /* it's  87380. */
  Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));
  printf("Set new SO_RCVBUF: %d\n", n);
  for ( ; ; ) {
    len = clilen;
    Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

    count++;
  }
}