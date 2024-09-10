void purge_sent(int days)
{
	char s[121];
	int howmany = 0;
	time_t age = 0;
	struct _finddata_t ff;
	struct _stat fileinfo;
	
	sprintf( s, "%sSENT\\*.*", net_data );
	long hFind = _findfirst( s, &ff );
	int nFindNext = ( hFind != -1 ) ? 0 : -1;
	while ( nFindNext == 0 ) 
	{
		sprintf( s, "%sSENT\\%s", net_data, ff.name );
		if ( _stat( s, &fileinfo ) == 0 ) 
		{
			age = ( time(NULL) - fileinfo.st_atime );
			if ( age > ( SECONDS_PER_DAY * days ) ) 
			{
				++howmany;
				_unlink( s );
			}
		}
		nFindNext = _findnext( hFind, &ff );
	}
	fprintf( stderr, " %d packet%s deleted.", howmany, howmany == 1 ? "" : "s" );
}