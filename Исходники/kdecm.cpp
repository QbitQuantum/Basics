//---------------------------------------------------------------------------
// RegisterServer
//---------------------------------------------------------------------------
BOOL RegisterServer(CLSID clsid, LPTSTR lpszTitle)
{
#if 0
    TCHAR           dllPath[MAX_PATH];

    QSettings       settings("HKEY_CLASSES_ROOT", QSettings::NativeFormat);

    //get this app's path and file name
    GetModuleFileNameW(_hModule, dllPath, MAX_PATH);

    qDebug() << "register dll for KDE ContextMenu:" << lptstr2QString( dllPath );

    settings.setValue(QString("CLSID/") + clsid2QString(clsid) + 
                      QString("/Default"), lptstr2QString( lpszTitle ));
    settings.setValue(QString("CLSID/") + clsid2QString(clsid) + 
                      QString("/InprocServer32/Default"), lptstr2QString( dllPath ) );
    settings.setValue(QString("CLSID/") + clsid2QString(clsid) + 
                      QString("/InprocServer32/ThreadingModel"), "Apartment" );
    settings.setValue(QString("/*/shellex/ContextMenuHandlers/") + lptstr2QString(lpszTitle) + 
                      QString("/Default"), clsid2QString(clsid) );
    return TRUE;
#else
  int      i;
  HKEY     hKey;
  LRESULT  lResult;
  DWORD    dwDisp;
  TCHAR    szSubKey[MAX_PATH];
  TCHAR    szCLSID[MAX_PATH];
  TCHAR    szModule[MAX_PATH];
  LPOLESTR   pwsz;

  StringFromIID(clsid, &pwsz);
  if(pwsz) {
    lstrcpy(szCLSID, pwsz);
    //free the string
    LPMALLOC pMalloc;
    CoGetMalloc(1, &pMalloc);
    pMalloc->Free(pwsz);
    pMalloc->Release();
  }

  //get this app's path and file name
  GetModuleFileName(_hModule, szModule, MAX_PATH);

  DOREGSTRUCT ClsidEntries[] = {
    HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                              NULL,                   lpszTitle,
    HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),              NULL,                   szModule,
    HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),              TEXT("ThreadingModel"), TEXT("Apartment"),
    HKEY_CLASSES_ROOT,   TEXT("*\\shellex\\ContextMenuHandlers\\Kate"), NULL,                   szCLSID,
    NULL,                NULL,                                           NULL,                   NULL
  };

  // Register the CLSID entries
  for(i = 0; ClsidEntries[i].hRootKey; i++) {
    // Create the sub key string - for this case, insert the file extension
    wsprintf(szSubKey, ClsidEntries[i].szSubKey, szCLSID);
    lResult = RegCreateKeyEx(ClsidEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);
    if(NOERROR == lResult) {
      TCHAR szData[MAX_PATH];
      // If necessary, create the value string
      wsprintf(szData, ClsidEntries[i].szData, szModule);
      lResult = RegSetValueEx(hKey, ClsidEntries[i].lpszValueName, 0, REG_SZ, (LPBYTE)szData, (lstrlen(szData) + 1) * sizeof(TCHAR));
      RegCloseKey(hKey);
    }
    else
      return FALSE;
  }
  return TRUE;
#endif
}