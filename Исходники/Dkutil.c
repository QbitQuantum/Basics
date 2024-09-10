void
get_real_time (timeout_t * to)
{
#if defined (WIN32)
#if 0
  static DWORD prec_nsec = 0, dummy;
  static BOOL b1;

  if (prec_nsec == 0)
    GetSystemTimeAdjustment (&dummy, &prec_nsec, &dummy);

  to->to_sec = time (NULL);

  if (prec_nsec)
    to->to_usec = (((long) (GetTickCount () / (prec_nsec * 10))) * (prec_nsec * 10)) % 1000;
  else
    to->to_usec = GetTickCount () % 1000;
#else
  ULARGE_INTEGER tim;
  GetSystemTimeAsFileTime ((FILETIME *) & tim);	 /* 100ns ticks since Jan 1, 1601 */
  tim.QuadPart -= 0x19DB1DED53E8000L;		 /* ticks between 1601 and 1970 year */
  tim.QuadPart /= 10;				 /* convert to microseconds */
  to->to_usec = (int32) (tim.QuadPart % 1000000);	/* microseconds */
  to->to_sec = (int32) (tim.QuadPart / 1000000); /* seconds */
#endif
#else
  struct timeval tv;
  gettimeofday (&tv, NULL);
  to->to_sec = tv.tv_sec;
  to->to_usec = tv.tv_usec;
#endif
}