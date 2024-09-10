BOOL WINAPI
RealSystemParametersInfoA(UINT uiAction,
		      UINT uiParam,
		      PVOID pvParam,
		      UINT fWinIni)
{
  switch (uiAction)
    {

      case SPI_GETNONCLIENTMETRICS:
        {
           LPNONCLIENTMETRICSA pnclma = (LPNONCLIENTMETRICSA)pvParam;
           NONCLIENTMETRICSW nclmw;
           if(pnclma->cbSize != sizeof(NONCLIENTMETRICSA))
           {
               SetLastError(ERROR_INVALID_PARAMETER);
               return FALSE;
           }
           nclmw.cbSize = sizeof(NONCLIENTMETRICSW);

           if (!SystemParametersInfoW(uiAction, sizeof(NONCLIENTMETRICSW),
                                      &nclmw, fWinIni))
             return FALSE;

           pnclma->iBorderWidth = nclmw.iBorderWidth;
           pnclma->iScrollWidth = nclmw.iScrollWidth;
           pnclma->iScrollHeight = nclmw.iScrollHeight;
           pnclma->iCaptionWidth = nclmw.iCaptionWidth;
           pnclma->iCaptionHeight = nclmw.iCaptionHeight;
           pnclma->iSmCaptionWidth = nclmw.iSmCaptionWidth;
           pnclma->iSmCaptionHeight = nclmw.iSmCaptionHeight;
           pnclma->iMenuWidth = nclmw.iMenuWidth;
           pnclma->iMenuHeight = nclmw.iMenuHeight;
           LogFontW2A(&(pnclma->lfCaptionFont), &(nclmw.lfCaptionFont));
           LogFontW2A(&(pnclma->lfSmCaptionFont), &(nclmw.lfSmCaptionFont));
           LogFontW2A(&(pnclma->lfMenuFont), &(nclmw.lfMenuFont));
           LogFontW2A(&(pnclma->lfStatusFont), &(nclmw.lfStatusFont));
           LogFontW2A(&(pnclma->lfMessageFont), &(nclmw.lfMessageFont));
           return TRUE;
        }
      case SPI_SETNONCLIENTMETRICS:
        {
           LPNONCLIENTMETRICSA pnclma = (LPNONCLIENTMETRICSA)pvParam;
           NONCLIENTMETRICSW nclmw;
           if(pnclma->cbSize != sizeof(NONCLIENTMETRICSA))
           {
               SetLastError(ERROR_INVALID_PARAMETER);
               return FALSE;
           }
           nclmw.cbSize = sizeof(NONCLIENTMETRICSW);
           nclmw.iBorderWidth = pnclma->iBorderWidth;
           nclmw.iScrollWidth = pnclma->iScrollWidth;
           nclmw.iScrollHeight = pnclma->iScrollHeight;
           nclmw.iCaptionWidth = pnclma->iCaptionWidth;
           nclmw.iCaptionHeight = pnclma->iCaptionHeight;
           nclmw.iSmCaptionWidth = pnclma->iSmCaptionWidth;
           nclmw.iSmCaptionHeight = pnclma->iSmCaptionHeight;
           nclmw.iMenuWidth = pnclma->iMenuWidth;
           nclmw.iMenuHeight = pnclma->iMenuHeight;
           LogFontA2W(&(nclmw.lfCaptionFont), &(pnclma->lfCaptionFont));
           LogFontA2W(&(nclmw.lfSmCaptionFont), &(pnclma->lfSmCaptionFont));
           LogFontA2W(&(nclmw.lfMenuFont), &(pnclma->lfMenuFont));
           LogFontA2W(&(nclmw.lfStatusFont), &(pnclma->lfStatusFont));
           LogFontA2W(&(nclmw.lfMessageFont), &(pnclma->lfMessageFont));

           return SystemParametersInfoW(uiAction, sizeof(NONCLIENTMETRICSW),
                                        &nclmw, fWinIni);
        }
      case SPI_GETICONMETRICS:
          {
              LPICONMETRICSA picma = (LPICONMETRICSA)pvParam;
              ICONMETRICSW icmw;
              if(picma->cbSize != sizeof(ICONMETRICSA))
              {
                  SetLastError(ERROR_INVALID_PARAMETER);
                  return FALSE;
              }
              icmw.cbSize = sizeof(ICONMETRICSW);
              if (!SystemParametersInfoW(uiAction, sizeof(ICONMETRICSW),
                                        &icmw, fWinIni))
                  return FALSE;

              picma->iHorzSpacing = icmw.iHorzSpacing;
              picma->iVertSpacing = icmw.iVertSpacing;
              picma->iTitleWrap = icmw.iTitleWrap;
              LogFontW2A(&(picma->lfFont), &(icmw.lfFont));
              return TRUE;
          }
      case SPI_SETICONMETRICS:
          {
              LPICONMETRICSA picma = (LPICONMETRICSA)pvParam;
              ICONMETRICSW icmw;
              if(picma->cbSize != sizeof(ICONMETRICSA))
              {
                  SetLastError(ERROR_INVALID_PARAMETER);
                  return FALSE;
              }
              icmw.cbSize = sizeof(ICONMETRICSW);
              icmw.iHorzSpacing = picma->iHorzSpacing;
              icmw.iVertSpacing = picma->iVertSpacing;
              icmw.iTitleWrap = picma->iTitleWrap;
              LogFontA2W(&(icmw.lfFont), &(picma->lfFont));

              return SystemParametersInfoW(uiAction, sizeof(ICONMETRICSW),
                                           &icmw, fWinIni);
          }
      case SPI_GETICONTITLELOGFONT:
        {
           LOGFONTW lfw;
           if (!SystemParametersInfoW(uiAction, 0, &lfw, fWinIni))
             return FALSE;
           LogFontW2A(pvParam, &lfw);
           return TRUE;
        }
      case SPI_SETICONTITLELOGFONT:
          {
              LPLOGFONTA plfa = (LPLOGFONTA)pvParam;
              LOGFONTW lfw;
              LogFontA2W(&lfw,plfa);
              return SystemParametersInfoW(uiAction, 0, &lfw, fWinIni);
          }
      case SPI_GETDESKWALLPAPER:
      {
        BOOL Ret;
        WCHAR awc[MAX_PATH];
        UNICODE_STRING ustrWallpaper;
        ANSI_STRING astrWallpaper;

        Ret = NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, awc, fWinIni);
        RtlInitUnicodeString(&ustrWallpaper, awc);
        RtlUnicodeStringToAnsiString(&astrWallpaper, &ustrWallpaper, TRUE);

        RtlCopyMemory(pvParam, astrWallpaper.Buffer, uiParam);
        RtlFreeAnsiString(&astrWallpaper);
        return Ret;
      }

      case SPI_SETDESKWALLPAPER:
      {
          UNICODE_STRING ustrWallpaper;
          BOOL Ret;

          if (pvParam)
          {
            if (!RtlCreateUnicodeStringFromAsciiz(&ustrWallpaper, pvParam))
            {
                ERR("RtlCreateUnicodeStringFromAsciiz failed\n");
                return FALSE;
            }
            pvParam = &ustrWallpaper;
          }

          Ret = NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, uiParam, pvParam, fWinIni);

          if (pvParam)
            RtlFreeUnicodeString(&ustrWallpaper);

          return Ret;
      }
    }
    return NtUserSystemParametersInfo(uiAction, uiParam, pvParam, fWinIni);
}