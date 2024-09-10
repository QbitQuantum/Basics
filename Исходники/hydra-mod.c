int
internal__hydra_connect(unsigned long int host, int port, int protocol, int type)
{
  int s, ret = -1;
  struct sockaddr_in target;
  char *buf, *tmpptr = NULL;
  struct sockaddr_in sin;

#ifndef CYGWIN
  char out[16];
#endif

  if ((s = socket(PF_INET, protocol, type)) >= 0) {
    if (src_port != 0)
    {
      int bind_ok=0;
      sin.sin_family = PF_INET;
      sin.sin_port = htons(src_port);
      sin.sin_addr.s_addr = INADDR_ANY;
      
      //we will try to find a free port down to 512
      while (!bind_ok && src_port >= 512)
      {
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin))==-1)
	{
	      if (verbose)
	        perror("error:");
	      if (errno == EADDRINUSE)
	      {
	      	  src_port--;
		  sin.sin_port = htons(src_port);
	      }
	      else
	      {
		if (errno == EACCES && (getuid() > 0))
		{
			printf("You need to be root to test this service\n");
			return -1;
		}
	      }
	}
	else
		bind_ok=1;
      }
    }  
    if (use_proxy > 0) {
      target.sin_port = htons(proxy_string_port);
      memcpy(&target.sin_addr.s_addr, &proxy_string_ip, 4);
    } else {
      target.sin_port = htons(port);
      memcpy(&target.sin_addr.s_addr, &host, 4);
    }
    target.sin_family = AF_INET;
    signal(SIGALRM, alarming);
    do {
      if (fail > 0)
        sleep(WAIT_BETWEEN_CONNECT_RETRY);
      alarm_went_off = 0;
      alarm(waittime);
      ret = connect(s, (struct sockaddr *) &target, sizeof(target));
      alarm(0);
      if (ret < 0 && alarm_went_off == 0) {
        fail++;
        if (verbose && fail <= MAX_CONNECT_RETRY)
          fprintf(stderr, "Process %d: Can not connect [unreachable], retrying (%d of %d retries)\n", (int) getpid(), fail, MAX_CONNECT_RETRY);
      }
    } while (ret < 0 && fail <= MAX_CONNECT_RETRY);
    if (ret < 0 && fail > MAX_CONNECT_RETRY) {
      if (debug)
        printf("DEBUG_CONNECT_UNREACHABLE\n");

/* we wont quit here, thats up to the module to decide what to do 
 *              fprintf(stderr, "Process %d: Can not connect [unreachable], process exiting\n", (int)getpid());
 *              hydra_child_exit(1);
 */
      extern_socket = -1;
      ret = -1;
      return ret;
    }
    ret = s;
    extern_socket = s;
    if (debug)
      printf("DEBUG_CONNECT_OK\n");

    if (use_proxy == 2) {
      buf = malloc(4096);
      memset(&target, 0, sizeof(target));
      memcpy(&target.sin_addr.s_addr, &host, 4);
      target.sin_family = AF_INET;
#ifdef CYGWIN
      if (proxy_authentication == NULL)
        snprintf(buf, 4096, "CONNECT %s:%d HTTP/1.0\r\n\r\n", inet_ntoa((struct in_addr) target.sin_addr), port);
      else
        snprintf(buf, 4096, "CONNECT %s:%d HTTP/1.0\r\nProxy-Authorization: Basic %s\r\n\r\n", inet_ntoa((struct in_addr) target.sin_addr), port, proxy_authentication);
#else
      if (proxy_authentication == NULL)
        snprintf(buf, 4096, "CONNECT %s:%d HTTP/1.0\r\n\r\n", inet_ntop(AF_INET, &target.sin_addr, out, sizeof(out)), port);
      else
        snprintf(buf, 4096, "CONNECT %s:%d HTTP/1.0\r\nProxy-Authorization: Basic %s\r\n\r\n", inet_ntop(AF_INET, &target.sin_addr, out, sizeof(out)), port,
                 proxy_authentication);
#endif
      send(s, buf, strlen(buf), 0);
      recv(s, buf, 4096, 0);
      if (strncmp("HTTP/", buf, strlen("HTTP/")) == 0 && (tmpptr = index(buf, ' ')) != NULL && *++tmpptr == '2') {
        if (debug)
          printf("DEBUG_CONNECT_SSL_OK\n");
      } else {
        if (debug)
          printf("DEBUG_CONNECT_SSL_FAILED (Code: %c%c%c)\n", *tmpptr, *(tmpptr + 1), *(tmpptr + 2));
        if (verbose)
          fprintf(stderr, "Error: CONNECT call to proxy failed with code %c%c%c\n", *tmpptr, *(tmpptr + 1), *(tmpptr + 2));
        close(s);
        extern_socket = -1;
        ret = -1;
        free(buf);
        return ret;
      }
      free(buf);
    }
    fail = 0;
    return ret;
  }
  return ret;
}