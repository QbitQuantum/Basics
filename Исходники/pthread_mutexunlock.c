int pthread_mutex_unlock(FAR pthread_mutex_t *mutex)
{
  int ret = OK;

  sdbg("mutex=0x%p\n", mutex);

  if (!mutex)
    {
      ret = EINVAL;
    }
  else
    {
      /* Make sure the semaphore is stable while we make the following
       * checks.  This all needs to be one atomic action.
       */

      sched_lock();

      /* Does the calling thread own the semaphore? */

      if (mutex->pid != (int)getpid())
        {
          /* No... return an error (default behavior is like PTHREAD_MUTEX_ERRORCHECK) */

          sdbg("Holder=%d returning EPERM\n", mutex->pid);
          ret = EPERM;
        }


      /* Yes, the caller owns the semaphore.. Is this a recursive mutex? */

#ifdef CONFIG_MUTEX_TYPES
      else if (mutex->type == PTHREAD_MUTEX_RECURSIVE && mutex->nlocks > 1)
        {
          /* This is a recursive mutex and we there are multiple locks held. Retain
           * the mutex lock, just decrement the count of locks held, and return
           * success.
           */
          mutex->nlocks--;
        }
#endif

      /* This is either a non-recursive mutex or is the outermost unlock of
       * a recursive mutex.
       */

      else
        {
          /* Nullify the pid and lock count then post the semaphore */

          mutex->pid    = -1;
#ifdef CONFIG_MUTEX_TYPES
          mutex->nlocks = 0;
#endif
          ret = pthread_givesemaphore((FAR sem_t *)&mutex->sem);
        }
      sched_unlock();
    }

  sdbg("Returning %d\n", ret);
  return ret;
}