DWORD Sm::IsYukonByInstanceString(__in_opt LPSTR szInstance, 
								  __out BOOL * pfIsYukon, 
								  __out_opt BOOL * pfNew, 
								  __out BOOL * pfVersionRetrieved)
{
	BidxScopeAutoSNI4( SNIAPI_TAG _T("szInstance: \"%hs\", pfIsYukon: %p{BOOL*}, pfNew: %p{BOOL*}, pfVersionRetrieved: %p{BOOL*}\n"), 
					szInstance, pfIsYukon, pfNew, pfVersionRetrieved );

	DWORD dwError = ERROR_SUCCESS;	

	Assert ( szInstance && szInstance[0] );
	Assert ( pfIsYukon != NULL );
	Assert ( pfNew != NULL );

	if ( szInstance == NULL 
		|| szInstance[0] == '\0'
		|| pfIsYukon == NULL 
		|| pfNew == NULL 
		|| pfVersionRetrieved == NULL )
	{
		dwError = ERROR_INVALID_PARAMETER;
		goto Exit;
	}

	*pfVersionRetrieved = FALSE; 
	*pfNew = FALSE;

	if ( !gpInstapiStruct )
	{
		*pfIsYukon = FALSE;
		goto Exit;
	}
	
	WCHAR wszVersion[MAX_VERSION_LENGTH+1];	
	DWORD cwszVersion = MAX_VERSION_LENGTH;
	WCHAR wszInstance[MAX_INSTANCENAME_LENGTH+1];
	
	int cRet = MultiByteToWideChar(CP_ACP, 
					    0, 
					    szInstance,
					    static_cast<int>(strlen(szInstance))+1, 
					    wszInstance,   
					    MAX_INSTANCENAME_LENGTH
					    );
	if( cRet == 0 )
	{
		dwError = GetLastError();
		goto Exit;
	}
	
	wszInstance[MAX_INSTANCENAME_LENGTH] = L'\0';

	// For obtain instance ID specifying SQL Server service to make sure we 
	// don't get version for AS or RS.  
	//
	INST_ID instID; 

	if( !gpInstapiStruct->pfnGetSvcInstanceIDFromName( wszInstance,	//instance name
													SVC_SQL, 
													&instID ) )
	{
		// If we cannot get the version, it is not yukon
		*pfIsYukon = FALSE;
		goto Exit;
	}

	if( !gpInstapiStruct->pfnGetSQLInstanceRegStringByID( &instID, 
										L"MSSQLSERVER\\CurrentVersion", 	//RegPath
										L"CurrentVersion", 					//ValueName
										wszVersion, 						//String													
										&cwszVersion)
	  )
	{
		// If we cannot get the version, it is not yukon
		*pfIsYukon = FALSE;
		goto Exit;
	}
	
	wszVersion[MAX_VERSION_LENGTH]=L'\0';	
	char szVersion[MAX_VERSION_LENGTH+1];
	cRet = WideCharToMultiByte( CP_ACP,
					     0,
					     wszVersion,
					     -1,
					     szVersion,
					     MAX_VERSION_LENGTH,
					     NULL,
					     NULL );
	
	if( cRet == 0 )
	{
		dwError = GetLastError();		
		goto Exit;
	}

	szVersion[MAX_VERSION_LENGTH]='\0';

	//4. We got Yukon Version number now!
	*pfIsYukon = FALSE;
	LPSTR szTmp = strchr(szVersion, '.');
	if( szTmp )
	{
		//szTmp = strtok(szVersion, ".");
		*szTmp = 0;
		int iMajorVer = _atoi_l(szVersion, GetDefaultLocale()); 
		if( 9 == iMajorVer )
		{
			*pfIsYukon = TRUE;
			szTmp = szTmp + 1;
			szTmp = strchr(szTmp, '.');
			if( szTmp )
			{
				szTmp = szTmp + 1;
				if( 579 <= _atoi_l(szTmp, GetDefaultLocale()) )
					*pfNew = TRUE;
			}
		}
		else if( 9 < iMajorVer )
		{
			*pfIsYukon = TRUE;
			*pfNew = TRUE; 
		}

		*pfVersionRetrieved = TRUE; 
	}

Exit:
	
	BidTraceU1( SNI_BID_TRACE_ON, RETURN_TAG _T("%d{WINERR}\n"), dwError);	
	if ( ERROR_SUCCESS != dwError )
		SNI_SET_LAST_ERROR( SM_PROV, SNIE_36 , dwError );
	return dwError;
	
}