static GURL
RegOpenReadConfig ( HKEY hParentKey )
{
  GURL retval;
   // To do:  This needs to be shared with SetProfile.cpp
  LPCTSTR path = registrypath;

  HKEY hKey = 0;
  // MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,argv[1],strlen(argv[1])+1,wszSrcFile,sizeof(wszSrcFile));
  if (RegOpenKeyEx(hParentKey, path, 0,
              KEY_READ, &hKey) == ERROR_SUCCESS )
  {
    TCHAR path[1024];
    // Success
    TCHAR *szPathValue = path;
    LPCTSTR lpszEntry = (LPCTSTR &)TEXT("");
    DWORD dwCount = (sizeof(path)/sizeof(TCHAR))-1;
    DWORD dwType;

    LONG lResult = RegQueryValueEx(hKey, lpszEntry, NULL,
             &dwType, (LPBYTE) szPathValue, &dwCount);

    RegCloseKey(hKey);

    if ((lResult == ERROR_SUCCESS))
    {
      szPathValue[dwCount] = 0;
      USES_CONVERSION;
      retval=GURL::Filename::Native(T2CA(path));
    }
  } 
//  if (hKey)  RegCloseKey(hKey); 
  return retval;
}