void rlTime::setLocalTime()
{
#ifdef RLUNIX
  struct timeval tv;
  struct tm t;

  t.tm_mday  = day;
  t.tm_mon   = month - 1;
  t.tm_year  = year - 1900;
  t.tm_hour  = hour;
  t.tm_min   = minute;
  t.tm_sec   = second;
  tv.tv_sec  = mktime(&t);
  tv.tv_usec = 1000 * millisecond;
  settimeofday(&tv,NULL);
#endif

#ifdef __VMS
  VAX_BIN_TIME vbt;
  struct dsc$descriptor_s  d_time;
  char smonth[12][4],buf[64];

  // Initialize month array
  memset (smonth   , 0, sizeof(smonth));
  memcpy (smonth  [0], "JAN", 3);
  memcpy (smonth  [1], "FEB", 3);
  memcpy (smonth  [2], "MAR", 3);
  memcpy (smonth  [3], "APR", 3);
  memcpy (smonth  [4], "MAY", 3);
  memcpy (smonth  [5], "JUN", 3);
  memcpy (smonth  [6], "JUL", 3);
  memcpy (smonth  [7], "AUG", 3);
  memcpy (smonth  [8], "SEP", 3);
  memcpy (smonth  [9], "OCT", 3);
  memcpy (smonth [10], "NOV", 3);
  memcpy (smonth [11], "DEC", 3);
  // Create time buffer
  sprintf(buf, "%02d-%3.3s-%04d %02d:%02d:%02d.%02d",
                day,
                smonth[month-1],
                year,
                hour,
                minute,
                second,
                millisecond / 10);

  // Fill string descriptor
  d_time.dsc$w_length  = strlen(buf);
  d_time.dsc$b_dtype   = DSC$K_DTYPE_T;
  d_time.dsc$b_class   = DSC$K_CLASS_S;
  d_time.dsc$a_pointer = buf;
  // Convert time buf to VAX bin time
  sys$bintim(&d_time, &vbt);
  // Set the system time
  sys$setime(&vbt);
#endif

#ifdef RLWIN32
  SYSTEMTIME st;
  st.wDay          = day;
  st.wMonth        = month;
  st.wYear         = year;
  st.wHour         = hour;
  st.wMinute       = minute;
  st.wSecond       = second;
  st.wMilliseconds = millisecond;
  SetSystemTime(&st);
#endif
}