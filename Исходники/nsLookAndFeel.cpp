NS_IMETHODIMP nsLookAndFeel::GetMetric(const nsMetricID aID, PRInt32 & aMetric)
{
  nsresult res = nsXPLookAndFeel::GetMetric(aID, aMetric);
  if (NS_SUCCEEDED(res))
    return res;
  res = NS_OK;

  switch (aID) {
    case eMetric_WindowTitleHeight:
        aMetric = ::GetSystemMetrics(SM_CYCAPTION);
        break;
#ifndef WINCE
    case eMetric_WindowBorderWidth:
        aMetric = ::GetSystemMetrics(SM_CXFRAME);
        break;
    case eMetric_WindowBorderHeight:
        aMetric = ::GetSystemMetrics(SM_CYFRAME);
        break;
#endif
    case eMetric_Widget3DBorder:
        aMetric = ::GetSystemMetrics(SM_CXEDGE);
        break;
    case eMetric_TextFieldBorder:
        aMetric = 3;
        break;
    case eMetric_TextFieldHeight:
        aMetric = 24;
        break;
    case eMetric_ButtonHorizontalInsidePaddingNavQuirks:
        aMetric = 10;
        break;
    case eMetric_ButtonHorizontalInsidePaddingOffsetNavQuirks:
        aMetric = 8;
        break;
    case eMetric_CheckboxSize:
        aMetric = 12;
        break;
    case eMetric_RadioboxSize:
        aMetric = 12;
        break;
    case eMetric_TextHorizontalInsideMinimumPadding:
        aMetric = 3;
        break;
    case eMetric_TextVerticalInsidePadding:
        aMetric = 0;
        break;
    case eMetric_TextShouldUseVerticalInsidePadding:
        aMetric = 0;
        break;
    case eMetric_TextShouldUseHorizontalInsideMinimumPadding:
        aMetric = 1;
        break;
    case eMetric_ListShouldUseHorizontalInsideMinimumPadding:
        aMetric = 0;
        break;
    case eMetric_ListHorizontalInsideMinimumPadding:
        aMetric = 3;
        break;
    case eMetric_ListShouldUseVerticalInsidePadding:
        aMetric = 0;
        break;
    case eMetric_ListVerticalInsidePadding:
        aMetric = 0;
        break;
    case eMetric_CaretBlinkTime:
        aMetric = (PRInt32)::GetCaretBlinkTime();
        break;
    case eMetric_CaretWidth:
        aMetric = 1;
        break;
    case eMetric_ShowCaretDuringSelection:
        aMetric = 0;
        break;
    case eMetric_SelectTextfieldsOnKeyFocus:
        // Select textfield content when focused by kbd
        // used by nsEventStateManager::sTextfieldSelectModel
        aMetric = 1;
        break;
    case eMetric_SubmenuDelay:
        // This will default to the Windows' default
        // (400ms) on error.
        aMetric = GetSystemParam(SPI_GETMENUSHOWDELAY, 400);
        break;
    case eMetric_MenusCanOverlapOSBar:
        // we want XUL popups to be able to overlap the task bar.
        aMetric = 1;
        break;
    case eMetric_DragFullWindow:
        // This will default to the Windows' default
        // (on by default) on error.
        aMetric = GetSystemParam(SPI_GETDRAGFULLWINDOWS, 1);
        break;
#ifndef WINCE
    case eMetric_DragThresholdX:
        // The system metric is the number of pixels at which a drag should
        // start.  Our look and feel metric is the number of pixels you can
        // move before starting a drag, so subtract 1.

        aMetric = ::GetSystemMetrics(SM_CXDRAG) - 1;
        break;
    case eMetric_DragThresholdY:
        aMetric = ::GetSystemMetrics(SM_CYDRAG) - 1;
        break;
    case eMetric_UseAccessibilityTheme:
        // High contrast is a misnomer under Win32 -- any theme can be used with it, 
        // e.g. normal contrast with large fonts, low contrast, etc.
        // The high contrast flag really means -- use this theme and don't override it.
        HIGHCONTRAST contrastThemeInfo;
        contrastThemeInfo.cbSize = sizeof(contrastThemeInfo);
        ::SystemParametersInfo(SPI_GETHIGHCONTRAST, 0, &contrastThemeInfo, 0);

        aMetric = ((contrastThemeInfo.dwFlags & HCF_HIGHCONTRASTON) != 0);
        break;
    case eMetric_IsScreenReaderActive:
        // This will default to the Windows' default
        // (off by default) on error.
        aMetric = GetSystemParam(SPI_GETSCREENREADER, 0);
      break;
#endif
    case eMetric_ScrollArrowStyle:
        aMetric = eMetric_ScrollArrowStyleSingle;
        break;
    case eMetric_ScrollSliderStyle:
        aMetric = eMetric_ScrollThumbStyleProportional;
        break;
    case eMetric_TreeOpenDelay:
        aMetric = 1000;
        break;
    case eMetric_TreeCloseDelay:
        aMetric = 0;
        break;
    case eMetric_TreeLazyScrollDelay:
        aMetric = 150;
        break;
    case eMetric_TreeScrollDelay:
        aMetric = 100;
        break;
    case eMetric_TreeScrollLinesMax:
        aMetric = 3;
        break;
    case eMetric_WindowsDefaultTheme:
        aMetric = 0;
#ifndef WINCE
        if (getCurrentThemeName) {
          WCHAR themeFileName[MAX_PATH + 1] = {L'\0'};
          HRESULT hresult = getCurrentThemeName(themeFileName, MAX_PATH,
                                                NULL, 0, NULL, 0);

          // WIN2K and earlier will not have getCurrentThemeName defined, so
          // they will never make it this far.  Unless we want to save 6.0
          // users a handful of clock cycles by skipping checks for the
          // 5.x themes (or vice-versa), we can use a single loop for all
          // the different Windows versions.
          if (hresult == S_OK && GetWindowsVersion() <= VISTA_VERSION) {
            LPCWSTR defThemes[] = {
              L"luna.msstyles",
              L"royale.msstyles",
              L"zune.msstyles",
              L"aero.msstyles"
            };

            LPWSTR curTheme = wcsrchr(themeFileName, L'\\');
            curTheme = curTheme ? curTheme + 1 : themeFileName;

            for (int i = 0; i < NS_ARRAY_LENGTH(defThemes); ++i) {
              if (!lstrcmpiW(curTheme, defThemes[i])) {
                aMetric = 1;
              }
            }
          } else {
            res = NS_ERROR_NOT_IMPLEMENTED;
          }
        } else
#endif
        {
          res = NS_ERROR_NOT_IMPLEMENTED;
        }
        break;
#ifndef WINCE
    case eMetric_AlertNotificationOrigin:
        aMetric = 0;
        if (gSHAppBarMessage)
        {
          // Get task bar window handle
          HWND shellWindow = FindWindow("Shell_TrayWnd", NULL);

          if (shellWindow != NULL)
          {
            // Determine position
            APPBARDATA appBarData;
            appBarData.hWnd = shellWindow;
            appBarData.cbSize = sizeof(appBarData);
            if (gSHAppBarMessage(ABM_GETTASKBARPOS, &appBarData))
            {
              // Set alert origin as a bit field - see nsILookAndFeel.h
              // 0 represents bottom right, sliding vertically.
              switch(appBarData.uEdge)
              {
                case ABE_LEFT:
                  aMetric = NS_ALERT_HORIZONTAL | NS_ALERT_LEFT;
                  break;
                case ABE_RIGHT:
                  aMetric = NS_ALERT_HORIZONTAL;
                  break;
                case ABE_TOP:
                  aMetric = NS_ALERT_TOP;
                  // fall through for the right-to-left handling.
                case ABE_BOTTOM:
                  // If the task bar is right-to-left,
                  // move the origin to the left
                  if (::GetWindowLong(shellWindow, GWL_EXSTYLE) &
                        WS_EX_LAYOUTRTL)
                    aMetric |= NS_ALERT_LEFT;
                  break;
              }
            }
          }
        }
        break;
#endif

    case eMetric_IMERawInputUnderlineStyle:
    case eMetric_IMEConvertedTextUnderlineStyle:
        aMetric = NS_UNDERLINE_STYLE_DASHED;
        break;
    case eMetric_IMESelectedRawTextUnderlineStyle:
    case eMetric_IMESelectedConvertedTextUnderline:
        aMetric = NS_UNDERLINE_STYLE_NONE;
        break;
    default:
        aMetric = 0;
        res = NS_ERROR_FAILURE;
    }
  return res;
}