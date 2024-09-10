HWND CTabPanelWin::CreateToolbar()
{
	gpSetCls->CheckTheming();

	if (!mh_Rebar || !gpSet->isMultiShowButtons)
		return NULL; // нет табов - нет и тулбара

	if (mh_Toolbar)
		return mh_Toolbar; // Уже создали

	mh_Toolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
	                            WS_CHILD|WS_VISIBLE|
	                            TBSTYLE_FLAT|CCS_NOPARENTALIGN|CCS_NORESIZE|CCS_NODIVIDER|
	                            TBSTYLE_TOOLTIPS|TBSTYLE_TRANSPARENT,
	                            0, 0, 0, 0, mh_Rebar,
	                            NULL, NULL, NULL);

	TabPanelWinMap map = {this}; //{ CTabPanelWin* object; HWND hWnd; WNDPROC defaultProc; };
	map.defaultProc = (WNDPROC)SetWindowLongPtr(mh_Toolbar, GWLP_WNDPROC, (LONG_PTR)_ToolProc);
	map.hWnd = mh_Toolbar;
	gp_TabPanelWinMap->Set(mh_Toolbar, map);

	DWORD lExStyle = ((DWORD)SendMessage(mh_Toolbar, TB_GETEXTENDEDSTYLE, 0, 0)) | TBSTYLE_EX_DRAWDDARROWS;
	SendMessage(mh_Toolbar, TB_SETEXTENDEDSTYLE, 0, lExStyle);
	SendMessage(mh_Toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0);
	SendMessage(mh_Toolbar, TB_SETBITMAPSIZE, 0, MAKELONG(14,14));

	TBADDBITMAP bmp = {g_hInstance,IDB_MAIN_TOOLBAR};
	int nFirst = SendMessage(mh_Toolbar, TB_ADDBITMAP, BID_TOOLBAR_LAST_IDX, (LPARAM)&bmp);
	_ASSERTE(BID_TOOLBAR_LAST_IDX==37);

	//DWORD nLoadErr = 0;
	if (gnOsVer >= 0x600)
	{
		bmp.hInst = g_hInstance;
		bmp.nID = IDB_COPY24;
	}
	else
	{
		bmp.hInst = NULL;
		COLORMAP colorMap = {RGB(255,0,0),GetSysColor(COLOR_BTNFACE)};
		bmp.nID = (UINT_PTR)CreateMappedBitmap(g_hInstance, IDB_COPY4, 0, &colorMap, 1);
		//bmp.nID = (UINT_PTR)LoadImage(g_hInstance, MAKEINTRESOURCE(IDB_COPY24), IMAGE_BITMAP, 0,0, LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
		//nLoadErr = GetLastError();
	}

	int nCopyBmp = SendMessage(mh_Toolbar, TB_ADDBITMAP, 1, (LPARAM)&bmp);
	// Должен 37 возвращать
	_ASSERTE(nCopyBmp == BID_TOOLBAR_LAST_IDX);
	if (nCopyBmp < BID_TOOLBAR_LAST_IDX)
		nCopyBmp = BID_TOOLBAR_LAST_IDX;

	{
		bmp.hInst = NULL;
		COLORMAP colorMap = {0xC0C0C0,GetSysColor(COLOR_BTNFACE)};
		bmp.nID = (UINT_PTR)CreateMappedBitmap(g_hInstance, IDB_SCROLL, 0, &colorMap, 1);
	}
	int nScrollBmp = SendMessage(mh_Toolbar, TB_ADDBITMAP, 1, (LPARAM)&bmp);
	// Должен 38 возвращать
	_ASSERTE(nScrollBmp == (BID_TOOLBAR_LAST_IDX+1));
	if (nScrollBmp < (BID_TOOLBAR_LAST_IDX+1))
		nScrollBmp = BID_TOOLBAR_LAST_IDX+1;


	//buttons
	TBBUTTON btn = {0, 0, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP};
	TBBUTTON sep = {0, TID_MINIMIZE_SEP+1, TBSTATE_ENABLED, TBSTYLE_SEP};
	int nActiveCon = gpConEmu->ActiveConNum()+1;

	// New console
	btn.iBitmap = nFirst + BID_NEWCON_IDX;
	btn.idCommand = TID_CREATE_CON;
	btn.fsStyle = BTNS_DROPDOWN;
	btn.fsState = TBSTATE_ENABLED;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);

	// Console numbers
	btn.iBitmap = ((nActiveCon >= 0) ? (nFirst + BID_FIST_CON) : BID_DUMMYBTN_IDX);
	btn.idCommand = TID_ACTIVE_NUMBER;
	btn.fsStyle = BTNS_DROPDOWN;
	btn.fsState = TBSTATE_ENABLED;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);

	btn.fsStyle = BTNS_BUTTON;
	//SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&sep); sep.idCommand++;
#if 0 //defined(_DEBUG)
	// Show copying state
	btn.iBitmap = nCopyBmp; btn.idCommand = TID_COPYING;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&sep); sep.idCommand++;
#endif
	// Buffer height mode
	btn.iBitmap = nFirst + BID_ALTERNATIVE_IDX; btn.idCommand = TID_ALTERNATIVE; btn.fsState = TBSTATE_ENABLED;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	// Show copying state
	btn.iBitmap = nScrollBmp; btn.idCommand = TID_SCROLL;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	// Separator before min/max/close
	sep.fsState |= TBSTATE_HIDDEN; sep.idCommand = TID_MINIMIZE_SEP;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&sep);
	// Min,Max,Close
	btn.iBitmap = nFirst + BID_MINIMIZE_IDX; btn.idCommand = TID_MINIMIZE; btn.fsState = TBSTATE_ENABLED|TBSTATE_HIDDEN;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	btn.iBitmap = nFirst + ((gpConEmu->GetWindowMode() != wmNormal) ? BID_MAXIMIZE_IDX : BID_RESTORE_IDX); btn.idCommand = TID_MAXIMIZE;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	btn.iBitmap = nFirst + BID_APPCLOSE_IDX; btn.idCommand = TID_APPCLOSE;
	SendMessage(mh_Toolbar, TB_ADDBUTTONS, 1, (LPARAM)&btn);
	SendMessage(mh_Toolbar, TB_AUTOSIZE, 0, 0);
#ifdef _DEBUG
	SIZE sz;
	SendMessage(mh_Toolbar, TB_GETMAXSIZE, 0, (LPARAM)&sz);
#endif
	return mh_Toolbar;
}