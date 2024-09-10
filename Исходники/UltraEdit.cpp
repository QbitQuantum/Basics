 UltraEdit()
 {
     installed_ = false;
     HKEY key;
     LPCWSTR szUltraEditHive = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\uedit32.exe";
     LONG lRet = RegOpenKeyW(HKEY_LOCAL_MACHINE, szUltraEditHive, &key);
     if( lRet == ERROR_SUCCESS )
     {
         DWORD dwType = REG_SZ;
         DWORD dwSize = sizeof(szPath_);
         lRet = RegQueryValueExW(key, L"Path", NULL, &dwType, (LPBYTE)szPath_, &dwSize);
         if( lRet == ERROR_SUCCESS ) installed_ = true;
     }
 }