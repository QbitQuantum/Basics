static int thread_create(FAR const char *name, uint8_t ttype, int priority,
                         int stack_size, main_t entry, FAR char * const argv[])
{
  FAR struct task_tcb_s *tcb;
  pid_t pid;
  int errcode;
  int ret;

  /* Allocate a TCB for the new task. */

  tcb = (FAR struct task_tcb_s *)kmm_zalloc(sizeof(struct task_tcb_s));
  if (!tcb)
    {
      sdbg("ERROR: Failed to allocate TCB\n");
      errcode = ENOMEM;
      goto errout;
    }

  /* Allocate a new task group with privileges appropriate for the parent
   * thread type.
   */

#ifdef HAVE_TASK_GROUP
  ret = group_allocate(tcb, ttype);
  if (ret < 0)
    {
      errcode = -ret;
      goto errout_with_tcb;
    }
#endif

  /* Associate file descriptors with the new task */

#if CONFIG_NFILE_DESCRIPTORS > 0 || CONFIG_NSOCKET_DESCRIPTORS > 0
  ret = group_setuptaskfiles(tcb);
  if (ret < OK)
    {
      errcode = -ret;
      goto errout_with_tcb;
    }
#endif

  /* Allocate the stack for the TCB */

  ret = up_create_stack((FAR struct tcb_s *)tcb, stack_size, ttype);
  if (ret < OK)
    {
      errcode = -ret;
      goto errout_with_tcb;
    }

  /* Initialize the task control block */

  ret = task_schedsetup(tcb, priority, task_start, entry, ttype);
  if (ret < OK)
    {
      errcode = EBUSY; /* No available PID */
      goto errout_with_tcb;
    }

  /* Setup to pass parameters to the new task */

  (void)task_argsetup(tcb, name, argv);

  /* Now we have enough in place that we can join the group */

#ifdef HAVE_TASK_GROUP
  ret = group_initialize(tcb);
  if (ret < 0)
    {
      errcode = -ret;
      goto errout_with_tcb;
    }
#endif

  /* Get the assigned pid before we start the task */

  pid = (int)tcb->cmn.pid;

  /* Activate the task */

  ret = task_activate((FAR struct tcb_s *)tcb);
  if (ret < OK)
    {
      errcode = get_errno();

      /* The TCB was added to the active task list by task_schedsetup() */

      dq_rem((FAR dq_entry_t*)tcb, (dq_queue_t*)&g_inactivetasks);
      goto errout_with_tcb;
    }

  return pid;

errout_with_tcb:
  sched_releasetcb((FAR struct tcb_s *)tcb, ttype);

errout:
  set_errno(errcode);
  return ERROR;
}