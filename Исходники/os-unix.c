int
os_daemonize(int argc, char **argv, const char *extra_arg)
{
     pid_t pid;

     /*
      *  The default is to ignore SIGCHLD signals.  However, unless
      *  this call is *explicitly* made, child processes will become
      *  zombies ("defunct") when they exit.
      */
     if (!did_ignore)
     {
	  did_ignore = 1;
	  signal(SIGCHLD, SIG_IGN);
     }

     if ((pid = FORK()) < 0)
	  return(-1);
     else if (pid)
	  /*
	   *  Parent goes bye-bye
	   */
	  _EXIT(0);

     /*
      *  Daemon child continues
      */
#if !defined(__MUST_EXEC)
     return(0);
#else
     {
	  char **argv2;
	  int i, istat;

	  /*
	   *  Need to do an exec*() call
	   */

	  /*
	   *  Build a new argument list which contains an extra argument
	   */
	  argv2 = (char **)malloc(sizeof(char *) * (argc + 2));
	  if (!argv2)
	       return(-1);

	  /*
	   *  Copy the original argument list
	   */
	  for (i = 0; i < argc; i++)
	       argv2[i] = (char *)argv[i];

	  /*
	   *  Add in the extra argument
	   */
	  argv2[argc] = (char *)extra_arg;

	  /*
	   *  And terminate the list
	   */
	  argv2[argc+1] = NULL;

	  /*
	   *  And exec ourself
	   */
	  istat = execve(argv[0], argv2, environ);
	  if (istat != -1)
	       _EXIT(0);

	  /*
	   *  If we're here, there's been an error-o-la
	   */
	  {
	       int save_errno = errno;
	       free(argv2);
	       errno = save_errno;
	       return(-1);
	  }
     }
#endif
}