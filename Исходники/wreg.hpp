 LONG SetKey(LPCWSTR lpSubKey, LPCWSTR lpData, DWORD dwSize)
   const
 {
   if (!IsValidHandle())
     return ERROR_INVALID_HANDLE;
   return RegSetValueW(hKey(), lpSubKey, REG_SZ, lpData, dwSize);
 }