BOOL _odbcinst_FileINI( char *pszPath )
{
	char b1[ ODBC_FILENAME_MAX + 1 ];

    /* we need a viable buffer (with space for FILENAME_MAX chars)... */
    if ( !pszPath )
        return FALSE;

    /* system configured to use a special location... */
    *pszPath = '\0';
    SQLGetPrivateProfileString( "ODBC", "FileDSNPath", "", pszPath, FILENAME_MAX - 2, "odbcinst.ini" );
    if ( *pszPath )
        return TRUE;

    /* default location... */
    sprintf( pszPath, "%s/ODBCDataSources", odbcinst_system_file_path( b1 ));

    return TRUE;
}