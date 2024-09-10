void cnv_tar2win_time(time_t tartime, FILETIME *ftm)
{
#ifdef HAS_LIBC_CAL_FUNCS
		  FILETIME ftLocal;
		  SYSTEMTIME st;
		  struct tm localt;
 
		  localt = *localtime(&tartime);
		  
		  st.wYear = (WORD)localt.tm_year+1900;
		  st.wMonth = (WORD)localt.tm_mon+1;    /* 1 based, not 0 based */
		  st.wDayOfWeek = (WORD)localt.tm_wday;
		  st.wDay = (WORD)localt.tm_mday;
		  st.wHour = (WORD)localt.tm_hour;
		  st.wMinute = (WORD)localt.tm_min;
		  st.wSecond = (WORD)localt.tm_sec;
		  st.wMilliseconds = 0;
		  SystemTimeToFileTime(&st,&ftLocal);
		  LocalFileTimeToFileTime(&ftLocal,ftm);
#else
	// avoid casts further below
    LONGLONG *t = (LONGLONG *)ftm;

	// tartime == number of seconds since midnight Jan 1 1970 (00:00:00)
	// convert to equivalent 100 nanosecond intervals
	*t = UInt32x32To64(tartime, 10000000UL);

	// now base on 1601, add number of 100 nansecond intervals between 1601 & 1970
	*t += HUNDREDSECINTERVAL;  /* 116444736000000000i64; */
#endif
}