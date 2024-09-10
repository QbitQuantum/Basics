int schedule_unload(pid_t pid, FAR struct binary_s *bin)
{
  struct sigaction act;
  struct sigaction oact;
  sigset_t sigset;
  irqstate_t flags;
  int errorcode;
  int ret;

  /* Make sure that SIGCHLD is unmasked */

  (void)sigemptyset(&sigset);
  (void)sigaddset(&sigset, SIGCHLD);
  ret = sigprocmask(SIG_UNBLOCK, &sigset, NULL);
  if (ret != OK)
    {
      /* The errno value will get trashed by the following debug output */

      errorcode = get_errno();
      bvdbg("ERROR: sigprocmask failed: %d\n", ret);
      goto errout;
    }

  /* Add the structure to the list.  We want to do this *before* connecting
   * the signal handler.  This does, however, make error recovery more
   * complex if sigaction() fails below because then we have to remove the
   * unload structure for the list in an unexpected context.
   */

  unload_list_add(pid, bin);

  /* Register the SIGCHLD handler */

  act.sa_sigaction = unload_callback;
  act.sa_flags     = SA_SIGINFO;

  (void)sigfillset(&act.sa_mask);
  (void)sigdelset(&act.sa_mask, SIGCHLD);

  ret = sigaction(SIGCHLD, &act, &oact);
  if (ret != OK)
    {
      /* The errno value will get trashed by the following debug output */

      errorcode = get_errno();
      bvdbg("ERROR: sigaction failed: %d\n" , ret);

      /* Emergency removal from the list */

      flags = irqsave();
      if (unload_list_remove(pid) != bin)
        {
          blldbg("ERROR: Failed to remove structure\n");
        }
      
      goto errout;
    }

  return OK;

errout:
  set_errno(errorcode);
  return ERROR;
}