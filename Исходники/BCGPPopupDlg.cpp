CSize CBCGPPopupDlg::GetOptimalTextSize (CString str)
{
	if (str.IsEmpty ())
	{
		return CSize (0, 0);
	}

	CRect rectScreen;

	CRect rectDlg;
	GetWindowRect (rectDlg);

	MONITORINFO mi;
	mi.cbSize = sizeof (MONITORINFO);
	if (GetMonitorInfo (MonitorFromPoint (rectDlg.TopLeft (), MONITOR_DEFAULTTONEAREST), &mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	CClientDC dc (this);

	CFont* pOldFont = dc.SelectObject (&globalData.fontRegular);
	ASSERT_VALID (pOldFont);

	int nStepY = globalData.GetTextHeight ();
	int nStepX = nStepY * 3;

	CRect rectText (0, 0, nStepX, nStepY);

	for (;;)
	{
		CRect rectTextSaved = rectText;

		int nHeight = dc.DrawText (str, rectText, DT_CALCRECT | DT_WORDBREAK | DT_NOPREFIX);
		int nWidth = rectText.Width ();

		rectText = rectTextSaved;

		if (nHeight <= rectText.Height () ||
			rectText.Width () > rectScreen.Width () ||
			rectText.Height () > rectScreen.Height ())
		{
			rectText.bottom = rectText.top + nHeight + 5;
			rectText.right = rectText.left + nWidth + 5;
			break;
		}

		rectText.right += nStepX;
		rectText.bottom += nStepY;
	}

	dc.SelectObject (pOldFont);
	return rectText.Size ();
}