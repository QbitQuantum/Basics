static FAR struct iob_s *iob_allocwait(bool throttled)
{
  FAR struct iob_s *iob;
  irqstate_t flags;
  FAR sem_t *sem;
  int ret = OK;

#if CONFIG_IOB_THROTTLE > 0
  /* Select the semaphore count to check. */

  sem = (throttled ? &g_throttle_sem : &g_iob_sem);
#else
  sem = &g_iob_sem;
#endif

  /* The following must be atomic; interrupt must be disabled so that there
   * is no conflict with interrupt level I/O buffer allocations.  This is
   * not as bad as it sounds because interrupts will be re-enabled while
   * we are waiting for I/O buffers to become free.
   */

  flags = irqsave();
  do
    {
      /* Try to get an I/O buffer.  If successful, the semaphore count
       * will be decremented atomically.
       */

      iob = iob_tryalloc(throttled);
      if (!iob)
        {
          /* If not successful, then the semaphore count was less than or
           * equal to zero (meaning that there are no free buffers).  We
           * need to wait for an I/O buffer to be released when the semaphore
           * count will be incremented.
           */

          ret = sem_wait(sem);
          if (ret < 0)
            {
              int errcode = get_errno();

              /* EINTR is not an error!  EINTR simply means that we were
               * awakened by a signal and we should try again.
               *
               * REVISIT:  Many end-user interfaces are required to return
               * with an error if EINTR is set.  Most uses of this function
               * is in internal, non-user logic.  But are there cases where
               * the error should be returned.
               */

              if (errcode == EINTR)
                {
                  /* Force a success indication so that we will continue
                   * looping.
                   */

                  ret = 0;
                }
              else
                {
                  /* Stop the loop and return a error */

                  DEBUGASSERT(errcode > 0);
                  ret = -errcode;
                }
            }
          else
            {
              /* When we wake up from wait successfully, an I/O buffer was
               * returned to the free list.  However, if there are concurrent
               * allocations from interrupt handling, then I suspect that
               * there is a race condition.  But no harm, we will just wait
               * again in that case.
               *
               * We need release our count so that it is available to
               * iob_tryalloc(), perhaps allowing another thread to take our
               * count.  In that event, iob_tryalloc() will fail above and
               * we will have to wait again.
               *
               * TODO: Consider a design modification to permit us to
               * complete the allocation without losing our count.
               */

              sem_post(sem);
            }
        }
    }
  while (ret == OK && iob == NULL);

  irqrestore(flags);
  return iob;
}