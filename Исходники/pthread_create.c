int pthread_create(FAR pthread_t *thread, FAR const pthread_attr_t *attr,
                   pthread_startroutine_t start_routine, pthread_addr_t arg)
{
  FAR struct pthread_tcb_s *ptcb;
  FAR struct join_s *pjoin;
  struct sched_param param;
  int policy;
  int errcode;
  pid_t pid;
  int ret;
#ifdef HAVE_TASK_GROUP
  bool group_joined = false;
#endif

  /* If attributes were not supplied, use the default attributes */

  if (!attr)
    {
      attr = &g_default_pthread_attr;
    }

  /* Allocate a TCB for the new task. */

  ptcb = (FAR struct pthread_tcb_s *)kmm_zalloc(sizeof(struct pthread_tcb_s));
  if (!ptcb)
    {
      sdbg("ERROR: Failed to allocate TCB\n");
      return ENOMEM;
    }

#ifdef HAVE_TASK_GROUP
  /* Bind the parent's group to the new TCB (we have not yet joined the
   * group).
   */

  ret = group_bind(ptcb);
  if (ret < 0)
    {
      errcode = ENOMEM;
      goto errout_with_tcb;
    }
#endif

#ifdef CONFIG_ARCH_ADDRENV
  /* Share the address environment of the parent task group. */

  ret = up_addrenv_attach(ptcb->cmn.group,
                          (FAR struct tcb_s *)g_readytorun.head);
  if (ret < 0)
    {
      errcode = -ret;
      goto errout_with_tcb;
    }
#endif

  /* Allocate a detachable structure to support pthread_join logic */

  pjoin = (FAR struct join_s *)kmm_zalloc(sizeof(struct join_s));
  if (!pjoin)
    {
      sdbg("ERROR: Failed to allocate join\n");
      errcode = ENOMEM;
      goto errout_with_tcb;
    }

  /* Allocate the stack for the TCB */

  ret = up_create_stack((FAR struct tcb_s *)ptcb, attr->stacksize,
                        TCB_FLAG_TTYPE_PTHREAD);
  if (ret != OK)
    {
      errcode = ENOMEM;
      goto errout_with_join;
    }

  /* Should we use the priority and scheduler specified in the pthread
   * attributes?  Or should we use the current thread's priority and
   * scheduler?
   */

  if (attr->inheritsched == PTHREAD_INHERIT_SCHED)
    {
      /* Get the priority (and any other scheduling parameters) for this
       * thread.
       */

      ret = sched_getparam(0, &param);
      if (ret == ERROR)
        {
          errcode = get_errno();
          goto errout_with_join;
        }

      /* Get the scheduler policy for this thread */

      policy = sched_getscheduler(0);
      if (policy == ERROR)
        {
          errcode = get_errno();
          goto errout_with_join;
        }
    }
  else
    {
      /* Use the scheduler policy and policy the attributes */

      policy                             = attr->policy;
      param.sched_priority               = attr->priority;

#ifdef CONFIG_SCHED_SPORADIC
      param.sched_ss_low_priority        = attr->low_priority;
      param.sched_ss_max_repl            = attr->max_repl;
      param.sched_ss_repl_period.tv_sec  = attr->repl_period.tv_sec;
      param.sched_ss_repl_period.tv_nsec = attr->repl_period.tv_nsec;
      param.sched_ss_init_budget.tv_sec  = attr->budget.tv_sec;
      param.sched_ss_init_budget.tv_nsec = attr->budget.tv_nsec;
#endif
    }

#ifdef CONFIG_SCHED_SPORADIC
  if (policy == SCHED_SPORADIC)
    {
      FAR struct sporadic_s *sporadic;
      int repl_ticks;
      int budget_ticks;

      /* Convert timespec values to system clock ticks */

      (void)clock_time2ticks(&param.sched_ss_repl_period, &repl_ticks);
      (void)clock_time2ticks(&param.sched_ss_init_budget, &budget_ticks);

      /* The replenishment period must be greater than or equal to the
       * budget period.
       */

      if (repl_ticks < budget_ticks)
        {
          errcode = EINVAL;
          goto errout_with_join;
        }

      /* Initialize the sporadic policy */

      ret = sched_sporadic_initialize(&ptcb->cmn);
      if (ret >= 0)
        {
          sporadic               = ptcb->cmn.sporadic;
          DEBUGASSERT(sporadic != NULL);

          /* Save the sporadic scheduling parameters */

          sporadic->hi_priority  = param.sched_priority;
          sporadic->low_priority = param.sched_ss_low_priority;
          sporadic->max_repl     = param.sched_ss_max_repl;
          sporadic->repl_period  = repl_ticks;
          sporadic->budget       = budget_ticks;

          /* And start the first replenishment interval */

          ret = sched_sporadic_start(&ptcb->cmn);
        }

      /* Handle any failures */

      if (ret < 0)
        {
          errcode = -ret;
          goto errout_with_join;
        }
    }
#endif

  /* Initialize the task control block */

  ret = pthread_schedsetup(ptcb, param.sched_priority, pthread_start,
                           start_routine);
  if (ret != OK)
    {
      errcode = EBUSY;
      goto errout_with_join;
    }

  /* Configure the TCB for a pthread receiving on parameter
   * passed by value
   */

  pthread_argsetup(ptcb, arg);

#ifdef HAVE_TASK_GROUP
  /* Join the parent's task group */

  ret = group_join(ptcb);
  if (ret < 0)
    {
      errcode = ENOMEM;
      goto errout_with_join;
    }

  group_joined = true;
#endif

  /* Attach the join info to the TCB. */

  ptcb->joininfo = (FAR void *)pjoin;

  /* Set the appropriate scheduling policy in the TCB */

  ptcb->cmn.flags &= ~TCB_FLAG_POLICY_MASK;
  switch (policy)
    {
      default:
        DEBUGPANIC();
      case SCHED_FIFO:
        ptcb->cmn.flags    |= TCB_FLAG_SCHED_FIFO;
        break;

#if CONFIG_RR_INTERVAL > 0
      case SCHED_RR:
        ptcb->cmn.flags    |= TCB_FLAG_SCHED_RR;
        ptcb->cmn.timeslice = MSEC2TICK(CONFIG_RR_INTERVAL);
        break;
#endif

#ifdef CONFIG_SCHED_SPORADIC
      case SCHED_SPORADIC:
        ptcb->cmn.flags    |= TCB_FLAG_SCHED_SPORADIC;
        break;
#endif

#if 0 /* Not supported */
      case SCHED_OTHER:
        ptcb->cmn.flags    |= TCB_FLAG_SCHED_OTHER;
        break;
#endif
    }

  /* Get the assigned pid before we start the task (who knows what
   * could happen to ptcb after this!).  Copy this ID into the join structure
   * as well.
   */

  pid = (int)ptcb->cmn.pid;
  pjoin->thread = (pthread_t)pid;

  /* Initialize the semaphores in the join structure to zero. */

  ret = sem_init(&pjoin->data_sem, 0, 0);
  if (ret == OK)
    {
      ret = sem_init(&pjoin->exit_sem, 0, 0);
    }

  /* Activate the task */

  sched_lock();
  if (ret == OK)
    {
      ret = task_activate((FAR struct tcb_s *)ptcb);
    }

  if (ret == OK)
    {
      /* Wait for the task to actually get running and to register
       * its join structure.
       */

      (void)pthread_takesemaphore(&pjoin->data_sem);

      /* Return the thread information to the caller */

      if (thread)
       {
         *thread = (pthread_t)pid;
       }

      if (!pjoin->started)
        {
          ret = EINVAL;
        }

      sched_unlock();
      (void)sem_destroy(&pjoin->data_sem);
    }
  else
    {
      sched_unlock();
      dq_rem((FAR dq_entry_t *)ptcb, (FAR dq_queue_t *)&g_inactivetasks);
      (void)sem_destroy(&pjoin->data_sem);
      (void)sem_destroy(&pjoin->exit_sem);

      errcode = EIO;
      goto errout_with_join;
    }

  return ret;

errout_with_join:
  sched_kfree(pjoin);
  ptcb->joininfo = NULL;

errout_with_tcb:
#ifdef HAVE_TASK_GROUP
  /* Clear group binding */

  if (ptcb && !group_joined)
    {
      ptcb->cmn.group = NULL;
    }
#endif

  sched_releasetcb((FAR struct tcb_s *)ptcb, TCB_FLAG_TTYPE_PTHREAD);
  return errcode;
}