LRESULT FProgress::OnPaint(UINT, WPARAM, LPARAM, BOOL&)
{
	CPaintDC PaintDC(m_hWnd); 
	FRect rcPaint, rcClient; 
	GetClientRect(&rcClient); 
	rcPaint = rcClient; 
	CDC dcCompat;	 dcCompat.CreateCompatibleDC(PaintDC);
	CBitmap bmCompat;bmCompat.CreateCompatibleBitmap(PaintDC, rcPaint.Width(), rcPaint.Height()); 
	dcCompat.SelectBitmap(bmCompat);

	dcCompat.FillRect(&rcPaint, m_BgBrush);

	dword dwStyle = GetWindowLong(GWL_STYLE); 
	if (dwStyle & PROG_DRAW_EDGE)
		dcCompat.DrawEdge(&rcPaint, EDGE_ETCHED, BF_RECT | BF_ADJUST);

	DrawMeter(dcCompat, rcPaint); 
	PaintDC.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), dcCompat, 0, 0, SRCCOPY); 
	return 0; 
}