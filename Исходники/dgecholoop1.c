void dg_echo2(int sockfd, SA *pcliaddr, socklen_t clilen)
{
  socklen_t len;
  char mesg[MAXLINE];

  Signal(SIGINT, recvfrom_int);

  for ( ; ; ) {
    len = clilen;
    Recvfrom(sockfd, mesg, MAXLINE, 0 , pcliaddr, &len);

    count++;
  }
}