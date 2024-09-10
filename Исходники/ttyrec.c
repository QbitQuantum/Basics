int
ttyrec_main (int game, char *username, char *ttyrec_path, char* ttyrec_filename)
{
  char dirname[100];

  /* Note our PID to let children kill the main dgl process for idling */
  dgl_parent = getpid();
  child = subchild = input_child = 0;

  if (!ttyrec_path) {
      child = fork();
      if (child < 0) {
	  perror ("fork");
	  fail ();
      }
      if (child == 0) {
	  execvp (myconfig[game]->game_path, myconfig[game]->bin_args);
      } else {
	  int status;
	  (void) wait(&status);
      }
      return 0;
  }

  if (ttyrec_path[strlen(ttyrec_path)-1] == '/')
      snprintf (dirname, 100, "%s%s", ttyrec_path, ttyrec_filename);
  else
      snprintf (dirname, 100, "%s/%s", ttyrec_path, ttyrec_filename);

  atexit(&remove_ipfile);
  if ((fscript = fopen (dirname, "w")) == NULL)
    {
      perror (dirname);
      fail ();
    }
  setbuf (fscript, NULL);

  fixtty ();

  (void) signal (SIGCHLD, finish);
  child = fork ();
  if (child < 0)
    {
      perror ("fork");
      fail ();
    }
  if (child == 0)
    {
      subchild = child = fork ();
      if (child < 0)
        {
          perror ("fork");
          fail ();
        }
      if (child)
        {
          close (slave);
          ipfile = gen_inprogress_lock (game, child, ttyrec_filename);
	  ttyrec_id(game, username, ttyrec_filename);
          dooutput (myconfig[game]->max_idle_time);
        }
      else
	  doshell (game, username);
    }

  (void) fclose (fscript);

  wait_for_menu = 1;
  input_child = fork();
  if (input_child < 0)
  {
      perror ("fork2");
      fail ();
  }
  if (!input_child)
      doinput ();
  else
  {
      while (wait_for_menu)
	  sleep(1);
  }

  remove_ipfile();
  child = 0;

  return 0;
}