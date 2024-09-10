void CHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect r;
	GetClientRect(&r);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SaveDC();

//	COLORREF c = RGB(0,0,0);
//	if( lpDrawItemStruct->itemState & ODS_SELECTED )
//	{
//		c = RGB(0,255,0);
//	}
//	else
//	{
//		if( m_bHover )
//		{
//			c = RGB(255,0,0);
//		}
//	}
//	CPen pen;
//	pen.CreatePen(PS_SOLID,0,c);
//	pDC->SelectObject(&pen);
//	pDC->Rectangle(r);

	CRect sr(0,0,13,13);

	if( m_bHover )
	{
		sr.OffsetRect(13*2,0);
	}

	if( m_bOpenState )
	{
		sr.OffsetRect(13,0);
	}

	SetRawPixels( pDC , MinimizeBitmaps , &CRect(0,0,13,13) , &sr );


	pDC->RestoreDC(-1);
}