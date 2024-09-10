void COsilloGraph::DrawPos()
{
	CDC *pDC = &m_MemDC;
	if(m_bIsPaint)
	{
		pDC->BitBlt(0, 0, m_Width - m_MoveUnit, m_Height, pDC, m_MoveUnit, 0, SRCCOPY);
		pDC->FillRect(&m_GraphRect, &m_GraphBk);

		static int x = m_Width - 1;
		static int y = m_Height - 1;
		static int cury;

		if(m_ShowPos > 0 && m_ShowPos < m_Unit)
			m_ShowPos = m_Unit;
		cury = m_Height - (m_ShowPos / m_Unit) - 1;
		if(cury < 0) cury = 0;

		pDC->MoveTo(x - m_MoveUnit, y);
		pDC->LineTo(x , cury);

		m_ShowPos = 0;
		y = cury;
		
		m_bIsPaint = FALSE;
	}

}