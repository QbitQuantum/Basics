HRESULT InitSystemMetricValues(THREADSTATE* pts)
{
    HIGHCONTRAST    hc;
    HFONT           hfontOld;
    TEXTMETRIC      tm;

    InterlockedIncrement(&g_cMetricChange);

    if(!pts->hdcDesktop)
    {
        pts->hdcDesktop = CreateCompatibleDC(NULL);
        if(!pts->hdcDesktop)
        {
            RRETURN(E_OUTOFMEMORY);
        }
    }

    _afxGlobalData._sizePixelsPerInch.cx = GetDeviceCaps(pts->hdcDesktop, LOGPIXELSX);
    _afxGlobalData._sizePixelsPerInch.cy = GetDeviceCaps(pts->hdcDesktop, LOGPIXELSY);

    g_sizeDragMin.cx = GetSystemMetrics(SM_CXDRAG);
    g_sizeDragMin.cy = GetSystemMetrics(SM_CYDRAG);

    _afxGlobalData._sizeScrollbar.cx = GetSystemMetrics(SM_CXVSCROLL);
    _afxGlobalData._sizeScrollbar.cy = GetSystemMetrics(SM_CYHSCROLL);
    _afxGlobalData._sizelScrollbar.cx = HimetricFromHPix(_afxGlobalData._sizeScrollbar.cx);
    _afxGlobalData._sizelScrollbar.cy = HimetricFromVPix(_afxGlobalData._sizeScrollbar.cy);

    // System font info
    hfontOld = (HFONT)SelectObject(pts->hdcDesktop, GetStockObject(SYSTEM_FONT));
    if(hfontOld)
    {
        GetTextMetrics(pts->hdcDesktop, &tm);

        g_sizeSystemChar.cx = tm.tmAveCharWidth;
        g_sizeSystemChar.cy = tm.tmHeight;

        SelectObject(pts->hdcDesktop, hfontOld);
    }
    else
    {
        g_sizeSystemChar.cx = g_sizeSystemChar.cy = 10;
    }

    // Locale info
    _afxGlobalData._cpDefault = GetACP();
    _afxGlobalData._lcidUserDefault = GetSystemDefaultLCID(); // Set Global Locale ID

    GetSystemNumberSettings(&_afxGlobalData._iNumShape, &_afxGlobalData._uLangNationalDigits);

    // Accessibility info
    SystemParametersInfo(SPI_GETSCREENREADER, 0, &g_fScreenReader, FALSE);

    memset(&hc, 0, sizeof(HIGHCONTRAST));
    hc.cbSize = sizeof(HIGHCONTRAST);
    if(SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, 0))
    {
        _afxGlobalData._fHighContrastMode = !!(hc.dwFlags & HCF_HIGHCONTRASTON);
    }
    else
    {
        Trace1("SPI failed with error %x\n", GetLastError());
    }

    RRETURN(S_OK);
}