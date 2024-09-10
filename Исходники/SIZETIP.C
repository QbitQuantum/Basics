void UpdateSizeTip(HWND src, int cx, int cy)
{
    TCHAR str[32];

    if (!tip_enabled)
	return;

    if (!tip_wnd) {
	NONCLIENTMETRICS nci;

	/* First make sure the window class is registered */

	if (!tip_class) {
	    WNDCLASS wc;
	    wc.style = CS_HREDRAW | CS_VREDRAW;
	    wc.lpfnWndProc = SizeTipWndProc;
	    wc.cbClsExtra = 0;
	    wc.cbWndExtra = 0;
	    wc.hInstance = hinst;
	    wc.hIcon = NULL;
	    wc.hCursor = NULL;
	    wc.hbrBackground = NULL;
	    wc.lpszMenuName = NULL;
	    wc.lpszClassName = "SizeTipClass";

	    tip_class = RegisterClass(&wc);
	}
#if 0
	/* Default values based on Windows Standard color scheme */

	tip_font = GetStockObject(SYSTEM_FONT);
	tip_bg = RGB(255, 255, 225);
	tip_text = RGB(0, 0, 0);
#endif

	/* Prepare other GDI objects and drawing info */

	tip_bg = GetSysColor(COLOR_INFOBK);
	tip_text = GetSysColor(COLOR_INFOTEXT);

	memset(&nci, 0, sizeof(NONCLIENTMETRICS));
	nci.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
			     sizeof(NONCLIENTMETRICS), &nci, 0);
	tip_font = CreateFontIndirect(&nci.lfStatusFont);
    }

    /* Generate the tip text */

    sprintf(str, "%dx%d", cx, cy);

    if (!tip_wnd) {
	HDC hdc;
	SIZE sz;
	RECT wr;
	int ix, iy;

	/* calculate the tip's size */

	hdc = CreateCompatibleDC(NULL);
	GetTextExtentPoint32(hdc, str, (int)_tcslen(str), &sz);
	DeleteDC(hdc);

	GetWindowRect(src, &wr);

	ix = wr.left;
	if (ix < 16)
	    ix = 16;

	iy = wr.top - sz.cy;
	if (iy < 16)
	    iy = 16;

	/* Create the tip window */

	tip_wnd =
	    CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
			   MAKEINTRESOURCE(tip_class), str, WS_POPUP, ix,
			   iy, sz.cx, sz.cy, NULL, NULL, hinst, NULL);

	ShowWindow(tip_wnd, SW_SHOWNOACTIVATE);

    } else {

	/* Tip already exists, just set the text */

	SetWindowText(tip_wnd, str);
    }
}