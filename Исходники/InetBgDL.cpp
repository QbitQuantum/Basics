DWORD CALLBACK TaskThreadProc(LPVOID ThreadParam)
{
  NSIS::stack_t *pURL,*pFile;
  HINTERNET hInetSes = NULL, hInetFile = NULL;
  DWORD cbio = sizeof(DWORD);
  HANDLE hLocalFile;
  bool completedFile = false;
startnexttask:
  hLocalFile = INVALID_HANDLE_VALUE;
  pFile = NULL;
  TaskLock_AcquireExclusive();
  // Now that we've acquired the lock, we can set the event to indicate this.
  // SetEvent will likely never fail, but if it does we should set it to NULL
  // to avoid anyone waiting on it.
  if (!SetEvent(g_hGETStartedEvent)) {
    CloseHandle(g_hGETStartedEvent);
    g_hGETStartedEvent = NULL;
  }
  pURL = g_pLocations;
  if (pURL)
  {
    pFile = pURL->next;
    g_pLocations = pFile->next;
  }
#ifndef ONELOCKTORULETHEMALL
  StatsLock_AcquireExclusive();
#endif
  if (completedFile)
  {
    ++g_FilesCompleted;
  }
  completedFile = false;
  g_cbCurrXF = 0;
  g_cbCurrTot = FILESIZE_UNKNOWN;
  if (!pURL)
  {
    if (g_FilesTotal)
    {
      if (g_FilesTotal == g_FilesCompleted)
      {
        g_Status = STATUS_COMPLETEDALL;
      }
    }
    g_hThread = NULL;
  }
#ifndef ONELOCKTORULETHEMALL
  StatsLock_ReleaseExclusive();
#endif
  TaskLock_ReleaseExclusive();

  if (!pURL)
  {
    if (0)
    {
diegle:
      DWORD gle = GetLastError();
      //TODO? if (ERROR_INTERNET_EXTENDED_ERROR==gle) InternetGetLastResponseInfo(...)
      g_Status = STATUS_ERR_GETLASTERROR;
    }
    if (hInetSes)
    {
      InternetCloseHandle(hInetSes);
    }
    if (INVALID_HANDLE_VALUE != hLocalFile)
    {
      CloseHandle(hLocalFile);
    }
    StackFreeItem(pURL);
    StackFreeItem(pFile);
    return 0;
  }

  if (!hInetSes)
  {
    hInetSes = InternetOpen(USERAGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInetSes)
    {
      TRACE(_T("InetBgDl: InternetOpen failed with gle=%u\n"),
            GetLastError());
      goto diegle;
    }
    InternetSetStatusCallback(hInetSes, (INTERNET_STATUS_CALLBACK)InetStatusCallback);

    //msdn.microsoft.com/library/default.asp?url=/workshop/components/offline/offline.asp#Supporting Offline Browsing in Applications and Components
    ULONG longOpt;
    DWORD cbio = sizeof(ULONG);
    if (InternetQueryOption(hInetSes, INTERNET_OPTION_CONNECTED_STATE, &longOpt, &cbio))
    {
      if (INTERNET_STATE_DISCONNECTED_BY_USER&longOpt)
      {
        INTERNET_CONNECTED_INFO ci = {INTERNET_STATE_CONNECTED, 0};
        InternetSetOption(hInetSes, INTERNET_OPTION_CONNECTED_STATE, &ci, sizeof(ci));
      }
    }

    // Change the default connect timeout if specified.
    if(g_ConnectTimeout > 0)
    {
      InternetSetOption(hInetSes, INTERNET_OPTION_CONNECT_TIMEOUT,
                        &g_ConnectTimeout, sizeof(g_ConnectTimeout));
    }

    // Change the default receive timeout if specified.
    if (g_ReceiveTimeout)
    {
      InternetSetOption(hInetSes, INTERNET_OPTION_RECEIVE_TIMEOUT,
                        &g_ReceiveTimeout, sizeof(DWORD));
    }
  }

  DWORD ec = ERROR_SUCCESS;
  hLocalFile = CreateFile(pFile->text, GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_DELETE,NULL,CREATE_ALWAYS, 0, NULL);
  if (INVALID_HANDLE_VALUE == hLocalFile)
  {
    TRACE(_T("InetBgDl: CreateFile file handle invalid\n"));
    goto diegle;
  }

  const DWORD IOURedirFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
                              INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS;
  const DWORD IOUCacheFlags = INTERNET_FLAG_RESYNCHRONIZE |
                              INTERNET_FLAG_NO_CACHE_WRITE |
                              INTERNET_FLAG_PRAGMA_NOCACHE |
                              INTERNET_FLAG_RELOAD;
  const DWORD IOUCookieFlags = INTERNET_FLAG_NO_COOKIES;
  DWORD IOUFlags = IOURedirFlags | IOUCacheFlags | IOUCookieFlags |
                   INTERNET_FLAG_NO_UI | INTERNET_FLAG_EXISTING_CONNECT;

  TCHAR *hostname = (TCHAR*) GlobalAlloc(GPTR, MAX_STRLEN * sizeof(TCHAR)),
        *urlpath = (TCHAR*) GlobalAlloc(GPTR, MAX_STRLEN * sizeof(TCHAR)),
        *extrainfo = (TCHAR*) GlobalAlloc(GPTR, MAX_STRLEN * sizeof(TCHAR));

  URL_COMPONENTS uc = { sizeof(URL_COMPONENTS), NULL, 0, (INTERNET_SCHEME)0,
                        hostname, MAX_STRLEN, (INTERNET_PORT)0, NULL, 0,
                        NULL, 0, urlpath, MAX_STRLEN, extrainfo, MAX_STRLEN};
  uc.dwHostNameLength = uc.dwUrlPathLength = uc.dwExtraInfoLength = MAX_STRLEN;

  if (!InternetCrackUrl(pURL->text, 0, ICU_ESCAPE, &uc))
  {
    // Bad url or param passed in
    TRACE(_T("InetBgDl: InternetCrackUrl false with url=%s, gle=%u\n"),
          pURL->text, GetLastError());
    goto diegle;
  }

  TRACE(_T("InetBgDl: scheme_id=%d, hostname=%s, port=%d, urlpath=%s, extrainfo=%s\n"),
        uc.nScheme, hostname, uc.nPort, urlpath, extrainfo);

  // Only http and https are supported
  if (uc.nScheme != INTERNET_SCHEME_HTTP &&
      uc.nScheme != INTERNET_SCHEME_HTTPS)
  {
    TRACE(_T("InetBgDl: only http and https is supported, aborting...\n"));
    goto diegle;
  }

  TRACE(_T("InetBgDl: calling InternetOpenUrl with url=%s\n"), pURL->text);
  hInetFile = InternetOpenUrl(hInetSes, pURL->text,
                              NULL, 0, IOUFlags |
                              (uc.nScheme == INTERNET_SCHEME_HTTPS ?
                               INTERNET_FLAG_SECURE : 0), 1);
  if (!hInetFile)
  {
    TRACE(_T("InetBgDl: InternetOpenUrl failed with gle=%u\n"),
          GetLastError());
    goto diegle;
  }

  // Get the file length via the Content-Length header
  FILESIZE_T cbThisFile;
  cbio = sizeof(cbThisFile);
  if (!HttpQueryInfo(hInetFile,
                     HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
                     &cbThisFile, &cbio, NULL))
  {
    cbThisFile = FILESIZE_UNKNOWN;
  }
  TRACE(_T("InetBgDl: file size=%d bytes\n"), cbThisFile);

  // Setup a buffer of size 256KiB to store the downloaded data.
  const UINT cbBufXF = 262144;
  // Use a 4MiB read buffer for the connection.
  // Bigger buffers will be faster.
  // cbReadBufXF should be a multiple of cbBufXF.
  const UINT cbReadBufXF = 4194304;
  BYTE bufXF[cbBufXF];

  // Up the default internal buffer size from 4096 to internalReadBufferSize.
  DWORD internalReadBufferSize = cbReadBufXF;
  if (!InternetSetOption(hInetFile, INTERNET_OPTION_READ_BUFFER_SIZE,
                         &internalReadBufferSize, sizeof(DWORD)))
  {
    TRACE(_T("InetBgDl: InternetSetOption failed to set read buffer size to %u bytes, gle=%u\n"),
          internalReadBufferSize, GetLastError());

    // Maybe it's too big, try half of the optimal value.  If that fails just
    // use the default.
    internalReadBufferSize /= 2;
    if (!InternetSetOption(hInetFile, INTERNET_OPTION_READ_BUFFER_SIZE,
                           &internalReadBufferSize, sizeof(DWORD)))
    {
      TRACE(_T("InetBgDl: InternetSetOption failed to set read buffer size ") \
            _T("to %u bytes (using default read buffer size), gle=%u\n"),
            internalReadBufferSize, GetLastError());
    }
  }

  for(;;)
  {
    DWORD cbio = 0, cbXF = 0;
    BOOL retXF = InternetReadFile(hInetFile, bufXF, cbBufXF, &cbio);
    if (!retXF)
    {
      ec = GetLastError();
      TRACE(_T("InetBgDl: InternetReadFile failed, gle=%u\n"), ec);
      break;
    }

    if (0 == cbio)
    {
      ASSERT(ERROR_SUCCESS == ec);
      // EOF or broken connection?
      // TODO: Can InternetQueryDataAvailable detect this?

      TRACE(_T("InetBgDl: InternetReadFile true with 0 cbio, cbThisFile=%d, gle=%u\n"),
            cbThisFile, GetLastError());
      // If we haven't transferred all of the file, and we know how big the file
      // is, and we have no more data to read from the HTTP request, then set a
      // broken pipe error. Reading without StatsLock is ok in this thread.
      if (FILESIZE_UNKNOWN != cbThisFile && g_cbCurrXF != cbThisFile)
      {
        TRACE(_T("InetBgDl: downloaded file size of %d bytes doesn't equal ") \
              _T("expected file size of %d bytes\n"), g_cbCurrXF, cbThisFile);
        ec = ERROR_BROKEN_PIPE;
      }
      break;
    }

    // Check if we canceled the download
    if (0 == g_FilesTotal)
    {
      TRACE(_T("InetBgDl: 0 == g_FilesTotal, aborting transfer loop...\n"));
      ec = ERROR_CANCELLED;
      break;
    }

    cbXF = cbio;
    if (cbXF)
    {
      retXF = WriteFile(hLocalFile, bufXF, cbXF, &cbio, NULL);
      if (!retXF || cbXF != cbio)
      {
        ec = GetLastError();
        break;
      }

      StatsLock_AcquireExclusive();
      if (FILESIZE_UNKNOWN != cbThisFile) {
        g_cbCurrTot = cbThisFile;
      }
      g_cbCurrXF += cbXF;
      StatsLock_ReleaseExclusive();
    }
  }

  TRACE(_T("InetBgDl: TaskThreadProc completed %s, ec=%u\n"), pURL->text, ec);
  InternetCloseHandle(hInetFile);
  if (ERROR_SUCCESS == ec)
  {
    if (INVALID_HANDLE_VALUE != hLocalFile)
    {
      CloseHandle(hLocalFile);
      hLocalFile = INVALID_HANDLE_VALUE;
    }
    StackFreeItem(pURL);
    StackFreeItem(pFile);
    ++completedFile;
  }
  else
  {
    TRACE(_T("InetBgDl: failed with ec=%u\n"), ec);
    SetLastError(ec);
    goto diegle;
  }
  goto startnexttask;
}