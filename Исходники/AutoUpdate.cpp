wxString DownloadURL( const wxString& server, const wxString& path )
{
  HINTERNET hInternetOpen = 0;
  HINTERNET hInternetConnect = 0;
  HINTERNET hHttpOpenRequest = 0;

  char sReadBuffer[2048] = "";
  DWORD dwLengthSizeBuffer = sizeof(sReadBuffer);

  long lRetVal(0), bRet(0), bDoLoop(1);
  ULONG lNumberOfBytesRead(0);
  wxString tmp, sBuffer;

  if (!InternetGetConnectedState(0, 0))
    return wxT("");

  hInternetOpen = InternetOpen(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if( hInternetOpen )
  {

    hInternetConnect = InternetConnect(hInternetOpen, server, INTERNET_DEFAULT_HTTP_PORT, NULL, AGENT, INTERNET_SERVICE_HTTP, 0, 0);
    if ( hInternetConnect )
    {

      hHttpOpenRequest = HttpOpenRequest(hInternetConnect, wxT("GET"), path, AGENT, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
      if ( hHttpOpenRequest )
      {
        long tmpVar;
        tmpVar = 10000; lRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &tmpVar, 4);
        tmpVar = 15000; lRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_RECEIVE_TIMEOUT, &tmpVar, 4);
        tmpVar = 20000; lRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_SEND_TIMEOUT, &tmpVar, 4);

        bRet = HttpAddRequestHeaders(hHttpOpenRequest, DEFAULT_HEADERS, wxStrlen(DEFAULT_HEADERS), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
        bRet = HttpSendRequest(hHttpOpenRequest, NULL, 0, 0, 0);

        while ( bDoLoop ) {
          sReadBuffer[0] = 0;

          bDoLoop = InternetReadFile(hHttpOpenRequest, sReadBuffer, dwLengthSizeBuffer, &lNumberOfBytesRead);

          if ( lNumberOfBytesRead > 0 )
          {
            tmp = wxString(sReadBuffer, wxConvLibc);
            tmp.Truncate(lNumberOfBytesRead);

            sBuffer += tmp;
          }
          else
          {
            bDoLoop = 0;
          }
        }

        bRet = InternetCloseHandle(hHttpOpenRequest);
      } // if ( hHttpOpenRequest )

      bRet = InternetCloseHandle(hInternetConnect);
    } // if ( hInternetConnect )

    bRet = InternetCloseHandle(hInternetOpen);
  } // if( hInternetOpen )


  return sBuffer;
}