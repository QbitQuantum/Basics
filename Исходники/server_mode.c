int
server_mode (const char *pidfile, struct sockaddr_in *phis_addr)
{
  int ctl_sock, fd;
  struct servent *sv;
  int port;
  static struct  sockaddr_in server_addr;  /* Our address.  */

  /* Become a daemon.  */
#ifdef HAVE_DAEMON
  if (daemon(1,1) < 0)
#endif
    {
      syslog (LOG_ERR, "failed to become a daemon");
      return -1;
    }
  (void) signal (SIGCHLD, reapchild);

  /* Get port for ftp/tcp.  */
  sv = getservbyname ("ftp", "tcp");
  port = (sv == NULL) ? DEFPORT : sv->s_port;

  /* Open socket, bind and start listen.  */
  ctl_sock = socket (AF_INET, SOCK_STREAM, 0);
  if (ctl_sock < 0)
    {
      syslog (LOG_ERR, "control socket: %m");
      return -1;
    }

  /* Enable local address reuse.  */
  {
    int on = 1;
    if (setsockopt (ctl_sock, SOL_SOCKET, SO_REUSEADDR,
		    (char *)&on, sizeof(on)) < 0)
      syslog (LOG_ERR, "control setsockopt: %m");
  }

  memset (&server_addr, 0, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (port);

  if (bind (ctl_sock, (struct sockaddr *)&server_addr, sizeof server_addr))
    {
      syslog (LOG_ERR, "control bind: %m");
      return -1;
    }
  if (listen (ctl_sock, 32) < 0)
    {
      syslog (LOG_ERR, "control listen: %m");
      return -1;
    }

  /* Stash pid in pidfile.  */
  {
    FILE *pid_fp = fopen (pidfile, "w");
    if (pid_fp == NULL)
      syslog (LOG_ERR, "can't open %s: %m", PATH_FTPDPID);
    else
      {
	fprintf (pid_fp, "%d\n", getpid());
	fchmod (fileno(pid_fp), S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	fclose (pid_fp);
      }
  }

  /* Loop forever accepting connection requests and forking off
     children to handle them.  */
  while (1)
    {
      int addrlen = sizeof (*phis_addr);
      fd = accept (ctl_sock, (struct sockaddr *)phis_addr, &addrlen);
#ifdef HAVE_WORKING_FORK
      if (fork () == 0) /* child */
#else
      if (vfork () == 0) /* child */
#endif
	{
	  (void) dup2 (fd, 0);
	  (void) dup2 (fd, 1);
	  close (ctl_sock);
	  break;
	}
      close (fd);
    }

#ifdef WITH_WRAP
  /* In the child.  */
  if (!check_host ((struct sockaddr *)phis_addr))
    return -1;
#endif
  return fd;
}