VOID CEditPrevWnd::Draw(CDC* pDC)
{

	LPBYTE       lpData = NULL;
	LPBITMAPINFO lpInfo = NULL;

		if(((CPhotoEditDlg*)m_pParentWnd)->GetCurObject())
			
			(((CPhotoEditDlg*)m_pParentWnd)->GetCurObject())->GetObjectData(lpData, lpInfo);
	 		
		else
			return;

		if((!lpData) || (!lpInfo))
			return;
	
	

	LPBITMAPINFOHEADER lpInfoHeader = &(lpInfo->bmiHeader);

	LONG lWidth = 0 ,	lHeight = 0;		// Width and height to show
	LONG lScalW = 0 ,   lScalH  = 0;		// Width and height of scaled image
	lScalW  = (LONG)(lpInfoHeader->biWidth  * m_dScaling);
	lScalH  = (LONG)(lpInfoHeader->biHeight * m_dScaling);
	lWidth  = (PREVWNDWIDTH < lScalW) ? PREVWNDWIDTH : lScalW;
	lHeight = (PREVWNDHEIGH < lScalH) ? PREVWNDHEIGH : lScalH;

	CPoint ptImgShowLt(0,0);				// Left top position of shown image part
	ptImgShowLt.x = (LONG)(((lScalW - lWidth )/2 - m_szMoved.cx) / m_dScaling);
	ptImgShowLt.y = (LONG)(((lScalH - lHeight)/2 + m_szMoved.cy) / m_dScaling);
	
	if(ptImgShowLt.x < 0)		ptImgShowLt.x = 0;
	else if(ptImgShowLt.x > lpInfoHeader->biWidth - (LONG)(lWidth / m_dScaling))
		ptImgShowLt.x = lpInfoHeader->biWidth - (LONG)(lWidth / m_dScaling);
	if(ptImgShowLt.y < 0)		ptImgShowLt.y = 0;
	else if(ptImgShowLt.y > lpInfoHeader->biHeight - (LONG)(lHeight / m_dScaling))
		ptImgShowLt.y = lpInfoHeader->biHeight - (LONG)(lHeight / m_dScaling);

	// m_ptShownLt is for move fore image
	m_ptShownLt.x = ptImgShowLt.x - (LONG)((PREVWNDWIDTH-lWidth)/(2*m_dScaling));
	m_ptShownLt.y = lpInfoHeader->biHeight - ptImgShowLt.y - (LONG)((PREVWNDHEIGH + lHeight)/(2*m_dScaling));

	//Draw image
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, lWidth, lHeight);
	CBitmap* pBmp = memDC.SelectObject(&bmp);
	memDC.SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(memDC.m_hDC, 0, 0, lWidth, lHeight, 
			ptImgShowLt.x, ptImgShowLt.y, (LONG)(lWidth / m_dScaling),  (LONG)(lHeight / m_dScaling),
			lpData, (LPBITMAPINFO)lpInfoHeader, DIB_RGB_COLORS, SRCCOPY);
	
	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->BitBlt((PREVWNDWIDTH-lWidth)/2, (PREVWNDHEIGH-lHeight)/2, lWidth, lHeight,&memDC,0,0,SRCCOPY);
	
	m_rtImageRect = CRect((PREVWNDWIDTH-lWidth)/2, (PREVWNDHEIGH-lHeight)/2, 
		              (PREVWNDWIDTH-lWidth)/2 + lWidth, (PREVWNDHEIGH-lHeight)/2 + lHeight);
	
	memDC.SelectObject(pBmp);
	memDC.DeleteDC();
	bmp.DeleteObject();

	//Draw fore image rect
	if(m_bForeSelected)
	{
		CGdiObject * Oldbr;
		CPen pen, *Oldpen;
		pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
		Oldpen = pDC->SelectObject(&pen);
		Oldbr  = pDC->SelectStockObject(NULL_BRUSH);

		CRect rc1 = m_rcFore;
		rc1.OffsetRect(-m_ptShownLt.x, -m_ptShownLt.y);
		rc1.left   = (LONG)(rc1.left*m_dScaling);
		rc1.top    = (LONG)(rc1.top*m_dScaling);
		rc1.right  = (LONG)(rc1.right*m_dScaling);
		rc1.bottom = (LONG)(rc1.bottom*m_dScaling);

		pDC->Rectangle(rc1);
		pDC->SelectObject(Oldpen);
		pDC->SelectObject(Oldbr);
	}
	if(m_bCropPress)// && m_bAfterCrop)
		if(m_bRectExist)
			DrawRect(pDC,m_rtPreRect);/////keep rect when Crop	
		
	
}