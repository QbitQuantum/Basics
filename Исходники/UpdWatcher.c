CHECK_RESULT _UpdWatcher_Check (UPDWATCHER * p)
{
  BOOL bSuccess ;
  CHECK_RESULT nResult = CHECK_UNDEFINED ;

  if( Config_GetInteger(CFGINT_CHECK_FOR_UPDATES) )
    {
      DWORD dwState = INTERNET_CONNECTION_OFFLINE ;
      
      // check if a connection is available
      bSuccess = InternetGetConnectedState (&dwState, 0) ;

      // connection available ?
      if( bSuccess ) 
	{
	  // open session
	  HINTERNET hSession = InternetOpen (TEXT(APPLICATION_NAME), 0, NULL, NULL, 0) ;
	  
	  // session opened ?
	  if( hSession )
	    {
	      // open connection
	      HINTERNET hConnect = InternetConnect (hSession, szServerName, nServerPort,
						    szUsername, szPassword, 
						    INTERNET_SERVICE_HTTP, 0,0) ;
	      
	      // connexion opened ?
	      if( hConnect )
		{
		  // open request
		  HINTERNET hRequest = HttpOpenRequest (hConnect, TEXT("GET"), szObjectName,
							HTTP_VERSION, NULL, NULL, 
							INTERNET_FLAG_RELOAD,0) ;
		  
		  // request opened ?
		  if( hRequest )
		    {  
		      // send request
		      bSuccess = HttpSendRequest (hRequest, NULL, 0, 0, 0) ;
		      
		      // request sent ?
		      if( bSuccess )
			{
			  char	szContent[256] ;
			  DWORD dwContentMax = 256 ;
			  DWORD dwBytesRead ;
			  
			  // read file
			  bSuccess = InternetReadFile (hRequest, szContent,
						       dwContentMax, 
						       &dwBytesRead);
			  
			  // failed to read file ?
			  if( bSuccess )
			    {			      
			      char * szVersion ;
			      
			      szContent[dwBytesRead] = 0 ;	      
			      
			      // look for version string
			      szVersion = strstr (szContent, "<!-- Version: ") ;
			      
			      // failed ?
			      if( szVersion )
				{
				  int nHigh, nMed, nLow ;
				  int nNetVersion, nMyVersion ;

				  szVersion += 14 ;

				  // read net's version
				  sscanf (szVersion, "%d.%d.%d", 
					  &nHigh, &nMed, &nLow) ;
				  nNetVersion = (nHigh*256 + nMed)*256 + nLow ;
				  TRACE_INFO (TEXT("Net version = %d.%d.%d\n"), nHigh, nMed, nLow) ;

				  // save net version
				  wsprintf (p->szNewVersion, TEXT("%d.%d.%d"), nHigh, nMed, nLow) ;
				  
				  // read my version
				  sscanf (APPLICATION_VERSION_STRING, "%d.%d.%d", 
					  &nHigh, &nMed, &nLow) ;			  
				  nMyVersion = (nHigh*256 + nMed)*256 + nLow ;
				  TRACE_INFO  (TEXT("Local version = %d.%d.%d\n"), nHigh, nMed, nLow) ;
				  			
				  // compare versions
				  bSuccess = nNetVersion > nMyVersion ;	      
		      				  
				  nResult = bSuccess ? CHECK_DIFFERENT_VERSION : CHECK_SAME_VERSION ;

				  if( bSuccess )
				    {
				      char *szStartPage, *szEndPage ;
				      
				      // look for page address
				      szStartPage = strstr (szContent, "<!-- Page: ") ;
				      
				      // failed ?
				      if( szStartPage )
					{
					  szStartPage += 11 ;
					  
					  szEndPage = strstr (szStartPage, " -->") ;
					  
					  if( szEndPage )
					    {
					      int nLen = min (szEndPage-szStartPage, MAX_PATH) ;
					      
					      nLen = MultiByteToWideChar (CP_ACP, 0,
									  szStartPage, nLen,
									  p->szDownloadPage, MAX_PATH) ;
					      p->szDownloadPage[nLen] = 0 ;

					      TRACE_INFO (TEXT("Download page = %s\n"), p->szDownloadPage) ;
					    }
					}
				    }
				}
			      else nResult = CHECK_LOOK_FOR_VERSION_FAILED ;
			      
			    }
			  else nResult = CHECK_READ_FILE_FAILED ;
			}
		      else nResult = CHECK_SEND_REQUEST_FAILED ;
		      
		      // close request
		      InternetCloseHandle (hRequest) ;
		    }
		  else nResult = CHECK_OPEN_REQUEST_FAILED ;
		  
		  // close connection
		  InternetCloseHandle (hConnect) ;
		}
	      else nResult = CHECK_OPEN_CONNECT_FAILED ;
	      
	      // close session
	      InternetCloseHandle (hSession) ;
	    }
	  else nResult = CHECK_OPEN_SESSION_FAILED ;
	}
      else nResult = CHECK_NO_CONNECTION ;
    }
  else nResult = CHECK_DISABLED ;
  
  return nResult ;
}