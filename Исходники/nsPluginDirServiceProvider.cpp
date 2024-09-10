// Get file version information from a file
static BOOL
GetFileVersion(LPCWSTR szFile, verBlock *vbVersion)
{
  UINT              uLen;
  UINT              dwLen;
  BOOL              bRv;
  DWORD             dwHandle;
  LPVOID            lpData;
  LPVOID            lpBuffer;
  VS_FIXEDFILEINFO  *lpBuffer2;

  ClearVersion(vbVersion);
  if (FileExists(szFile)) {
    bRv    = TRUE;
#ifdef WINCE
    // WinCe takes a non const file path string, while desktop take a const
    LPWSTR lpFilepath = const_cast<LPWSTR>(szFile);
#else
    LPCWSTR lpFilepath = szFile;
#endif
    dwLen  = GetFileVersionInfoSizeW(lpFilepath, &dwHandle);
    lpData = (LPVOID)malloc(dwLen);
    uLen   = 0;

    if (lpData && GetFileVersionInfoW(lpFilepath, dwHandle, dwLen, lpData) != 0) {
      if (VerQueryValueW(lpData, L"\\", &lpBuffer, &uLen) != 0) {
        lpBuffer2 = (VS_FIXEDFILEINFO *)lpBuffer;

        vbVersion->wMajor   = HIWORD(lpBuffer2->dwFileVersionMS);
        vbVersion->wMinor   = LOWORD(lpBuffer2->dwFileVersionMS);
        vbVersion->wRelease = HIWORD(lpBuffer2->dwFileVersionLS);
        vbVersion->wBuild   = LOWORD(lpBuffer2->dwFileVersionLS);
      }
    }

    free(lpData);
  } else {
    /* File does not exist */
    bRv = FALSE;
  }

  return bRv;
}