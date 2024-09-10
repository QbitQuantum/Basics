void
xsleep (double seconds)
{
#ifdef HAVE_USLEEP
  if (seconds > 1000)
    {
      /* Explained in utils.c. */
      sleep (seconds);
      seconds -= (long) seconds;
    }
  usleep (seconds * 1000000);
#else  /* not HAVE_USLEEP */
  SleepEx ((DWORD) (seconds * 1000 + .5), FALSE);
#endif /* not HAVE_USLEEP */
}