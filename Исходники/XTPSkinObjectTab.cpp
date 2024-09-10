HBRUSH CXTPSkinObjectFrame::GetClientBrush(HDC hDC, HWND hWnd, UINT nCtlColor)
{
	if (m_dwDialogTexture != ETDT_ENABLETAB)
	{
		GrayCtlColor(hDC, hWnd, nCtlColor, GetMetrics()->m_brushDialog, GetColor(COLOR_BTNTEXT));
		return GetMetrics()->m_brushDialog;
	}

	if (GetMetrics()->m_brushTabControl == NULL)
	{
		CWindowDC dcWindow(this);

		CXTPSkinManagerClass* pClass = GetSkinManager()->GetSkinClass(this, _T("TAB"));

		CString strImageFile = pClass->GetThemeString(TABP_BODY, 0, TMT_STOCKIMAGEFILE);
		if (strImageFile.IsEmpty())
		{
			return GetMetrics()->m_brushDialog;
		}

		CXTPSkinImage* pImage = pClass->GetImages()->LoadFile(m_pManager->GetResourceFile(), strImageFile);

		if (!pImage)
		{
			return GetMetrics()->m_brushDialog;
		}

		CRect rc(0, 0, pImage->GetWidth(), pImage->GetHeight());

		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&dcWindow, rc.Width(), rc.Height());

		CXTPCompatibleDC dc(&dcWindow, bmp);

		pImage->DrawImage(&dc, rc, rc, CRect(0, 0, 0, 0), COLORREF_NULL, ST_TRUESIZE, FALSE);

		GetMetrics()->m_brushTabControl = ::CreatePatternBrush(bmp);
	}


	if (hWnd != m_hWnd)
	{
		CXTPWindowRect rcPaint(hWnd);
		CXTPWindowRect rcBrush(m_hWnd);
		::SetBrushOrgEx(hDC, rcBrush.left - rcPaint.left, rcBrush.top - rcPaint.top, NULL);

		::SetBkMode(hDC, TRANSPARENT);
		::SetTextColor(hDC, GetColor(COLOR_BTNTEXT));
	}

	return GetMetrics()->m_brushTabControl;

}