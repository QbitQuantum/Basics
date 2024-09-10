void CWelcomeWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// get our own DC instead, with no restrictions
	CDC* pDC = GetDC();

	// realize the palette
	CPalette* pOldPalette = pDC->SelectPalette(m_bitmap.GetPalette(), FALSE);
	pDC->RealizePalette();

	// And draw the bitmap
	BITMAP bmInfo;
	if (m_bitmap.m_hObject == NULL)
		return;
	m_bitmap.GetObject(sizeof(BITMAP),&bmInfo);
	CDC newDC;
	newDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = newDC.SelectObject(&m_bitmap);
	pDC->BitBlt(0,0,bmInfo.bmWidth,bmInfo.bmHeight,&newDC,0,0,SRCCOPY);

	//
	(void)newDC.SelectObject(pOldBitmap);
	newDC.DeleteDC();
	pDC->SelectPalette(pOldPalette, FALSE);
	ReleaseDC(pDC);

	// draw the 'OK' button
	CRect winRect, rect;
	GetClientRect(&winRect);
	CButton* pBtn = (CButton*) GetDlgItem(IDOK);
	pBtn->GetWindowRect(&rect);
	ScreenToClient(&rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	rect.bottom = winRect.bottom - 24;
	rect.top = rect.bottom - nHeight;
	rect.left = (winRect.right - nWidth) / 2;
	rect.right = rect.left + nWidth;
	pBtn->MoveWindow(&rect);
	pBtn->ShowWindow(SW_SHOW);
}