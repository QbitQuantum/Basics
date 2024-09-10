void CSignatureWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Check that the LButton is down
	if (nFlags & MK_LBUTTON)
	{
		CDC* pDC = GetDC();
		CPen* p = pDC->SelectObject(&m_Pen);

		m_line[1] = point;
		if (m_line[0] != m_line[1])
		{
			pDC->Polyline(m_line, 2);
			m_SaveLine[m_nPoint] = point;

			m_nPoint++;
			if (m_nPoint >= 1000)
			{
				m_nPoint = 0;
			}
		}
		m_line[0] = m_line[1];
		pDC->SelectObject(p);
		ReleaseDC(pDC);
	}
	
	CWnd::OnMouseMove(nFlags, point);
}