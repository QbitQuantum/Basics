void CCharSymbolSelectListBox::SetNewSelectId(long lNewSelectId)
{
	long preId = m_lNewSelectId;
	m_lNewSelectId = lNewSelectId;
	CRect RectOld,RectNew;
	DIS_RECT rectOld, rectNew;
	
	if(m_lNewSelectId != m_lOldSelectId)
	{
		UpdateWindow();

		//old
		GetItemRect((m_lOldSelectId - 1) / NUMSYMBOLPERROW, &RectOld);										
			
		RectOld.left = RectOld.left + (m_lOldSelectId - 1) % NUMSYMBOLPERROW * m_lItemHeight;
		RectOld.right = RectOld.left + m_lItemHeight;

		rectOld.left = RectOld.left;
		rectOld.right = RectOld.right;
		rectOld.top = RectOld.top;
		rectOld.bottom = RectOld.bottom;
		
		//new
		GetItemRect((m_lNewSelectId - 1) / NUMSYMBOLPERROW, &RectNew);

		RectNew.left = RectNew.left + (m_lNewSelectId - 1) % NUMSYMBOLPERROW * m_lItemHeight;
		RectNew.right = RectNew.left + m_lItemHeight;

		rectNew.left = RectNew.left;
		rectNew.right = RectNew.right;
		rectNew.top = RectNew.top;
		rectNew.bottom = RectNew.bottom;

		//draw
		CDC * pDC = GetDC();
		COLORREF bgCr = pDC->GetBkColor();
		Display::IDisplayPtr pDisplay ( new Display::IDisplay);
		pDisplay->SetDC( (long)pDC->GetSafeHdc() , m_rect.Width() , m_rect.Height() );
	
		CPen* pOldPen;
		//绘制旧
		CPen nPen(PS_SOLID,2,RGB(0,0,0)) ;
		pOldPen = pDC->SelectObject(&nPen);	
		pDC->Rectangle(&RectOld); 
		pDC->SelectObject(pOldPen);

		m_pCharDraw->SetCharMap(m_lOldSelectId);	
		pDisplay->DrawLegend( m_pCharDraw.get() , &rectOld , 0 );

		//绘制新
		CPen nNewPen(PS_SOLID,2,RGB(255,0,0));
		pOldPen = pDC->SelectObject(&nNewPen);	
		pDC->Rectangle(&RectNew); 
		pDC->SelectObject(pOldPen);

		m_pCharDraw->SetCharMap(m_lNewSelectId);		
		pDisplay->DrawLegend( m_pCharDraw.get() , &rectNew , 0 );
		
		ReleaseDC(pDC);
		UpdateWindow();

		m_lOldSelectId = preId;
	}
	
}