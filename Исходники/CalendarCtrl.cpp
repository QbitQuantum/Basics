void CCalendarCtrl::OnPaint() 
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap *pOldBitmap = MemDC.SelectObject(&MemBitmap);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(RGB(252,255,255));
	MemDC.FillRect(&rc ,&brBkGnd);
	MemDC.SetBkMode(TRANSPARENT);
	
	// Draw calendar elements
	DrawHeader(&MemDC);			
	DrawCells(&MemDC);	
	DrawGrid(&MemDC);

	// Render
	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}