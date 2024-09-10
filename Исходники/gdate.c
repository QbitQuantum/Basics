static gsize
win32_strftime_helper (const GDate     *d,
		       const gchar     *format,
		       const struct tm *tm,
		       gchar           *s,
		       gsize	        slen)
{
  SYSTEMTIME systemtime;
  TIME_ZONE_INFORMATION tzinfo;
  LCID lcid;
  int n, k;
  GArray *result;
  const gchar *p;
  gunichar c;
  const wchar_t digits[] = L"0123456789";
  gchar *convbuf;
  glong convlen = 0;
  gsize retval;

  systemtime.wYear = tm->tm_year + 1900;
  systemtime.wMonth = tm->tm_mon + 1;
  systemtime.wDayOfWeek = tm->tm_wday;
  systemtime.wDay = tm->tm_mday;
  systemtime.wHour = tm->tm_hour;
  systemtime.wMinute = tm->tm_min;
  systemtime.wSecond = tm->tm_sec;
  systemtime.wMilliseconds = 0;
  
  lcid = GetThreadLocale ();
  result = g_array_sized_new (FALSE, FALSE, sizeof (wchar_t), MAX (128, strlen (format) * 2));

  p = format;
  while (*p)
    {
      c = g_utf8_get_char (p);
      if (c == '%')
	{
	  p = g_utf8_next_char (p);
	  if (!*p)
	    {
	      s[0] = '\0';
	      g_array_free (result, TRUE);

	      return 0;
	    }
	  
	  c = g_utf8_get_char (p);
	  if (c == 'E' || c == 'O')
	    {
	      /* Ignore modified conversion specifiers for now. */
	      p = g_utf8_next_char (p);
	      if (!*p)
		{
		  s[0] = '\0';
		  g_array_free (result, TRUE);
		  
		  return 0;
		}

	      c = g_utf8_get_char (p);
	    }

	  switch (c)
	    {
	    case 'a':
	      if (systemtime.wDayOfWeek == 0)
		k = 6;
	      else
		k = systemtime.wDayOfWeek - 1;
	      n = GetLocaleInfoW (lcid, LOCALE_SABBREVDAYNAME1+k, NULL, 0);
	      g_array_set_size (result, result->len + n);
	      GetLocaleInfoW (lcid, LOCALE_SABBREVDAYNAME1+k, ((wchar_t *) result->data) + result->len - n, n);
	      g_array_set_size (result, result->len - 1);
	      break;
	    case 'A':
	      if (systemtime.wDayOfWeek == 0)
		k = 6;
	      else
		k = systemtime.wDayOfWeek - 1;
	      n = GetLocaleInfoW (lcid, LOCALE_SDAYNAME1+k, NULL, 0);
	      g_array_set_size (result, result->len + n);
	      GetLocaleInfoW (lcid, LOCALE_SDAYNAME1+k, ((wchar_t *) result->data) + result->len - n, n);
	      g_array_set_size (result, result->len - 1);
	      break;
	    case 'b':
	    case 'h':
	      n = GetLocaleInfoW (lcid, LOCALE_SABBREVMONTHNAME1+systemtime.wMonth-1, NULL, 0);
	      g_array_set_size (result, result->len + n);
	      GetLocaleInfoW (lcid, LOCALE_SABBREVMONTHNAME1+systemtime.wMonth-1, ((wchar_t *) result->data) + result->len - n, n);
	      g_array_set_size (result, result->len - 1);
	      break;
	    case 'B':
	      n = GetLocaleInfoW (lcid, LOCALE_SMONTHNAME1+systemtime.wMonth-1, NULL, 0);
	      g_array_set_size (result, result->len + n);
	      GetLocaleInfoW (lcid, LOCALE_SMONTHNAME1+systemtime.wMonth-1, ((wchar_t *) result->data) + result->len - n, n);
	      g_array_set_size (result, result->len - 1);
	      break;
	    case 'c':
	      n = GetDateFormatW (lcid, 0, &systemtime, NULL, NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetDateFormatW (lcid, 0, &systemtime, NULL, ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      g_array_append_vals (result, L" ", 1);
	      n = GetTimeFormatW (lcid, 0, &systemtime, NULL, NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetTimeFormatW (lcid, 0, &systemtime, NULL, ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      break;
	    case 'C':
	      g_array_append_vals (result, digits + systemtime.wYear/1000, 1);
	      g_array_append_vals (result, digits + (systemtime.wYear/1000)%10, 1);
	      break;
	    case 'd':
	      g_array_append_vals (result, digits + systemtime.wDay/10, 1);
	      g_array_append_vals (result, digits + systemtime.wDay%10, 1);
	      break;
	    case 'D':
	      g_array_append_vals (result, digits + systemtime.wMonth/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMonth%10, 1);
	      g_array_append_vals (result, L"/", 1);
	      g_array_append_vals (result, digits + systemtime.wDay/10, 1);
	      g_array_append_vals (result, digits + systemtime.wDay%10, 1);
	      g_array_append_vals (result, L"/", 1);
	      g_array_append_vals (result, digits + (systemtime.wYear/10)%10, 1);
	      g_array_append_vals (result, digits + systemtime.wYear%10, 1);
	      break;
	    case 'e':
	      if (systemtime.wDay >= 10)
		g_array_append_vals (result, digits + systemtime.wDay/10, 1);
	      else
		g_array_append_vals (result, L" ", 1);
	      g_array_append_vals (result, digits + systemtime.wDay%10, 1);
	      break;

	      /* A GDate has no time fields, so for now we can
	       * hardcode all time conversions into zeros (or 12 for
	       * %I). The alternative code snippets in the #else
	       * branches are here ready to be taken into use when
	       * needed by a g_strftime() or g_date_and_time_format()
	       * or whatever.
	       */
	    case 'H':
#if 1
	      g_array_append_vals (result, L"00", 2);
#else
	      g_array_append_vals (result, digits + systemtime.wHour/10, 1);
	      g_array_append_vals (result, digits + systemtime.wHour%10, 1);
#endif
	      break;
	    case 'I':
#if 1
	      g_array_append_vals (result, L"12", 2);
#else
	      if (systemtime.wHour == 0)
		g_array_append_vals (result, L"12", 2);
	      else
		{
		  g_array_append_vals (result, digits + (systemtime.wHour%12)/10, 1);
		  g_array_append_vals (result, digits + (systemtime.wHour%12)%10, 1);
		}
#endif
	      break;
	    case  'j':
	      g_array_append_vals (result, digits + (tm->tm_yday+1)/100, 1);
	      g_array_append_vals (result, digits + ((tm->tm_yday+1)/10)%10, 1);
	      g_array_append_vals (result, digits + (tm->tm_yday+1)%10, 1);
	      break;
	    case 'm':
	      g_array_append_vals (result, digits + systemtime.wMonth/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMonth%10, 1);
	      break;
	    case 'M':
#if 1
	      g_array_append_vals (result, L"00", 2);
#else
	      g_array_append_vals (result, digits + systemtime.wMinute/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMinute%10, 1);
#endif
	      break;
	    case 'n':
	      g_array_append_vals (result, L"\n", 1);
	      break;
	    case 'p':
	      n = GetTimeFormatW (lcid, 0, &systemtime, L"tt", NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetTimeFormatW (lcid, 0, &systemtime, L"tt", ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      break;
	    case 'r':
	      /* This is a rather odd format. Hard to say what to do.
	       * Let's always use the POSIX %I:%M:%S %p
	       */
#if 1
	      g_array_append_vals (result, L"12:00:00", 8);
#else
	      if (systemtime.wHour == 0)
		g_array_append_vals (result, L"12", 2);
	      else
		{
		  g_array_append_vals (result, digits + (systemtime.wHour%12)/10, 1);
		  g_array_append_vals (result, digits + (systemtime.wHour%12)%10, 1);
		}
	      g_array_append_vals (result, L":", 1);
	      g_array_append_vals (result, digits + systemtime.wMinute/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMinute%10, 1);
	      g_array_append_vals (result, L":", 1);
	      g_array_append_vals (result, digits + systemtime.wSecond/10, 1);
	      g_array_append_vals (result, digits + systemtime.wSecond%10, 1);
	      g_array_append_vals (result, L" ", 1);
#endif
	      n = GetTimeFormatW (lcid, 0, &systemtime, L"tt", NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetTimeFormatW (lcid, 0, &systemtime, L"tt", ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      break;
	    case 'R':
#if 1
	      g_array_append_vals (result, L"00:00", 5);
#else
	      g_array_append_vals (result, digits + systemtime.wHour/10, 1);
	      g_array_append_vals (result, digits + systemtime.wHour%10, 1);
	      g_array_append_vals (result, L":", 1);
	      g_array_append_vals (result, digits + systemtime.wMinute/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMinute%10, 1);
#endif
	      break;
	    case 'S':
#if 1
	      g_array_append_vals (result, L"00", 2);
#else
	      g_array_append_vals (result, digits + systemtime.wSecond/10, 1);
	      g_array_append_vals (result, digits + systemtime.wSecond%10, 1);
#endif
	      break;
	    case 't':
	      g_array_append_vals (result, L"\t", 1);
	      break;
	    case 'T':
#if 1
	      g_array_append_vals (result, L"00:00:00", 8);
#else
	      g_array_append_vals (result, digits + systemtime.wHour/10, 1);
	      g_array_append_vals (result, digits + systemtime.wHour%10, 1);
	      g_array_append_vals (result, L":", 1);
	      g_array_append_vals (result, digits + systemtime.wMinute/10, 1);
	      g_array_append_vals (result, digits + systemtime.wMinute%10, 1);
	      g_array_append_vals (result, L":", 1);
	      g_array_append_vals (result, digits + systemtime.wSecond/10, 1);
	      g_array_append_vals (result, digits + systemtime.wSecond%10, 1);
#endif
	      break;
	    case 'u':
	      if (systemtime.wDayOfWeek == 0)
		g_array_append_vals (result, L"7", 1);
	      else
		g_array_append_vals (result, digits + systemtime.wDayOfWeek, 1);
	      break;
	    case 'U':
	      n = g_date_get_sunday_week_of_year (d);
	      g_array_append_vals (result, digits + n/10, 1);
	      g_array_append_vals (result, digits + n%10, 1);
	      break;
	    case 'V':
	      n = g_date_get_iso8601_week_of_year (d);
	      g_array_append_vals (result, digits + n/10, 1);
	      g_array_append_vals (result, digits + n%10, 1);
	      break;
	    case 'w':
	      g_array_append_vals (result, digits + systemtime.wDayOfWeek, 1);
	      break;
	    case 'W':
	      n = g_date_get_monday_week_of_year (d);
	      g_array_append_vals (result, digits + n/10, 1);
	      g_array_append_vals (result, digits + n%10, 1);
	      break;
	    case 'x':
	      n = GetDateFormatW (lcid, 0, &systemtime, NULL, NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetDateFormatW (lcid, 0, &systemtime, NULL, ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      break;
	    case 'X':
	      n = GetTimeFormatW (lcid, 0, &systemtime, NULL, NULL, 0);
	      if (n > 0)
		{
		  g_array_set_size (result, result->len + n);
		  GetTimeFormatW (lcid, 0, &systemtime, NULL, ((wchar_t *) result->data) + result->len - n, n);
		  g_array_set_size (result, result->len - 1);
		}
	      break;
	    case 'y':
	      g_array_append_vals (result, digits + (systemtime.wYear/10)%10, 1);
	      g_array_append_vals (result, digits + systemtime.wYear%10, 1);
	      break;
	    case 'Y':
	      g_array_append_vals (result, digits + systemtime.wYear/1000, 1);
	      g_array_append_vals (result, digits + (systemtime.wYear/100)%10, 1);
	      g_array_append_vals (result, digits + (systemtime.wYear/10)%10, 1);
	      g_array_append_vals (result, digits + systemtime.wYear%10, 1);
	      break;
	    case 'Z':
	      n = GetTimeZoneInformation (&tzinfo);
	      if (n == TIME_ZONE_ID_UNKNOWN)
		;
	      else if (n == TIME_ZONE_ID_STANDARD)
		g_array_append_vals (result, tzinfo.StandardName, wcslen (tzinfo.StandardName));
	      else if (n == TIME_ZONE_ID_DAYLIGHT)
		g_array_append_vals (result, tzinfo.DaylightName, wcslen (tzinfo.DaylightName));
	      break;
	    case '%':
	      g_array_append_vals (result, L"%", 1);
	      break;
	    }      
	} 
      else if (c <= 0xFFFF)
	{
	  wchar_t wc = c;
	  g_array_append_vals (result, &wc, 1);
	}
      else
	{
	  glong nwc;
	  wchar_t *ws;

	  ws = g_ucs4_to_utf16 (&c, 1, NULL, &nwc, NULL);
	  g_array_append_vals (result, ws, nwc);
	  g_free (ws);
	}
      p = g_utf8_next_char (p);
    }
  
  convbuf = g_utf16_to_utf8 ((wchar_t *) result->data, result->len, NULL, &convlen, NULL);
  g_array_free (result, TRUE);

  if (!convbuf)
    {
      s[0] = '\0';
      return 0;
    }
  
  if (slen <= convlen)
    {
      /* Ensure only whole characters are copied into the buffer. */
      gchar *end = g_utf8_find_prev_char (convbuf, convbuf + slen);
      g_assert (end != NULL);
      convlen = end - convbuf;

      /* Return 0 because the buffer isn't large enough. */
      retval = 0;
    }
  else
    retval = convlen;

  memcpy (s, convbuf, convlen);
  s[convlen] = '\0';
  g_free (convbuf);

  return retval;
}