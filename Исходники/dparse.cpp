time_t date_parse(const char *str)
{
    time_t now;
    struct tm* now_tmP;
    struct tm tm;
    const char* cp;
    char str_mon[500], str_wday[500], str_gmtoff[500], str_ampm[500];
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, gmtoff, local_gmtoff;
    int ampm, got_zone;
    time_t t;


    if (!str || !*str) return (time_t) 0;

    /* Initialize tm with relevant parts of current local time. */
    now = time( (time_t*) 0 );
    now_tmP = localtime( &now );

    bzero( (char*) &tm, sizeof(struct tm) );
    tm.tm_sec = now_tmP->tm_sec;
    tm.tm_min = now_tmP->tm_min;
    tm.tm_hour = now_tmP->tm_hour;
    tm.tm_mday = now_tmP->tm_mday;
    tm.tm_mon = now_tmP->tm_mon;
    tm.tm_year = now_tmP->tm_year;
    ampm = AMPM_NONE;
    got_zone = 0;

    /* Find local zone offset.  This is the only real area of
    ** non-portability, and it's only used for local times that don't
    ** specify a zone - those don't occur in email and netnews.
    */
#ifdef HAVE_STRUCT_TM_GMTOFF
    gmtoff = now_tmP->tm_gmtoff;
#else
    tzset();
    gmtoff = -timezone;
#endif

	local_gmtoff = gmtoff;

    /* Skip initial whitespace ourselves - sscanf is clumsy at this. */
    for ( cp = str; *cp == ' ' || *cp == '\t'; ++cp )
	;

    /* And do the sscanfs.  WARNING: you can add more formats here,
    ** but be careful!  You can easily screw up the parsing of existing
    ** formats when you add new ones.
    */

    /* N mth YYYY HH:MM:SS ampm zone */
    if ( ( ( sscanf( cp, "%d %[a-zA-Z] %d %d:%d:%d %[apmAPM] %[^: ]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min, &tm_sec, str_ampm, str_gmtoff ) == 8 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
            sscanf( cp, "%d %[a-zA-Z] %d %d:%d:%d %[^: ]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min, &tm_sec, str_gmtoff ) == 7 ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
	DP( "N mth YYYY HH:MM:SS ampm zone" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = tm_sec;
	got_zone = 1;
	}
    /* N mth YYYY HH:MM ampm zone */
    else if ( ( ( sscanf( cp, "%d %[a-zA-Z] %d %d:%d %[apmAPM] %[^: ]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min, str_ampm, str_gmtoff ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
            sscanf( cp, "%d %[a-zA-Z] %d %d:%d %[^: ]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,	str_gmtoff ) == 6 ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
	DP( "N mth YYYY HH:MM ampm zone" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = 0;
	got_zone = 1;
	}
    /* N mth YYYY HH:MM:SS ampm */
    else if ( ( ( sscanf( cp, "%d %[a-zA-Z] %d %d:%d:%d %[apmAPM]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min, &tm_sec, str_ampm ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
            sscanf( cp, "%d %[a-zA-Z] %d %d:%d:%d",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,	&tm_sec ) == 6 ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
	DP( "N mth YYYY HH:MM:SS ampm" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = tm_sec;
	}
    /* N mth YYYY HH:MM ampm */
    else if ( ( ( sscanf( cp, "%d %[a-zA-Z] %d %d:%d %[apmAPM]",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min, str_ampm ) == 6 &&
		scan_ampm( str_ampm, &ampm ) ) ||
            sscanf( cp, "%d %[a-zA-Z] %d %d:%d",
		&tm_mday, str_mon, &tm_year, &tm_hour, &tm_min ) == 5 ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
	DP( "N mth YYYY HH:MM ampm" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = 0;
	}
    /* mm/dd/yy[yy] HH:MM:SS [ampm] [zone]*/
    else if (
			( sscanf( cp, "%d/%d/%d %d:%d:%d %[apmAPM] %[^: ]",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, &tm_sec, str_ampm, str_gmtoff ) == 8 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && scan_ampm( str_ampm, &ampm ) && (got_zone = 1))
		||
			( sscanf( cp, "%d/%d/%d %d:%d:%d %[apmAPM]",
			&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, &tm_sec, str_ampm ) == 7 &&
			scan_ampm( str_ampm, &ampm ) )
		||
			( sscanf( cp, "%d/%d/%d %d:%d:%d",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, &tm_sec ) == 6 )
			)
	{
	DP( "mm/dd/yy[yy] HH:MM:SS [ampm] [zone]" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = tm_sec;
	}
    /* mm/dd/yy[yy] HH:MM [ampm] [zone]*/
    else if (
		( sscanf( cp, "%d/%d/%d %d:%d %[apmAPM] %[^: ]",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, str_ampm, str_gmtoff ) == 7 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && scan_ampm( str_ampm, &ampm ) && (got_zone = 1) )
		||
		( sscanf( cp, "%d/%d/%d %d:%d %[apmAPM]",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, str_ampm ) == 6 &&
	    scan_ampm( str_ampm, &ampm ) ) 
		||
		( sscanf( cp, "%d/%d/%d %d:%d %[^: ]",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min, str_gmtoff ) == 6 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && (got_zone = 1) ) 
		||
        ( sscanf( cp, "%d/%d/%d %d:%d",
		&tm_mon, &tm_mday, &tm_year, &tm_hour, &tm_min ) == 5 ) 
		)
	{
	DP( "mm/dd/yy[yy] HH:MM [ampm] [zone]" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = mm_fix(tm_mon);
	tm.tm_year = tm_year;
	tm.tm_hour = ampm_fix( tm_hour, ampm );
	tm.tm_min = tm_min;
	tm.tm_sec = 0;
	}
    /* yy[yy]-mm-dd hh:nn:ss [ampm] [zone]*/
    else if (
		( sscanf( cp, "%d-%d-%d %d:%d:%d %[apmAPM] %[^: ]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec, str_ampm, str_gmtoff ) == 8 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && scan_ampm( str_ampm, &ampm ) && (got_zone = 1) )
		||
		( sscanf( cp, "%d-%d-%d %d:%d:%d %[apmAPM]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec, str_ampm ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) 
		||
		( sscanf( cp, "%d-%d-%d %d:%d:%d %[^: ]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec, str_gmtoff ) == 7 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && (got_zone = 1) ) 
		||
        ( sscanf( cp, "%d-%d-%d %d:%d:%d",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec ) == 6 ) 
		)
	{
		DP( "yy[yy]-mm-dd hh:nn:ss [ampm] [zone]" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
	}
    /* yy[yy]-mm-dd hh:nn [ampm] [zone]*/
    else if (
		( sscanf( cp, "%d-%d-%d %d:%d %[apmAPM] %[^: ]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, str_ampm, str_gmtoff ) == 7 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && scan_ampm( str_ampm, &ampm ) && (got_zone = 1) )
		||
		( sscanf( cp, "%d-%d-%d %d:%d %[apmAPM]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, str_ampm ) == 6 &&
	    scan_ampm( str_ampm, &ampm ) ) 
		||
		( sscanf( cp, "%d-%d-%d %d:%d %[^: ]",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, str_gmtoff ) == 6 &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) && (got_zone = 1) ) 
		||
        ( sscanf( cp, "%d-%d-%d %d:%d",
		&tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min) == 5 ) 
		)
	{
		DP( "yy[yy]-mm-dd hh:nn:ss [ampm] [zone]" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
	}
	/* mm/dd/yy[yy]*/
    else if ( sscanf( cp, "%d/%d/%d", &tm_mon, &tm_mday, &tm_year) == 3 ) {
		DP( "mm/dd/yy[yy]" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		tm.tm_year = tm_year;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
	/*yy[yy]-mm-dd*/
    else if ( sscanf( cp, "%d-%d-%d", &tm_year, &tm_mon, &tm_mday) == 3 ) {
		DP( "yy[yy]-mm-dd" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		tm.tm_year = tm_year;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}	/* mm/dd*/
    else if ( sscanf( cp, "%d/%d %d:%d %[apmAPM]", &tm_mon, &tm_mday, &tm_hour, &tm_min, str_ampm) == 5  && scan_ampm( str_ampm, &ampm ) ) {
		DP( "mm/dd hh:ss aa" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		//  tm.tm_year = same as it was;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    else if ( sscanf( cp, "%d/%d %d:%d", &tm_mon, &tm_mday, &tm_hour, &tm_min) == 4 ) {
		DP( "mm/dd hh:ss" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		//  tm.tm_year = same as it was;
		tm.tm_hour = tm_hour;
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
	}
    else if ( sscanf( cp, "%d/%d", &tm_mon, &tm_mday) == 2 ) {
		DP( "mm/dd" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = mm_fix(tm_mon);
		//  tm.tm_year = same as it was;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    /* HH:MM:SS ampm zone N mth YYYY */
    else if ( ( ( sscanf( cp, "%d:%d:%d %[apmAPM] %[^: ] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, &tm_sec, str_ampm, str_gmtoff, &tm_mday,
		str_mon, &tm_year ) == 8 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d:%d %[^: ] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, &tm_sec, str_gmtoff, &tm_mday, str_mon,
		&tm_year ) == 7 ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "HH:MM:SS ampm zone N mth YYYY" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
	}
    /* HH:MM ampm zone N mth YYYY */
    else if ( ( ( sscanf( cp, "%d:%d %[apmAPM] %[^: ] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, str_ampm, str_gmtoff, &tm_mday, str_mon,
		&tm_year ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d %[^: ] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, str_gmtoff, &tm_mday, str_mon,
		&tm_year ) == 6 ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
	DP( "HH:MM ampm N mth YYYY" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
	}
    /* HH:MM:SS ampm N mth YYYY */
    else if ( ( ( sscanf( cp, "%d:%d:%d %[apmAPM] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, &tm_sec, str_ampm, &tm_mday, str_mon,
		&tm_year ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d:%d %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, &tm_sec, &tm_mday, str_mon,
		&tm_year ) == 6 ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
	DP( "HH:MM:SS ampm N mth YYYY" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
	}
    /* HH:MM ampm N mth YYYY */
    else if ( ( ( sscanf( cp, "%d:%d %[apmAPM] %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, str_ampm, &tm_mday, str_mon,
		&tm_year ) == 6 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d %d %[a-zA-Z] %d",
		&tm_hour, &tm_min, &tm_mday, str_mon, &tm_year ) == 5 ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "HH:MM ampm N mth YYYY" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
	}
    /* wdy, N mth YYYY HH:MM:SS ampm zone */
    else if ( ( ( sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d:%d %[apmAPM] %[^: ]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		&tm_sec, str_ampm, str_gmtoff ) == 9 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d:%d %[^: ]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		&tm_sec, str_gmtoff ) == 8 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
		DP( "wdy, N mth YYYY HH:MM:SS ampm zone" );
		tm.tm_wday = tm_wday;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
		got_zone = 1;
	}
    /* wdy, N mth YYYY HH:MM ampm zone */
    else if ( ( ( sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d %[apmAPM] %[^: ]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		str_ampm, str_gmtoff ) == 8 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d %[^: ]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		str_gmtoff ) == 7 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
		DP( "wdy, N mth YYYY HH:MM ampm zone" );
		tm.tm_wday = tm_wday;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
		got_zone = 1;
	}
    /* wdy, N mth YYYY HH:MM:SS ampm */
    else if ( ( ( sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d:%d %[apmAPM]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		&tm_sec, str_ampm ) == 8 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d:%d",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		&tm_sec ) == 7 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "wdy, N mth YYYY HH:MM:SS ampm" );
		tm.tm_wday = tm_wday;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
	}
    /* wdy, N mth YYYY HH:MM ampm */
    else if ( ( ( sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d %[apmAPM]",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour, &tm_min,
		str_ampm ) == 7 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z], %d %[a-zA-Z] %d %d:%d",
		str_wday, &tm_mday, str_mon, &tm_year, &tm_hour,
		&tm_min ) == 6 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "wdy, N mth YYYY HH:MM ampm" );
		tm.tm_wday = tm_wday;
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
	}
    /* wdy mth N HH:MM:SS ampm zone YYYY */
    else if ( ( ( sscanf( cp, "%[a-zA-Z] %[a-zA-Z] %d %d:%d:%d %[apmAPM] %[^: ] %d",
		str_wday, str_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec,
		str_ampm, str_gmtoff, &tm_year ) == 9 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z] %[a-zA-Z] %d %d:%d:%d %[^: ] %d",
		str_wday, str_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec,
		str_gmtoff, &tm_year ) == 8 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
		DP( "wdy mth N HH:MM:SS ampm zone YYYY" );
		tm.tm_wday = tm_wday;
		tm.tm_mon = tm_mon;
		tm.tm_mday = tm_mday;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
		got_zone = 1;
		tm.tm_year = tm_year;
	}
    /* wdy mth N HH:MM ampm zone YYYY */
    else if ( ( ( sscanf( cp, "%[a-zA-Z] %[a-zA-Z] %d %d:%d %[apmAPM] %[^: ] %d",
	    str_wday, str_mon, &tm_mday, &tm_hour, &tm_min,
	    str_ampm, str_gmtoff, &tm_year ) == 8 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%[a-zA-Z] %[a-zA-Z] %d %d:%d %[^: ] %d",
		str_wday, str_mon, &tm_mday, &tm_hour, &tm_min,
		str_gmtoff, &tm_year ) == 7 ) &&
	    scan_wday( str_wday, &tm_wday ) &&
	    scan_mon( str_mon, &tm_mon ) &&
	    scan_gmtoff( str_gmtoff, &gmtoff ) )
	{
		DP( "wdy mth N HH:MM ampm zone YYYY" );
		tm.tm_wday = tm_wday;
		tm.tm_mon = tm_mon;
		tm.tm_mday = tm_mday;
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
		got_zone = 1;
		tm.tm_year = tm_year;
	}
    /* N mth YY[YY] */
    else if ( sscanf( cp, "%d %[a-zA-Z] %d",
	    &tm_mday, str_mon, &tm_year ) == 3 &&
	    scan_mon( str_mon, &tm_mon ) )
	{
	DP( "N mth YYYY" );
	tm.tm_mday = tm_mday;
	tm.tm_mon = tm_mon;
	tm.tm_year = tm_year;
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	}
    /* mth N [,] YY[YY] */
    else if ( (sscanf( cp, "%[a-zA-Z] %d %d",
			str_mon, &tm_mday, &tm_year ) == 3 || 
			   sscanf( cp, "%[a-zA-Z] %d , %d",
			str_mon, &tm_mday, &tm_year ) == 3)
		&&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "N mth YYYY" );
		tm.tm_mday = tm_mday;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    /* mth [,] YY[YY] */
    else if ( (
			sscanf( cp, "%[a-zA-Z] %d", str_mon, &tm_year ) == 2
			||
			sscanf( cp, "%[a-zA-Z] , %d", str_mon, &tm_year ) == 2
		) &&
	    scan_mon( str_mon, &tm_mon ) )
	{
		DP( "mth [,] YY[YY]" );
		tm.tm_mday = 1;
		tm.tm_mon = tm_mon;
		tm.tm_year = tm_year;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    /* mth*/
    else if ( sscanf( cp, "%[a-zA-Z]", str_mon) == 1 && 
		scan_mon( str_mon, &tm_mon ) )
	{
		DP( "mth" );
		tm.tm_mday = 1;
		tm.tm_mon = tm_mon;
		//  tm.tm_year = same as it was;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    /* HH:MM:SS ampm */
    else if ( ( sscanf( cp, "%d:%d:%d %[apmAPM]",
	    &tm_hour, &tm_min, &tm_sec, str_ampm ) == 4 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d:%d", &tm_hour, &tm_min, &tm_sec ) == 3 )
	{
		DP( "HH:MM:SS ampm" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = tm_sec;
	}
    /* HH:MM ampm */
    else if ( ( sscanf( cp, "%d:%d %[apmAPM]", &tm_hour, &tm_min,
		str_ampm ) == 3 &&
	    scan_ampm( str_ampm, &ampm ) ) ||
	    sscanf( cp, "%d:%d", &tm_hour, &tm_min ) == 2 )
	{
		DP( "HH:MM" );
		tm.tm_hour = ampm_fix( tm_hour, ampm );
		tm.tm_min = tm_min;
		tm.tm_sec = 0;
	}
    /* yymmdd */
    else if ( (sscanf( cp, "%d", &tm_year) == 1) && 
			(tm_year % 100 > 0) &&
			(tm_year % 100 <= 31) &&
			((tm_year / 100) % 100 > 0) &&
			((tm_year / 100) % 100 <= 12) &&
			(strlen(cp) == 6) )
	{
		DP( "yymmdd" );
		tm.tm_mday = (int) (tm_mon % 100);
		tm.tm_mon =  mm_fix((int) (tm_mon / 100) % 100);
		tm.tm_year = (int) (tm_year / 10000);
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
    }
	else if ( (sscanf( cp, "%d", &tm_year) == 1) && 
			(tm_year % 100 > 0) &&
			(tm_year % 100 <= 31) &&
			((tm_year / 100) % 100 > 0) &&
			((tm_year / 100) % 100 <= 12) &&
			(strlen(cp) == 8) )
	{
		DP( "yyyymmdd" );
		tm.tm_mday = (int) (tm_mon % 100);
		tm.tm_mon =  mm_fix((int) (tm_mon / 100) % 100);
		tm.tm_year = (int) (tm_year / 10000);
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
	}
    else
	return (time_t) -1;

	// solve yNk bug.... 2 digit year = closest to now
	static int yk_low = -1;
	static int yk_off = 0;
	if (yk_low < 0) {
		yk_low = ((now_tmP->tm_year + 50) % 100);
		yk_off = 100 * (int) ((now_tmP->tm_year-50) / 100);
	}

    if ( tm.tm_year > 1900 )
		tm.tm_year -= 1900;
    else {
		if ( tm.tm_year < yk_low )
			tm.tm_year += 100;
		tm.tm_year += yk_off;
	}

	tm.tm_isdst = -1;
    t = mktime(&tm);
	t += (local_gmtoff - gmtoff);

    return t;
}