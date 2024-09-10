int CUtils::CheckOS() {
  int iType = OS_UNSUPPORTED;

#ifdef ENABLE_DISPLAY_MODULE
  OSVERSIONINFOEX osvi;
  ZeroMemory (&osvi, sizeof (OSVERSIONINFOEX));
  osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
  osvi.dwPlatformId = VER_PLATFORM_WIN32_NT;
  osvi.dwMajorVersion = 6; // Vista
  DWORDLONG condmask = VerSetConditionMask (VerSetConditionMask (0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                       VER_PLATFORMID, VER_EQUAL);

  if (VerifyVersionInfo (&osvi, VER_MAJORVERSION | VER_PLATFORMID, condmask)) {
    iType = OS_VISTA_UPPER;
  } else {
    osvi.dwMajorVersion = 5; // XP/2000
    if (VerifyVersionInfo (&osvi, VER_MAJORVERSION | VER_PLATFORMID, condmask))
      iType = OS_XP;
  }
#endif

  return iType;
}