BOOL CVisualManager::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
{
	if (!CanDrawImage ())
	{
		return CBCGPWinXPVisualManager::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
	}

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

        BOOL bActive = IsWindowActive (pWnd);

		CRect rectCaption (rtWindow);
		CSize szSysBorder (GetSystemBorders ());

		rectCaption.bottom = rectCaption.top + szSysBorder.cy;

		const DWORD dwStyle = pWnd->GetStyle ();
		BOOL bMaximized = (dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE;

		const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
		rectCaption.bottom += nSysCaptionHeight;

		const DWORD dwStyleEx = pWnd->GetExStyle ();

		BOOL bDestroyIcon = FALSE;
		HICON hIcon = globalUtils.GetWndIcon (pWnd, &bDestroyIcon);

		CString strText;
		pWnd->GetWindowText (strText);

		CString strTitle (strText);
		CString strDocument;

		BOOL bPrefix = FALSE;
		if ((dwStyle & FWS_ADDTOTITLE) == FWS_ADDTOTITLE)
		{
			bPrefix = (dwStyle & FWS_PREFIXTITLE) == FWS_PREFIXTITLE;
			CFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);

			if (pFrameWnd != NULL)
			{
				strTitle = pFrameWnd->GetTitle();

				if (!strTitle.IsEmpty ())
				{
					if (strText.GetLength () >= strTitle.GetLength ())
					{
						if (bPrefix)
						{
							int pos = strText.Find (strTitle, strText.GetLength () - strTitle.GetLength ());
							if (pos != -1)
							{
								strTitle = strText.Right (strTitle.GetLength () + 3);
								strDocument = strText.Left (strText.GetLength () - strTitle.GetLength ());
							}
						}
						else
						{
							int pos = strText.Find (strTitle);
							if (pos != -1)
							{
								strTitle = strText.Left (strTitle.GetLength () + 3);
								strDocument = strText.Right (strText.GetLength () - strTitle.GetLength ());
							}	
						}
					}
				}
				else
				{
					strDocument = strText;
				}
			}
		}

		if (bMaximized)
		{
			rectCaption.InflateRect (szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);
		}

		DrawNcCaption (&dc, rectCaption, dwStyle, dwStyleEx, 
						strTitle, strDocument, hIcon, bPrefix, bActive, FALSE,
						lstSysButtons);

		if (bDestroyIcon)
		{
			::DestroyIcon (hIcon);
		}

		if (bMaximized)
		{
			return TRUE;
		}

		rtWindow.top = rectCaption.bottom;

		dc.ExcludeClipRect (rectCaption);

		int indexBorder = 0;
		int indexNavi   = IsLargeNaviControl () ? 1 : 0;

		CRect rtPart (rtWindow);
		rtPart.right  = rtPart.left + szSysBorder.cx;
		rtPart.bottom = rtPart.top + 
			m_ctrlMainBorderExplorerL.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderExplorerL.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - 
			(m_ctrlMainBorderNaviL[indexNavi].GetParams ().m_rectImage.Height () + 
			 m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ());
		m_ctrlMainBorderL.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviL[indexNavi].Draw (&dc, rtPart, indexBorder);

		rtPart = rtWindow;
		rtPart.left   = rtPart.right - szSysBorder.cx;
		rtPart.bottom = rtPart.top + 
			m_ctrlMainBorderExplorerR.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderExplorerR.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - 
			(m_ctrlMainBorderNaviR[indexNavi].GetParams ().m_rectImage.Height () + 
			 m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ());
		m_ctrlMainBorderR.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviR[indexNavi].Draw (&dc, rtPart, indexBorder);

		rtPart = rtWindow;
		rtPart.top = rtPart.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviB[indexNavi].Draw (&dc, rtPart, indexBorder);

		if (indexNavi == 1)
		{
			m_ctrlMainBorderNaviBCtrl.DrawEx (&dc, rtPart, 0, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
		}

		dc.SelectClipRgn (NULL);

		return TRUE;
	}

	return CBCGPWinXPVisualManager::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
}