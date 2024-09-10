int nsDateTimeFormatWin::nsGetTimeFormatW(DWORD dwFlags, const SYSTEMTIME *lpTime,
                                          const char* format, PRUnichar *timeStr, int cchTime)
{
  int len = 0;
  len = GetTimeFormatW(mLCID, dwFlags, lpTime, 
                       format ?
                       NS_ConvertASCIItoUTF16(format).get() :
                       nullptr,
                       (LPWSTR) timeStr, cchTime);
  return len;
}