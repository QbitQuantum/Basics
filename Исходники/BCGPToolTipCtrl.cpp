//**********************************************************************
void CBCGPToolTipCtrl::OnShow(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	*pResult = 0;

	if (m_Params.m_bVislManagerTheme)
	{
		CBCGPVisualManager::GetInstance ()->GetToolTipParams (m_Params);
		m_Params.m_bVislManagerTheme = TRUE;
	}

	if (m_Params.m_bBallonTooltip)
	{
		return;
	}

	CPoint ptCursor;
	::GetCursorPos (&ptCursor);

	GetHotButton ();

	m_sizeImage = m_Params.m_bDrawIcon ? GetIconSize () : CSize (0, 0);
	m_ptMargin = CPoint (6, 4);

	m_ptMargin.x += m_Params.m_nPaddingX;
	m_ptMargin.y += m_Params.m_nPaddingY;

	CRect rectMargin;
	GetMargin (rectMargin);

	CRect rectText;
	GetClientRect (rectText);

	CClientDC dc (this);
	CSize sizeText = OnDrawLabel (&dc, rectText, TRUE);
	
	int cx = sizeText.cx;
	int cy = sizeText.cy;

	CSize sizeDescr (0, 0);
	
	if (!m_Params.m_bDrawDescription || m_strDescription.IsEmpty ())
	{
		cy = max (cy, m_sizeImage.cy);
	}
	else
	{
		sizeDescr = OnDrawDescription (&dc, rectText, TRUE);

		cy += sizeDescr.cy + 2 * m_ptMargin.y;
		cx = max (cx, sizeDescr.cx);

		cy = max (cy, m_sizeImage.cy);
	}

	if (m_sizeImage.cx > 0 && m_Params.m_bDrawIcon)
	{
		cx += m_sizeImage.cx + m_ptMargin.x;
	}

	cx += 2 * m_ptMargin.x;
	cy += 2 * m_ptMargin.y;

	int nFixedWidth = GetFixedWidth ();
	if (nFixedWidth > 0 && sizeDescr != CSize (0, 0))
	{
		cx = max (cx, nFixedWidth);
	}

	CRect rectWindow;
	GetWindowRect (rectWindow);

	int x = rectWindow.left;
	int y = rectWindow.top;

	if (m_ptLocation != CPoint (-1, -1))
	{
		x = m_ptLocation.x;
		y = m_ptLocation.y;

		*pResult = 1;
	}

	CRect rectScreen;

	MONITORINFO mi;
	mi.cbSize = sizeof (MONITORINFO);
	if (GetMonitorInfo (MonitorFromPoint (rectWindow.TopLeft (), MONITOR_DEFAULTTONEAREST),
		&mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	int nBottom = max (
		ptCursor.y + cy + ::GetSystemMetrics (SM_CYCURSOR),
		y + cy + 2);

	if (nBottom > rectScreen.bottom)
	{
		y = ptCursor.y - cy - 1;

#ifndef BCGP_EXCLUDE_RIBBON
		if (m_pRibbonButton != NULL && m_ptLocation != CPoint (-1, -1))
		{
			ASSERT_VALID (m_pRibbonButton);

			CBCGPRibbonBar* pRibbon = m_pRibbonButton->GetTopLevelRibbonBar ();
			if (pRibbon->GetSafeHwnd () != NULL)
			{
				CRect rectRibbon;
				pRibbon->GetWindowRect (rectRibbon);

				y = rectRibbon.top - cy;
			}
		}
#endif

		*pResult = 1;
	}

	if (x + cx + 2 > rectScreen.right)
	{
		if ((*pResult) == 1)	// Y has been changed
		{
			x = ptCursor.x - cx - 1;
		}
		else
		{
			x = rectScreen.right - cx - 1;
			*pResult = 1;
		}
	}

	if ((*pResult) == 1)
	{
		SetWindowPos (NULL, x, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	m_sizeCornerRadius = CBCGPVisualManager::GetInstance()->GetSystemToolTipCornerRadius(this);
	
	SetWindowPos (&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE | SWP_DRAWFRAME);
}