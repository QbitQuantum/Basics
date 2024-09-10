BOOL CStroke::DrawStrokeIn( CDC* pDC, int nRestricWidth, int nRestricHeight )
{
	CPen penStroke;
	if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, m_rgbPenColor))
		return FALSE;

	CPen* pOldPen = pDC->SelectObject( &penStroke );

	CPoint prev = m_pointArray[0];

	pDC->MoveTo( m_pointArray[0] );
	for( int i=1; i < m_pointArray.GetSize(); i++ )
	{
		if (m_pointArray[i].x>nRestricWidth || m_pointArray[i].y > nRestricHeight)
		{
			prev = m_pointArray[i];
			continue;
		}

		if (prev.x>nRestricWidth || prev.y > nRestricHeight)
		{
			pDC->MoveTo(m_pointArray[i]);
		}
		pDC->LineTo( m_pointArray[i] );
		prev = m_pointArray[i];
	}
	pDC->SelectObject( pOldPen );
	return TRUE;
}