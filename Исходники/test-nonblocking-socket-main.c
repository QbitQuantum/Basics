int
main (int argc, char *argv[])
{
  const char *child_path = argv[1];
  int test = atoi (argv[2]);
  int server;
  int port;
  int child;
  int server_socket;
  int exitcode;

  /* Create a server socket.  */
  server = create_server (0, 1, &port);

  /* Spawn the child process.  */
  {
    char port_arg[10+1];
    const char *child_argv[4];

    sprintf (port_arg, "%u", port);
    child_argv[0] = child_path;
    child_argv[1] = argv[2];
    child_argv[2] = port_arg;
    child_argv[3] = NULL;

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    child = spawnvpe (P_NOWAIT, child_path, child_argv,
                      (const char **) environ);
    ASSERT (child >= 0);
#else
    {
      pid_t child_pid;
      int err =
        posix_spawnp (&child_pid, child_path, NULL, NULL, (char **) child_argv,
                      environ);
      ASSERT (err == 0);
      child = child_pid;
    }
#endif
  }

  /* Accept a connection from the child process.  */
  server_socket = create_server_socket (server);

  /* Prepare the file descriptor.  */
  if (test & 1)
    ASSERT (set_nonblocking_flag (server_socket, true) >= 0);

#if ENABLE_DEBUGGING
# ifdef SO_SNDBUF
  {
    int value;
    socklen_t value_len = sizeof (value);
    if (getsockopt (server_socket, SOL_SOCKET, SO_SNDBUF, &value, &value_len) >= 0)
      fprintf (stderr, "SO_SNDBUF = %d\n", value);
  }
# endif
# ifdef SO_RCVBUF
  {
    int value;
    socklen_t value_len = sizeof (value);
    if (getsockopt (server_socket, SOL_SOCKET, SO_RCVBUF, &value, &value_len) >= 0)
      fprintf (stderr, "SO_RCVBUF = %d\n", value);
  }
# endif
#endif

  exitcode =
    main_writer_loop (test, SOCKET_DATA_BLOCK_SIZE, server_socket,
                      SOCKET_HAS_LARGE_BUFFER);

  {
    int err =
      wait_subprocess (child, child_path, false, false, false, false, NULL);
    ASSERT (err == 0);
  }

  return exitcode;
}