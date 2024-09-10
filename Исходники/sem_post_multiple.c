int
sem_post_multiple (sem_t * sem, int count)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function posts multiple wakeups to a semaphore.
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      *      count
      *              counter, must be greater than zero.
      *
      * DESCRIPTION
      *      This function posts multiple wakeups to a semaphore. If there
      *      are waiting threads (or processes), n <= count are awakened;
      *      the semaphore value is incremented by count - n.
      *
      * RESULTS
      *              0               successfully posted semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore
      *                              or count is less than or equal to zero.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
#ifndef NEED_SEM
  long waiters;
  sem_t s = *sem;
#endif

  if (s == NULL || count <= 0)
    {
      result = EINVAL;
    }

#ifdef NEED_SEM

  else if (!ptw32_increase_semaphore (sem, count))
    {
      result = EINVAL;
    }

#else /* NEED_SEM */

  else if ((result = pthread_mutex_lock (&s->lock)) == 0)
    {
      waiters = -s->value;
      s->value += count;
      if (waiters > 0)
        {
          if (!ReleaseSemaphore (s->sem,  (waiters<=count)?waiters:count, 0))
            {
              result = EINVAL;
            }
        }
      (void) pthread_mutex_unlock (&s->lock);
    }

#endif /* NEED_SEM */

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* sem_post_multiple */