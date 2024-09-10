int
pthread_barrier_wait (pthread_barrier_t * barrier)
{
  int result;
  int step;
  pthread_barrier_t b;

  if (barrier == NULL || *barrier == (pthread_barrier_t) PTW32_OBJECT_INVALID)
    {
      return EINVAL;
    }

  b = *barrier;
  step = b->iStep;

  if (0 == InterlockedDecrement ((long *) &(b->nCurrentBarrierHeight)))
    {
      /* Must be done before posting the semaphore. */
      b->nCurrentBarrierHeight = b->nInitialBarrierHeight;

      /*
       * There is no race condition between the semaphore wait and post
       * because we are using two alternating semas and all threads have
       * entered barrier_wait and checked nCurrentBarrierHeight before this
       * barrier's sema can be posted. Any threads that have not quite
       * entered sem_wait below when the multiple_post has completed
       * will nevertheless continue through the semaphore (barrier)
       * and will not be left stranded.
       */
      result = (b->nInitialBarrierHeight > 1
		? sem_post_multiple (&(b->semBarrierBreeched[step]),
				     b->nInitialBarrierHeight - 1) : 0);
    }
  else
    {
      /*
       * Use the non-cancelable version of sem_wait().
       */
      result = ptw32_semwait (&(b->semBarrierBreeched[step]));
    }

  /*
   * The first thread across will be the PTHREAD_BARRIER_SERIAL_THREAD.
   * This also sets up the alternate semaphore as the next barrier.
   */
  if (0 == result)
    {
      result = ( step ==
		_InterlockedCompareExchange ( &(b->iStep), (1L - step), step) ?
		PTHREAD_BARRIER_SERIAL_THREAD : 0);
    }

  return (result);
}