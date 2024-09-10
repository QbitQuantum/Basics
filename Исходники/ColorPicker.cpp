STDMETHODIMP CColorPicker::Pick(long hParent, long X, long Y, OLE_COLOR clr, OLE_COLOR* pclr)
{	
	m_hEvent = CreateEvent(0, 0, 0, 0);
	if (!m_hEvent) 
		return E_FAIL;

	if (!Create((HWND) hParent))
		return E_FAIL;
	
	m_clr = clr;

	BOOL b;
	int idx = SetStartColor(m_clr);		
	TabCtrl_SetCurSel(m_winTab, idx);		
	OnTabSelChange(idx, 0, b);

	int nSizeX = 0;
	HDC hdc = GetDC();
		
	HFONT hFont = (HFONT)::SelectObject(hdc, m_hFont);

	for(int i = 0; m_SystemColors[i].text; i++)
	{
		SIZE sizeText;
		::GetTextExtentPoint32(hdc, m_SystemColors[i].text, lstrlen(m_SystemColors[i].text), &sizeText);
		if(nSizeX < sizeText.cx + sizeText.cy)	nSizeX = sizeText.cx + sizeText.cy;
	}

	::SelectObject(hdc, hFont);
	::ReleaseDC(m_hWnd, hdc);

	nSizeX += GetSystemMetrics(SM_CXVSCROLL);
	nSizeX += GetSystemMetrics(SM_CXBORDER) * 2;
	m_nCellSize = MulDiv(nSizeX, 100, 800);
	
	RECT rc = {0, 0, m_nCellSize * 8, m_nCellSize * 8};
	
	TabCtrl_AdjustRect(m_winTab, TRUE, &rc);
	
	if(rc.left < 0)
	{
		rc.right -= rc.left; rc.left = 0;
	}
	if(rc.top < 0)
	{
		rc.bottom -= rc.top; rc.top = 0;
	}

	rc.bottom += ::GetSystemMetrics(SM_CYEDGE) * 2 + 2;
	rc.right += ::GetSystemMetrics(SM_CXEDGE) * 2 + 2;

	SetWindowPos(m_hWnd, &rc, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
	
	GetClientRect(&rc);

	m_winTab.MoveWindow(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, FALSE);
	TabCtrl_AdjustRect(m_winTab, FALSE, &rc); 	

	m_winList.MoveWindow(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, FALSE);
	m_wndPalette.MoveWindow(&rc, FALSE);	


	GetWindowRect(&rc);		
	int height = rc.bottom - rc.top;
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);						
	if(Y + height >= cyScreen)
		Y = cyScreen -  height; 		
	int left = max(0, X - (rc.right - rc.left));
	
	SetWindowPos(HWND_TOPMOST, left, Y, 0, 0, SWP_NOSIZE);
	
	ShowWindow(SW_SHOW);
//////////////////////////////////////////////
/*	for (;;)
	{
		MSG msg;
		::GetMessage(&msg, NULL, 0, 0);
		HWND hCaptureWnd = ::GetCapture();
		if (hCaptureWnd && (hCaptureWnd != m_hWnd && ::GetParent(hCaptureWnd) != m_hWnd))
			break;
	}
*/
	AtlWaitWithMessageLoop(m_hEvent);
///////////////////////////////////////////////
	
	HWND hWndGetFocus = GetFocus();
	HWND hWndParent = GetParent();
	DestroyWindow();
	if (hWndGetFocus != hWndParent && ::GetParent(hWndGetFocus) != hWndParent)
		::SetFocus(hWndParent);
	CloseHandle(m_hEvent);
	m_hEvent = 0;	
	*pclr = m_clr;
	return S_OK;
}