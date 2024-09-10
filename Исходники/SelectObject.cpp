void CSelectObject::DrawTracker(HDC hDC, TrackerState state, BOOL bDrawSelectTool)
{
	BOOL bRet = FALSE;
	CDCHandle dc(hDC);

	LOGPEN logPen;
	logPen.lopnStyle = PS_DOT;
	logPen.lopnColor = RGB(0, 0, 0);
	logPen.lopnWidth.x = 1;
	logPen.lopnWidth.y = 1;
	CPen pen;
	API_VERIFY(NULL != pen.CreatePenIndirect(&logPen));

	CBrushHandle pOldBrush;
	CPenHandle pOldPen;

	pOldBrush = dc.SelectStockBrush(NULL_BRUSH);


	if (m_bPen)
	{
		pOldPen = dc.SelectPen(pen);
	}
	else
	{
		pOldPen = dc.SelectStockPen(NULL_PEN);
	}

	//ATLTRACE(_T("DrawTracker top %d btn %d left %d right %d \n"), m_position.top, m_position.bottom, m_position.left, m_position.right);
	//draw on device units
	CRect rect = m_position;
	//ATLTRACE(_T("DrawTracker DocToClient top %d btn %d left %d right %d \n"), m_position.top, m_position.bottom, m_position.left, m_position.right);
	m_pDrawCanvas->DocToClient(&rect);
	//ATLTRACE(_T("DrawTracker DocToClient top %d btn %d left %d right %d \n"), rect.top, rect.bottom, rect.left, rect.right);

	HBRUSH hOldBrush = dc.SelectStockBrush(NULL_BRUSH);
	dc.Rectangle(rect);
	dc.SelectBrush(hOldBrush);
	dc.SelectPen(pOldPen);
	CDrawObject::DrawTracker(hDC, state, bDrawSelectTool);
}	