void CSettingsSpawn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC * pDC = m_csBGColor.GetDC();
	CRgn rgn;
	CRect rect;
	m_csBGColor.GetWindowRect( &rect );
	CBrush * pNewBrush = new (CBrush);
	pNewBrush->CreateSolidBrush( (COLORREF) m_dwSpawnBGColor );
	CBrush * pOldBrush = pDC->SelectObject(pNewBrush);
	CRect cr;
	m_csBGColor.GetClientRect(&cr);
	rgn.CreateRectRgnIndirect(cr);
	pDC->SelectClipRgn(&rgn);
	pDC->FillRect(cr, pNewBrush);
	pDC->SelectObject(pOldBrush);
	delete (pNewBrush);
	rgn.DeleteObject();
	m_csBGColor.ReleaseDC( pDC );

}