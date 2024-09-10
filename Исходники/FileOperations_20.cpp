bool SaveFile(LPCSTR pszFile, int iCodePage, bool bSaveCopy)
{
  HANDLE hFile;
  bool   bWriteSuccess;
  
  LPSTR lpData;
  DWORD cbData;
  DWORD dwBytesWritten;
  
  hFile = CreateFile(pszFile,
                     GENERIC_WRITE,
                     FILE_SHARE_READ|FILE_SHARE_WRITE,
                     NULL,
                     CREATE_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL);

  // failure could be due to missing attributes (2k/XP)
  if (hFile == INVALID_HANDLE_VALUE)
  {
    DWORD dwAttributes = GetFileAttributes(pszFile);
    if (dwAttributes != 0) // INVALID_FILE_ATTRIBUTES FILE_ATTRIBUTE_READONLY
    {
      dwAttributes = dwAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
      hFile = CreateFile(pszFile,
                        GENERIC_WRITE,
                        FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL | dwAttributes,
                        NULL);
    }
  }

  if (hFile == INVALID_HANDLE_VALUE)
    return FALSE;

  // get text
  cbData = SendMessage(hwnd,SCI_GETLENGTH,0,0);
  lpData = GlobalAlloc(GPTR,cbData + 1);
  SendMessage(hwnd,SCI_GETTEXT,GlobalSize(lpData),(LPARAM)lpData);
  
  if (cbData == 0)
    bWriteSuccess = SetEndOfFile(hFile);

  else
  {
    if (iCodePage & NCP_UNICODE)
    {
      LPWSTR lpDataWide;
      int    cbDataWide;
      CPINFO cpi;
      UINT   uCP_UTF8;

      // UTF-8 text is interpreted as ANSI when saving as Unicode on Windows 95
      uCP_UTF8 = (GetCPInfo(CP_UTF8, &cpi) || IsValidCodePage(CP_UTF8)) ? CP_UTF8 : CP_ACP;

      lpDataWide = GlobalAlloc(GPTR,cbData * 2 + 16);
      cbDataWide = MultiByteToWideChar(uCP_UTF8,0,lpData,cbData,lpDataWide,GlobalSize(lpDataWide));

      if (iCodePage & NCP_UNICODE_BOM) 
      {
        if (iCodePage & NCP_UNICODE_REVERSE)
          WriteFile(hFile,(LPCVOID)"\xFE\xFF",2,&dwBytesWritten,NULL);
        else
          WriteFile(hFile,(LPCVOID)"\xFF\xFE",2,&dwBytesWritten,NULL); 
      }
      
      if (iCodePage & NCP_UNICODE_REVERSE)
      {
        _swab((char*)lpDataWide,(char*)lpDataWide,cbDataWide * sizeof(WCHAR));
      }

      bWriteSuccess = WriteFile(hFile,lpDataWide,cbDataWide * sizeof(WCHAR),&dwBytesWritten,NULL);

      GlobalFree(lpData);
    }

    else if (iCodePage & NCP_UTF8)
    {
      if (iCodePage & NCP_UTF8_SIGN)
        WriteFile(hFile,(LPCVOID)"\xEF\xBB\xBF",3,&dwBytesWritten,NULL);

      bWriteSuccess = WriteFile(hFile,lpData,cbData,&dwBytesWritten,NULL);
    }

    else // convert text to 8bit
    {
      //LPWSTR lpDataWide = GlobalAlloc(GPTR,cbData * 2 + 16);
      //int    cbDataWide = MultiByteToWideChar(CP_UTF8,0,lpData,cbData,lpDataWide,GlobalSize(lpDataWide));

      //ZeroMemory(lpData,GlobalSize(lpData));
      //cbData = WideCharToMultiByte(CP_ACP,0,lpDataWide,cbDataWide,lpData,GlobalSize(lpData),NULL,NULL);
      //GlobalFree(lpDataWide);

      bWriteSuccess = WriteFile(hFile,lpData,cbData,&dwBytesWritten,NULL);

      GlobalFree(lpData);
    }
  }

  CloseHandle(hFile);

  if (bWriteSuccess)
  {
    if (!bSaveCopy)
      SendMessage(hwnd,SCI_SETSAVEPOINT,0,0);

    return TRUE;
  }

  else
    return FALSE;

}