void recv_server(void)
{
  struct sockaddr_in server;
  struct sockaddr_in client;
  in_addr_t tmpaddr;
  unsigned char inbuf[1024];
  int sockfd;
  int nbytes;
  int optval;
  int offset;
  socklen_t addrlen;

  /* Create a new UDP socket */

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    {
      printf("server: socket failure: %d\n", errno);
      exit(1);
    }

  /* Set socket to reuse address */

  optval = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&optval, sizeof(int)) < 0)
    {
      printf("server: setsockopt SO_REUSEADDR failure: %d\n", errno);
      exit(1);
    }

  /* Bind the socket to a local address */

  server.sin_family      = AF_INET;
  server.sin_port        = HTONS(PORTNO);
  server.sin_addr.s_addr = HTONL(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) < 0)
    {
      printf("server: bind failure: %d\n", errno);
      exit(1);
    }

  /* Then receive up to 256 packets of data */

  for (offset = 0; offset < 256; offset++)
    {
      printf("server: %d. Receiving up 1024 bytes\n", offset);
      addrlen = sizeof(struct sockaddr_in);
      nbytes = recvfrom(sockfd, inbuf, 1024, 0,
                        (struct sockaddr*)&client, &addrlen);

      tmpaddr = ntohl(client.sin_addr.s_addr);
      printf("server: %d. Received %d bytes from %d.%d.%d.%d:%d\n",
             offset, nbytes,
             tmpaddr >> 24, (tmpaddr >> 16) & 0xff,
             (tmpaddr >> 8) & 0xff, tmpaddr & 0xff,
             ntohs(client.sin_port));

      if (nbytes < 0)
        {
          printf("server: %d. recv failed: %d\n", offset, errno);
          close(sockfd);
          exit(-1);
        }

      if (nbytes != SENDSIZE)
        {
          printf("server: %d. recv size incorrect: %d vs %d\n", offset, nbytes, SENDSIZE);
          close(sockfd);
          exit(-1);
        }

      if (offset < inbuf[0])
        {
          printf("server: %d. %d packets lost, resetting offset\n", offset, inbuf[0] - offset);
          offset = inbuf[0];
        }
      else if (offset > inbuf[0])
        {
          printf("server: %d. Bad offset in buffer: %d\n", offset, inbuf[0]);
          close(sockfd);
          exit(-1);
        }

      if (!check_buffer(inbuf))
        {
          printf("server: %d. Bad buffer contents\n", offset);
          close(sockfd);
          exit(-1);
        }
    }
  close(sockfd);
}