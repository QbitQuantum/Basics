static int
profile_off (struct profinfo *p)
{
  if (p->profthr)
    {
      SignalObjectAndWait (p->quitevt, p->profthr, INFINITE, FALSE);
      CloseHandle (p->quitevt);
      CloseHandle (p->profthr);
    }
  if (p->targthr)
    CloseHandle (p->targthr);
  return 0;
}