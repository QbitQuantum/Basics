void COXItemTipWnd::Display(CRect& rect, CString sText, int nOffset, int nAlignment,
							CFont* pFont, COLORREF clrText, COLORREF clrBackground)
{
	ASSERT_VALID(m_pParentWnd);
    ASSERT(::IsWindow(m_pParentWnd->GetSafeHwnd()));
	ASSERT(::IsWindow(m_hWnd));

	CWnd* pWnd=GetActiveWindow();
	if(pWnd==NULL || (!IsDescendant(pWnd,m_pParentWnd) && 
		(m_pParentWnd->GetExStyle()&WS_EX_TOPMOST)!=WS_EX_TOPMOST))
	{
		return;
	}

	CClientDC dc(this); // device context for drawing
	
	CFont* pOldFont=NULL;
	if(pFont)
	{
		pOldFont=dc.SelectObject(pFont);
	}
	COLORREF clrOld=ID_OX_COLOR_NONE;
	if(clrText!=ID_OX_COLOR_NONE)
	{
		clrOld=dc.SetTextColor(clrText);
	}
	int nOldBkMode=dc.SetBkMode(TRANSPARENT);

	CRect rectDraw=rect;
	dc.DrawText(sText,&rectDraw,DT_CALCRECT|DT_LEFT|DT_SINGLELINE|DT_NOPREFIX);
	rectDraw.right+=2*nOffset;
	if(rectDraw.Width()>rect.Width())
	{
		rect.right=rect.left+rectDraw.Width();
	}
	if(rectDraw.Height()>rect.Height())
	{
		rect.bottom=rect.top+rectDraw.Height();
	}

	// it's show time!
	m_pParentWnd->ClientToScreen(&rect);

	// adjust rectangle to fit the screen
	//
	CWnd* pParentWnd=m_pParentWnd;
	BOOL bTopMostParent=FALSE;
	while(pParentWnd!=NULL)
	{
		if(pParentWnd->GetExStyle() & WS_EX_TOPMOST)
		{
			bTopMostParent=TRUE;
			break;
		}
		pParentWnd=pParentWnd->GetParent();
	}

	DWORD dwMessagePos=::GetMessagePos();
	CPoint point(GET_X_LPARAM(dwMessagePos),GET_Y_LPARAM(dwMessagePos));
	CRect rectDisplay=GetMonitorRectFromPoint(point,!bTopMostParent);

	if(rect.right>rectDisplay.right)
	{
		rect.OffsetRect(rectDisplay.right-rect.right,0);
	}
	if(rect.left<rectDisplay.left)
	{
		rect.OffsetRect(rectDisplay.left-rect.left,0);
	}
	//
	/////////////////////////////////////////////////////////////

	if(bTopMostParent)
	{
		SetWindowPos(&wndTopMost,rect.left,rect.top,rect.Width(),
			rect.Height(),SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos(NULL,rect.left,rect.top,rect.Width(),
			rect.Height(),SWP_NOZORDER|SWP_NOACTIVATE);
	}
	ShowWindow(SW_SHOWNA);

	if(clrBackground!=ID_OX_COLOR_NONE)
	{
		CBrush brush;
		brush.CreateSolidBrush(clrBackground);
		CRect rectClient;
		GetClientRect(rectClient);
		dc.FillRect(&rectClient,&brush);
	}
	else
	{
		SendMessage(WM_ERASEBKGND,(WPARAM)(HDC)dc);
	}

	rectDraw=rect;
	rectDraw.DeflateRect(nOffset,0);
	ScreenToClient(&rectDraw);
	dc.DrawText(sText,&rectDraw,nAlignment|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);

	if(pOldFont)
	{
		dc.SelectObject(pOldFont);
	}
	if(clrOld!=ID_OX_COLOR_NONE)
	{
		dc.SetTextColor(clrOld);
	}
	dc.SetBkMode(nOldBkMode);

	m_nTimerID=SetTimer(ID_OXITEMTIP_TIMER,ID_OXITEMTIP_TIMER_DELAY,NULL);
	if(m_nTimerID==0)
	{
		TRACE(_T("COXItemTipWnd::Display: failed to set timer to check item tip state\n"));
	}
}