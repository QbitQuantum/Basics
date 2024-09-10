LRESULT CRegionSelect::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	BeginPaint(&ps);

	HDC dc = ps.hdc;

	int w = ps.rcPaint.right-ps.rcPaint.left;
	int h = ps.rcPaint.bottom-ps.rcPaint.top;

	if(m_bPictureChanged)
	{
		if(Down) return 0;
		RECT rc;
		GetClientRect(&rc);
		CRgn newRegion;
		newRegion.CreateRectRgn(0,0,rc.right,rc.bottom);
		SelectClipRgn(doubleDC, newRegion);
		BitBlt(doubleDC,ps.rcPaint.left,ps.rcPaint.top,w,h,memDC2,  ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
		newRegion.CombineRgn(m_SelectionRegion,RGN_DIFF);
		CBrush br;
		SelectClipRgn(doubleDC, newRegion);
		br.CreateSolidBrush(RGB(200,200,0));
		BLENDFUNCTION bf ;
		//настройки прозрачности
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 1;
		bf.SourceConstantAlpha = 40; // прозрачность 50% (0 - 255)
		bf.AlphaFormat = 0;///*0 */ /*AC_SRC_ALPHA*/0;
		
		if(RectCount) 
			if(AlphaBlend(doubleDC, ps.rcPaint.left, ps.rcPaint.top, w,h, alphaDC, ps.rcPaint.left, ps.rcPaint.top, w,h, bf)==FALSE)
			{
				//MessageBox(_T("Alphablend failed"));
			};
		newRegion.DeleteObject();
		newRegion.CreateRectRgn(0,0,rc.right,rc.bottom);
		SelectClipRgn(doubleDC, newRegion);
		RECT SelWndRect;
		if(hSelWnd)
		{
			CRgn WindowRgn = GetWindowVisibleRegion(hSelWnd);
			WindowRgn.OffsetRgn(topLeft);
			WindowRgn.GetRgnBox(&SelWndRect);
			CRect DrawingRect = SelWndRect;
			DrawingRect.DeflateRect(2, 2);
			SelectObject(doubleDC, pen);
			SetROP2(doubleDC, R2_NOTXORPEN);
			SelectClipRgn(doubleDC, 0);
			Rectangle(doubleDC, DrawingRect.left,DrawingRect.top, DrawingRect.right, DrawingRect.bottom);
		}
		m_bPictureChanged = false;
	}
	BitBlt(dc,ps.rcPaint.left,
		ps.rcPaint.top,w,h,doubleDC,ps.rcPaint.left,
		ps.rcPaint.top,SRCCOPY);

	EndPaint(&ps);
	m_bPainted = true;
	return 0;
}