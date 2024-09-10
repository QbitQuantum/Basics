void CSonicSkin::SetRgn(RECT * pRect /* = NULL */, BOOL bDraw /* = TRUE */)
{
	if(m_bg.nColorKey < 0)
	{
		return;
	}

	static BOOL bEnter = FALSE;
	if(bEnter)
	{
		return;
	}
	bEnter = TRUE;

	CRect rtClient;
	
	if(pRect == NULL)
	{
		GetClientRect(m_hWnd, &rtClient);
	}
	else
	{
		rtClient = *pRect;
	}
	const int nCorner = 20;

	HRGN hOldRgn = m_bg.hMainRgn;
	m_bg.hMainRgn = CreateRectRgn(0, 0, rtClient.Width(),rtClient.Height());
	CRect rtSrc;
	// left top corner
	rtSrc.SetRect(0, 0, nCorner, nCorner);
	m_bg.hRgn[0] = m_bg.pImg->CreateRgn(m_bg.nColorKey, 0, 0, &rtSrc, TRUE);
	CombineRgn(m_bg.hMainRgn, m_bg.hMainRgn, m_bg.hRgn[0], RGN_XOR);

	// right top corner
	rtSrc.SetRect(m_bg.pImg->GetWidth() - nCorner, 0, m_bg.pImg->GetWidth(), nCorner);
	m_bg.hRgn[1] = m_bg.pImg->CreateRgn(m_bg.nColorKey, rtClient.Width() - nCorner, 0, &rtSrc, TRUE);
	CombineRgn(m_bg.hMainRgn, m_bg.hMainRgn, m_bg.hRgn[1], RGN_XOR);

	// left bottom corner
	rtSrc.SetRect(0, m_bg.pImg->GetHeight() - nCorner, nCorner, m_bg.pImg->GetHeight());
	m_bg.hRgn[2] = m_bg.pImg->CreateRgn(m_bg.nColorKey, 0, rtClient.Height() - nCorner, &rtSrc, TRUE);
	CombineRgn(m_bg.hMainRgn, m_bg.hMainRgn, m_bg.hRgn[2], RGN_XOR);

	// right bottom corner
	rtSrc.SetRect(m_bg.pImg->GetWidth() - nCorner, m_bg.pImg->GetHeight() - nCorner, m_bg.pImg->GetWidth(), m_bg.pImg->GetHeight());
	m_bg.hRgn[3] = m_bg.pImg->CreateRgn(m_bg.nColorKey, rtClient.Width() - nCorner, rtClient.Height() - nCorner, &rtSrc, TRUE);
	CombineRgn(m_bg.hMainRgn, m_bg.hMainRgn, m_bg.hRgn[3], RGN_XOR);

	SetWindowRgn(m_hWnd, m_bg.hMainRgn, bDraw);

	for(int i = 0; i < 4; i++)
	{
		if(m_bg.hRgn[i])
		{
			DeleteObject(m_bg.hRgn[i]);
			m_bg.hRgn[i] = NULL;
		}
	}
	if(hOldRgn)
	{
		DeleteObject(hOldRgn);
	}

	bEnter = FALSE;
}