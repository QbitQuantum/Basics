//-----  OnSizeParent()  ------------------------------------------------------
void BCTabBarCtrl::OnNcPaint() 
{
	CRect rectCLient, rectNC;
	GetWindowRect(rectNC);
	
	rectNC.OffsetRect(-rectNC.left, -rectNC.top);
	
	CWindowDC dc(this);
	CPen pen;
	
	DWORD dwSysGray = GetSysColor(COLOR_BTNFACE);
	
	dc.DrawEdge(rectNC, EDGE_ETCHED, BF_TOP);
	
	rectNC.DeflateRect(0, 2, 0, 0);
	
	CBrush brush(dwSysGray);
	dc.FrameRect(rectNC, &brush);
	
	for(int iIndx = 0; iIndx < 2; iIndx++)
	{
		rectNC.DeflateRect(1, 1, 1, 1);
		dc.FrameRect(rectNC, &brush);
	}
	
	rectNC.DeflateRect(0, 1, 0, 2);
	pen.DeleteObject();
	
	pen.CreatePen(PS_GEOMETRIC | PS_SOLID, 1, dwSysGray);
	dc.SelectObject(&pen);
	
	dc.MoveTo(rectNC.left, rectNC.top);
	dc.LineTo(rectNC.right, rectNC.top);
}