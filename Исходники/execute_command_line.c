static void
execute_command_line (const char *command, bool wait, int *exitstat,
		      int *cmdstat, char *cmdmsg,
		      gfc_charlen_type command_len,
		      gfc_charlen_type cmdmsg_len)
{
  /* Transform the Fortran string to a C string.  */
  char cmd[command_len + 1];
  memcpy (cmd, command, command_len);
  cmd[command_len] = '\0';

  /* Flush all I/O units before executing the command.  */
  flush_all_units();

#if defined(HAVE_FORK)
  if (!wait)
    {
      /* Asynchronous execution.  */
      pid_t pid;

      set_cmdstat (cmdstat, EXEC_NOERROR);

      if ((pid = fork()) < 0)
	set_cmdstat (cmdstat, EXEC_CHILDFAILED);
      else if (pid == 0)
	{
	  /* Child process.  */
	  int res = system (cmd);
	  _exit (WIFEXITED(res) ? WEXITSTATUS(res) : res);
	}
    }
  else
#endif
    {
      /* Synchronous execution.  */
      int res = system (cmd);

      if (res == -1)
	set_cmdstat (cmdstat, EXEC_SYSTEMFAILED);
      else if (!wait)
	set_cmdstat (cmdstat, EXEC_SYNCHRONOUS);
      else
	set_cmdstat (cmdstat, EXEC_NOERROR);

      if (res != -1)
	{
#if defined(WEXITSTATUS) && defined(WIFEXITED)
	  *exitstat = WIFEXITED(res) ? WEXITSTATUS(res) : res;
#else
	  *exitstat = res;
#endif
	}
    }

  /* Now copy back to the Fortran string if needed.  */
  if (cmdstat && *cmdstat > EXEC_NOERROR)
    {
      if (cmdmsg)
	fstrcpy (cmdmsg, cmdmsg_len, cmdmsg_values[*cmdstat],
		strlen (cmdmsg_values[*cmdstat]));
      else
	runtime_error ("Failure in EXECUTE_COMMAND_LINE: %s",
		       cmdmsg_values[*cmdstat]);
    }
}