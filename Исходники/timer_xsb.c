VOID CALLBACK xsb_timer_handler(HWND wind, UINT msg, UINT eventid, DWORD time)
{
  if (exitFlag == STILL_WAITING)
    exitFlag = TIMED_OUT; /* tell the timed thread to quit */
  TerminateThread((HANDLE)timedThread, 1);
}