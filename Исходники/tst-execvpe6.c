static int
run_script (const char *fname, char *args[])
{
  /* We want to test the `execvpe' function.  To do this we restart the
     program with an additional parameter.  */
  int status;
  pid_t pid = fork ();
  if (pid == 0)
    {
      execvpe (fname, args, NULL);

      puts ("Cannot exec");
      exit (EXIT_FAILURE);
    }
  else if (pid == (pid_t) -1)
    {
      puts ("Cannot fork");
      return 1;
    }

  /* Wait for the child.  */
  if (waitpid (pid, &status, 0) != pid)
    {
      puts ("Wrong child");
      return 1;
    }

  if (WTERMSIG (status) != 0)
    {
      puts ("Child terminated incorrectly");
      return 1;
    }

  return 0;
}