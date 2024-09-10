void CSimpleSplitter::InvertTracker()
{
	CDC* pDC = GetDC();
	CBrush* pBrush = CDC::GetHalftoneBrush();
	HBRUSH hOldBrush;
	
	hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
	if (m_nOrientation == SSP_HORZ)
		pDC->PatBlt(m_nTracker - m_nBarThickness, 0, m_nBarThickness, m_nTrackerLength, PATINVERT);
	else
		pDC->PatBlt(0, m_nTracker - m_nBarThickness, m_nTrackerLength, m_nBarThickness, PATINVERT);
	if (hOldBrush != NULL)
		SelectObject(pDC->m_hDC, hOldBrush);
	ReleaseDC(pDC);
}