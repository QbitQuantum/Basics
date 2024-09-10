BOOL WINAPI FileTimeToDosDateTime( const FILETIME *ft, WORD *fatdate, WORD *fattime ) {
  LARGE_INTEGER       li;
  ULONG               t;
  time_t              unixtime;
  struct tm*          tm;

  TRACEN((printf("FileTimeToDosDateTime\n")))
  li.QuadPart = ft->dwHighDateTime;
  li.QuadPart = (li.QuadPart << 32) | ft->dwLowDateTime;
  RtlTimeToSecondsSince1970( &li, &t );
  unixtime = t;
  tm = gmtime( &unixtime );
  if (fattime)
    *fattime = (tm->tm_hour << 11) + (tm->tm_min << 5) + (tm->tm_sec / 2);
  if (fatdate)
    *fatdate = ((tm->tm_year - 80) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday;
  return TRUE;
}