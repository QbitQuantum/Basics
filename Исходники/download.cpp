bool Download::httpSendReqEx(HINTERNET hConnect, const string &dest,
                             const vector< pair<string, string> > &headers,
                             const string &upFile, const string &outFile, ProgressWindow &pw) const {
  INTERNET_BUFFERS BufferIn;
  memset(&BufferIn, 0, sizeof(BufferIn));
  BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS );

  HINTERNET hRequest = HttpOpenRequest (hConnect, "POST", dest.c_str(), NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0);

  DWORD dwBytesRead = 0;
  DWORD dwBytesWritten = 0;
  BYTE pBuffer[4*1024]; // Read from file in 4K chunks

  string hdr;
  for (size_t k = 0; k<headers.size(); k++) {
    if (!trim(headers[k].second).empty()) {
      hdr += headers[k].first + ": " + headers[k].second + "\r\n";
    }
  }

  int retry = 5;
  while (retry>0) {

    HANDLE hFile = CreateFile(upFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == HANDLE(-1))
      return false;


    BufferIn.dwBufferTotal = GetFileSize (hFile, NULL);
    BufferIn.dwHeadersLength = hdr.length();
    BufferIn.lpcszHeader = hdr.c_str();

    double totSize = BufferIn.dwBufferTotal;

    if (!HttpSendRequestEx( hRequest, &BufferIn, NULL, 0, 0)) {
      CloseHandle(hFile);
      InternetCloseHandle(hRequest);
      return false;
    }

    DWORD sum = 0;
    do {
      if (!ReadFile (hFile, pBuffer, sizeof(pBuffer), &dwBytesRead, NULL)) {
        CloseHandle(hFile);
        InternetCloseHandle(hRequest);
        return false;
      }

      if (dwBytesRead > 0) {
        if (!InternetWriteFile(hRequest, pBuffer, dwBytesRead, &dwBytesWritten)) {
          CloseHandle(hFile);
          InternetCloseHandle(hRequest);
          return false;
        }
      }
      sum += dwBytesWritten;

      try {
        pw.setProgress(int(1000 * double(sum) / totSize));
      }
      catch (std::exception &) {
        CloseHandle(hFile);
        InternetCloseHandle(hRequest);
        throw;
      }
    }
    while (dwBytesRead == sizeof(pBuffer)) ;

    CloseHandle(hFile);

    if (!HttpEndRequest(hRequest, NULL, 0, 0)) {
      DWORD error = GetLastError();
      if (error == ERROR_INTERNET_FORCE_RETRY)
        retry--;
      else if (error == ERROR_INTERNET_TIMEOUT) {
        throw std::exception("Fick inget svar i tid (ERROR_INTERNET_TIMEOUT)");
      }
      else {
        InternetCloseHandle(hRequest);
        return false;
      }
    }
    else
      retry = 0; // Done
  }

  DWORD dwStatus = 0;
  DWORD dwBufLen = sizeof(dwStatus);
  int success = HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER,
                                        (LPVOID)&dwStatus, &dwBufLen, 0);

  if (success) {
    if (dwStatus >= 400) {
      char bf[256];
      switch (dwStatus) {
        case HTTP_STATUS_BAD_REQUEST:
          sprintf_s(bf, "HTTP Error 400: The request could not be processed by the server due to invalid syntax.");
          break;
        case HTTP_STATUS_DENIED:
          sprintf_s(bf, "HTTP Error 401: The requested resource requires user authentication.");
          break;
        case HTTP_STATUS_FORBIDDEN:
          sprintf_s(bf, "HTTP Error 403: Åtkomst nekad (access is denied).");
          break;
        case HTTP_STATUS_NOT_FOUND:
          sprintf_s(bf, "HTTP Error 404: Resursen kunde ej hittas (not found).");
          break;
        case HTTP_STATUS_NOT_SUPPORTED:
          sprintf_s(bf, "HTTP Error 501: Förfrågan stöds ej (not supported).");
          break;
        case HTTP_STATUS_SERVER_ERROR:
          sprintf_s(bf, "HTTP Error 500: Internt serverfel (server error).");
          break;
        default:
          sprintf_s(bf, "HTTP Status Error %d", dwStatus);
      }
      throw dwException(bf, dwStatus);
    }
  }

  int fileno = _open(outFile.c_str(), O_BINARY|O_CREAT|O_WRONLY|O_TRUNC, S_IREAD|S_IWRITE);

  do {
    dwBytesRead=0;
    if (InternetReadFile(hRequest, pBuffer, sizeof(pBuffer)-1, &dwBytesRead)) {
      _write(fileno, pBuffer, dwBytesRead);
    }
  } while(dwBytesRead>0);

  _close(fileno);

  InternetCloseHandle(hRequest);
  return true;
}