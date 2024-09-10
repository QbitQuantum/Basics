int waitid(idtype_t idtype, id_t id, siginfo_t *info, int options)
{
  FAR _TCB *rtcb = (FAR _TCB *)g_readytorun.head;
  sigset_t sigset;
  int err;
  int ret;

  /* MISSING LOGIC:   If WNOHANG is provided in the options, then this function
   * should returned immediately.  However, there is no mechanism available now
   * know if the thread has child:  The children remember their parents (if
   * CONFIG_SCHED_HAVE_PARENT) but the parents do not remember their children.
   */

  /* None of the options are supported except for WEXITED (which must be
   * provided.  Currently SIGCHILD always reports CLD_EXITED so we cannot
   * distinguish any other events.
   */

#ifdef CONFIG_DEBUG
  if (options != WEXITED)
    {
      set_errno(ENOSYS);
      return ERROR;
    }
#endif

  /* Create a signal set that contains only SIGCHLD */

  (void)sigemptyset(&sigset);
  (void)sigaddset(&sigset, SIGCHLD);

  /* Disable pre-emption so that nothing changes while the loop executes */

  sched_lock();

  /* Verify that this task actually has children and that the the requeste
   * TCB is actually a child of this task.
   */

  if (rtcb->nchildren == 0)
    {
      err = ECHILD;
      goto errout_with_errno;
    }
  else if (idtype == P_PID)
    {
     /* Get the TCB corresponding to this PID and make sure it is our child. */

      FAR _TCB *ctcb = sched_gettcb((pid_t)id);
      if (!ctcb || ctcb->parent != rtcb->pid)
        {
          err = ECHILD;
          goto errout_with_errno;
        }
    }

  /* Loop until the child that we are waiting for dies */

  for (;;)
    {
      /* Check if the task has already died. Signals are not queued in
       * NuttX.  So a possibility is that the child has died and we
       * missed the death of child signal (we got some other signal
       * instead).
       */

      if (rtcb->nchildren == 0 ||
          (idtype == P_PID && (ret = kill((pid_t)id, 0)) < 0))
        {
          /* We know that the child task was running okay we stared,
           * so we must have lost the signal.  What can we do?
           * Let's claim we were interrupted by a signal.
           */

          err = EINTR;
          goto errout_with_errno;
        }

      /* Wait for any death-of-child signal */

      ret = sigwaitinfo(&sigset, info);
      if (ret < 0)
        {
          goto errout;
        }

      /* Make there this was SIGCHLD */

      if (info->si_signo == SIGCHLD)
        {
          /* Yes.. Are we waiting for the death of a specific child? */

          if (idtype == P_PID)
            {
              /* Was this the death of the thread we were waiting for? */

              if (info->si_pid == (pid_t)id)
                {
                   /* Yes... return success */

                   break;
                }
            }

          /* Are we waiting for any child to change state? */

          else if (idtype == P_ALL)
            {
              /* Return success */

              break;
            }

          /* Other ID types are not supported */

          else /* if (idtype == P_PGID) */
            {
              set_errno(ENOSYS);
              goto errout;
            }
        }
    }

  sched_unlock();
  return OK;

errout_with_errno:
  set_errno(err);
errout:
  sched_unlock();
  return ERROR;
}