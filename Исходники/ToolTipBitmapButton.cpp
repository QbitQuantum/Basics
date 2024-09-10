void CToolTipBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item

	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC * pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);



	CBitmap * pOldBitmap;
	pOldBitmap = pMemDC->SelectObject(&m_Bitmap);
	
	CPoint point(0,0);
	
	if (IsWindowEnabled()) {	
		if ( (lpDrawItemStruct->itemState & ODS_SELECTED) || m_pressed)
		{
			//pDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, m_ButtonSize.cx, 0, SRCCOPY);
			pDC->TransparentBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, 
				m_ButtonSize.cx, 0,m_ButtonSize.cx, m_ButtonSize.cy,RGB(255,255,0));
		} else {
			if (m_bHover) // focused ?
			{
				//pDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, m_ButtonSize.cx*2, 0, SRCCOPY);
				pDC->TransparentBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, 
					m_ButtonSize.cx*2, 0,m_ButtonSize.cx, m_ButtonSize.cy,RGB(255,255,0));
			} else {
				//pDC->BitBlt(0,0,m_ButtonSize.cx,m_ButtonSize.cy,pMemDC,0,0,SRCCOPY);
				pDC->TransparentBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, 
					0, 0,m_ButtonSize.cx, m_ButtonSize.cy,RGB(255,255,0));
			}
		}
	} else {
		//pDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, m_ButtonSize.cx*3, 0, SRCCOPY);
		pDC->TransparentBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, 
			m_ButtonSize.cx*3, 0,m_ButtonSize.cx, m_ButtonSize.cy,RGB(255,255,0));
	}
	// clean up
	pMemDC -> SelectObject(pOldBitmap);
	delete pMemDC;
}