KDint xmBadaStat ( const KDchar* path, struct stat* buf )
{
	struct tm       t;
	FileAttributes  attr;
	DateTime        dt;
	result          r;

	r = File::GetAttributes ( path, attr );

	if ( IsFailed ( r ) )
	{
		goto failed;
	}

	dt = attr.GetLastModifiedTime ( );

	t.tm_year = dt.GetYear   ( );
	t.tm_mon  = dt.GetMonth  ( ) - 1;
	t.tm_mday = dt.GetDay    ( );
	t.tm_hour = dt.GetHour   ( );
	t.tm_min  = dt.GetMinute ( );
	t.tm_sec  = dt.GetSecond ( );

	buf->st_mtime = mktime ( &t );
	buf->st_mode  = attr.IsDirectory ( ) ? 0x4000 : 0x8000;
	buf->st_size  = attr.GetFileSize ( );

	return 0;

failed :

	xmBadaSetError ( r );

	return -1;
}