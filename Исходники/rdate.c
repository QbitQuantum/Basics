static int
rdate(const char *hostname, time_t *retval)
{
  struct servent *sent;
  struct sockaddr_in saddr;
  int fd;
  unsigned char time_buf[4];
  int nr, n_toread;

  assert(hostname);
  assert(retval);

  saddr.sin_family = AF_INET;

  if(!inet_aton(hostname, &saddr.sin_addr))
    {
      struct hostent *hent;

      hent = gethostbyname(hostname);
      if(!hent)
	{
	  fprintf(stderr, "%s: Unknown host %s: %s\n", program_invocation_short_name, hostname, hstrerror(h_errno));
	  return -1;
	}

      assert(hent->h_addrtype == AF_INET);
      memcpy(&saddr.sin_addr, hent->h_addr_list[0], hent->h_length);
    }

  if((sent = getservbyname("time", "tcp")))
    saddr.sin_port = sent->s_port;      
  else
    saddr.sin_port = htons(DEFAULT_PORT);

  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(fd < 0)
    {
      fprintf(stderr, "%s: couldn't create socket: %s\n", program_invocation_short_name, strerror(errno));
      return -1;
    }

  if(connect(fd, (struct sockaddr *)&saddr, sizeof(saddr)))
    {
      fprintf(stderr, "%s: couldn't connect to host %s: %s\n", program_invocation_short_name, hostname, strerror(errno));
      close(fd);
      return -1;
    }

  for(n_toread = sizeof(time_buf), nr = 1; nr > 0 && n_toread > 0; n_toread -= nr)
    nr = read(fd, time_buf + sizeof(time_buf) - n_toread, n_toread);
  if(n_toread)
    {
      if(nr)
	fprintf(stderr, "%s: error in read: %s\n", program_invocation_short_name, strerror(errno));
      else
	fprintf(stderr, "%s: got EOF from time server\n", program_invocation_short_name);
      close(fd);

      return -1;
    }

  /* See inetd's builtins.c for an explanation */
  *retval = (time_t)(ntohl(*(uint32_t *)time_buf) - 2208988800UL);

  return 0;
}