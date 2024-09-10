static
DWORD WINAPI
ThreadFunc(LPVOID Context)
{
    IBindStatusCallback *dl = NULL;
    WCHAR path[MAX_PATH];
    PWSTR p, q;
    HWND Dlg = (HWND) Context;
    DWORD dwContentLen, dwBytesWritten, dwBytesRead, dwStatus;
    DWORD dwCurrentBytesRead = 0;
    DWORD dwStatusLen = sizeof(dwStatus);
    BOOL bCancelled = FALSE;
    BOOL bTempfile = FALSE;
    BOOL bCab = FALSE;
    HINTERNET hOpen = NULL;
    HINTERNET hFile = NULL;
    HANDLE hOut = INVALID_HANDLE_VALUE;
    unsigned char lpBuffer[4096];
    const LPWSTR lpszAgent = L"RApps/1.0";
    URL_COMPONENTS urlComponents;
    size_t urlLength, filenameLength;

    /* build the path for the download */
    p = wcsrchr(AppInfo->szUrlDownload, L'/');
    q = wcsrchr(AppInfo->szUrlDownload, L'?');

    /* do we have a final slash separator? */
    if (!p)
        goto end;

    /* prepare the tentative length of the filename, maybe we've to remove part of it later on */
    filenameLength = wcslen(p) * sizeof(WCHAR);

    /* do we have query arguments in the target URL after the filename? account for them
      (e.g. https://example.org/myfile.exe?no_adware_plz) */
    if (q && q > p && (q - p) > 0)
        filenameLength -= wcslen(q - 1) * sizeof(WCHAR);

    /* is this URL an update package for RAPPS? if so store it in a different place */
    if (wcscmp(AppInfo->szUrlDownload, APPLICATION_DATABASE_URL) == 0)
    {
        bCab = TRUE;
        if (!GetStorageDirectory(path, _countof(path)))
            goto end;
    }
    else
    {
        if (FAILED(StringCbCopyW(path, sizeof(path),  SettingsInfo.szDownloadDir)))
            goto end;
    }

    /* is the path valid? can we access it? */
    if (GetFileAttributesW(path) == INVALID_FILE_ATTRIBUTES)
    {
        if (!CreateDirectoryW(path, NULL))
            goto end;
    }

    /* append a \ to the provided file system path, and the filename portion from the URL after that */
    if (FAILED(StringCbCatW(path, sizeof(path), L"\\")))
        goto end;
    if (FAILED(StringCbCatNW(path, sizeof(path), p + 1, filenameLength)))
        goto end;

    /* is the file already there? let's avoid having to download it */
    if (!bCab && AppInfo->szSHA1[0] != 0 && GetFileAttributesW(path) != INVALID_FILE_ATTRIBUTES)
    {
        /* only open it in case of total correctness */
        if (VerifyInteg(AppInfo->szSHA1, path))
            goto run;
    }

    /* create an async download context for it */
    bTempfile = TRUE;
    dl = CreateDl(Context, &bCancelled);

    if (dl == NULL)
        goto end;

    /* FIXME: this should just be using the system-wide proxy settings */
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

    hFile = InternetOpenUrlW(hOpen, AppInfo->szUrlDownload, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);
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

    urlLength /= sizeof(WCHAR);
    urlComponents.dwSchemeLength = urlLength + 1;
    urlComponents.lpszScheme = malloc(urlComponents.dwSchemeLength * sizeof(WCHAR));
    urlComponents.dwHostNameLength = urlLength + 1;
    urlComponents.lpszHostName = malloc(urlComponents.dwHostNameLength * sizeof(WCHAR));

    if(!InternetCrackUrlW(AppInfo->szUrlDownload, urlLength+1, ICU_DECODE | ICU_ESCAPE, &urlComponents))
        goto end;

    if(urlComponents.nScheme == INTERNET_SCHEME_HTTP || urlComponents.nScheme == INTERNET_SCHEME_HTTPS)
        HttpQueryInfo(hFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &dwContentLen, &dwStatus, 0);

    if(urlComponents.nScheme == INTERNET_SCHEME_FTP)
        dwContentLen = FtpGetFileSize(hFile, &dwStatus);

#ifdef USE_CERT_PINNING
    /* are we using HTTPS to download the RAPPS update package? check if the certificate is original */
    if ((urlComponents.nScheme == INTERNET_SCHEME_HTTPS) &&
        (wcscmp(AppInfo->szUrlDownload, APPLICATION_DATABASE_URL) == 0) &&
        (!CertIsValid(hOpen, urlComponents.lpszHostName)))
    {
        WCHAR szMsgText[MAX_STR_LEN];

        if (!LoadStringW(hInst, IDS_CERT_DOES_NOT_MATCH, szMsgText, sizeof(szMsgText) / sizeof(WCHAR)))
            goto end;

        MessageBoxW(Dlg, szMsgText, NULL, MB_OK | MB_ICONERROR);
        goto end;
    }
#endif

    free(urlComponents.lpszScheme);
    free(urlComponents.lpszHostName);

    hOut = CreateFileW(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);

    if (hOut == INVALID_HANDLE_VALUE)
        goto end;

    do
    {
        if (!InternetReadFile(hFile, lpBuffer, _countof(lpBuffer), &dwBytesRead)) goto end;
        if (!WriteFile(hOut, &lpBuffer[0], dwBytesRead, &dwBytesWritten, NULL)) goto end;
        dwCurrentBytesRead += dwBytesRead;
        IBindStatusCallback_OnProgress(dl, dwCurrentBytesRead, dwContentLen, 0, AppInfo->szUrlDownload);
    }
    while (dwBytesRead && !bCancelled);

    CloseHandle(hOut);
    hOut = INVALID_HANDLE_VALUE;

    if (bCancelled)
        goto end;

    /* if this thing isn't a RAPPS update and it has a SHA-1 checksum
       verify its integrity by using the native advapi32.A_SHA1 functions */
    if (!bCab && AppInfo->szSHA1[0] != 0)
    {
        WCHAR szMsgText[MAX_STR_LEN];

        /* change a few strings in the download dialog to reflect the verification process */
        LoadStringW(hInst, IDS_INTEG_CHECK_TITLE, szMsgText, _countof(szMsgText));

        SetWindowText(Dlg, szMsgText);
        SendMessageW(GetDlgItem(Dlg, IDC_DOWNLOAD_STATUS), WM_SETTEXT, 0, (LPARAM)path);

        /* this may take a while, depending on the file size */
        if (!VerifyInteg(AppInfo->szSHA1, path))
        {
            if (!LoadStringW(hInst, IDS_INTEG_CHECK_FAIL, szMsgText, _countof(szMsgText)))
                goto end;

            MessageBoxW(Dlg, szMsgText, NULL, MB_OK | MB_ICONERROR);
            goto end;
        }
    }

    ShowWindow(Dlg, SW_HIDE);

run:
    /* run it */
    if (!bCab)
        ShellExecuteW( NULL, L"open", path, NULL, NULL, SW_SHOWNORMAL );

end:
    if (hOut != INVALID_HANDLE_VALUE)
        CloseHandle(hOut);

    InternetCloseHandle(hFile);
    InternetCloseHandle(hOpen);

    if (dl)
        IBindStatusCallback_Release(dl);

    if (bTempfile)
    {
        if (bCancelled || (SettingsInfo.bDelInstaller && !bCab))
            DeleteFileW(path);
    }

    EndDialog(Dlg, 0);

    return 0;
}