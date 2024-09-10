//
//	Initialize the cool scrollbars for a window by subclassing it
//	and using the coolsb window procedure instead
//
BOOL WINAPI InitializeCoolSB(HWND hwnd)
{
	SCROLLWND *sw;
	SCROLLINFO *si;
	INITCOMMONCONTROLSEX ice;
	TOOLINFO ti;
	RECT rect;
	DWORD dwCurStyle;
	//BOOL fDisabled;

	if(pEnableScrollBar == 0)
		pEnableScrollBar = EnableScrollBar;

	GetClientRect(hwnd, &rect);

	//if we have already initialized Cool Scrollbars for this window,
	//then stop the user from doing it again
	if(GetScrollWndFromHwnd(hwnd) != 0)
	{
		return FALSE;
	}

	//allocate a private scrollbar structure which we 
	//will use to keep track of the scrollbar data
	sw = (SCROLLWND *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SCROLLWND));

	si = &sw->sbarHorz.scrollInfo;
	si->cbSize = sizeof(SCROLLINFO);
	si->fMask  = SIF_ALL;
	GetScrollInfo(hwnd, SB_HORZ, si);

	si = &sw->sbarVert.scrollInfo;
	si->cbSize = sizeof(SCROLLINFO);
	si->fMask  = SIF_ALL;
	GetScrollInfo(hwnd, SB_VERT, si);

	//check to see if the window has left-aligned scrollbars
	if(GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LEFTSCROLLBAR)
		sw->fLeftScrollbar = TRUE;
	else
		sw->fLeftScrollbar = FALSE;

	dwCurStyle = GetWindowLong(hwnd, GWL_STYLE);

	SetProp(hwnd, szPropStr, (HANDLE)sw);

	//try to enable the scrollbar arrows - if the return value is
	//non-zero, then the scrollbars were previously disabled
	//fDisabled = pEnableScrollBar(hwnd, SB_HORZ, ESB_ENABLE_BOTH);

	//scrollbars will automatically get enabled, even if
	//they aren't to start with....sorry, but there isn't an
	//easy alternative.
	if(dwCurStyle & WS_HSCROLL)
		sw->sbarHorz.fScrollFlags = CSBS_VISIBLE;

	if(dwCurStyle & WS_VSCROLL)
		sw->sbarVert.fScrollFlags = CSBS_VISIBLE;

	//need to be able to distinguish between horizontal and vertical
	//scrollbars in some instances
	sw->sbarHorz.nBarType	     = SB_HORZ;
	sw->sbarVert.nBarType	     = SB_VERT;

	sw->sbarHorz.fFlatScrollbar  = CSBS_NORMAL;
	sw->sbarVert.fFlatScrollbar  = CSBS_NORMAL;

	//set the default arrow sizes for the scrollbars
	sw->sbarHorz.nArrowLength	 = SYSTEM_METRIC;
	sw->sbarHorz.nArrowWidth	 = SYSTEM_METRIC;
	sw->sbarVert.nArrowLength	 = SYSTEM_METRIC;
	sw->sbarVert.nArrowWidth	 = SYSTEM_METRIC;

	sw->bPreventStyleChange		 = FALSE;
	
	sw->oldproc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)CoolSBWndProc);

	CoolSB_SetMinThumbSize(hwnd, SB_BOTH, CoolSB_GetDefaultMinThumbSize());

#ifdef COOLSB_TOOLTIPS
	ice.dwSize = sizeof(ice);
	ice.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&ice);

	sw->hwndToolTip = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, TOOLTIPS_CLASS, _T(""),
                            WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            hwnd, NULL, GetModuleHandle(0),
                            NULL);

	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_IDISHWND;
	ti.hwnd   = hwnd;
	ti.uId    = (UINT)hwnd;
	ti.lpszText = LPSTR_TEXTCALLBACK;
	ti.hinst   = GetModuleHandle(0);

	SendMessage(sw->hwndToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
	
#else

	UNREFERENCED_PARAMETER(ice);
	UNREFERENCED_PARAMETER(ti);
	sw->hwndToolTip = 0;

#endif
	
	//send the window a frame changed message to update the scrollbars
	RedrawNonClient(hwnd, TRUE);

	return TRUE;
}