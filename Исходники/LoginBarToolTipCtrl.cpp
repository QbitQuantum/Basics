//*******************************************************************************************
void CLoginBarToolTipCtrl::Track (CRect rect, const CString& strText)
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	if (m_rectLast == rect && m_strText == strText)
	{
		return;
	}

	ASSERT_VALID (m_pWndParent);

	m_rectLast = rect;
	m_strText = strText;

	CClientDC dc (this);

    //ASSERT_VALID(m_pFont);
	CFont* pPrevFont = m_pFont == NULL ?
		(CFont*) dc.SelectStockObject (DEFAULT_GUI_FONT) :
		dc.SelectObject (&theApp.m_font);
	ASSERT (pPrevFont != NULL);

	int nTextHeight = rect.Height () ;
	int nTextWidth = rect.Width ();
	if (m_strText.FindOneOf (_T("\n")) != -1)	// multi-line tooltip
	{
		const int nDefaultHeight = globalData.GetTextHeight () ;
		const int nDefaultWidth = 200;
		CRect rectText (0, 0, nDefaultWidth, nDefaultHeight);
 
		nTextHeight = dc.DrawText (m_strText, rectText, DT_LEFT | /*DT_WORDBREAK | */DT_CALCRECT | DT_NOPREFIX);
		nTextWidth = rectText.Width ();
		nTextHeight += 2 * m_nTextMargin ;
		nTextWidth += 2 * m_nTextMargin;
		nTextHeight += (GetLineCount(m_strText) - 1) * m_nTextMargin; //加上行间距
	}
	else
	{
		nTextWidth = dc.GetTextExtent (m_strText).cx + 2 * m_nTextMargin;
	}

	dc.SelectObject (pPrevFont);

	if (m_pWndParent->GetExStyle () & WS_EX_LAYOUTRTL)
	{
		rect.left = rect.right - nTextWidth;
	}
	else
	{
		rect.right = rect.left + nTextWidth;
	}
	rect.bottom = rect.top + nTextHeight;
	if (rect.Height () < m_rectLast.Height ())
	{
		rect.top = m_rectLast.top;
		rect.bottom = m_rectLast.bottom;
	}

	MONITORINFO mi;
	mi.cbSize = sizeof (MONITORINFO);

	CRect rectScreen;

	if (GetMonitorInfo (MonitorFromPoint (rect.TopLeft (), MONITOR_DEFAULTTONEAREST), &mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	if (rect.Width () > rectScreen.Width ())
	{
		rect.left = rectScreen.left;
		rect.right = rectScreen.right;
	}
	else if (rect.right > rectScreen.right)
	{
		rect.OffsetRect( rectScreen.right - rect.right, 0 );
		//rect.right = rectScreen.right;
		//rect.left = rect.right - nTextWidth;
	}
	else if (rect.left < rectScreen.left)
	{
		rect.OffsetRect( rectScreen.left - rect.left, 0 );
		//rect.left = rectScreen.left;
		//rect.right = rect.left + nTextWidth;
	}

	if (rect.Height () > rectScreen.Height ())
	{
		rect.top = rectScreen.top;
		rect.bottom = rectScreen.bottom;
	}
	else if (rect.bottom > rectScreen.bottom)
	{
		rect.OffsetRect(0,  rectScreen.bottom - rect.bottom);
		//rect.bottom = rectScreen.bottom;
		//rect.top = rect.bottom - nTextHeight;
	}
	else if (rect.top < rectScreen.top)
	{
		rect.OffsetRect(0, rectScreen.top - rect.top);
		//rect.top = rectScreen.top;
		//rect.bottom = rect.bottom + nTextHeight;
	}

	rect.bottom += 3;

	SetWindowPos (&wndTop, rect.left, rect.top, 
		rect.Width (), rect.Height (), SWP_NOACTIVATE | SWP_NOOWNERZORDER);
  
    ShowWindow (SW_SHOWNOACTIVATE);
	Invalidate ();
	UpdateWindow ();

	SetCursor (AfxGetApp ()->LoadStandardCursor (IDC_ARROW));
}