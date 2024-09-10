BOOL CToolTipEx::Show(CPoint point)
{
	m_reducedWindowSize = false;
    if(m_pBitmap)
    {
        m_RichEdit.ShowWindow(SW_HIDE);
    }
    else
    {
        m_RichEdit.ShowWindow(SW_SHOW);
    }

	CRect rect;

	if(CGetSetOptions::GetSizeDescWindowToContent() == FALSE)
	{
		rect.left = point.x;
		rect.top = point.y;
		CSize size;
		CGetSetOptions::GetDescWndSize(size);
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;

		EnsureWindowVisible(&rect);
	}
	else
	{
		rect = GetBoundsRect();

		//account for the scroll bars
		rect.right += 20;
		rect.bottom += 20;

		if (m_pBitmap)
		{
			int nWidth = CBitmapHelper::GetCBitmapWidth(*m_pBitmap);
			int nHeight = CBitmapHelper::GetCBitmapHeight(*m_pBitmap);

			rect.right = rect.left + nWidth;
			rect.bottom = rect.top + nHeight;
		}
		else if(m_csRTF != "")
		{
			//if showing rtf then increase the size because
			//rtf will probably draw bigger
			long lNewWidth = (long)rect.Width() + (long)(rect.Width() *1.5);
			rect.right = rect.left + lNewWidth;

			long lNewHeight = (long)rect.Height() + (long)(rect.Height() *1.5);
			rect.bottom = rect.top + lNewHeight;
		}

		rect.right += CAPTION_BORDER * 2;
		rect.bottom += CAPTION_BORDER * 2;

		

		CRect rcScreen;

		ClientToScreen(rect);

		CRect cr(point, point);

		int nMonitor = GetMonitorFromRect(&cr);
		GetMonitorRect(nMonitor, &rcScreen);

		//ensure that we don't go outside the screen
		if(point.x < 0)
		{
			point.x = 5;
			m_reducedWindowSize = true;
		}
		if(point.y < 0)
		{
			point.y = 5;
			m_reducedWindowSize = true;
		}

		rcScreen.DeflateRect(0, 0, 5, 5);

		long lWidth = rect.Width();
		long lHeight = rect.Height();

		rect.left = point.x;
		rect.top = point.y;
		rect.right = rect.left + lWidth;
		rect.bottom = rect.top + lHeight;
		
		if (rect.right > rcScreen.right)
		{
			rect.right = rcScreen.right;
			m_reducedWindowSize = true;
		}
		if (rect.bottom > rcScreen.bottom)
		{
			rect.bottom = rcScreen.bottom;
			m_reducedWindowSize = true;
		}
	}

    SetWindowPos(&CWnd::wndTopMost, rect.left, rect.top, rect.Width(), rect.Height
                 (), SWP_SHOWWINDOW | SWP_NOCOPYBITS | SWP_NOACTIVATE |
                 SWP_NOZORDER);

    return TRUE;
}