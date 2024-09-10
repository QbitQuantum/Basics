    void InetProcessCookies(HTTP_REQUEST_HANDLE *lpReq)
    {
        if ((lpReq) && (lpReq->dwType == HTTP_REQUEST))
        {
            EnterSafeCriticalSection(&lpReq->lpUrl->lpSession->csSession);
            {
                WCHAR *lpUrl=NULL,
                      *lpPath=NULL,
                      *lpHost=NULL;
                do
                {
                    DWORD dwLen=INTERNET_MAX_URL_LENGTH*sizeof(WCHAR);
                    lpUrl=(WCHAR*)MemQuickAlloc(dwLen);
                    if (!lpUrl)
                        break;

                    if (!InternetQueryOptionW(lpReq->hReq,INTERNET_OPTION_URL,lpUrl,&dwLen))
                        break;

                    lpPath=WCHAR_QuickAlloc(INTERNET_MAX_PATH_LENGTH);
                    if (!lpPath)
                        break;

                    lpHost=WCHAR_QuickAlloc(INTERNET_MAX_HOST_NAME_LENGTH);
                    if (!lpHost)
                        break;

                    URL_COMPONENTSW url={0};
                    url.dwStructSize=sizeof(url);
                    url.lpszHostName=lpHost;
                    url.dwHostNameLength=INTERNET_MAX_HOST_NAME_LENGTH;
                    url.lpszUrlPath=lpPath;
                    url.dwUrlPathLength=INTERNET_MAX_PATH_LENGTH;
                    if (!InternetCrackUrlW(lpUrl,NULL,0,&url))
                        break;

                    DWORD i=0;
                    while (true)
                    {
                        WCHAR *lpCookie=NULL,szTmp[1];
                        DWORD dwSize=0;
                        if ((HttpQueryInfoW(lpReq->hReq,HTTP_QUERY_SET_COOKIE,szTmp,&dwSize,&i)) || (GetLastError() != ERROR_INSUFFICIENT_BUFFER))
                            break;

                        dwSize+=2;
                        lpCookie=(WCHAR*)MemQuickAlloc(dwSize);
                        if (!lpCookie)
                            break;

                        if (HttpQueryInfoW(lpReq->hReq,HTTP_QUERY_SET_COOKIE,lpCookie,&dwSize,&i))
                        {
                            WCHAR *lpData=StrChrW(lpCookie,L'=');
                            if (lpData)
                            {
                                *lpData++=0;
                                Cookie_Parse(lpReq->lpUrl->lpSession,lpHost,lpPath,lpCookie,lpData);
                            }
                        }
                        MemFree(lpCookie);
                    }
                }
                while (false);

                MemFree(lpUrl);
                MemFree(lpPath);
                MemFree(lpHost);
            }
            LeaveSafeCriticalSection(&lpReq->lpUrl->lpSession->csSession);
        }
        return;
    }