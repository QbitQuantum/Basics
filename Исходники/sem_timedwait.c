int sem_timedwait(FAR sem_t *sem, FAR const struct timespec *abstime)
{
  FAR struct tcb_s *rtcb = this_task();
  irqstate_t flags;
  int        ticks;
  int        errcode;
  int        ret = ERROR;

  DEBUGASSERT(up_interrupt_context() == false && rtcb->waitdog == NULL);

  /* Verify the input parameters and, in case of an error, set
   * errno appropriately.
   */

#ifdef CONFIG_DEBUG
  if (!abstime || !sem)
    {
      errcode = EINVAL;
      goto errout;
    }
#endif

  /* Create a watchdog.  We will not actually need this watchdog
   * unless the semaphore is unavailable, but we will reserve it up
   * front before we enter the following critical section.
   */

  rtcb->waitdog = wd_create();
  if (!rtcb->waitdog)
    {
      errcode = ENOMEM;
      goto errout;
    }

  /* We will disable interrupts until we have completed the semaphore
   * wait.  We need to do this (as opposed to just disabling pre-emption)
   * because there could be interrupt handlers that are asynchronously
   * posting semaphores and to prevent race conditions with watchdog
   * timeout.  This is not too bad because interrupts will be re-
   * enabled while we are blocked waiting for the semaphore.
   */

  flags = irqsave();

  /* Try to take the semaphore without waiting. */

  ret = sem_trywait(sem);
  if (ret == OK)
    {
      /* We got it! */

      goto success_with_irqdisabled;
    }

  /* We will have to wait for the semaphore.  Make sure that we were provided
   * with a valid timeout.
   */

  if (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000)
    {
      errcode = EINVAL;
      goto errout_with_irqdisabled;
    }

  /* Convert the timespec to clock ticks.  We must have interrupts
   * disabled here so that this time stays valid until the wait begins.
   */

  errcode = clock_abstime2ticks(CLOCK_REALTIME, abstime, &ticks);

  /* If the time has already expired return immediately. */

  if (errcode == OK && ticks <= 0)
    {
      errcode = ETIMEDOUT;
      goto errout_with_irqdisabled;
    }

  /* Handle any time-related errors */

  if (errcode != OK)
    {
      goto errout_with_irqdisabled;
    }

  /* Start the watchdog */

  (void)wd_start(rtcb->waitdog, ticks, (wdentry_t)sem_timeout, 1, getpid());

  /* Now perform the blocking wait */

  ret = sem_wait(sem);
  if (ret < 0)
    {
      /* sem_wait() failed.  Save the errno value */

      errcode = get_errno();
    }

  /* Stop the watchdog timer */

  wd_cancel(rtcb->waitdog);

  if (errcode != OK)
    {
      goto errout_with_irqdisabled;
    }

  /* We can now restore interrupts and delete the watchdog */

  /* Success exits */

success_with_irqdisabled:
  irqrestore(flags);
  wd_delete(rtcb->waitdog);
  rtcb->waitdog = NULL;
  return OK;

  /* Error exits */

errout_with_irqdisabled:
  irqrestore(flags);
  wd_delete(rtcb->waitdog);
  rtcb->waitdog = NULL;

errout:
  set_errno(errcode);
  return ERROR;
}