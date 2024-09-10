// static
void
nsUXThemeData::UpdateNativeThemeInfo()
{
  // Trigger a refresh of themed button metrics if needed
  sTitlebarInfoPopulatedThemed = (nsWindow::GetWindowsVersion() < VISTA_VERSION);

  sIsDefaultWindowsTheme = PR_FALSE;
  sThemeId = nsILookAndFeel::eWindowsTheme_Generic;

  if (!IsAppThemed() || !getCurrentThemeName) {
    sThemeId = nsILookAndFeel::eWindowsTheme_Classic;
    return;
  }

  WCHAR themeFileName[MAX_PATH + 1];
  WCHAR themeColor[MAX_PATH + 1];
  if (FAILED(getCurrentThemeName(themeFileName,
                                 MAX_PATH,
                                 themeColor,
                                 MAX_PATH,
                                 NULL, 0))) {
    sThemeId = nsILookAndFeel::eWindowsTheme_Classic;
    return;
  }

  LPCWSTR themeName = wcsrchr(themeFileName, L'\\');
  themeName = themeName ? themeName + 1 : themeFileName;

  WindowsTheme theme = WINTHEME_UNRECOGNIZED;
  for (int i = 0; i < NS_ARRAY_LENGTH(knownThemes); ++i) {
    if (!lstrcmpiW(themeName, knownThemes[i].name)) {
      theme = (WindowsTheme)knownThemes[i].type;
      break;
    }
  }

  if (theme == WINTHEME_UNRECOGNIZED)
    return;

  if (theme == WINTHEME_AERO || theme == WINTHEME_LUNA)
    sIsDefaultWindowsTheme = PR_TRUE;
  
  if (theme != WINTHEME_LUNA) {
    switch(theme) {
      case WINTHEME_AERO:
        sThemeId = nsILookAndFeel::eWindowsTheme_Aero;
        return;
      case WINTHEME_ZUNE:
        sThemeId = nsILookAndFeel::eWindowsTheme_Zune;
        return;
      case WINTHEME_ROYALE:
        sThemeId = nsILookAndFeel::eWindowsTheme_Royale;
        return;
      default:
        NS_WARNING("unhandled theme type.");
        return;
    }
  }

  // calculate the luna color scheme
  WindowsThemeColor color = WINTHEMECOLOR_UNRECOGNIZED;
  for (int i = 0; i < NS_ARRAY_LENGTH(knownColors); ++i) {
    if (!lstrcmpiW(themeColor, knownColors[i].name)) {
      color = (WindowsThemeColor)knownColors[i].type;
      break;
    }
  }

  switch(color) {
    case WINTHEMECOLOR_NORMAL:
      sThemeId = nsILookAndFeel::eWindowsTheme_LunaBlue;
      return;
    case WINTHEMECOLOR_HOMESTEAD:
      sThemeId = nsILookAndFeel::eWindowsTheme_LunaOlive;
      return;
    case WINTHEMECOLOR_METALLIC:
      sThemeId = nsILookAndFeel::eWindowsTheme_LunaSilver;
      return;
    default:
      NS_WARNING("unhandled theme color.");
      return;
  }
}