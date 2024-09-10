rboolean
r_cond_wait_timed (RCond * cond, RMutex * mutex, rulong microsec)
{
  rboolean ret;
#if defined (R_OS_WIN32)
  if (!(ret = SleepConditionVariableCS ((PCONDITION_VARIABLE)*cond,
      (LPCRITICAL_SECTION)*mutex, microsec / 1000))) {
    /* GetLastError () should be ERROR_TIMEOUT */
  }
#elif defined (HAVE_PTHREAD_H)
  struct timespec expire;
  int waitret;
  clock_gettime (CLOCK_MONOTONIC, &expire)
  expire.tv_sec = microsec / R_USEC_PER_SEC;
  expire.tv_nsec = 1000 * (microsec % R_USEC_PER_SEC);
  waitret = pthread_cond_timedwait ((pthread_cond_t *)*cond,
      (pthread_mutex_t *)*mutex, &expire);

  if (!(ret = (waitret == 0))) {
    /* waitret should be ETIMEDOUT */
  }
#else
  (void) cond;
  ret = FALSE;
#endif
  return ret;
}