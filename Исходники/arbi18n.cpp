CString
ArbI18N::convert_tm(const tm& theTM)
{
   CString s;
   SYSTEMTIME date;

   date.wYear   = theTM.tm_year + 1900;
   date.wMonth  = theTM.tm_mon + 1;
   date.wDay    = theTM.tm_mday;
   date.wHour   = theTM.tm_hour + 1;
   date.wMinute = theTM.tm_min;
   date.wSecond = theTM.tm_sec;
   date.wDayOfWeek = 0;
   date.wMilliseconds = 0;


   GetDateFormat(GetThreadLocale(), DATE_SHORTDATE, &date, NULL,
      s.GetBuffer(ARB_DATE_LEN), ARB_DATE_LEN);
   s.ReleaseBuffer();

   return s;
}