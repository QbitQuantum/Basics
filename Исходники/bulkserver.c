void HandleClient(int sock) {
  char buffer[BUFFSIZE];
  char *tailptr;
  int received = -1;
  long long int respsize,sendsize;
  char* blockptr = malloc(BLOCKSIZE);
  memset(blockptr,0xaa,BLOCKSIZE);

  /* Receive message */
  if ((received = recv(sock, buffer, BUFFSIZE-1, 0)) < 0) {
    Die("Failed to receive initial bytes from client");
  }
  /* get the client request - for now, just expect a number which is the size of the
     expected response message */
  buffer[received] = 0; /* parsing needs to know where the input string ends.... */
  respsize = strtoll(buffer, &tailptr,10);
  fprintf(stderr, "client request (\"%s\")",buffer);
  if (errno) {
      Die("\nFailed to parse client request");
    } else {
      switch ( *tailptr ) {
        case 'k' :
        case 'K' :
          respsize <<= 10;
          break;
        case 'm' :
        case 'M' :
          respsize <<= 20;
          break;
        case 'g' :
        case 'G' :
          respsize <<= 30;
          break;
      };
      fprintf(stderr, ", parsed request as %lld bytes\n",respsize);
    }
  /* Send bytes and check for more incoming data in loop */
#ifdef ZEROCOPY

  char tmpn[] = "/tmp/XXXXXX" ; 
  int   tmpfd = mkstemp(tmpn);
  ftruncate(tmpfd,respsize);

  while (respsize > 0) {
    sendsize = respsize > MAX_RW_COUNT ? MAX_RW_COUNT : respsize;
    respsize -= sendsize;
    /* Send the next block */
    if (sendfile(sock, tmpfd, 0, sendsize) != sendsize) {
      Die("Failed to send bytes to client");
    }
  }

  close(tmpfd);
  unlink(tmpn);
  
#else
  while (respsize > 0) {
    sendsize = respsize > BLOCKSIZE ? BLOCKSIZE : respsize;
    respsize -= sendsize;
    /* Send the next block */
    if (send(sock, blockptr, sendsize, 0) != sendsize) {
      Die("Failed to send bytes to client");
    }
  }
#endif
  close(sock);
}