extern "C" DWORD WINAPI dllGetFullPathNameA(LPCTSTR lpFileName, DWORD nBufferLength, LPTSTR lpBuffer, LPTSTR* lpFilePart)
{
#ifdef TARGET_WINDOWS
  if (!lpFileName) return 0;
  if(strstr(lpFileName, "://"))
  {
    unsigned int length = strlen(lpFileName);
    if (nBufferLength < (length + 1))
      return length + 1;
    else
    {
      strcpy(lpBuffer, lpFileName);
      if(lpFilePart)
      {
        char* s1 = strrchr(lpBuffer, '\\');
        char* s2 = strrchr(lpBuffer, '/');
        if(s2 && s1 > s2)
          *lpFilePart = s1 + 1;
        else if(s1 && s2 > s1)
          *lpFilePart = s2 + 1;
        else
          *lpFilePart = lpBuffer;
      }
      return length;
    }
  }
  return GetFullPathNameA(lpFileName, nBufferLength, lpBuffer, lpFilePart);
#else
  not_implement("kernel32.dll fake function GetFullPathNameW called\n"); //warning
  return 0;
#endif
}