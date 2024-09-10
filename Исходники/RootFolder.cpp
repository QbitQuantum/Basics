UString GetMyDocsPath()
{
  UString us;
  WCHAR s[MAX_PATH + 1];
  SHGetSpecialFolderPathWp getW = (SHGetSpecialFolderPathWp)
      #ifdef UNDER_CE
      My_GetProcAddress(GetModuleHandle(TEXT("coredll.dll")), "SHGetSpecialFolderPath");
      #else
      My_GetProcAddress(GetModuleHandle(TEXT("shell32.dll")), "SHGetSpecialFolderPathW");
      #endif
  if (getW && getW(0, s, CSIDL_PERSONAL, FALSE))
    us = s;
  #ifndef _UNICODE
  else
  {
    SHGetSpecialFolderPathAp getA = (SHGetSpecialFolderPathAp)
        ::GetProcAddress(::GetModuleHandleA("shell32.dll"), "SHGetSpecialFolderPathA");
    CHAR s2[MAX_PATH + 1];
    if (getA && getA(0, s2, CSIDL_PERSONAL, FALSE))
      us = GetUnicodeString(s2);
  }
  #endif
  if (us.Length() > 0 && us[us.Length() - 1] != WCHAR_PATH_SEPARATOR)
    us += WCHAR_PATH_SEPARATOR;
  return us;
}