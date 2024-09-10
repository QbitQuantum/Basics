int pthread_cond_waitImpl (pthread_cond_t *cv, 
                   pthread_mutex_t *external_mutex,
                   const struct timespec *abstime,
                   bool infinite)
{
    int last_waiter;
    DWORD dwMilliseconds = INFINITE;

  // Avoid race conditions.
  EnterCriticalSection (&cv->waiters_count_lock_);
  cv->waiters_count_++;
  LeaveCriticalSection (&cv->waiters_count_lock_);

  // This call atomically releases the mutex and waits on the
  // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
  // are called by another thread.
  if (!infinite && abstime != NULL)
  { dwMilliseconds = abstime->tv_sec * 1000 + abstime->tv_nsec / 1000000; }
  SignalObjectAndWait (*external_mutex, cv->sema_, dwMilliseconds, FALSE);

  // Reacquire lock to avoid race conditions.
  EnterCriticalSection (&cv->waiters_count_lock_);

  // We're no longer waiting...
  cv->waiters_count_--;

  // Check to see if we're the last waiter after <pthread_cond_broadcast>.
  last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;

  LeaveCriticalSection (&cv->waiters_count_lock_);

  // If we're the last waiter thread during this particular broadcast
  // then let all the other threads proceed.
  if (last_waiter)
    // This call atomically signals the <waiters_done_> event and waits until
    // it can acquire the <external_mutex>.
    // This is required to ensure fairness.
    SignalObjectAndWait (cv->waiters_done_, *external_mutex, INFINITE, FALSE);
  else {
    // Always regain the external mutex since that's the guarantee we
    // give to our callers. 
/*      fprintf(stderr, "%s: WaitForSingleObject...\n", __func__); */
    WaitForSingleObject (*external_mutex, INFINITE);
/*      fprintf(stderr, "... %s: WaitForSingleObject\n", __func__); */
  }

  return 0;
}