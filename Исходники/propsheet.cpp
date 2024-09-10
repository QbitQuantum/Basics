bool CPropSheet::UpdateDSN( void )
{
	char* lpszDSN;
	char  szBuf[ _MAX_PATH];

	lpszDSN = aAttr[ KEY_DSN].szAttr;

// if the data source name has changed, remove the old name
	if( !bNewDSN && strcmp( szDSN, lpszDSN) != 0)
	{
		SQLRemoveDSNFromIni( szDSN);
// remove File Data Source Name
		DeleteFileDSN( szDSN );
	}

	if(strcmp( szDSN, lpszDSN )!=0)
	{
		WritePrivateProfileString( lpszDSN,	INI_KDESC, aAttr[ KEY_DESC].szAttr,	ODBC_INI);
		WritePrivateProfileString( lpszDSN,	INI_KSN, aAttr[ KEY_SERVICE_NAME].szAttr,	ODBC_INI);
// update File DSN
		lstrcpy(szBuf, lpszDSN );
		lstrcat(szBuf, " (not sharable)");
		SQLWriteFileDSN( szBuf, "ODBC", "DSN", lpszDSN );
		SQLWritePrivateProfileString( lpszDSN,	INI_KDESC, aAttr[ KEY_DESC].szAttr,	ODBC_INI);
		SQLWritePrivateProfileString( lpszDSN,	INI_KSN, aAttr[ KEY_SERVICE_NAME].szAttr,	ODBC_INI);
	}

// write data source name
	if( !SQLWriteDSNToIni( lpszDSN, lpszDrvr))
	{
		char  szMsg[ MAXPATHLEN];
		CString szBuf;
			
		szBuf.LoadString(IDS_BADDSN);
		wsprintf( szMsg, szBuf, lpszDSN);			
		AfxMessageBox( szMsg);
		return FALSE;
	}

// update ODBC.INI
// save the value if the data source is new, edited, or explicitly supplied
	WritePrivateProfileString( lpszDSN,	INI_KDESC, aAttr[ KEY_DESC].szAttr,	ODBC_INI);
	WritePrivateProfileString( lpszDSN,	INI_KSN, aAttr[ KEY_SERVICE_NAME].szAttr,	ODBC_INI);
// update File DSN
	lstrcpy(szBuf, lpszDSN );
	lstrcat(szBuf, " (not sharable)");
	SQLWriteFileDSN( szBuf, "ODBC", "DSN", lpszDSN );
	SQLWritePrivateProfileString( lpszDSN,	INI_KDESC, aAttr[ KEY_DESC].szAttr,	ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_KSN, aAttr[ KEY_SERVICE_NAME].szAttr,	ODBC_INI);

// the following are the localization (internationalization) attributes
	WritePrivateProfileString( lpszDSN,	INI_ERRORLANG, aAttr[ KEY_ERRORLANG].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_ERRORLANG, aAttr[ KEY_ERRORLANG].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_DATALANG, aAttr[ KEY_DATALANG].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_DATALANG, aAttr[ KEY_DATALANG].szAttr, ODBC_INI);

// Association Service (IP Address and Port Number)
	wsprintf(szBuf, "%s%s/%s", TCP_STR, aAttr[ KEY_IPADDRESS].szAttr, aAttr[ KEY_PORTNUM].szAttr);

	WritePrivateProfileString( lpszDSN,	INI_NETWORK, szBuf, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_NETWORK, szBuf, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_LOGIN, aAttr[ KEY_LOGIN].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_LOGIN, aAttr[ KEY_LOGIN].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_CONNECTION, aAttr[ KEY_CONNECTION].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_CONNECTION, aAttr[ KEY_CONNECTION].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_QUERY, aAttr[ KEY_QUERY].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_QUERY, aAttr[ KEY_QUERY].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_CATALOG, aAttr[ KEY_CATALOG].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_CATALOG, aAttr[ KEY_CATALOG].szAttr, ODBC_INI);
	
	WritePrivateProfileString( lpszDSN,	INI_SCHEMA, aAttr[ KEY_SCHEMA].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_SCHEMA, aAttr[ KEY_SCHEMA].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_TRANSLATION_DLL, aAttr[ KEY_TRANSLATION_DLL].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_TRANSLATION_DLL, aAttr[ KEY_TRANSLATION_DLL].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_TRANSLATION_OPTION, aAttr[ KEY_TRANSLATION_OPTION].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_TRANSLATION_OPTION, aAttr[ KEY_TRANSLATION_OPTION].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_FETCH_BUFFER_SIZE, aAttr[ KEY_FETCH_BUFFER_SIZE].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_FETCH_BUFFER_SIZE, aAttr[ KEY_FETCH_BUFFER_SIZE].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_REPLACEMENT_CHAR, aAttr[ KEY_REPLACEMENT_CHAR].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_REPLACEMENT_CHAR, aAttr[ KEY_REPLACEMENT_CHAR].szAttr, ODBC_INI);

	WritePrivateProfileString( lpszDSN,	INI_COMPRESSION, aAttr[ KEY_COMPRESSION].szAttr, ODBC_INI);
	SQLWritePrivateProfileString( lpszDSN,	INI_COMPRESSION, aAttr[ KEY_COMPRESSION].szAttr, ODBC_INI);

	WriteTraceRegistry( INI_TRACE_FILE,aAttr[ KEY_TRACE_FILE].szAttr);
	
	WriteTraceRegistry( INI_TRACE_FLAGS,aAttr[ KEY_TRACE_FLAGS].szAttr);

	return TRUE;
}