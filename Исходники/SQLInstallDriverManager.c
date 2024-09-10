BOOL INSTAPI SQLInstallDriverManagerW (LPWSTR      lpszPath,
                                      WORD       cbPathMax,
                                      WORD      * pcbPathOut)
{
	char *path;
	BOOL ret;

    inst_logClear();

	path = calloc( cbPathMax, 1 );

	ret = SQLInstallDriverManager( path, cbPathMax, pcbPathOut );

	if ( ret ) 
	{
		_single_string_copy_to_wide( lpszPath, path, cbPathMax );
	}

	free( path );

	return ret;
}