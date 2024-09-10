static void 
MakeLightBitmap(CBitmap *bitmap, CPaintDC *dc, CRect *rect, COLORREF color)
{
	CBrush brush(dc->GetNearestColor(GetSysColor(COLOR_3DFACE)));
	CBrush colorBrush(dc->GetNearestColor(color));
	CPen pen(PS_SOLID, 1, dc->GetNearestColor(GetSysColor(COLOR_3DFACE)));
	CDC lightDC;
	CRect workRect;

	//Make the bitmap we'll work on:
	lightDC.CreateCompatibleDC(dc);
	bitmap->CreateCompatibleBitmap(dc,
							rect->Width(), 
							rect->Height());
	lightDC.SelectObject(bitmap);

	//The first step is to blank out the background
	lightDC.SelectObject(&brush);
	lightDC.SelectObject(&pen);

	lightDC.Rectangle(0, 0, rect->Width(), rect->Height());

	//Next, get a black pen and make a circle...
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 1, dc->GetNearestColor(RGB(0, 0, 0)));
	lightDC.SelectObject(&pen);
	lightDC.Ellipse(rect);
	workRect = *rect;
	workRect.DeflateRect(LIGHT_WIDTH / 4, LIGHT_HEIGHT / 4);
	lightDC.Ellipse(workRect);

	//Last, fill it with the appropriate color:
	//Next, get a black pen and make a circle...
	lightDC.SelectObject(colorBrush);
	lightDC.FloodFill(LIGHT_WIDTH / 2, 
					  LIGHT_HEIGHT / 2, 
					  dc->GetNearestColor(RGB(0, 0, 0)));
}