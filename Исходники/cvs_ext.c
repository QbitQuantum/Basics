/* cvs_ext_connect
 *
 * connect to the cvs :ext: server as further described in the cvsfs_config
 * configuration structure
 */
error_t
cvs_ext_connect(FILE **send, FILE **recv)
{
  char port[10];
  int fd_to_rsh[2], fd_from_rsh[2];
  pid_t pid;

  if(pipe(fd_to_rsh))
    return errno;
  if(pipe(fd_from_rsh))
    return errno;

  if((pid = fork()) < 0)
    {
      perror(PACKAGE ": cannot fork remote shell client");
      return pid;
    }

  if(! pid)
    {
      /* okay, child process, fork to remote shell client */
      close(fd_to_rsh[1]);   /* close writing end */
      close(fd_from_rsh[0]); /* close reading end */

      if(dup2(fd_to_rsh[0], 0) < 0 || dup2(fd_from_rsh[1], 1) < 0)
	{
	  perror(PACKAGE ": unable to dup2 pipe to stdin/stdout");
	  exit(1);
	}

      if(config.cvs_mode == EXT) 
	{
	  snprintf(port, sizeof(port), "%d",
		   config.cvs_port ? config.cvs_port : 22);

	  execlp(config.cvs_shell_client, config.cvs_shell_client,
		 "-p", port,
		 "-l", config.cvs_username, config.cvs_hostname,
		 "--", "cvs", "server", NULL);
	}
      else if(config.cvs_mode == LOCAL)
	{
	  execlp("cvs", "cvs", "server", NULL);
	}
      else
	{
	  fprintf(stderr, PACKAGE ": damn, this line was not reached.\n");
	  abort();
	}

      exit(1);
    }

  close(fd_to_rsh[0]);
  close(fd_from_rsh[1]);

  if(! ((*send = fdopen(fd_to_rsh[1], "w"))
	&& (*recv = fdopen(fd_from_rsh[0], "r"))))
    {
      perror(PACKAGE ": unable to convert pipe's fds to file streams");

      if(send)
	fclose(*send);
      else
	close(fd_to_rsh[1]);

      if(recv)
	fclose(*recv);
      else
	close(fd_from_rsh[0]);

      kill(pid, SIGTERM);
      return EIO;
    }

  if(setvbuf(*send, NULL, _IOLBF, 0) || setvbuf(*recv, NULL, _IOLBF, 0))
    {
      perror(PACKAGE ": cannot force streams to be linebuffered");
      fclose(*send);
      fclose(*recv);
      return EIO;
    }

  return 0;
}