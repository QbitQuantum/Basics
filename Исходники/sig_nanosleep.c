int nanosleep(FAR const struct timespec *rqtp, FAR struct timespec *rmtp)
{
  irqstate_t flags;
  systime_t starttick;
  sigset_t set;
  struct siginfo value;
  int errval;
#ifdef CONFIG_DEBUG /* Warning avoidance */
  int ret;
#endif

  if (!rqtp || rqtp->tv_nsec < 0 || rqtp->tv_nsec >= 1000000000)
    {
      errval = EINVAL;
      goto errout;
    }

  /* Get the start time of the wait.  Interrupts are disabled to prevent
   * timer interrupts while we do tick-related calculations before and
   * after the wait.
   */

  flags     = irqsave();
  starttick = clock_systimer();

  /* Set up for the sleep.  Using the empty set means that we are not
   * waiting for any particular signal.  However, any unmasked signal can
   * still awaken sigtimedwait().
   */

  (void)sigemptyset(&set);

  /* nanosleep is a simple application of sigtimedwait. */

#ifdef CONFIG_DEBUG /* Warning avoidance */
  ret = sigtimedwait(&set, &value, rqtp);
#else
  (void)sigtimedwait(&set, &value, rqtp);
#endif

  /* sigtimedwait() cannot succeed.  It should always return error with
   * either (1) EAGAIN meaning that the timeout occurred, or (2) EINTR
   * meaning that some other unblocked signal was caught.
   */

  errval = get_errno();
  DEBUGASSERT(ret < 0 && (errval == EAGAIN || errval == EINTR));

  if (errval == EAGAIN)
    {
      /* The timeout "error" is the normal, successful result */

      irqrestore(flags);
      return OK;
    }

  /* If we get there, the wait has failed because we were awakened by a
   * signal.  Return the amount of "unwaited" time if rmtp is non-NULL.
   */

  if (rmtp)
    {
      systime_t elapsed;
      systime_t remaining;
      int ticks;

      /* First get the number of clock ticks that we were requested to
       * wait.
       */

      (void)clock_time2ticks(rqtp, &ticks);

      /* Get the number of ticks that we actually waited */

      elapsed = clock_systimer() - starttick;

      /* The difference between the number of ticks that we were requested
       * to wait and the number of ticks that we actualy waited is that
       * amount of time that we failed to wait.
       */

      if (elapsed >= (uint32_t)ticks)
        {
          remaining = 0;
        }
      else
        {
          remaining = (uint32_t)ticks - elapsed;
        }

      (void)clock_ticks2time((int)remaining, rmtp);
    }

  irqrestore(flags);

errout:
  set_errno(errval);
  return ERROR;
}