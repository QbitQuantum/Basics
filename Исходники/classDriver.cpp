/*******************************************************
 * Init
 *******************************************************
 * Call the odbcinst to get Driver description.
 *
 * NOTE: 	This should be done via the Driver Manager by
 *			calling SQLDrivers() but the iODBC Driver Manager
 *			does not, at this time, adequately support this call.
 *******************************************************/
void classDriver::Init( char *pszDriverName, SQLHENV hEnv )
{
	char 				szResults[1024];
	char				szPropertyValue[INI_MAX_PROPERTY_VALUE+1];

	qsDriverName = "";
	if ( pszDriverName != 0 )
		qsDriverName = pszDriverName;

	this->pCanvas 	= pCanvas;
	this->hEnv 		= hEnv;
	setPixmap( 0, QPixmap( driver_xpm ) );

	szResults[0] 		= '\0';
    szPropertyValue[0]	= '\0';
	if ( SQLGetPrivateProfileString((char*) qsDriverName.data(), "Description", "", szResults, sizeof(szResults), "odbcinst" ) > 0 )
		iniElement( szResults, '\0', '\0', 0, szPropertyValue, INI_MAX_PROPERTY_VALUE );
	else
	{
		//SQLInstallerError( 1, &nError, szError, FILENAME_MAX, 0 );
		//if ( cVerbose == 0 ) printf( "[odbcinst] SQLGetPrivateProfileString failed with %s.\n", szError );
		//return;
	}

	setText( 0, qsDriverName );
	setText( 1, "" );
	setText( 2, szPropertyValue );
}