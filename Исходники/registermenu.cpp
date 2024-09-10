bool CRegisterMenu::RegisterMenu(const tstring& strSubKey, const tstring& strValue)
{
  HKEY hKey;
  DWORD strValueSize = strValue.empty() ? 0 : (strValue.length() + 1) * sizeof(TCHAR);

  if (RegOpenKeyEx(HKEY_CLASSES_ROOT, strSubKey.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS )
  {
    if (!strValue.empty())
      RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)strValue.c_str(), strValueSize);

    RegCloseKey(hKey);
  }
  else
  {
    DWORD disp = REG_CREATED_NEW_KEY;
    if (RegCreateKeyEx(HKEY_CLASSES_ROOT, strSubKey.c_str(), 
      NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
      &hKey, &disp) == ERROR_SUCCESS )
    {
      if (!strValue.empty())
        RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)strValue.c_str(), strValueSize);

      RegCloseKey(hKey);
    }
  }

  return true;
}