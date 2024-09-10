int
airThreadCondWait(airThreadCond *cond, airThreadMutex *mutex) {
  int last;

  /* increment count */
  EnterCriticalSection(&(cond->lock)); /* avoid race conditions */
  cond->count++;
  LeaveCriticalSection(&(cond->lock));
  /* atomically release the mutex and wait on the
     semaphore until airThreadCondSignal or airThreadCondBroadcast
     are called by another thread */
  if (WAIT_FAILED == SignalObjectAndWait(mutex->handle, cond->sema,
                                         INFINITE, FALSE)) {
    return 1;
  }
  /* reacquire lock to avoid race conditions */
  EnterCriticalSection(&(cond->lock));
  /* we're no longer waiting... */
  cond->count--;
  /* check to see if we're the last waiter after airThreadCondBroadcast */
  last = (cond->broadcast && 0 == cond->count);
  LeaveCriticalSection(&(cond->lock));
  /* if we're the last waiter thread during this particular broadcast
     then let all the other threads proceed */
  if (last) {
    /* atomically signal the done event and waits until
       we can acquire the mutex (this is required to ensure fairness) */
    if (WAIT_FAILED == SignalObjectAndWait(cond->done, mutex->handle,
                                           INFINITE, FALSE)) {
      return 1;
    }
  } else {
    /* regain the external mutex since that's the guarantee to our callers */
    if (WAIT_FAILED == WaitForSingleObject(mutex->handle, INFINITE)) {
      return 1;
    }
  }
  return 0;
}