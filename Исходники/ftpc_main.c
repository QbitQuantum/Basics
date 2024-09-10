int ftpc_main(int argc, char **argv, char **envp)
{
  struct ftpc_connect_s connect = {{0}, 0};
  SESSION handle;
  FAR char *ptr;
#ifndef CONFIG_EXAMPLES_FTPC_FGETS
  int ret;
#endif

  if (argc != 2)
    {
      printf("Usage:\n");
      printf("   %s xx.xx.xx.xx[:pp]\n", argv[0]);
      printf("Where\n");
      printf("  xx.xx.xx.xx is the IP address of the FTP server\n");
      printf("  pp is option port to use with the FTP server\n");
      exit(1);
    }

  /* Check if the argument includes a port number */

  ptr = strchr(argv[1], ':');
  if (ptr)
    {
      *ptr = '\0';
      connect.port = atoi(ptr+1);
    }

  /* In any event, we can now extract the IP address from the comman-line */

  connect.addr.s_addr = inet_addr(argv[1]);

  /* Connect to the FTP server */

  handle = ftpc_connect(&connect);
  if (!handle)
    {
      printf("Failed to connect to the server: %d\n", errno);
      exit(1);
    }

  /* Present a greeting */

  printf("NuttX FTP Client:\n");
  FFLUSH();

  /* Setting optind to -1 is a non-standard, backdoor way to reinitialize
   * getopt().  getopt() is not thread safe and we have no idea what state
   * it is in now!
   */

  optind = -1;

  /* Then enter the command line parsing loop */

  for (;;)
    {
      /* Display the prompt string */

      fputs("nfc> ", stdout);
      FFLUSH();

      /* Get the next line of input */

#ifdef CONFIG_EXAMPLES_FTPC_FGETS
      /* fgets returns NULL on end-of-file or any I/O error */

      if (fgets(g_line, CONFIG_FTPC_LINELEN, stdin) == NULL)
        {
          printf("ERROR: fgets failed: %d\n", errno);
          return 1;
        }
#else
      ret = readline(g_line, CONFIG_FTPC_LINELEN, stdin, stdout);

      /* Readline normally returns the number of characters read,
       * but will return EOF on end of file or if an error occurs.
       * Either will cause the session to terminate.
       */

      if (ret == EOF)
        {
          printf("ERROR: readline failed: %d\n", errno);
          return 1;
        }
#endif
      else
        {
          /* Parse and process the command */

          (void)ftpc_parse(handle, g_line);
          FFLUSH();
        }
    }

  return 0;
}