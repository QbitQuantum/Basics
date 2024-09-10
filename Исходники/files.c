/* Use sockets or pipes.  */
int
_gst_open_pipe (const char *command,
		const char *mode)
{
  int fd[2];
  int our_fd, child_fd;
  int access;
  int result;

  _gst_set_signal_handler (SIGCHLD, sigchld_handler);
  access = strchr (mode, '+') ? O_RDWR :
    (mode[0] == 'r' ? O_RDONLY : O_WRONLY);

  if (access == O_RDWR)
    {
      result = socketpair (AF_UNIX, SOCK_STREAM, 0, fd);
      our_fd = fd[1];
      child_fd = fd[0];
    }
  else
    {
      result = pipe (fd);
      our_fd = access == O_RDONLY ? fd[0] : fd[1];
      child_fd = access == O_RDONLY ? fd[1] : fd[0];
    }

  if (result == -1)
    return -1;

  _gst_set_signal_handler (SIGPIPE, SIG_DFL);
  _gst_set_signal_handler (SIGFPE, SIG_DFL);

#ifdef HAVE_SPAWNL
  {
    /* Prepare file descriptors, saving the old ones so that we can keep
       them.  */
    int save_stdin = -1, save_stdout = -1, save_stderr = -1;
    if (access != O_WRONLY)
      {
        save_stdout = dup (1);
        save_stderr = dup (2);
        dup2 (child_fd, 1);
        dup2 (child_fd, 2);
      }
    if (access != O_RDONLY)
      {
        save_stdin = dup (0);
        dup2 (child_fd, 0);
      }

    result = spawnl (P_NOWAIT, "/bin/sh", "/bin/sh", "-c", command, NULL);

    if (save_stdin != -1)
      {
        dup2 (save_stdin, 0);
        close (save_stdin);
      }

    if (save_stdout != -1)
      {
        dup2 (save_stdout, 1);
        close (save_stdout);
      }

    if (save_stderr != -1)
      {
        dup2 (save_stderr, 2);
        close (save_stderr);
      }
  }
#else /* !HAVE_SPAWNL */
  /* We suppose it is a system that has fork.  */
  result = fork ();
  if (result == 0)
    {
      /* Child process */
      close (our_fd);
      if (access != O_WRONLY)
	dup2 (child_fd, 1);
      if (access != O_RDONLY)
        dup2 (child_fd, 0);

      _exit (system (command) >= 0);
      /*NOTREACHED*/
    }

#endif /* !HAVE_SPAWNL */

  close (child_fd);
  _gst_set_signal_handler (SIGPIPE, SIG_IGN);
  _gst_set_signal_handler (SIGFPE, SIG_IGN);

  if (result == -1)
    {
      int save_errno;
      save_errno = errno;
      close (our_fd);
      errno = save_errno;
      return (-1);
    }
  else
    return (our_fd);
}