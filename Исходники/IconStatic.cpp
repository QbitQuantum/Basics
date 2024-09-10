void CIconStatic::SetIcon(LPCTSTR pszIconID)
{
	m_strIconID = pszIconID;

	// If this function is called for the first time and we did not yet call 'SetWindowText', we take
	// the window label which is already specified for the window (the label which comes from the resource)
	CString strText;
	CStatic::GetWindowText(strText);
	CStatic::SetWindowText(_T(""));
	if (!strText.IsEmpty() && m_strText.IsEmpty())
		m_strText = strText;

	CRect rRect;
	GetClientRect(rRect);

	CDC *pDC = GetDC();
	CDC MemDC;
	CBitmap *pOldBMP;
	
	VERIFY( MemDC.CreateCompatibleDC(pDC) );

	CFont *pOldFont = MemDC.SelectObject(GetFont());

	CRect rCaption(0,0,0,0);
	MemDC.DrawText(m_strText, rCaption, DT_CALCRECT);
	ASSERT( rCaption.Width() >= 0 );
	ASSERT( rCaption.Height() >= 0 );
	if (rCaption.Height() < 16)
		rCaption.bottom = rCaption.top + 16;
	rCaption.right += 25;
	if (rRect.Width() >= 16 && rCaption.Width() > rRect.Width() - 16)
		rCaption.right = rCaption.left + rRect.Width() - 16;

	if (m_MemBMP.m_hObject)
		VERIFY( m_MemBMP.DeleteObject() );
	VERIFY( m_MemBMP.CreateCompatibleBitmap(pDC, rCaption.Width(), rCaption.Height()) );
	pOldBMP = MemDC.SelectObject(&m_MemBMP);

	// Get the background color from the parent window. This way the controls which are
	// embedded in a dialog window can get painted with the same background color as
	// the dialog window.
	HBRUSH hbr = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORSTATIC, (WPARAM)MemDC.m_hDC, (LPARAM)m_hWnd);
	FillRect(MemDC, &rCaption, hbr);

	if (!m_strIconID.IsEmpty())
		VERIFY( DrawState( MemDC.m_hDC, NULL, NULL, (LPARAM)(HICON)CTempIconLoader(m_strIconID, 16, 16), NULL, 3, 0, 16, 16, DST_ICON | DSS_NORMAL) );

	// clear all alpha channel data
	BITMAP bmMem;
	if (m_MemBMP.GetObject(sizeof bmMem, &bmMem) >= sizeof bmMem && bmMem.bmBitsPixel == 32)
	{
		DWORD dwSize = m_MemBMP.GetBitmapBits(0, NULL);
		if (dwSize)
		{
			LPBYTE pPixels = (LPBYTE)malloc(dwSize);
			if (pPixels)
			{
				if (m_MemBMP.GetBitmapBits(dwSize, pPixels) == dwSize)
				{
					LPBYTE pLine = pPixels;
					int iLines = bmMem.bmHeight;
					while (iLines-- > 0)
					{
						LPDWORD pdwPixel = (LPDWORD)pLine;
						for (int x = 0; x < bmMem.bmWidth; x++)
							*pdwPixel++ &= 0x00FFFFFF;
						pLine += bmMem.bmWidthBytes;
					}
					m_MemBMP.SetBitmapBits(dwSize, pPixels);
				}
				free(pPixels);
			}
		}
	}

	rCaption.left += 22;
	
	if(IsThemeActive() && IsAppThemed())
    {
		HTHEME hTheme = OpenThemeData(NULL, L"BUTTON"); 
		DrawThemeText(hTheme, MemDC.m_hDC, BP_GROUPBOX, GBS_NORMAL, m_strText, m_strText.GetLength(), 
			DT_WORDBREAK | DT_CENTER | DT_WORD_ELLIPSIS, NULL, &rCaption); 
		CloseThemeData(hTheme);
	}
	else
	{
		MemDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		MemDC.DrawText(m_strText, rCaption, DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS);
	}

	ReleaseDC(pDC);

	MemDC.SelectObject(pOldBMP);
	MemDC.SelectObject(pOldFont);
	
	if (m_wndPicture.m_hWnd == NULL)
		m_wndPicture.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0,0,0,0), this);
	m_wndPicture.SetWindowPos(NULL, rRect.left+8, rRect.top, rCaption.Width()+22, rCaption.Height(), SWP_SHOWWINDOW);
	m_wndPicture.SetBitmap(m_MemBMP);

	CRect r;
	GetWindowRect(r);
	r.bottom = r.top + 20;
	GetParent()->ScreenToClient(&r);
	GetParent()->RedrawWindow(r);
}