//****************************************************************************************
void CBCGPControlBarImpl::DrawNcArea ()
{
	CWindowDC dc(m_pBar);

	CRect rectClient;
	m_pBar->GetClientRect(rectClient);

	CRect rectWindow;
	m_pBar->GetWindowRect(rectWindow);

	m_pBar->ScreenToClient(rectWindow);
	rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
	dc.ExcludeClipRect (rectClient);

	BOOL bRTL = m_pBar->GetExStyle() & WS_EX_LAYOUTRTL;

	{
		MSG* pMsg = &AfxGetThreadState()->m_lastSentMsg;

		ASSERT (pMsg->hwnd == m_pBar->m_hWnd);
		ASSERT (pMsg->message == WM_NCPAINT);

		CRgn* pRgn = NULL;
		if (pMsg->wParam != 1 && 
			(pRgn = CRgn::FromHandle ((HRGN) pMsg->wParam)) != NULL)
		{
			CRect rect;
			m_pBar->GetWindowRect (rect);

			if (bRTL)
			{
				CRect rect2;
				pRgn->GetRgnBox(&rect2);
				rect2.OffsetRect(rect.right - rect2.right - rect2.left, -rect.top);
				CRgn rgn;
				rgn.CreateRectRgnIndirect(&rect2);
				dc.SelectClipRgn(&rgn, RGN_AND);
			}
			else
			{
				pRgn->OffsetRgn (- rect.TopLeft ());
				dc.SelectClipRgn (pRgn, RGN_AND);
			}
		}
	}

	if (!m_pBar->m_bIsTransparentBorder)
	{
		// draw borders in non-client area
		rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
		CBCGPVisualManager::GetInstance ()->OnDrawBarBorder (&dc, m_pBar, rectWindow);

		// erase parts not drawn
		dc.IntersectClipRect(rectWindow);
		CBCGPVisualManager::GetInstance ()->OnFillBarBackground  (&dc, m_pBar, rectWindow,
			CRect (0, 0, 0, 0), TRUE /* NC area */);
	}
	else
	{
		GetBackgroundFromParent(&dc);
	}

	// draw gripper in non-client area
	if ((m_pBar->GetBarStyle () & (CBRS_GRIPPER|CBRS_FLOATING)) != CBRS_GRIPPER)
	{
		dc.SelectClipRgn (NULL);
		return;
	}

	CRect rectGripper;
	GetGripperRect (rectGripper);

	if (rectGripper.Width() >= 1 && rectGripper.Height() >= 1)
	{
		BOOL bHorz = (m_pBar->GetBarStyle () & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

		CBCGPVisualManager::GetInstance ()->OnDrawBarGripper (
			&dc, rectGripper, bHorz, m_pBar);
	}

	dc.SelectClipRgn (NULL);
}