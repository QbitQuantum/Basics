void Time::SetSystemTime ()
{
	int hr, mn, sec, m, d, y;
	char timebuf[100];
	char datebuf[100];
	std::string line;

	#ifdef _MSC_VER
		#ifdef VS2005
		_strtime_s ( timebuf, 100 );
		_strdate_s ( datebuf, 100 );
		#else
		_strtime ( timebuf );
		_strdate ( datebuf );
		#endif
	#endif
	#if (defined(__linux__) || defined(__CYGWIN__))
		time_t tt; 
		struct tm tim;
		tt = time(NULL);	
		localtime_r(&tt, &tim);	
		sprintf( timebuf, "%02i:%02i:%02i", tim.tm_hour, tim.tm_min, tim.tm_sec);
		sprintf( datebuf, "%02i:%02i:%02i", tim.tm_mon, tim.tm_mday, tim.tm_year % 100);
	#endif

	line = timebuf;
	hr = atoi ( line.substr ( 0, 2).c_str() );
	mn = atoi ( line.substr ( 3, 2).c_str() );
	sec = atoi ( line.substr ( 6, 2).c_str() );
	line = datebuf;
	m = atoi ( line.substr ( 0, 2).c_str() );
	d = atoi ( line.substr ( 3, 2).c_str() );
	y = atoi ( line.substr ( 6, 2).c_str() );
	
	// NOTE: This only works from 1930 to 2030
	if ( y > 30) y += 1900;
	else y += 2000;
	
	SetTime ( hr, mn, m, d, y, sec, 0, 0);
}