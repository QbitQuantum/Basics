void CCenTime::GenCurrentTime(char *timebuf, int Len)
{

    char tmpbuf[128];
	if(!timebuf) 
	{
		return;
	}
    // Set time zone from TZ environment variable. If TZ is not set,
    // the operating system is queried to obtain the default value 
    // for the variable. 
    //
    _tzset();

    // Display operating system-style date and time. 
    _strtime_s( tmpbuf, 128 );
	strcpy_s(timebuf, Len, tmpbuf);

	return;
}