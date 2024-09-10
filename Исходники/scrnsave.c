/* screen saver entry point */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdLine, int nCmdShow)
{
  LPSTR p;
  OSVERSIONINFO vi;

  /* initialize */
  hMainInstance = hInst;
  szSaverName[0] = 0;

  vi.dwOSVersionInfoSize = sizeof(vi);
  GetVersionEx(&vi);
  /* check if we are going to check for passwords */
  if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
  {
    HKEY hKey;
    /* we are using windows 95 */
    w95 = TRUE;
    if (RegOpenKey(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, &hKey) == ERROR_SUCCESS)
    {
      DWORD check_pwd;
      DWORD size = sizeof(DWORD);
      DWORD type;
      LONG res;
      res = RegQueryValueEx(hKey, REGSTR_VALUE_USESCRPASSWORD, NULL, &type, (PBYTE) &check_pwd, &size);
      if (check_pwd && res == ERROR_SUCCESS)
      {
        hPwdLib = LoadLibrary(TEXT("PASSWORD.CPL"));
        if (hPwdLib)
          VerifyScreenSavePwd = GetProcAddress(hPwdLib, szVerifyPassword);
      }
      RegCloseKey(hKey);
    }
  }

  /* parse arguments */
  for (p = CmdLine; *p; p++)
  {
    switch (*p)
    {
      case 'S':
      case 's':
      {
        /* copy the savers name (if any) */
        while (ISSPACE(*++p))
          ;
        strncpy(szSaverName, p, _MAX_PATH);

        /* start screen saver */
        return LaunchScreenSaver(NULL);
      }

      case 'P':
      case 'p':
      {
        /* start screen saver in preview window */
        HWND hParent;
        fChildPreview = TRUE;
        while (ISSPACE(*++p));
        hParent = (HWND) _toul(p);
        if (hParent && IsWindow(hParent))
          return LaunchScreenSaver(hParent);
      }
      return 0;

      case 'C':
      case 'c':
        /* display configure dialog */
        LaunchConfig();
        return 0;

      case 'A':
      case 'a':
      {
        /* change screen saver password */
        HWND hParent;
        while (ISSPACE(*++p));
        hParent = (HWND) _toul(p);
        if (!hParent || !IsWindow(hParent))
          hParent = GetForegroundWindow();
        ScreenSaverChangePassword(hParent);
      }
      return 0;

      case '-':
      case '/':
      case ' ':
      default:
        break;
    }
  }
  LaunchConfig();
  return 0;
}