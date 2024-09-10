int
mf_mftalk_initscreen (void)
{
  int app;				/* Client application type. */
  char *prog, *name;			/* Client program name. */
    /* Size of METAFONT window. */
  char height[MAX_INT_LENGTH], width[MAX_INT_LENGTH];
    /* Inherited pipe handles. */
  char input[MAX_INT_LENGTH], output[MAX_INT_LENGTH];
  char parent[MAX_INT_LENGTH];		/* My own process ID. */
  int sc_pipe[2];			/* Server->Client pipe. */
  int cs_pipe[2];			/* Client->Server pipe. */
  int res, ack;				/* Wait until child is ready. */

  prog = kpse_var_value ("MFTALK");
  if (prog == NULL)
    prog = "mftalk.exe";

  name = app_type (prog, &app);
  if (!name)
    return 0;

  if (pipe (sc_pipe) == -1)
    return 0;
  if (pipe (cs_pipe) == -1)
    {
      close (sc_pipe[0]);
      close (sc_pipe[1]);
      return 0;
    }
#ifdef OS2
  fatal (setmode, setmode (sc_pipe[0], O_BINARY) == -1);
  fatal (setmode, setmode (sc_pipe[1], O_BINARY) == -1);
  fatal (setmode, setmode (cs_pipe[0], O_BINARY) == -1);
  fatal (setmode, setmode (cs_pipe[1], O_BINARY) == -1);
#endif

  old = signal (SIGCHLD, child_died);
  fatal (old, old == SIG_ERR);

  sprintf (height, "-h%d", screendepth);
  sprintf (width, "-w%d", screenwidth);
  sprintf (input, "-i%d", sc_pipe[0]);
  sprintf (output, "-o%d", cs_pipe[1]);
  sprintf (parent, "-p%d", getpid ());

#ifdef OS2
  pid = spawnl (app, name, prog, height, width, input, output, parent, NULL);
#else
  pid = fork ();
  if (pid == 0)
    {
      fatal (close, close (0) == -1);
      fatal (dup, dup (sc_pipe[0]) != 0);
      fatal (close, close (sc_pipe[0]) == -1);
      fatal (close, close (sc_pipe[1]) == -1);      
      fatal (close, close (1) == -1);
      fatal (dup, dup (cs_pipe[1]) != 1);
      fatal (close, close (cs_pipe[0]) == -1);
      fatal (close, close (cs_pipe[1]) == -1);      
      
      /* We still pass the file handles as parameters for
       * backward compatibility. instead of sc_pipe[0] and
       * cs_pipe[1] we just pass 0 (stdin) and 1 (stdout).
       */

      sprintf (input, "-i0");
      sprintf (output, "-o1");
      
      execl (name, prog, height, width, input, output, parent, NULL);
    }
#endif /* not OS2 */
  switch (pid)
    {
    case -1:
    failure:
      fatal (close, close (sc_pipe[0]) == -1);
      fatal (close, close (sc_pipe[1]) == -1);
      fatal (close, close (cs_pipe[0]) == -1);
      fatal (close, close (cs_pipe[1]) == -1);
      fatal (signal, signal (SIGCHLD, old) == SIG_ERR);
      break;
    default:
      res = read (cs_pipe[0], &ack, sizeof (int));
      if (res != sizeof (int) || ack != MF_ACK)
	goto failure;
      fatal (close, close (cs_pipe[0]) == -1);
      win = sc_pipe[1];
      break;
    }

  return (win == -1) ? 0 : 1;
}