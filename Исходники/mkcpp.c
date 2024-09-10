static void utime2ftime(struct timeval *tv,FILETIME *ftime)
{	int year,mon,day,hour,min,sec;
	struct tm *tm;
	WORD ddate,dtime;
	struct tm tm0;
	time_t tsec;

	tsec = tv->tv_sec;
	tm = gmtime(&tsec);
	/*
	tm = gmtime(&tv->tv_sec);
	*/
	if( tm == 0 ){
		memset(&tm0,0,sizeof(tm0));
		tm = &tm0;
	}

	year = tm->tm_year + 1900 - 1980;
	mon  = tm->tm_mon  +  1;
	day  = tm->tm_mday;
	hour = tm->tm_hour;
	min  = tm->tm_min;
	sec  = tm->tm_sec / 2;
	ddate = (year <<  9) | (mon << 5) | day;
	dtime = (hour << 11) | (min << 5) | sec;
	DosDateTimeToFileTime(ddate,dtime,ftime);
}