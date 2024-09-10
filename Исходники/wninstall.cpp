bool WNInstall_MoveFileOnReboot(const char * pszExisting, const char * pszNew)
{	
  bool fOk = 0;
#if !JDK_IS_WINE   
  HMODULE hLib=LoadLibrary("kernel32.dll");
  if (hLib)
  {
    typedef BOOL (WINAPI *mfea_t)(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,DWORD dwFlags);
    mfea_t mfea;
    mfea=(mfea_t) GetProcAddress(hLib,"MoveFileExA");
    if (mfea)
    {
      fOk=(mfea(pszExisting, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)!=0);
    }
    FreeLibrary(hLib);
  }

  if (!fOk)
  {
    static char szRenameLine[1024];
    int cchRenameLine;
    char *szRenameSec = "[Rename]\r\n";
    HANDLE hfile, hfilemap;
    DWORD dwFileSize, dwRenameLinePos=0;
    static char wininit[1024];
    static char tmpbuf[1024];
    static char nulint[4]="NUL";

    if (pszNew) GetShortPathName(pszNew,tmpbuf,1024);
    else *((int *)tmpbuf) = *((int *)nulint);
    // wininit is used as a temporary here
    GetShortPathName(pszExisting,wininit,1024);
    pszExisting=wininit;
    cchRenameLine = wsprintf(szRenameLine,"%s=%s\r\n",tmpbuf,pszExisting);

    GetWindowsDirectory(wininit, 1024-16);
    lstrcat(wininit, "\\wininit.ini");
    hfile = CreateFile(wininit,
        GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (hfile != INVALID_HANDLE_VALUE) 
    {
      dwFileSize = GetFileSize(hfile, NULL);
      hfilemap = CreateFileMapping(hfile, NULL, PAGE_READWRITE, 0, dwFileSize + cchRenameLine + 10, NULL);

      if (hfilemap != NULL) 
      {
        LPSTR pszWinInit = (LPSTR) MapViewOfFile(hfilemap, FILE_MAP_WRITE, 0, 0, 0);

        if (pszWinInit != NULL) 
        {
          int do_write=0;
          LPSTR pszRenameSecInFile = strstr(pszWinInit, szRenameSec);
          if (pszRenameSecInFile == NULL) 
          {
            lstrcpy(pszWinInit+dwFileSize, szRenameSec);
            dwFileSize += 10;
            dwRenameLinePos = dwFileSize;
            do_write++;
          } 
          else
          {
            char *pszFirstRenameLine = strstr(pszRenameSecInFile, "\n")+1;
            int l=pszWinInit + dwFileSize-pszFirstRenameLine;
            if (!wninstall_findinmem(pszFirstRenameLine,szRenameLine,l))
            {
              memmove(pszFirstRenameLine + cchRenameLine, pszFirstRenameLine, l);
              dwRenameLinePos = pszFirstRenameLine - pszWinInit;
              do_write++;
            }
          }

          if (do_write)
          {
            memcpy(&pszWinInit[dwRenameLinePos], szRenameLine,cchRenameLine);
            dwFileSize += cchRenameLine;
          }

          UnmapViewOfFile(pszWinInit);

          fOk++;
        }
        CloseHandle(hfilemap);
      }
      SetFilePointer(hfile, dwFileSize, NULL, FILE_BEGIN);
      SetEndOfFile(hfile);
      CloseHandle(hfile);
    }
  }
#endif
  return fOk;
	
}