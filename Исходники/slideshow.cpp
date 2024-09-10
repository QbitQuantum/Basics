slide_show(HWND hwndParent, int string_size, TCHAR *variables, stack_t **stacktop)
{
  EXDLL_INIT();
  slide_abort();

  // argument default values
  iHAlign = HALIGN_CENTER;
  iVAlign = VALIGN_CENTER;
  iFit    = FIT_BOTH;
  g_hWnd = NULL;
  captionColor = RGB(255,255,255);
  int duration = 1000; // transition duration in ms (default = 1s)
  TCHAR caption[MAX_PATH];
  caption[0] = '\0';

  // parse arguments
  TCHAR arg[MAX_PATH];
  LPTSTR argValue;
  while(!popstring(arg, sizeof arg) && *arg == '/' && (argValue = StrChr(arg, '=')) != NULL)
    {
      *argValue++ = '\0';     // replace '=' by '\0'
      if(lstrcmpi(arg, TEXT("/hwnd")) == 0)
        StrToIntEx(argValue, STIF_SUPPORT_HEX, (int*) &g_hWnd);
      else if(lstrcmpi(arg, TEXT("/fit")) == 0)
        {
          if(lstrcmpi(argValue, TEXT("height")) == 0)		iFit = FIT_HEIGHT;
          else if(lstrcmpi(argValue, TEXT("width")) == 0)	iFit = FIT_WIDTH;
          else if(lstrcmpi(argValue, TEXT("stretch")) == 0)	iFit = FIT_STRETCH;
        }
      else if(lstrcmpi(arg, TEXT("/halign")) == 0)
        {
          if(lstrcmpi(argValue, TEXT("left")) == 0) iHAlign = HALIGN_LEFT;
          else if(lstrcmpi(argValue, TEXT("right")) == 0) iHAlign = HALIGN_RIGHT;
        }
      else if(lstrcmpi(arg, TEXT("/valign")) == 0)
        {
          if(lstrcmpi(argValue, TEXT("top")) == 0) iVAlign = VALIGN_TOP;
          else if(lstrcmpi(argValue, TEXT("bottom")) == 0) iVAlign = VALIGN_BOTTOM;
        }
      else if(lstrcmpi(arg, TEXT("/duration")) == 0)
        StrToIntEx(argValue, STIF_SUPPORT_HEX, &duration);
      else if(lstrcmpi(arg, TEXT("/caption")) == 0)
        lstrcpy(caption, argValue);
      else if(lstrcmpi(arg, TEXT("/ccolor")) == 0)
        StrToIntEx(argValue, STIF_SUPPORT_HEX, (int*) &captionColor);
      else if(lstrcmpi(arg, TEXT("/auto")) == 0)
        {
          lstrcpy(g_autoPath, argValue);
          PathRemoveFileSpec(g_autoPath);
          HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, 32767*sizeof(TCHAR));
          DWORD count = GetPrivateProfileSection(getuservariable(INST_LANG), LPTSTR(hMem), 32767, argValue);
          if (count == 0)
            {
              count = GetPrivateProfileSection(TEXT("1033"), LPTSTR(hMem), 32767, argValue);
              if (count == 0)
                count = GetPrivateProfileSection(TEXT("0"), LPTSTR(hMem), 32767, argValue);
            }
          if (count)
            {
              g_autoBuffer = LPTSTR(GlobalReAlloc(hMem, (count+1)*sizeof(TCHAR), 0));
              g_autoNext = g_autoBuffer;
            }
          else
            GlobalFree(hMem);
        }
    }

  // if target window not defined we'll search for default (the details listview)
  if (g_hWnd == NULL)
    {
      g_hWnd = FindWindowEx(hwndParent, NULL, TEXT("#32770"), NULL);
      if (g_hWnd == NULL)
        return;
      hwndParent = FindWindowEx(hwndParent, g_hWnd, TEXT("#32770"), NULL);
      if (hwndParent != NULL && !IsWindowVisible(hwndParent))
        g_hWnd = hwndParent;
      if (g_hWnd == NULL)
        return;
      HWND hWnd = GetDlgItem(g_hWnd, 1016);
      GetWindowRect(hWnd, &rDest);
      ScreenToClient(g_hWnd, (LPPOINT) &rDest.left);
      ScreenToClient(g_hWnd, (LPPOINT) &rDest.right);
    }
  else
    GetClientRect(g_hWnd, &rDest);

  // load new image
  if (arg[0] == '\0')
    return; // stop here if no filename

  if (g_autoNext != NULL)
    slide_NextAuto();
  else
    slide_NewImage(arg, caption, duration);
}