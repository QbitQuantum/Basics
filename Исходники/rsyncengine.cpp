char* remote_data(LPWSTR verb, char* url, char* body, size_t body_size, 
				  bool bGetHeaders, bool bGetRawData = false, bool bCheckSession = false, DWORD* pdwDataSize = NULL) {
  char       *cstr = NULL;
  char		 *session = NULL;
  std::string data = "";
  //CAtlStringA data;
  char        sBuf[1024];
  DWORD       dwBytesRead  = 0;
  LPWSTR      urlw;
  HINTERNET   hInet, hConnection, hRequest;
  LPTSTR      pszFunction = NULL;

  if ( url==NULL || strlen(url)==0 ) return NULL;

  urlw = wce_mbtowc(url);  
  hInet = hConnection = hRequest = NULL;

  do {
	  // Don't make a connection attempt if there is no session
    session = get_db_session(load_source_url());
	  if ( bCheckSession && !session && !strstr(url, "clientcreate") ) {
	    break;
	  }
	  if (session) free(session);

    if( !SetupInternetConnection(urlw) ) {
      break;
    }

    hInet = InternetOpen(_T("rhodes-wm"), 
      INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL );
    if ( !hInet ) {
      pszFunction = L"InternetOpen";
      break;
    }

    DWORD lpdwBufferLength = sizeof(sBuf)/sizeof(wchar_t);
    if ( !InternetCanonicalizeUrl(urlw, (LPWSTR)sBuf, &lpdwBufferLength, 0) ) {
      pszFunction = L"InternetCanonicalizeUrl";
      break;
    }

    ATLTRACE(L"Connecting to url: %s\n",(LPWSTR)sBuf);

    URL_COMPONENTS uri;
    alloc_url_components(&uri,url);
    if( !InternetCrackUrl((LPWSTR)sBuf,lpdwBufferLength,0,&uri) ) {
      pszFunction = L"InternetCrackUrl";
      free_url_components(&uri);
      break;
    }

    hConnection = InternetConnect( hInet, 
      uri.lpszHostName, uri.nPort, _T("anonymous"), NULL, 
      INTERNET_SERVICE_HTTP, 0, 0 );
    if ( !hConnection ) {
      pszFunction = L"InternetConnect";
      free_url_components(&uri);
      break;
    }

    wsprintf((LPWSTR)sBuf,L"%s%s",uri.lpszUrlPath,uri.lpszExtraInfo);
    hRequest = HttpOpenRequest( hConnection, verb, 
      (LPWSTR)sBuf, NULL, NULL, NULL, 
      INTERNET_FLAG_KEEP_CONNECTION|INTERNET_FLAG_NO_CACHE_WRITE, NULL );
    if ( !hRequest ) {
      pszFunction = L"HttpOpenRequest";
      free_url_components(&uri);
      break;
    }

    free_url_components(&uri);

    //Send data
    if ( HttpSendRequest( hRequest, NULL, 0, body, body_size) ) {
      wchar_t res[10];
      DWORD dwLen = 10;
      DWORD nIndex = 0;
      bool bOk = false;
      if( HttpQueryInfo(hRequest,HTTP_QUERY_STATUS_CODE,res,&dwLen,&nIndex) ){
        if ( wcscmp(res,L"200") == 0 )
          bOk = true;
		else {
          bOk = false;
		  // If we're unauthorized, delete any cookies that might have been
		  // stored so we don't reuse them later
		  if ( wcscmp(res,L"401") == 0 ) delete_winmo_session(load_source_url());
		}
      }

      if ( bOk ){
        if ( bGetHeaders ){
          DWORD dwSize = 0;
	        HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS, NULL, &dwSize, NULL);
	        if( dwSize != 0 )
	        {
		        cstr = new char [dwSize+1];
		        // Call HttpQueryInfo again to get the headers.
		        bOk = (bool) HttpQueryInfoA(hRequest, HTTP_QUERY_RAW_HEADERS, (LPVOID) cstr, &dwSize, NULL);
          }
        }else{
          BOOL bRead = InternetReadFile(hRequest, &sBuf, sizeof(sBuf), &dwBytesRead);
          while (bRead && (dwBytesRead > 0)) {
            data.append(sBuf, dwBytesRead);
            //data.Append(sBuf, dwBytesRead);
            bRead = InternetReadFile(hRequest, &sBuf, sizeof(sBuf), &dwBytesRead);
          }
		      if ( bGetRawData && pdwDataSize ){
			      cstr = new char [*pdwDataSize];
            memcpy (cstr, data.c_str(), *pdwDataSize);
		      }
		      else {
			      //make a copy of recieved data
			      cstr = new char [data.size()+1];
			      strcpy (cstr, data.c_str());
            //cstr = new char [data.GetLength()+1];
            //strcpy (cstr, data.GetString());
		      }
        }
      }
    } else {
      pszFunction = L"HttpOpenRequest";
    }

  } while(0);

  if (pszFunction) {
    ErrorMessage(pszFunction);
  }

  if(hRequest) InternetCloseHandle(hRequest);
  if(hConnection) InternetCloseHandle(hConnection);
  if(hInet) InternetCloseHandle(hInet);

  free(urlw);
  return cstr;
}