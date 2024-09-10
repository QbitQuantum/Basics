BOOL INSTAPI SQLGetInstalledDriversW  (LPWSTR      lpszBuf,
                                      WORD       cbBufMax,
                                      WORD      * pcbBufOut)
{
	char *path;
	BOOL ret;

    inst_logClear();

	path = calloc( cbBufMax, 1 );

	ret = SQLGetInstalledDrivers( path, cbBufMax, pcbBufOut );

	if ( ret ) 
	{
		_multi_string_copy_to_wide( lpszBuf, path, cbBufMax );
	}

	free( path );

	return ret;
}