void classDataSources::setOpen( bool bOpen )
{
	int					nElement;
	char 				szResults[9600];
	char				szObjectName[INI_MAX_OBJECT_NAME+1];

    memset( szResults, 0, sizeof(szResults) );  // Results buffer must be cleared 
    classDataSource     *pLastDataSource    = NULL;

    if ( bOpen )
    {
		memset( szResults, 0, sizeof(szResults) );
		if ( nDataSourceType == User )
			SQLSetConfigMode( ODBC_USER_DSN );
		else
			SQLSetConfigMode( ODBC_SYSTEM_DSN );

		if ( SQLGetPrivateProfileString( 0, 0, 0, szResults, 9600, 0 ) > 0 )
		{
			for ( nElement = 0; iniElement( szResults, '\0', '\0', nElement, szObjectName, INI_MAX_OBJECT_NAME ) == INI_SUCCESS; nElement++ )
			{
				listDataSources.append( pLastDataSource = new classDataSource( this, pLastDataSource, pCanvas, nDataSourceType, szObjectName, hEnv ) );
			}
		}
		else
		{
			//SQLInstallerError( 1, &nError, szError, FILENAME_MAX, 0 );
			//if ( cVerbose == 0 ) printf( "[odbcinst] SQLGetPrivateProfileString failed with %s.\n", szError );
			//return;
		}
		SQLSetConfigMode( ODBC_BOTH_DSN );
    }
    else
    {
        listDataSources.clear();
    }
    QListViewItem::setOpen( bOpen );
}