int datetime_( char* sDate, char* sTime, char* zone, integer* values, 

				ftnlen dateLen, ftnlen timeLen, ftnlen zoneLen )

{

	time_t 		t1;

	struct tm 	*now;

	struct tm 	localNow;

	struct tm 	utcNow;

	integer 	zoneTime;

	char		temp[11];		/* allow room for terminating null */

	int			maxLen;

	int			i;

	

	time( &t1 );				/* System time */

	now = gmtime( &t1 );		/* format as struct in utc time */

	utcNow = *now;

	now = localtime( &t1 ); 	/* format as struct in local time */

	localNow = *now;



	/* Set up the values array */

	values[0] = localNow.tm_year + 1900;

	values[1] = localNow.tm_mon + 1;

	values[2] = localNow.tm_mday;

	

	/* Handle non-whole hour timezones correctly; produce value in minutes */

	values[3] = (localNow.tm_hour - utcNow.tm_hour) * 60;

	values[3] += localNow.tm_min - utcNow.tm_min;				

	

	values[4] = localNow.tm_hour;

	values[5] = localNow.tm_min;

	values[6] = localNow.tm_sec;

	values[7] = 0;

	

	

	/* Fill in the date string */

	strftime( temp, 11, "%Y%y%m%d", now ); 	/* use ANSI strftime to format */	

	/* Copy over at most the first 8 characters */

	maxLen = (dateLen < 8) ? dateLen : 8;

	for ( i = 0; i < maxLen; i++ )

		sDate[i] = temp[i];

	

	/* Fill in the time string, zeroing out the milliseconds */

	strftime( temp, 11, "%H%M%S", now );

	temp[6] = '.';

	temp[7] = temp[8] = temp[9] = '0';

	/* Copy over at most the first 11 characters */

	maxLen = (timeLen < 11) ? timeLen : 11;

	for ( i = 0; i < maxLen; i++ )

		sTime[i] = temp[i];

	

	/* Fill in the zone string */

	/* ...Get sign */

	if ( values[3] < 0 )

	{

		temp[0] = '-';

		zoneTime = -values[3];				// Force positive for following computations

	}

	else

	{

		temp[0] = '+';

		zoneTime = values[3];	

	}	

	/* ...Get hours */

	sprintf( temp+1, "%2d", zoneTime/60 );

	/* ...Get the minutes */

	sprintf( temp+3, "%2d", zoneTime % 60 );

	/* Copy over at most the first 5 characters */

	maxLen = (zoneLen < 5) ? zoneLen : 5;

	for ( i = 0; i < maxLen; i++ )

		zone[i] = temp[i];

	

	

	return 1;

}