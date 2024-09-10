void RarTime::GetLocal(RarLocalTime *lt)
{
#ifdef _WIN_ALL
  FILETIME ft;
  GetWin32(&ft);
  FILETIME lft;

  if (WinNT() < WNT_VISTA)
  {
    // SystemTimeToTzSpecificLocalTime based code produces 1 hour error on XP.
    FileTimeToLocalFileTime(&ft,&lft);
  }
  else
  {
    // We use these functions instead of FileTimeToLocalFileTime according to
    // MSDN recommendation: "To account for daylight saving time
    // when converting a file time to a local time ..."
    SYSTEMTIME st1,st2;
    FileTimeToSystemTime(&ft,&st1);
    SystemTimeToTzSpecificLocalTime(NULL,&st1,&st2);
    SystemTimeToFileTime(&st2,&lft);

    // Correct precision loss (low 4 decimal digits) in FileTimeToSystemTime.
    FILETIME rft;
    SystemTimeToFileTime(&st1,&rft);
    int64 Corrected=INT32TO64(ft.dwHighDateTime,ft.dwLowDateTime)-
                    INT32TO64(rft.dwHighDateTime,rft.dwLowDateTime)+
                    INT32TO64(lft.dwHighDateTime,lft.dwLowDateTime);
    lft.dwLowDateTime=(DWORD)Corrected;
    lft.dwHighDateTime=(DWORD)(Corrected>>32);
  }

  SYSTEMTIME st;
  FileTimeToSystemTime(&lft,&st);
  lt->Year=st.wYear;
  lt->Month=st.wMonth;
  lt->Day=st.wDay;
  lt->Hour=st.wHour;
  lt->Minute=st.wMinute;
  lt->Second=st.wSecond;
  lt->wDay=st.wDayOfWeek;
  lt->yDay=lt->Day-1;

  static int mdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  for (uint I=1;I<lt->Month && I<=ASIZE(mdays);I++)
    lt->yDay+=mdays[I-1];

  if (lt->Month>2 && IsLeapYear(lt->Year))
    lt->yDay++;

  st.wMilliseconds=0;
  FILETIME zft;
  SystemTimeToFileTime(&st,&zft);

  // Calculate the time reminder, which is the part of time smaller
  // than 1 second, represented in 100-nanosecond intervals.
  lt->Reminder=INT32TO64(lft.dwHighDateTime,lft.dwLowDateTime)-
               INT32TO64(zft.dwHighDateTime,zft.dwLowDateTime);
#else
  time_t ut=GetUnix();
  struct tm *t;
  t=localtime(&ut);

  lt->Year=t->tm_year+1900;
  lt->Month=t->tm_mon+1;
  lt->Day=t->tm_mday;
  lt->Hour=t->tm_hour;
  lt->Minute=t->tm_min;
  lt->Second=t->tm_sec;
  lt->Reminder=itime % 10000000;
  lt->wDay=t->tm_wday;
  lt->yDay=t->tm_yday;
#endif
}