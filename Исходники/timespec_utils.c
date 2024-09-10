void			timespec_update(struct timespec *time)
{
  assert(time != NULL);
#if defined(_POSIX_C_SOURCE)
  if (clock_gettime(CLOCK_BOOTTIME, time))
    error("clock_gettime");
#else
  if (!timespec_get(time, TIME_UTC))
    error("timespec_get");
#endif
}