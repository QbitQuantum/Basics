void send_client(void)
{
#ifdef CONFIG_EXAMPLES_UDP_IPv6
  struct sockaddr_in6 server;
#else
  struct sockaddr_in server;
#endif
  unsigned char outbuf[SENDSIZE];
  socklen_t addrlen;
  int sockfd;
  int nbytes;
  int offset;

  /* Create a new UDP socket */

  sockfd = socket(PF_INETX, SOCK_DGRAM, 0);
  if (sockfd < 0)
    {
      printf("client socket failure %d\n", errno);
      exit(1);
    }

  /* Then send and receive 256 messages */

  for (offset = 0; offset < 256; offset++)
    {
      /* Set up the output buffer */

      fill_buffer(outbuf, offset);

      /* Set up the server address */

#ifdef CONFIG_EXAMPLES_UDP_IPv6
      server.sin6_family            = AF_INET6;
      server.sin6_port              = HTONS(PORTNO);

      server.sin6_addr.s6_addr16[0] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_1);
      server.sin6_addr.s6_addr16[1] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_2);
      server.sin6_addr.s6_addr16[2] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_3);
      server.sin6_addr.s6_addr16[3] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_4);
      server.sin6_addr.s6_addr16[4] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_5);
      server.sin6_addr.s6_addr16[5] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_6);
      server.sin6_addr.s6_addr16[6] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_7);
      server.sin6_addr.s6_addr16[7] = HTONS(CONFIG_EXAMPLES_UDP_SERVERIPv6ADDR_8);

      addrlen                       = sizeof(struct sockaddr_in6);
#else
      server.sin_family             = AF_INET;
      server.sin_port               = HTONS(PORTNO);
      server.sin_addr.s_addr        = HTONL(CONFIG_EXAMPLES_UDP_SERVERIP);

      addrlen                       = sizeof(struct sockaddr_in);
#endif

      /* Send the message */

      printf("client: %d. Sending %d bytes\n", offset, SENDSIZE);
      nbytes = sendto(sockfd, outbuf, SENDSIZE, 0,
                      (struct sockaddr*)&server, addrlen);
      printf("client: %d. Sent %d bytes\n", offset, nbytes);

      if (nbytes < 0)
        {
          printf("client: %d. sendto failed: %d\n", offset, errno);
          close(sockfd);
          exit(-1);
        }
      else if (nbytes != SENDSIZE)
        {
          printf("client: %d. Bad send length: %d Expected: %d\n",
                 offset, nbytes, SENDSIZE);
          close(sockfd);
          exit(-1);
        }

      /* Now, sleep a bit.  No packets should be dropped due to overrunning
       * the server.
       */

      sleep(2);
    }
  close(sockfd);
}