// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
char* formattedTime(const char* formatting, char* output)
{
  struct tm* t;
#ifdef _MSC_VER
#if _MSC_VER >= 1400
  struct tm time;
  errno_t tError;
#endif
#endif
  TimeType long_time;
  TimeFunc(&long_time);
  t = NULL;
#ifdef _MSC_VER
#if _MSC_VER < 1400
  t = _localtime64(&long_time);
#else
  t = &time;
  tError = _localtime64_s(&time, &long_time);
#endif
#else  // Non windows platforms
  t = localtime(&long_time);
#endif
  memset(output, 0, 128);
  snprintf(output, 128, formatting, t->tm_year + 1900, t->tm_mon + 1,
    t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec  );
  return output;
}