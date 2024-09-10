BOOL RegisterToolBand(CLSID clsid)
{
HKEY     hKey;
LRESULT  lResult;
DWORD    dwDisp;
TCHAR    szCLSID[MAX_PATH];
LPWSTR   pwsz;

//get the CLSID in string form
StringFromIID(clsid, &pwsz);

if(pwsz)
   {
#ifdef UNICODE
   lstrcpyn(szCLSID, pwsz, ARRAYSIZE(szCLSID));
#else
   WideCharToMultiByte( CP_ACP,
                        0,
                        pwsz,
                        -1,
                        szCLSID,
                        ARRAYSIZE(szCLSID),
                        NULL,
                        NULL);
#endif

   //free the string
   CoTaskMemFree(pwsz);
   }

lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                           TEXT("Software\\Microsoft\\Internet Explorer\\Toolbar"),
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &hKey,
                           &dwDisp);
   
if(NOERROR == lResult)
   {
   TCHAR szData[] = TEXT("");

   lResult = RegSetValueEx(   hKey,
                              szCLSID,
                              0,
                              REG_SZ,
                              (LPBYTE)szData,
                              lstrlen(szData) + 1);
   
   RegCloseKey(hKey);
   }
else
   return FALSE;

return TRUE;
}