static void a_initTimer(void)
{
#ifdef HAVEMMLIB
  TIMECAPS timecaps;
  BOOL tok;

  timerEvent_g = CreateSemaphore(NULL, 0, 2*HZ, NULL);
  tok = (timerEvent_g != NULL);

  if (tok)
    tok = timeGetDevCaps(&timecaps, sizeof(timecaps)) == TIMERR_NOERROR;

  if (tok)
    tok = timeBeginPeriod(timecaps.wPeriodMin) == TIMERR_NOERROR;

  if (tok)
  {

    if (timeSetEvent(1000 / HZ, 1000 / HZ,
                     (LPTIMECALLBACK) a_timerCallback,
                     0, TIME_PERIODIC) == 0)
    {
      timeEndPeriod(timecaps.wPeriodMin);
      tok = FALSE;
    }
  }

  if (!tok && (timerEvent_g != NULL))
  {
    CloseHandle(timerEvent_g);
    timerEvent_g = NULL;
  }
#endif
}