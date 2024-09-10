bool ConvertFileTimeToString(const FILETIME &ft, char *s, bool includeTime, bool includeSeconds)
{
#ifdef _WIN32
  s[0] = '\0';
  SYSTEMTIME st;
  if (!BOOLToBool(FileTimeToSystemTime(&ft, &st)))
    return false;
  s = UIntToStringSpec(0, st.wYear, s, 4);
  s = UIntToStringSpec('-', st.wMonth, s, 2);
  s = UIntToStringSpec('-', st.wDay, s, 2);
  if (includeTime)
  {
    s = UIntToStringSpec(' ', st.wHour, s, 2);
    s = UIntToStringSpec(':', st.wMinute, s, 2);
    if (includeSeconds)
      UIntToStringSpec(':', st.wSecond, s, 2);
  }
  /*
  sprintf(s, "%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
  if (includeTime)
  {
    sprintf(s + strlen(s), " %02d:%02d", st.wHour, st.wMinute);
    if (includeSeconds)
      sprintf(s + strlen(s), ":%02d", st.wSecond);
  }
  */
#else
  BOOLEAN WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, DWORD *Seconds );

  FILETIME filetime;
  LocalFileTimeToFileTime(&ft, &filetime);

  LARGE_INTEGER  ltime;

  ltime.QuadPart = filetime.dwHighDateTime;
  ltime.QuadPart = (ltime.QuadPart << 32) | filetime.dwLowDateTime;

  DWORD dw;
  RtlTimeToSecondsSince1970(&ltime, &dw );
  time_t timep = (time_t)dw;

  struct tm * date = localtime(&timep);

  sprintf(s, "%04d-%02d-%02d", date->tm_year+1900, date->tm_mon+1,date->tm_mday);
  if (includeTime)
  {
    sprintf(s + strlen(s), " %02d:%02d", date->tm_hour,date->tm_min);
    if (includeSeconds)
      sprintf(s + strlen(s), ":%02d", date->tm_sec);
  }
#endif
  return true;
}