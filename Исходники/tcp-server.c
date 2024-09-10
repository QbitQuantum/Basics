/* driver function */
int main(int argc, char **argv)
{
  char hostaddr[MAXLINE], hostname[MAXLINE], *progname = argv[0], *portstring;
  int listenfd, connfd, error, pid, threaded = 0;
  size_t port, total = 0;
  FILE *logfile = NULL;
  sem_t count;
  struct options options;
  pthread_t cleaning;
  socklen_t clientlen;
  union
  {
    struct sockaddr_in client4;
    struct sockaddr_in6 client6;
  } clientaddr;

  if (sem_init(&count, 0, 0) == -1 || pthread_create(&cleaning, NULL, clean, &count) != 0) {
    perror(NULL);
    fprintf(stderr, "Warning : Unable to initialize thread mechanisms, child processes may not be cleaned up\n");
  } else {
    threaded = 1;
  }

  memset(&options, 0, sizeof(struct options));
  options.argc = argc - 1;
  options.argv = argv + 1;
  options.log_level = &log_level;

  error = optparse(&options);

  if (error || options.argc != 1) {
    fprintf(stderr, usage, progname);
    return error ? error - 1 : 0;
  }

  if (options.logfilename) {
    logfile = fopen(options.logfilename, "a");
  }

  portstring = options.argv[0];

  listenfd = open_socketfd(NULL, portstring, AI_PASSIVE, SOCK_STREAM, &bind);

  if(listenfd < 0) {
    fprintf(stderr, "Error : Cannot listen to socket %s with error %d\n", portstring, listenfd);
    return 1;
  }

  SETSOCKOPT(logfile, LOG_LEVEL_V, listenfd, SOL_SOCKET, SO_REUSEADDR, &option_true);
  SETSOCKOPT(logfile, LOG_LEVEL_L, listenfd, SOL_SOCKET, SO_PRIORITY, options.sopriority);
  SETSOCKOPT(logfile, LOG_LEVEL_L, listenfd, IPPROTO_TCP, TCP_NODELAY, options.tcpnodelay);
  SETSOCKOPT(logfile, LOG_LEVEL_L, listenfd, IPPROTO_TCP, TCP_QUICKACK, options.tcpquickack);

  if (listen(listenfd, LISTEN_MAX) == -1) {
    fprintf(stderr, "Error : Cannot listen on port\n");
    return 1;
  }
  LOG(logfile, LOG_LEVEL_L, "listening\n");

  while(1)
  {
    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (void *)(&clientaddr), &clientlen);
    if (connfd == -1) {
      continue;
    }

    LOGSOCKOPT(logfile, LOG_LEVEL_L, connfd, SOL_SOCKET, SO_PRIORITY);
    LOGSOCKOPT(logfile, LOG_LEVEL_L, connfd, IPPROTO_TCP, TCP_NODELAY);
    LOGSOCKOPT(logfile, LOG_LEVEL_L, connfd, IPPROTO_TCP, TCP_QUICKACK);

    error = getnameinfo((struct sockaddr*)&clientaddr, clientlen, hostname, sizeof(hostname), NULL, 0, 0);
    if (error != 0) {
      close(connfd);
      continue;
    }
    error = getnameinfo((struct sockaddr*)&clientaddr, clientlen, hostaddr, sizeof(hostaddr), NULL, 0, NI_NUMERICHOST);

    port = ntohs(((struct sockaddr*)&clientaddr)->sa_family == AF_INET
         ? ((struct sockaddr_in*)&clientaddr)->sin_port
         : ((struct sockaddr_in6*)&clientaddr)->sin6_port);
    if (error) {
      LOGF(logfile, LOG_LEVEL_L, "connected to %s : %lu\n", hostname, port);
    } else {
      LOGF(logfile, LOG_LEVEL_L, "connected to %s (%s) : %lu\n", hostname, hostaddr, port);
    }

    if ((pid = fork()) == 0) {
      close(listenfd);
      respond(connfd, port, logfile, options.tcpquickack);
      LOGF(logfile, LOG_LEVEL_L, "server: closing connection to %s (%s) : %lu\n", hostname, hostaddr, port);
      if (logfile) {
        fclose(logfile);
      }
      close(connfd);
      exit(0);
    }
    ++total;
    close(connfd);
    if (pid > 0) {
      if (threaded && sem_post(&count) == -1) {
        fprintf(stderr, "Warning : Semaphore overflow, child processes may not be cleaned up\n");
      }
      LOGF(logfile, LOG_LEVEL_L, "server: forked to pid %d, connection accepted\n", pid);
    }
    if(pid == -1) {
      fprintf(stderr, "Error : Failed to fork, connection refused\n");
    }
  }
}