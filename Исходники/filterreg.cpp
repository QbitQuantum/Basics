bool DeleteRegKey(std::wstring szKey, std::wstring szSubkey)
{
  bool bOK = false;

  HKEY hKey;
  LONG ec = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, szKey.c_str(), 0, KEY_ALL_ACCESS, &hKey);
  if(ec == ERROR_SUCCESS)
  {
    if(szSubkey.length() > 0)
      ec = ::RegDeleteKey(hKey, szSubkey.c_str());

    bOK = (ec == ERROR_SUCCESS);

    ::RegCloseKey(hKey);
  }

  return bOK;
}