void CWBButton::DrawBitmap(CDC * pDC, int mode)
{
	if (m_State < FileLoaded) return;

	CRect rc;
	GetClientRect(rc);
	
	COLORREF crOldText = pDC->SetTextColor(RGB(0, 0, 0));
	CDC dcImage, dcTrans, dcOffScr;
		
	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);
	dcOffScr.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
	CBitmap* pOldBitmapImage;
	switch (mode)
	{
	case normal:
		pOldBitmapImage = dcImage.SelectObject(&NormalBitmap);
		break;
	case select:
		pOldBitmapImage = dcImage.SelectObject(&SelectBitmap);
		break;
	case focus:
		pOldBitmapImage = dcImage.SelectObject(&FocusBitmap);
		break;
	case disable:
		pOldBitmapImage = dcImage.SelectObject(&DisableBitmap);
		break;
	default:
		return;
	}

	// Create the mask bitmap
	CBitmap bitmapTrans, OffScr;
	CBitmap* pOldBitmapOffScr;
	int nWidth = rc.Width();
	int nHeight = rc.Height();

	OffScr.CreateBitmap(nWidth, nHeight, (BYTE)pDC->GetDeviceCaps(PLANES), (BYTE)pDC->GetDeviceCaps(BITSPIXEL), NULL);
	pOldBitmapOffScr = dcOffScr.SelectObject(&OffScr);

	// Select the mask bitmap into the appropriate dc
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	DrawThemeParentBackground(GetSafeHwnd(), dcOffScr.GetSafeHdc(), rc);

	// Build mask based on transparent colour
	COLORREF oldColor = dcImage.SetBkColor(m_TransparentColor);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);	// create monochrome bitmap

	dcOffScr.SetBkColor(oldColor);
	dcOffScr.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	dcOffScr.BitBlt(0, 0, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
	dcOffScr.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);

	pDC->BitBlt(0, 0, nWidth, nHeight, &dcOffScr, 0, 0, SRCCOPY);

	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	dcOffScr.SelectObject(pOldBitmapOffScr);
	
	//pDC->SetTextColor(crOldText);
}