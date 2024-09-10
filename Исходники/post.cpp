void main()
{
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer = NULL;
    HINTERNET  hSession = NULL,
               hConnect = NULL,
               hRequest = NULL;

    BOOL  bResults = FALSE;

    hSession=WinHttpOpen(L"User-Agent",WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,WINHTTP_NO_PROXY_NAME,WINHTTP_NO_PROXY_BYPASS,0);

    if(hSession)
    {
        hConnect=WinHttpConnect(hSession,L"kinggigi.sinaapp.com",INTERNET_DEFAULT_HTTP_PORT,0);
    }

    if(hConnect)
    {
        hRequest=WinHttpOpenRequest(hConnect, L"POST",L"hello.php",L"HTTP/1.1", WINHTTP_NO_REFERER,WINHTTP_DEFAULT_ACCEPT_TYPES,0);
    }
    
    LPCWSTR header=L"Content-type: application/x-www-form-urlencoded";
    SIZE_T len = lstrlenW(header);
    WinHttpAddRequestHeaders(hRequest,header,DWORD(len), WINHTTP_ADDREQ_FLAG_ADD);

    if(hRequest)
    {
    std::string data="val1=10&val2=9";

    const void *ss=(const char *)data.c_str();

	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, const_cast<void *>(ss), data.length(), data.length(), 0);

        ////bResults=WinHttpSendRequest(hRequest,WINHTTP_NO_ADDITIONAL_HEADERS, 0,WINHTTP_NO_REQUEST_DATA, 0, 0, 0 );
    }

    if(bResults)
    {
        bResults=WinHttpReceiveResponse(hRequest,NULL);

    }
    
    if(bResults)
    {
        do
        {
            // Check for available data.

             dwSize = 0;

             if (!WinHttpQueryDataAvailable( hRequest, &dwSize))
             {
                 printf( "Error %u in WinHttpQueryDataAvailable.\n",GetLastError());

                 break;
             }

             if (!dwSize)
                 break;

              pszOutBuffer = new char[dwSize+1];

              if (!pszOutBuffer)
              {
                   printf("Out of memory\n");
                break;
              }

               ZeroMemory(pszOutBuffer, dwSize+1);

               if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,  dwSize, &dwDownloaded))
               {
                     printf( "Error %u in WinHttpReadData.\n", GetLastError());
               }
               else
               {
                   printf("%s", pszOutBuffer);
               }

               delete [] pszOutBuffer;

               if (!dwDownloaded)
                   break;

        } while (dwSize > 0);
    }
    
    

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    

     system("pause");


}