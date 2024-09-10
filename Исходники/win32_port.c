int _GetFileTime(const char *fileName, char *lpszString, long dwSize) {
  BOOL fOk;
  WIN32_FILE_ATTRIBUTE_DATA fileInfo;
  SYSTEMTIME stUTC, stLocal;
  DWORD dwRet;

  if (NULL == fileName)
    return FALSE;

  fOk = GetFileAttributesEx(fileName, GetFileExInfoStandard, (void *)&fileInfo);
  if (!fOk)
    return FALSE;


  // Convert the last-write time to local time.
  FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &stUTC);
  SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

  // Build a string showing the date and time.
  dwRet = sprintf_s(lpszString, dwSize,
                    TEXT("%02d/%02d/%d  %02d:%02d"),
                    stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, stLocal.wMinute);

  if (S_OK == dwRet)
    return TRUE;
  else
    return FALSE;
}                               /* _GetFileTime() */