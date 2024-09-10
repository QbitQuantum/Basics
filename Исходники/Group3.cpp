void CGroup1::LinesTop14(CDC* pDC, CSize& ScreenSize,
						 int CameraX, int CameraY, // position on camera
						 long x, long y, // position on screen
						 long lFactorX, long lFactorY, long CameraFactor,
						 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R, G, B);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	if (x<ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (0,0);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx,0);
		pDC->LineTo(x,y);
	}
	else if (x<ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (0,ScreenSize.cy);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx,ScreenSize.cy);
		pDC->LineTo(x,y);
	}
	
	b.DeleteObject();	
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}