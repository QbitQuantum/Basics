MAGMA_DLLPORT int MAGMA_CDECL pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
  int last;

  if ( *mutex == PTHREAD_MUTEX_INITIALIZER ) pthread_mutex_check_for_static_initialization( mutex );

  /* Avoid race condition on waiting thread counter. */
  EnterCriticalSection(&cond->cs);
  cond->waitCount++;
  LeaveCriticalSection(&cond->cs);

  /* Releases _atomically_ the mutex and wait on the semaphore until
     pthread_cond_signal() or pthread_cond_broadcast() are called (by another thread). */
  SignalObjectAndWait(*mutex, cond->hSem, INFINITE, FALSE);

  /* Avoid race condition on waiting thread counter. */
  EnterCriticalSection(&cond->cs);
  cond->waitCount--; /* this thread doesn't wait any more */

  /* if this is the last thread to have waited */
  last = cond->waitCount == 0;

  LeaveCriticalSection(&cond->cs);

  /* If this thread is the last waiter thread during this particular broadcast
     then let all the other threads proceed. */
  if (last)
    /* This call ensures that two things happen atomically: signaling the hEvt event and
       waiting until "mutex" can be acquired. */
    SignalObjectAndWait(cond->hEvt, *mutex, INFINITE, FALSE);
  else
    WaitForSingleObject(*mutex, INFINITE); /* Upon return, this thread has to own "mutex". */

  return 0;
}