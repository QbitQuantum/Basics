static
DWORD WINAPI
ThreadFunc(LPVOID Context)
{
    CComPtr<IBindStatusCallback> dl;
    WCHAR path[MAX_PATH];
    LPWSTR p;
    HWND Dlg = (HWND) Context;
    ULONG dwContentLen, dwBytesWritten, dwBytesRead, dwStatus;
    ULONG dwCurrentBytesRead = 0;
    ULONG dwStatusLen = sizeof(dwStatus);
    BOOL bCancelled = FALSE;
    BOOL bTempfile = FALSE;
    BOOL bCab = FALSE;
    HINTERNET hOpen = NULL;
    HINTERNET hFile = NULL;
    HANDLE hOut = INVALID_HANDLE_VALUE;
    unsigned char lpBuffer[4096];
    PCWSTR lpszAgent = L"RApps/1.0";
    URL_COMPONENTS urlComponents;
    size_t urlLength;

    /* built the path for the download */
    p = wcsrchr(AppInfo->szUrlDownload, L'/');

    if (!p)
        goto end;

        if (wcscmp(AppInfo->szUrlDownload, APPLICATION_DATABASE_URL) == 0)
        {
            bCab = TRUE;
            if (!GetStorageDirectory(path, sizeof(path) / sizeof(path[0])))
                goto end;
        }
        else
        {
            if (FAILED(StringCbCopyW(path, sizeof(path),  SettingsInfo.szDownloadDir)))
                goto end;
        }


    if (GetFileAttributesW(path) == INVALID_FILE_ATTRIBUTES)
    {
        if (!CreateDirectoryW(path, NULL))
            goto end;
    }

    if (FAILED(StringCbCatW(path, sizeof(path), L"\\")))
        goto end;
    if (FAILED(StringCbCatW(path, sizeof(path), p + 1)))
        goto end;

    /* download it */
    bTempfile = TRUE;
    CDownloadDialog_Constructor(Dlg, &bCancelled, IID_PPV_ARG(IBindStatusCallback, &dl));

    if (dl == NULL)
        goto end;

    switch(SettingsInfo.Proxy)
    {
        case 0: /* preconfig */
            hOpen = InternetOpenW(lpszAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
            break;
        case 1: /* direct (no proxy) */
            hOpen = InternetOpenW(lpszAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
            break;
        case 2: /* use proxy */
            hOpen = InternetOpenW(lpszAgent, INTERNET_OPEN_TYPE_PROXY, SettingsInfo.szProxyServer, SettingsInfo.szNoProxyFor, 0);
            break;
        default: /* preconfig */
            hOpen = InternetOpenW(lpszAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
            break;
    }

    if (!hOpen)
        goto end;

    hFile = InternetOpenUrlW(hOpen, AppInfo->szUrlDownload, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_KEEP_CONNECTION, 0);
    if (!hFile)
        goto end;

    if (!HttpQueryInfoW(hFile, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwStatusLen, NULL))
        goto end;

    if(dwStatus != HTTP_STATUS_OK)
    {
        WCHAR szMsgText[MAX_STR_LEN];

        if (!LoadStringW(hInst, IDS_UNABLE_TO_DOWNLOAD, szMsgText, sizeof(szMsgText) / sizeof(WCHAR)))
            goto end;

        MessageBoxW(hMainWnd, szMsgText, NULL, MB_OK | MB_ICONERROR);
        goto end;
    }

    dwStatusLen = sizeof(dwStatus);

    memset(&urlComponents, 0, sizeof(urlComponents));
    urlComponents.dwStructSize = sizeof(urlComponents);

    if(FAILED(StringCbLengthW(AppInfo->szUrlDownload, sizeof(AppInfo->szUrlDownload), &urlLength)))
        goto end;
    
    urlComponents.dwSchemeLength = urlLength*sizeof(WCHAR);
    urlComponents.lpszScheme = (PWSTR)malloc(urlComponents.dwSchemeLength);
    
    if(!InternetCrackUrlW(AppInfo->szUrlDownload, urlLength+1, ICU_DECODE | ICU_ESCAPE, &urlComponents))
        goto end;
    
    if(urlComponents.nScheme == INTERNET_SCHEME_HTTP || urlComponents.nScheme == INTERNET_SCHEME_HTTPS)
        HttpQueryInfo(hFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &dwContentLen, &dwStatus, 0);

    if(urlComponents.nScheme == INTERNET_SCHEME_FTP)
        dwContentLen = FtpGetFileSize(hFile, &dwStatus);

    free(urlComponents.lpszScheme);

    hOut = CreateFileW(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);

    if (hOut == INVALID_HANDLE_VALUE)
        goto end;

    do
    {
        if (!InternetReadFile(hFile, lpBuffer, _countof(lpBuffer), &dwBytesRead)) goto end;
        if (!WriteFile(hOut, &lpBuffer[0], dwBytesRead, &dwBytesWritten, NULL)) goto end;
        dwCurrentBytesRead += dwBytesRead;
        dl->OnProgress(dwCurrentBytesRead, dwContentLen, 0, AppInfo->szUrlDownload);
    }
    while (dwBytesRead);

    CloseHandle(hOut);
    hOut = INVALID_HANDLE_VALUE;

    if (bCancelled)
        goto end;

    ShowWindow(Dlg, SW_HIDE);

    /* run it */
    if (!bCab)
        ShellExecuteW( NULL, L"open", path, NULL, NULL, SW_SHOWNORMAL );

end:
    if (hOut != INVALID_HANDLE_VALUE)
        CloseHandle(hOut);

    InternetCloseHandle(hFile);
    InternetCloseHandle(hOpen);

    if (bTempfile)
    {
        if (bCancelled || (SettingsInfo.bDelInstaller && !bCab))
            DeleteFileW(path);
    }

    EndDialog(Dlg, 0);

    return 0;
}