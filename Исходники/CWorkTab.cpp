BOOL CWorkTab::OnPaint(HDC hDC)
{
	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorXP());
	
	GetClientRect(m_rectCliente);
	m_rectTab = m_rectCliente;
	m_rectDraw = m_rectCliente;
	
	if (m_alnTab == ALN_BOTTOM)
		m_rectDraw.bottom = m_rectCliente.bottom- (theApp->m_WinMain->m_sizeImagDocks.cy + SPACE_TAB + 2);	
	
	CRect rc = m_rectDraw;
	rc.top += 1;
	rc.bottom = rc.top + 1;
	dc.Draw3dRect(rc, CDrawLayer::GetRGBColorFace(), CDrawLayer::GetRGBColorFace());
	
	if (m_alnTab == ALN_BOTTOM)
	{
		m_rectCliente.bottom = m_rectCliente.bottom- (DEFAULT_FLAT);
		m_rectTab.top = m_rectCliente.bottom + 2;
	}
	cbr.DeleteObject();
	Drawtabs(&dc);
	dc.DeleteDC();
	return TRUE;
}