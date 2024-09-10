int mtx_timedlock(mtx_t *mtx, const struct timespec *ts)
{
#if defined(_TTHREAD_WIN32_)
  struct timespec current_ts;
  DWORD timeoutMs;

  if (!mtx->mTimed)
  {
    return thrd_error;
  }

  timespec_get(&current_ts, TIME_UTC);

  if ((current_ts.tv_sec > ts->tv_sec) || ((current_ts.tv_sec == ts->tv_sec) && (current_ts.tv_nsec >= ts->tv_nsec)))
  {
    timeoutMs = 0;
  }
  else
  {
    timeoutMs  = (DWORD)(ts->tv_sec  - current_ts.tv_sec)  * 1000;
    timeoutMs += (ts->tv_nsec - current_ts.tv_nsec) / 1000000;
    timeoutMs += 1;
  }

  /* TODO: the timeout for WaitForSingleObject doesn't include time
     while the computer is asleep. */
  switch (WaitForSingleObject(mtx->mHandle.mut, timeoutMs))
  {
    case WAIT_OBJECT_0:
      break;
    case WAIT_TIMEOUT:
      return thrd_timedout;
    case WAIT_ABANDONED:
    default:
      return thrd_error;
  }

  if (!mtx->mRecursive)
  {
    while(mtx->mAlreadyLocked) Sleep(1); /* Simulate deadlock... */
    mtx->mAlreadyLocked = TRUE;
  }

  return thrd_success;
#elif defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >= 200112L) && defined(_POSIX_THREADS) && (_POSIX_THREADS >= 200112L)
  switch (pthread_mutex_timedlock(mtx, ts)) {
    case 0:
      return thrd_success;
    case ETIMEDOUT:
      return thrd_timedout;
    default:
      return thrd_error;
  }
#else
  int rc;
  struct timespec cur, dur;

  /* Try to acquire the lock and, if we fail, sleep for 5ms. */
  while ((rc = pthread_mutex_trylock (mtx)) == EBUSY) {
    timespec_get(&cur, TIME_UTC);

    if ((cur.tv_sec > ts->tv_sec) || ((cur.tv_sec == ts->tv_sec) && (cur.tv_nsec >= ts->tv_nsec)))
    {
      break;
    }

    dur.tv_sec = ts->tv_sec - cur.tv_sec;
    dur.tv_nsec = ts->tv_nsec - cur.tv_nsec;
    if (dur.tv_nsec < 0)
    {
      dur.tv_sec--;
      dur.tv_nsec += 1000000000;
    }

    if ((dur.tv_sec != 0) || (dur.tv_nsec > 5000000))
    {
      dur.tv_sec = 0;
      dur.tv_nsec = 5000000;
    }

    nanosleep(&dur, NULL);
  }

  switch (rc) {
    case 0:
      return thrd_success;
    case ETIMEDOUT:
    case EBUSY:
      return thrd_timedout;
    default:
      return thrd_error;
  }
#endif
}