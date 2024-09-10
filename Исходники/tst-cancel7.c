static void
sl (void)
{
  FILE *f = fopen (pidfile, "w");
  if (f == NULL)
    exit (1);

  fprintf (f, "%lld\n", (long long) getpid ());
  fflush (f);

  struct flock fl =
    {
      .l_type = F_WRLCK,
      .l_start = 0,
      .l_whence = SEEK_SET,
      .l_len = 1
    };
  if (fcntl (fileno (f), F_SETLK, &fl) != 0)
    exit (1);

  sigset_t ss;
  sigfillset (&ss);
  sigsuspend (&ss);
  exit (0);
}


static void
do_prepare (int argc, char *argv[])
{
  if (command == NULL)
    command = argv[0];

  if (pidfile)
    sl ();

  int fd = mkstemp (pidfilename);
  if (fd == -1)
    {
      puts ("mkstemp failed");
      exit (1);
    }

  write (fd, " ", 1);
  close (fd);
}


static int
do_test (void)
{
  pthread_t th;
  if (pthread_create (&th, NULL, tf, NULL) != 0)
    {
      puts ("pthread_create failed");
      return 1;
    }

  do
    sleep (1);
  while (access (pidfilename, R_OK) != 0);

  if (pthread_cancel (th) != 0)
    {
      puts ("pthread_cancel failed");
      return 1;
    }

  void *r;
  if (pthread_join (th, &r) != 0)
    {
      puts ("pthread_join failed");
      return 1;
    }

  sleep (1);

  FILE *f = fopen (pidfilename, "r+");
  if (f == NULL)
    {
      puts ("no pidfile");
      return 1;
    }

  long long ll;
  if (fscanf (f, "%lld\n", &ll) != 1)
    {
      puts ("could not read pid");
      unlink (pidfilename);
      return 1;
    }

  struct flock fl =
    {
      .l_type = F_WRLCK,
      .l_start = 0,
      .l_whence = SEEK_SET,
      .l_len = 1
    };
  if (fcntl (fileno (f), F_GETLK, &fl) != 0)
    {
      puts ("F_GETLK failed");
      unlink (pidfilename);
      return 1;
    }

  if (fl.l_type != F_UNLCK)
    {
      printf ("child %lld still running\n", (long long) fl.l_pid);
      if (fl.l_pid == ll)
	kill (fl.l_pid, SIGKILL);

      unlink (pidfilename);
      return 1;
    }

  fclose (f);

  unlink (pidfilename);

  return r != PTHREAD_CANCELED;
}

static void
do_cleanup (void)
{
  FILE *f = fopen (pidfilename, "r+");
  long long ll;

  if (f != NULL && fscanf (f, "%lld\n", &ll) == 1)
    {
      struct flock fl =
	{
	  .l_type = F_WRLCK,
	  .l_start = 0,
	  .l_whence = SEEK_SET,
	  .l_len = 1
	};
      if (fcntl (fileno (f), F_GETLK, &fl) == 0 && fl.l_type != F_UNLCK
	  && fl.l_pid == ll)
	kill (fl.l_pid, SIGKILL);

      fclose (f);
    }

  unlink (pidfilename);
}