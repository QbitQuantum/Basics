void GetSysParms(void)
{
	TRACEBEGIN(TRCSUBSYSHOST, TRCSCOPEINTERN, "GetSysParms");

	crAuto		= GetSysColor(COLOR_WINDOWTEXT);
	cxBorder	= GetSystemMetrics(SM_CXBORDER);	// Unsizable window border
	cyBorder	= GetSystemMetrics(SM_CYBORDER);	//  widths
	cxHScroll	= GetSystemMetrics(SM_CXHSCROLL);	// Scrollbar-arrow bitmap 
	cxVScroll	= GetSystemMetrics(SM_CXVSCROLL);	//  dimensions
	cyHScroll	= GetSystemMetrics(SM_CYHSCROLL);	//
	cyVScroll	= GetSystemMetrics(SM_CYVSCROLL);	//
	cxDoubleClk	= GetSystemMetrics(SM_CXDOUBLECLK);
	cyDoubleClk	= GetSystemMetrics(SM_CYDOUBLECLK);
	DCT			= GetDoubleClickTime();
    
    // Get system metrics (do this only once)
    // CF - Ideally we should not need these stupid metrics

    HWND hwnd = GetDesktopWindow();
    HDC hdc = ::GetDC(hwnd);
    HFONT hfontOld;
    TEXTMETRIC tm;

	xPerInchScreenDC = GetDeviceCaps(hdc, LOGPIXELSX); 
	yPerInchScreenDC = GetDeviceCaps(hdc, LOGPIXELSY);
	int cPalette = GetDeviceCaps(hdc, SIZEPALETTE);

	// 256 colors is where we seem to need to use the palette.
	if (256 == cPalette)
	{
		fUsePalette = TRUE;
	}

	// calculate a himetric selection bar for the window's host.
	dxSelBar = DXtoHimetricX(dxSelBarDefaultSize, xPerInchScreenDC);

    hfontOld = (HFONT)SelectObject(hdc, GetStockObject(SYSTEM_FONT));
    if(hfontOld)
    {
		GetTextMetrics(hdc, &tm);
		CDisplay::_xWidthSys = (INT) tm.tmAveCharWidth;
		CDisplay::_yHeightSys = (INT) tm.tmHeight;

		SelectObject(hdc, hfontOld);
    }

    ::ReleaseDC(hwnd, hdc);		
}