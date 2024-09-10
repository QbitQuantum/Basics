//*****************************************************************************
BOOL CMacStyle::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
{
	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	CWindowDC dc (pWnd);

	if (dc.GetSafeHdc () != NULL)
	{
		CRgn rgn;
		if (!rectRedraw.IsRectEmpty ())
		{
			rgn.CreateRectRgnIndirect (rectRedraw);
			dc.SelectClipRgn (&rgn);
		}

		CRect rtWindow;
		pWnd->GetWindowRect (rtWindow);
		pWnd->ScreenToClient (rtWindow);

		CRect rtClient;
		pWnd->GetClientRect (rtClient);

		rtClient.OffsetRect (-rtWindow.TopLeft ());
		dc.ExcludeClipRect (rtClient);

		rtWindow.OffsetRect (-rtWindow.TopLeft ());

		CRect rectCaption (rtWindow);
		CSize szSysBorder (GetSystemBorders ());

		rectCaption.bottom = rectCaption.top + szSysBorder.cy;

		const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
		rectCaption.bottom += nSysCaptionHeight;

		const DWORD dwStyle   = pWnd->GetStyle ();
		const DWORD dwStyleEx = pWnd->GetExStyle ();

		HICON hIcon = globalUtils.GetWndIcon (pWnd);

		CString strTitle;
		pWnd->GetWindowText (strTitle);

		DrawNcCaption (&dc, rectCaption, dwStyle, dwStyleEx, 
						strTitle, hIcon, m_bActive, TRUE,
						lstSysButtons);

		rtWindow.top = rectCaption.bottom;

		dc.ExcludeClipRect (rectCaption);
		m_ctrlMainBorder.DrawFrame (&dc, rtWindow, m_bActive ? 0 : 1);

		//-------------------------------
		// Find status bar extended area:
		//-------------------------------
		CBCGPStatusBar* pStatusBar = DYNAMIC_DOWNCAST (
			CBCGPStatusBar, pWnd->GetDescendantWindow (AFX_IDW_STATUS_BAR, TRUE));

		if (pStatusBar->GetSafeHwnd () != NULL && pStatusBar->IsWindowVisible ())
		{
			CRect rectStatus;
			pStatusBar->GetClientRect (rectStatus);

			int nHeight = rectStatus.Height ();
			rectStatus.bottom = rtWindow.bottom;
			rectStatus.top    = rectStatus.bottom - nHeight - szSysBorder.cy;
			rectStatus.left   = rtWindow.left;
			rectStatus.right  = rtWindow.right;

			m_ctrlStatusBarBack.Draw (&dc, rectStatus, m_bActive ? 0 : 1);
		}

		dc.SelectClipRgn (NULL);
		return TRUE;
	}

	return CBCGPVisualManagerXP::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
}