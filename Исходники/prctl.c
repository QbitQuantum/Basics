int prctl(int option, ...)
{
  va_list ap;
  int err;

  va_start(ap, option);
  switch (option)
    {
    case PR_SET_NAME:
    case PR_GET_NAME:
#if CONFIG_TASK_NAME_SIZE > 0
      {
        /* Get the prctl arguments */

        char     *name = va_arg(ap, char *);
        int       pid  = va_arg(ap, int);
        FAR _TCB *tcb;

        /* Get the TCB associated with the PID (handling the special case of
         * pid==0 meaning "this thread")
         */

        if (!pid)
          {
            tcb = (FAR _TCB *)g_readytorun.head;
          }
        else
          {
            tcb = sched_gettcb(pid);
          }

        /* An invalid pid will be indicated by a NULL TCB returned from
         * sched_gettcb()
         */

        if (!tcb)
          {
            sdbg("Pid does not correspond to a task: %d\n", pid);
            err = ESRCH;
            goto errout;
          }

        /* A pointer to the task name storage must also be provided */

        if (!name)
          {
            sdbg("No name provide\n");
            err = EFAULT;
            goto errout;
          }

        /* Now get or set the task name */

        if (option == PR_SET_NAME)
          {
            /* tcb->name may not be null-terminated */

            strncpy(tcb->name, name, CONFIG_TASK_NAME_SIZE);
          }
        else
          {
            /* The returned value will be null-terminated, truncating if necessary */

            strncpy(name, tcb->name, CONFIG_TASK_NAME_SIZE-1);
            name[CONFIG_TASK_NAME_SIZE-1] = '\0';
          }
      }
      break;
#else
      sdbg("Option not enabled: %d\n", option);
      err = ENOSYS;
      goto errout;
#endif

    default:
      sdbg("Unrecognized option: %d\n", option);
      err = EINVAL;
      goto errout;
    }

  va_end(ap);
  return OK;

errout:
  va_end(ap);
  set_errno(err);
  return ERROR;
}