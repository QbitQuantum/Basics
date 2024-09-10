void InformApp::SetFonts(void)
{
  // Clear existing fonts
  m_fonts[FontDisplay].DeleteObject();
  m_fonts[FontFixedWidth].DeleteObject();

  // Look for registry settings
  CRegKey registryKey;
  if (registryKey.Open(HKEY_CURRENT_USER,REGISTRY_PATH_WINDOW,KEY_READ) == ERROR_SUCCESS)
  {
    char fontName[MAX_PATH];
    ULONG len = sizeof fontName;
    if (registryKey.QueryStringValue("Font Name",fontName,&len) == ERROR_SUCCESS)
      m_fontNames[FontDisplay] = fontName;
    len = sizeof fontName;
    if (registryKey.QueryStringValue("Fixed Font Name",fontName,&len) == ERROR_SUCCESS)
      m_fontNames[FontFixedWidth] = fontName;
    DWORD fontSize = 0;
    if (registryKey.QueryDWORDValue("Font Size",fontSize) == ERROR_SUCCESS)
    {
      m_fontSizes[FontDisplay] = fontSize;
      m_fontSizes[FontFixedWidth] = fontSize;
    }
  }

  // Get a device context for the display
  CWnd* wnd = CWnd::GetDesktopWindow();
  CDC* dc = wnd->GetDC();

  if (m_fontNames[FontFixedWidth].IsEmpty())
  {
    const char* fixedFonts[] =
    {
      "Consolas",
      "Lucida Console",
      "Courier New",
      "Courier"
    };

    // Search the list of known fixed width fonts for a match
    LOGFONT fontInfo;
    ::ZeroMemory(&fontInfo,sizeof fontInfo);
    fontInfo.lfCharSet = DEFAULT_CHARSET;
    bool found = false;
    for (int i = 0; i < sizeof fixedFonts / sizeof fixedFonts[0]; i++)
    {
      strcpy(fontInfo.lfFaceName,fixedFonts[i]);
      ::EnumFontFamiliesEx(dc->GetSafeHdc(),&fontInfo,(FONTENUMPROC)EnumFontProc,(LPARAM)&found,0);
      if (found)
      {
        m_fontNames[FontFixedWidth] = fontInfo.lfFaceName;
        break;
      }
    }
  }

  // Get desktop settings, and use the message font as a default
  NONCLIENTMETRICS ncm;
  ::ZeroMemory(&ncm,sizeof ncm);
  ncm.cbSize = sizeof ncm;
  ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof ncm,&ncm,0);
  int fontSize = abs(MulDiv(ncm.lfMessageFont.lfHeight,72,dc->GetDeviceCaps(LOGPIXELSY)));
  fontSize = max(fontSize,(theOS.GetWindowsVersion() < 6) ? 8 : 9);
  for (int i = 0; i < 3; i++)
  {
    if (m_fontNames[i].IsEmpty())
      m_fontNames[i] = ncm.lfMessageFont.lfFaceName;
    if (m_fontSizes[i] == 0)
      m_fontSizes[i] = fontSize;
  }

  if ((HFONT)m_fonts[FontPanel] == 0)
  {
    LOGFONT fontInfo;
    ::ZeroMemory(&fontInfo,sizeof fontInfo);
    GetFont(InformApp::FontSystem)->GetLogFont(&fontInfo);
    fontInfo.lfHeight = (LONG)(Panel::GetFontScale(wnd,dc) * fontInfo.lfHeight);

    m_fontNames[FontPanel] = m_fontNames[FontSystem];
    m_fontSizes[FontPanel] = abs(::MulDiv(fontInfo.lfHeight,72,dc->GetDeviceCaps(LOGPIXELSY)));
    m_fonts[FontPanel].CreateFontIndirect(&fontInfo);
  }

  // Release the desktop device context
  wnd->ReleaseDC(dc);
}