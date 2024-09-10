int task_restart(pid_t pid)
{
  FAR struct tcb_s *rtcb;
  FAR struct task_tcb_s *tcb;
  FAR dq_queue_t *tasklist;
  irqstate_t state;
  int status;

  /* Make sure this task does not become ready-to-run while
   * we are futzing with its TCB
   */

  sched_lock();

  /* Check if the task to restart is the calling task */

  rtcb = this_task();
  if ((pid == 0) || (pid == rtcb->pid))
    {
      /* Not implemented */

      set_errno(ENOSYS);
      return ERROR;
    }

#ifdef CONFIG_SMP
  /* There is currently no capability to restart a task that is actively
   * running on another CPU either.  This is not the calling cast so if it
   * is running, then it could only be running a a different CPU.
   *
   * Also, will need some interlocks to assure that no tasks are rescheduled
   * on any other CPU while we do this.
   */

#warning Missing SMP logic
  if (rtcb->task_state == TSTATE_TASK_RUNNING)
    {
      /* Not implemented */

      set_errno(ENOSYS);
      return ERROR;
    }
#endif

  /* We are restarting some other task than ourselves */
  /* Find for the TCB associated with matching pid  */

  tcb = (FAR struct task_tcb_s *)sched_gettcb(pid);
#ifndef CONFIG_DISABLE_PTHREAD
  if (!tcb || (tcb->cmn.flags & TCB_FLAG_TTYPE_MASK) == TCB_FLAG_TTYPE_PTHREAD)
#else
  if (!tcb)
#endif
    {
      /* There is no TCB with this pid or, if there is, it is not a task. */

      set_errno(ESRCH);
      return ERROR;
    }

  /* Try to recover from any bad states */

  task_recover((FAR struct tcb_s *)tcb);

  /* Kill any children of this thread */

#ifdef HAVE_GROUP_MEMBERS
  (void)group_killchildren(tcb);
#endif

  /* Remove the TCB from whatever list it is in.  After this point, the TCB
   * should no longer be accessible to the system
   */

#ifdef CONFIG_SMP
  tasklist = TLIST_HEAD(tcb->cmn.task_state, tcb->cmn.cpu);
#else
  tasklist = TLIST_HEAD(tcb->cmn.task_state);
#endif

  state = irqsave();
  dq_rem((FAR dq_entry_t *)tcb, tasklist);
  tcb->cmn.task_state = TSTATE_TASK_INVALID;
  irqrestore(state);

  /* Deallocate anything left in the TCB's queues */

  sig_cleanup((FAR struct tcb_s *)tcb); /* Deallocate Signal lists */

  /* Reset the current task priority  */

  tcb->cmn.sched_priority = tcb->init_priority;

  /* Reset the base task priority and the number of pending reprioritizations */

#ifdef CONFIG_PRIORITY_INHERITANCE
  tcb->cmn.base_priority = tcb->init_priority;
#  if CONFIG_SEM_NNESTPRIO > 0
  tcb->cmn.npend_reprio = 0;
#  endif
#endif

  /* Re-initialize the processor-specific portion of the TCB.  This will
   * reset the entry point and the start-up parameters
   */

  up_initial_state((FAR struct tcb_s *)tcb);

  /* Add the task to the inactive task list */

  dq_addfirst((FAR dq_entry_t *)tcb, (FAR dq_queue_t *)&g_inactivetasks);
  tcb->cmn.task_state = TSTATE_TASK_INACTIVE;

  /* Activate the task */

  status = task_activate((FAR struct tcb_s *)tcb);
  if (status != OK)
    {
      (void)task_delete(pid);
      set_errno(-status);
      return ERROR;
    }

  sched_unlock();
  return OK;
}