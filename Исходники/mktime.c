time_t __cdecl mktime(struct tm *_Tm)
{
  return _mktime64(_Tm);
}