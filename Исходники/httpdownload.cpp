int HttpDownLoad_real(
                  std::string& tmp_file,
                  const std::string& url,
                  const std::string& file,
                  std::function<void(double)> callback)
{
  HINTERNET hSession  =  InternetOpen(_T("HTTPDOWNLOAD"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  scloud::ScopeGuard session([hSession]{InternetCloseHandle(hSession);});
  if (!hSession) {
    session.cancel();
    return GetLastError();
  }

  HINTERNET hInternet  =  InternetOpenUrl(hSession, url.c_str(), NULL,  0 , INTERNET_FLAG_RAW_DATA,  0 );
  scloud::ScopeGuard internet([hInternet]{InternetCloseHandle(hInternet);});
  if (!hInternet) {
    internet.cancel();
    return GetLastError();
  }

  //get http return code.
  char szContent[32] = {0};
  DWORD dwInfoSize = 32;
  HttpQueryInfoA(hInternet, HTTP_QUERY_STATUS_CODE, szContent, &dwInfoSize, NULL);
  int ret = StrToIntA(szContent);
  if (ret >= 400)
  {
      return ret;
  }

  //get file size
  ZeroMemory(szContent, 32);
  dwInfoSize = 32;
  HttpQueryInfoA(hInternet, HTTP_QUERY_CONTENT_LENGTH, szContent, &dwInfoSize, NULL);
  __int64 size = 0;
  StrToInt64ExA(szContent, 10, &size);
  if (size <= 0)
  {
    return ERROR_CONTENT_LENGTH_LESS_THAN_ZERO;
  }

  TCHAR szTmpFile[MAX_PATH] = {0};
  if (!tmp_file.empty())
  {
    lstrcpy(szTmpFile, tmp_file.c_str());
  }
  else
  {
    TCHAR szTmpPath[MAX_PATH] = {0};
    GetTempPath(MAX_PATH, szTmpPath);
    if (0 == GetTempFileName(szTmpPath, _T("http"), 0, szTmpFile))
    {
      return GetLastError();
    }
  }
  tmp_file = szTmpFile;

  HANDLE hFile = CreateFile(szTmpFile,
                            GENERIC_WRITE,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
  scloud::ScopeGuard create_file([hFile]{CloseHandle(hFile);});

  if (INVALID_HANDLE_VALUE == hFile)
  {
    create_file.cancel();
    return GetLastError();
  }

  LARGE_INTEGER large_int = {0};
  GetFileSizeEx(hFile, &large_int);

  if (large_int.QuadPart > size)
  {
    return ERROR_TMP_FILE_TOO_BIG;
  }

  if (large_int.QuadPart > 0)
  {
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_END))
    {
      return GetLastError();
    }

    if (INVALID_SET_FILE_POINTER == InternetSetFilePointer(
      hInternet, large_int.LowPart, NULL, FILE_BEGIN, 0))
    {
      return GetLastError();
    }
  }

  __int64 rsize = large_int.QuadPart;

  for(;rsize < size;)
  {
    char buf[512] = {0};
    DWORD dwRead = 0; 

    if (!InternetReadFile(hInternet, buf, 512, &dwRead))
    {
        return GetLastError();
    }

    if (dwRead == 0)
    {
      return ERROR_WTF_NO_DATA;
    }

    for(DWORD dwOnce=0; dwRead != dwOnce;)
    {
      DWORD dwWritten = 0;
      if (0 == WriteFile(hFile, buf+dwOnce, dwRead-dwOnce, &dwWritten, NULL))
        return GetLastError();
      dwOnce += dwWritten;
    }

    rsize += dwRead;

    if (rsize == size)
      break;

    if (callback)
      callback((double)rsize/size);
  }

  if (rsize == size)
  {
    create_file.cancel();
    CloseHandle(hFile);

    SetFileAttributes(file.c_str(), FILE_ATTRIBUTE_NORMAL);
    DeleteFile(file.c_str());

    if (MoveFile(szTmpFile, file.c_str()))
    {
      //succeed.
      if (callback)
        callback(1.0);

      return 0;
    }
  }

  return GetLastError();
}